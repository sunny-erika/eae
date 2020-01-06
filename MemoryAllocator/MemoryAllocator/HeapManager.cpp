
#include "HeapManager.h"
#include <Windows.h>

HeapManager::HeapManager() {
	m_pHeapMemory = nullptr;
	m_freeBlocks = nullptr;
	m_oustandingBlocks = nullptr;
	test = 3;
}

HeapManager::HeapManager(void * i_pHeapMemory, size_t i_HeapMemorySize)
{
	m_pHeapMemory = i_pHeapMemory;
	m_HeapMemorySize = i_HeapMemorySize;
	m_freeBlocks = nullptr;
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

void HeapManager::find(size_t size, size_t alignment, size_t& padding, BlockDescriptor *& previousNode, BlockDescriptor *& foundNode)
{
	BlockDescriptor* ptr_iteration = m_freeBlocks;
	BlockDescriptor* ptr_iterationPrev = nullptr;
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
}



//within find() split()

void * HeapManager::_alloc(size_t i_bytes)
{

	 
	return nullptr;
}



void * HeapManager::_alloc(size_t i_bytes, unsigned int i_alignment)
{
	//size_t block_size = ALIGN(i_bytes + SIZE_T_SIZE);
	//find: iterate through free list/check size of free block/reduce 
	BlockDescriptor* node;//set by find()
	BlockDescriptor* prevNode;//set by find()
	size_t padding;//set by find()
	find(i_bytes, i_alignment, padding, prevNode, node);
	
	size_t blockDescriptorSize = sizeof(BlockDescriptor);
	size_t requiredSize = i_bytes + padding;
	size_t sizeDifference = node->m_sizeBlock - requiredSize;//check

	if (sizeDifference > 0) {//splitting
		BlockDescriptor* newFreeBlock = (BlockDescriptor*)((size_t)node + requiredSize);
		newFreeBlock->m_sizeBlock = sizeDifference;
		//insert split free block in free list
		m_freeBlocks;
		if (prevNode == nullptr) {//1st element
			if (m_freeBlocks != nullptr) {
				node->next = m_freeBlocks;
				node->next->prev = node;
			}
			else {
				node->next = nullptr;
			}
			m_freeBlocks = node;
			m_freeBlocks->prev = nullptr;
		}
		else {
			if (prevNode->next == nullptr) {//if last
				prevNode->next = node;
				node->next = nullptr;
			}
			else { //middle
				node->next = prevNode->next;
				if (node->next != nullptr) {
					node->next->prev = node;
				}
				prevNode->next = node;
				node->prev = prevNode;
			}
		}

	}//remove from free list and put in outstanding list


	return nullptr;
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
