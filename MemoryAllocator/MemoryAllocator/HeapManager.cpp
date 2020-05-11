
#include "HeapManager.h"
#include <Windows.h>
#include <iostream>

HeapManager::HeapManager() {
	m_pHeapMemory = nullptr;
	m_freeBlocks = nullptr;
	m_oustandingBlocks = nullptr;
	//test = 3;
}

//called in main
HeapManager::HeapManager(void * i_pHeapMemory, size_t i_HeapMemorySize)
{
	m_pHeapMemory = i_pHeapMemory;
	m_HeapMemorySize = i_HeapMemorySize;
	m_freeBlocks = (BlockDescriptor*)m_pHeapMemory;
	//m_freeBlocks = nullptr;
	m_freeBlocks->m_pBlockStartAddr = m_pHeapMemory;
	m_freeBlocks->m_sizeBlock = m_HeapMemorySize;
	m_oustandingBlocks = nullptr;
}

HeapManager::HeapManager(int i_test)
{
	test = i_test;
}

HeapManager::~HeapManager()
{
	m_pHeapMemory = nullptr;
	m_freeBlocks = nullptr;
	m_oustandingBlocks = nullptr;
	//and within freeBlock & outstandingBlocks
	m_freeBlocks->m_pBlockStartAddr = nullptr;
	m_oustandingBlocks = nullptr;
}


HeapManager * HeapManager::create(void * i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors)
{
	const size_t sizeHeapManager = sizeof(HeapManager);//
	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	size_t sizeHeapInPageMultiples = SysInfo.dwPageSize * ((sizeHeapManager + SysInfo.dwPageSize) / SysInfo.dwPageSize);
	void* pHeapMemory = VirtualAlloc(NULL, sizeHeapInPageMultiples, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	//HeapManager* o_pHeapManager = (HeapManager*)pHeapMemory;
	//o_pHeapManager->initialize(i_pHeapMemory, i_HeapMemorySize);
	HeapManager * pHeapManager = &HeapManager::HeapManager();
	pHeapManager->m_pHeapMemory = i_pHeapMemory;
	pHeapManager->m_HeapMemorySize = i_HeapMemorySize;
	pHeapManager->m_freeBlocks = (BlockDescriptor*)pHeapManager->m_pHeapMemory;
	//pHeapManager->m_freeBlocks->m_pBlockStartAddr = i_pHeapMemory;
	pHeapManager->m_freeBlocks->m_pBlockStartAddr = pHeapManager->m_pHeapMemory;
	return pHeapManager;

	//return o_pHeapManager;
}

/*
HeapManager * HeapManager::create(void * i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors)
{
	//return &HeapManager::HeapManager();//works
	return &HeapManager::HeapManager(i_pHeapMemory, i_HeapMemorySize);

}*/

void HeapManager::initialize(void * i_pHeapMemory, size_t i_HeapMemorySize)
{
	m_pHeapMemory = i_pHeapMemory;
	m_HeapMemorySize = i_HeapMemorySize;
	m_freeBlocks = nullptr;
	m_oustandingBlocks = nullptr;
}

size_t HeapManager::calculateAlignment(size_t baseAddress, size_t alignment)
{
	size_t multiplier = (baseAddress / alignment) + 1;
	size_t alignedAddress = multiplier * alignment;
	size_t padding = alignedAddress - baseAddress;
	return padding;

}

size_t HeapManager::alignSize(size_t requiredBytes) {//tutorial - aligns to machine word either 4 or 8
	return (requiredBytes + 4 - 1) & ~(4 - 1);//32--bit machine// returns required size + padding for alignment
}


void HeapManager::insert(BlockDescriptor* head, BlockDescriptor * previousNode, BlockDescriptor * newNode)//doubly,insert at head
{
	if (previousNode == nullptr) {
		// Is the first node
		if (head != nullptr) {
			// The list has more elements
			newNode->next = head;
			newNode->next->prev = newNode;
		}
		else {
			newNode->next = nullptr;
		}
		head = newNode;
		head->prev = nullptr;
	}
	else {
		if (previousNode->next == nullptr) {
			// Is the last node
			previousNode->next = newNode;
			newNode->next = nullptr;
		}
		else {
			// Is a middle node
			newNode->next = previousNode->next;
			if (newNode->next != nullptr) {
				newNode->next->prev = newNode;
			}
			previousNode->next = newNode;
			newNode->prev = previousNode;
		}
	}

}

void HeapManager::remove(BlockDescriptor * head, BlockDescriptor * deleteNode)
{
	if (deleteNode->prev == nullptr) {//is first
		if (deleteNode->next == nullptr) {//has only one
			head = nullptr;
		}
		else {
			head = deleteNode->next;
			head->prev = nullptr;
		}
	}
	else {
		if (deleteNode->next == nullptr) {//is last
			deleteNode->prev->next = nullptr;
		}
		else {//is middle
			deleteNode->prev->next = deleteNode->next;
			deleteNode->next->prev = deleteNode->prev;
		}
	}
}

void HeapManager::s_insert(BlockDescriptor * head, BlockDescriptor * previousNode, BlockDescriptor * newNode)//insert,single at head
{
	if (previousNode == nullptr) {
		// Is the first node
		if (head != nullptr) {
			// The list has more elements
			newNode->next = head;
		}
		else {
			newNode->next = nullptr;
		}
		head = newNode;
	}
	else {
		if (previousNode->next == nullptr) {
			// Is the last node
			previousNode->next = newNode;
			newNode->next = nullptr;
		}
		else {
			// Is a middle node
			newNode->next = previousNode->next;
			previousNode->next = newNode;
		}
	}
}

void HeapManager::s_remove(BlockDescriptor * head, BlockDescriptor * previousNode, BlockDescriptor * deleteNode)
{
	if (previousNode == nullptr) {
		// Is the first node
		if (deleteNode->next == nullptr) {
			// List only has one element
			head = nullptr;
		}
		else {
			// List has more elements
			head = deleteNode->next;
		}
	}
	else {
		previousNode->next = deleteNode->next;
	}
}



void HeapManager::find(size_t size, size_t alignment, size_t& padding, BlockDescriptor *& previousNode, BlockDescriptor *& foundNode)//called in _alloc
{
	BlockDescriptor* ptr_iteration = m_freeBlocks;//
	BlockDescriptor* ptr_iterationPrev = nullptr;
	std::cout << "within find(): size of head: " << ptr_iteration->m_sizeBlock << "\n";
	while (ptr_iteration != nullptr) {
		padding = calculateAlignment((size_t)ptr_iteration, alignment);
		size_t requiredSize = size + padding;//plus guardbanding, plus alignment
		if (ptr_iteration->m_sizeBlock >= requiredSize) {//found
			break;
		}
		ptr_iterationPrev = ptr_iteration;
		ptr_iteration = ptr_iteration->next;
	}
	previousNode = ptr_iterationPrev;
	foundNode = ptr_iteration;
	std::cout << "node found in find() at: " << foundNode->m_pBlockStartAddr << "size:  " << foundNode->m_sizeBlock << "\n";
}


void HeapManager::find1(size_t size, size_t alignment, size_t& padding, BlockDescriptor *& previousNode, BlockDescriptor *& foundNode)//called in _alloc
{
	BlockDescriptor* ptr_iteration = m_freeBlocks;//
	BlockDescriptor* ptr_iterationPrev = nullptr;
	std::cout << "within find(): size of head: " << ptr_iteration->m_sizeBlock << "\n";
	while (ptr_iteration != nullptr) {
		padding = calculateAlignment((size_t)ptr_iteration, alignment);
		size_t requiredSize = size + padding;//plus guardbanding, plus alignment
		if (ptr_iteration->m_sizeBlock >= requiredSize) {//found
			break;
		}
		else {
			ptr_iteration = nullptr;
			std::cout << "within find(): ******NOTHING FOUND******* ";
			foundNode = ptr_iteration;
			return;
		}
		ptr_iterationPrev = ptr_iteration;
		ptr_iteration = ptr_iteration->next;
	}
	previousNode = ptr_iterationPrev;
	foundNode = ptr_iteration;
	std::cout << "node found in find() at: " << foundNode->m_pBlockStartAddr << "size:  " << foundNode->m_sizeBlock << "\n";
}

void HeapManager::find2(size_t size, size_t alignment, size_t& padding, BlockDescriptor *& previousNode, BlockDescriptor *& foundNode)//called in _alloc
{
	BlockDescriptor* ptr_iteration = m_freeBlocks;//
	BlockDescriptor* ptr_iterationPrev = nullptr;
	std::cout << "within find(): size of head: " << ptr_iteration->m_sizeBlock << "\n";
	while (ptr_iteration != nullptr) {
		padding = calculateAlignment((size_t)ptr_iteration, alignment);
		//size_t requiredSize = size + padding;//plus guardbanding, plus alignment
		size_t requiredSize = alignSize(size);//alignment 4
		if (ptr_iteration->m_sizeBlock >= requiredSize) {//found
			break;
		}
		else {
			ptr_iteration = nullptr;
			std::cout << "within find(): ******NOTHING FOUND******* ";
			foundNode = ptr_iteration;
			return;
		}
		ptr_iterationPrev = ptr_iteration;
		ptr_iteration = ptr_iteration->next;
	}
	previousNode = ptr_iterationPrev;
	foundNode = ptr_iteration;
	std::cout << "node found in find() at: " << foundNode->m_pBlockStartAddr << "size:  " << foundNode->m_sizeBlock << "\n";
}

//within find() split()

void * HeapManager::_alloc(size_t i_bytes)
{

	 
	return nullptr;
}



void * HeapManager::_alloc(size_t i_bytes, unsigned int i_alignment)//returning nullptr if it can't fulfill the request
{
	//size_t block_size = ALIGN(i_bytes + SIZE_T_SIZE);
	//find: iterate through free list/check size of free block/reduce 
	BlockDescriptor* node = nullptr;//set by find()//foundNode in find() since passing a ptr
	std::cout << "node in _alloc at start of function call: " << node << "\n";
	BlockDescriptor* prevNode = nullptr;//set by find()
	size_t padding = 0;
	//find
	//find(i_bytes, i_alignment, padding, prevNode, node);//reference
	find(i_bytes, i_alignment, padding, prevNode, node);

	std::cout << "node in _alloc after find function call: " << node << "\n";
	std::cout << " blocksize: " << node ->m_sizeBlock << "\n";
	std::cout << "previous node : " << prevNode << "\n";

	size_t blockDescriptorSize = sizeof(BlockDescriptor);
	size_t requiredSize = i_bytes + padding;
	size_t sizeDifference = node->m_sizeBlock - requiredSize;
	size_t alignmentPadding = padding - blockDescriptorSize;
	std::cout << "size of BD " << blockDescriptorSize << "\n";
	std::cout << "padding " << padding << "\n";
	std::cout << "requiredSize = bytes +padding: " << requiredSize << "\n";
	std::cout << "sizedifference: " << sizeDifference << "\n";
	std::cout << "alignmentPadding " << alignmentPadding << "\n";


	if (sizeDifference > 0) {//splitting
		BlockDescriptor* newFreeBlock = (BlockDescriptor*)((size_t)node + requiredSize);
		newFreeBlock->m_sizeBlock = sizeDifference;
		//insert split free block in free list
		s_insert(m_freeBlocks, node, newFreeBlock);
		std::cout << "newFreeBlockBD's address " << newFreeBlock << "\n";
	}
	else {//remove from free list 
		s_remove(m_freeBlocks, prevNode, node);
	}

	//size_t blockDescriptorAddress = (size_t)node + alignmentPadding;
	size_t blockDescriptorAddress = (size_t)node + padding;
	size_t userPtr = blockDescriptorAddress + blockDescriptorSize;//includes padding for alignment
	((BlockDescriptor*)blockDescriptorAddress)->m_sizeBlock = requiredSize;
	std::cout << "BDaddress(node+alignment) " << blockDescriptorAddress << "\n";
	std::cout << "userPtr(BDaddress+BDsize) " << userPtr << "\n";
	
	//s_insert(m_oustandingBlocks, nullptr, node);//insert at front
	//std::cout << "\n inserted to outstanding and returning as void ptr: node address: " << node->m_pBlockStartAddr << " \n size: " << node->m_sizeBlock << "\n";
	
	//return node ->m_pBlockStartAddr;//return user pointer to data block - therefore the return address needs to be adjusted
	return (void*)userPtr;
}

void * HeapManager::_alloc1(size_t i_bytes, unsigned int i_alignment)//returning nullptr if it can't fulfill the request
{
	//size_t block_size = ALIGN(i_bytes + SIZE_T_SIZE);
	//find: iterate through free list/check size of free block/reduce 
	BlockDescriptor* node = nullptr;//set by find()//foundNode in find() since passing a ptr
	size_t userPtr = 0;
	std::cout << "node in _alloc at start of function call: " << node << "\n";
	BlockDescriptor* prevNode = nullptr;//set by find()
	
	size_t padding = 0;
	//find
	//find(i_bytes, i_alignment, padding, prevNode, node);//reference
	find1(i_bytes, i_alignment, padding, prevNode, node);

	if (node != nullptr) {
		std::cout << "node in _alloc after find function call: " << node << "\n";
		std::cout << " blocksize: " << node->m_sizeBlock << "\n";
		std::cout << "previous node : " << prevNode << "\n";

		size_t blockDescriptorSize = sizeof(BlockDescriptor);
		size_t requiredSize = i_bytes + padding;
		size_t sizeDifference = node->m_sizeBlock - requiredSize;
		size_t alignmentPadding = padding - blockDescriptorSize;
		std::cout << "size of BD " << blockDescriptorSize << "\n";
		std::cout << "padding " << padding << "\n";
		std::cout << "requiredSize = bytes +padding: " << requiredSize << "\n";
		std::cout << "sizedifference: " << sizeDifference << "\n";
		std::cout << "alignmentPadding " << alignmentPadding << "\n";

		if (sizeDifference > 0) {//splitting
			BlockDescriptor* newFreeBlock = (BlockDescriptor*)((size_t)node + requiredSize);
			newFreeBlock->m_sizeBlock = sizeDifference;
			//insert split free block in free list
			s_insert(m_freeBlocks, node, newFreeBlock);
			std::cout << "newFreeBlockBD's address " << newFreeBlock << "\n";
		}
		else {//remove from free list 
			s_remove(m_freeBlocks, prevNode, node);
		}

		//size_t blockDescriptorAddress = (size_t)node + alignmentPadding;
		size_t blockDescriptorAddress = (size_t)node + padding;
		userPtr = blockDescriptorAddress + blockDescriptorSize;//includes padding for alignment
		((BlockDescriptor*)blockDescriptorAddress)->m_sizeBlock = requiredSize;
		std::cout << "BDaddress(node+alignment) " << blockDescriptorAddress << "\n";
		std::cout << "userPtr(BDaddress+BDsize) " << userPtr << "\n";

		//s_insert(m_oustandingBlocks, nullptr, node);//insert at front
		//std::cout << "\n inserted to outstanding and returning as void ptr: node address: " << node->m_pBlockStartAddr << " \n size: " << node->m_sizeBlock << "\n";

		//return node ->m_pBlockStartAddr;//return user pointer to data block - therefore the return address needs to be adjusted
	}
	else {
		std::cout << "found node " << node << "\n";
		return (void*)node;
	}
	return (void*)userPtr;
}

void * HeapManager::_alloc2(size_t i_bytes, unsigned int i_alignment)//returning nullptr if it can't fulfill the request
{
	//size_t block_size = ALIGN(i_bytes + SIZE_T_SIZE);
	//find: iterate through free list/check size of free block/reduce 
	BlockDescriptor* node = nullptr;//set by find()//foundNode in find() since passing a ptr
	size_t *userPtr = nullptr;
	std::cout << "node in _alloc at start of function call: " << node << "\n";
	BlockDescriptor* prevNode = nullptr;//set by find()

	size_t padding = 0;//set by find2()
	//find
	//find(i_bytes, i_alignment, padding, prevNode, node);//reference
	find2(i_bytes, i_alignment, padding, prevNode, node);

	if (node != nullptr) {
		std::cout << "node in _alloc after find function call: " << node << "\n";
		std::cout << " blocksize: " << node->m_sizeBlock << "\n";
		std::cout << "previous node : " << prevNode << "\n";

		size_t blockDescriptorSize = sizeof(BlockDescriptor);
		size_t requiredSize = i_bytes + padding;
		size_t sizeDifference = node->m_sizeBlock - requiredSize;
		BlockDescriptor * blockDescriptorAddress = node;

		//size_t alignmentPadding = padding - blockDescriptorSize;
		std::cout << "size of BD " << blockDescriptorSize << "\n";
		std::cout << "padding in alloc2 " << padding << "\n";
		std::cout << "alignedSize = required bytes +padding: " << requiredSize << "\n";
		std::cout << "sizedifference: " << sizeDifference << "\n";
		std::cout << "BDaddress( is BD* node) " << blockDescriptorAddress << "\n";
		std::cout << "BDaddress(as size_t * ) " << (size_t*)node << "\n";
		//size_t * test = (size_t*)node + 16;
		//size_t * test = reinterpret_cast<size_t*>(node) + 16;
		//size_t * test = reinterpret_cast<size_t*>(node) ;
		//size_t * test = (size_t*)16;
		size_t * test = reinterpret_cast<size_t*>(16);
		size_t * test2 = reinterpret_cast<size_t*>(node);
		//size_t * sumTests = test + test2;
		
				
		std::cout << "test: 16 in HEX " << test << "\n";
		std::cout << "test2: node (BDaddress) " << test2 << "\n";
		//std::cout << "alignmentPadding " << alignmentPadding << "\n";
		


		//size_t blockDescriptorAddress = (size_t)node + alignmentPadding;
		//size_t blockDescriptorAddress = (size_t)node + padding;
		//BlockDescriptor * blockDescriptorAddress = node;
		//userPtr = blockDescriptorAddress + blockDescriptorSize;//includes padding for alignment
		//userPtr = (size_t*)node + blockDescriptorSize;
		userPtr = (size_t*)node + blockDescriptorSize;
		((BlockDescriptor*)blockDescriptorAddress)->m_sizeBlock = requiredSize;
		//std::cout << "BDaddress(node+alignment) " << blockDescriptorAddress << "\n";
		std::cout << "BDaddress(node) " << blockDescriptorAddress << "\n";
		std::cout << "userPtr(BDaddress+BDsize) " << userPtr << "\n";


		if (sizeDifference > 0) {//splitting
			//BlockDescriptor* newFreeBlock = (BlockDescriptor*)((size_t)node + requiredSize);
			//BlockDescriptor* newFreeBlock = (BlockDescriptor*)((size_t)node + requiredSize);
			//BlockDescriptor* newFreeBlock = node + blockDescriptorSize + requiredSize;
			std::cout << "in if - requiredSize = bytes +padding: " << requiredSize << "\n";
			std::cout << "in if - size of BD " << blockDescriptorSize << "\n";
			std::cout << "in if - BDaddress(node) " << blockDescriptorAddress << "\n";

			//BlockDescriptor* newFreeBlock = (BlockDescriptor*)node + blockDescriptorSize + requiredSize;

			BlockDescriptor* newFreeBlock = (BlockDescriptor*)userPtr + requiredSize;

			newFreeBlock->m_sizeBlock = sizeDifference;
			//insert split free block in free list
			s_insert(m_freeBlocks, node, newFreeBlock);
			std::cout << "in if newFreeBlockBD's address " << newFreeBlock << "\n";
		}
		else {//remove from free list 
			s_remove(m_freeBlocks, prevNode, node);
		}

		//s_insert(m_oustandingBlocks, nullptr, node);//insert at front
		//std::cout << "\n inserted to outstanding and returning as void ptr: node address: " << node->m_pBlockStartAddr << " \n size: " << node->m_sizeBlock << "\n";

		//return node ->m_pBlockStartAddr;//return user pointer to data block - therefore the return address needs to be adjusted
	}
	else {
		std::cout << "no node found " << node << "\n";
		return (void*)node;
	}
	return (void*)userPtr;
}



void * HeapManager::_alloc(HeapManager * i_heapManager, size_t i_bytes, unsigned int i_alignment)
{
	return nullptr;
}

void * HeapManager::alloc(HeapManager * i_pManager, size_t i_size)
{
	return nullptr;
}

void * HeapManager::alloc(HeapManager * i_pManager, size_t i_size, unsigned int i_alignment)
{
	return nullptr;
}

void HeapManager::Destroy(HeapManager * i_pManager)
{
}

void HeapManager::_free(void * i_ptr)
{
}

bool HeapManager::free(HeapManager * i_pManager, void * i_ptr)
{
	return false;
}

void HeapManager::collect()
{
}

void HeapManager::Collect(HeapManager * i_pManager)
{
}

size_t HeapManager::getLargestFreeBlock()
{
	return size_t();
}

size_t HeapManager::GetLargestFreeBlock(const HeapManager * i_pManager)
{
	return size_t();
}

size_t HeapManager::getTotalFreeMemory()
{
	return size_t();
}

size_t HeapManager::GetTotalFreeMemory(const HeapManager * i_pManager)
{
	return size_t();
}

bool HeapManager::Contains(void * i_ptr)
{
	return false;
}

bool HeapManager::Contains(const HeapManager * i_pManager, void * i_ptr)
{
	return false;
}

bool HeapManager::IsAllocated(void * i_ptr)
{
	return false;
}

bool HeapManager::IsAllocated(const HeapManager * i_pManager, void * i_ptr)
{
	return false;
}

void HeapManager::ShowFreeBlocks()
{
}

void HeapManager::ShowFreeBlocks(const HeapManager * i_pManager)
{
}

void HeapManager::ShowOutstandingAllocations(const HeapManager * i_pManager)
{
}
