
#include "HeapManager.h"
#include <Windows.h>
#include <iostream>


//TODO
/*
only split when big, if it just about fits I will allocate it as it is


*/
HeapManager::HeapManager() {
	m_pHeapMemory = nullptr;
	m_freeBlocks = nullptr;
	m_outstandingBlocks = nullptr;
	//test = 3;
}

//called in main
HeapManager::HeapManager(void * i_pHeapMemory, size_t i_HeapMemorySize)
{
	m_pHeapMemory = i_pHeapMemory;
	m_HeapMemorySize = i_HeapMemorySize;
	m_freeBlocks = (BlockDescriptor*)m_pHeapMemory;
	//m_freeBlocks = nullptr;
	//m_freeBlocks->m_pBlockStartAddr = m_pHeapMemory;
	m_freeBlocks->m_pBlockStartAddr = m_pHeapMemory;
	std::cout << "***in constructor***m_freeBlocks: " << m_freeBlocks << " \n";
	std::cout << "***in constructor***m_freeBlocks->m_pBlockStartAddr the memory assigned from main: " << m_freeBlocks->m_pBlockStartAddr << " \n";
	m_freeBlocks->m_sizeBlock = m_HeapMemorySize;
	m_outstandingBlocks = nullptr;
}

HeapManager::HeapManager(int i_test)
{
	test = i_test;
}

HeapManager::~HeapManager()
{
	m_pHeapMemory = nullptr;
	m_freeBlocks = nullptr;
	m_outstandingBlocks = nullptr;
	//and within freeBlock & outstandingBlocks
	m_freeBlocks->m_pBlockStartAddr = nullptr;
	m_outstandingBlocks = nullptr;
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

void HeapManager::HeapManager::initialize(void * i_pHeapMemory, size_t i_HeapMemorySize)
{
	m_pHeapMemory = i_pHeapMemory;
	m_HeapMemorySize = i_HeapMemorySize;
	m_freeBlocks = nullptr;
	m_outstandingBlocks = nullptr;
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

void HeapManager::insertFront(BlockDescriptor **head, BlockDescriptor *newNode) {
	newNode->next = (*head);
	//newNode->prev = NULL;//making it first
	newNode->prev = nullptr;

	//if ((*head) != NULL) {
	if ((*head) != nullptr) {
		(*head)->prev = newNode;

	}

	(*head) = newNode;
}

void HeapManager::insertFront1(BlockDescriptor ** head, BlockDescriptor ** newNode)
{
	(*newNode)->next = (*head);
	(*newNode)->prev = nullptr;

	if ((*head) != nullptr) {
		(*head)->prev = *newNode;

	}

	(*head) = *newNode;

	std::cout << "***in insertFront: " << m_freeBlocks << " \n";
	std::cout << "***in insertFront *head: " << *head << " \n";
	std::cout << "***in insertFront (*head)->next: " << (*head)->next << " \n";
	std::cout << "***in insertFront (*head)->next->prev: " << (*head)->next->prev << " \n";
}

void HeapManager::insertFront2(BlockDescriptor ** head, BlockDescriptor ** newNode)
{
	/*
	if ((*head)->prev == nullptr) {
		*head = *newNode;
	}*/
	if (*head == nullptr) {
		*head = *newNode;
		(*head)->prev = nullptr;
	}
	else {
		(*newNode)->next = (*head);
		(*newNode)->next->prev = (*newNode);
		//(*newNode)->prev = nullptr;

		(*head) = *newNode;
	}

}

void HeapManager::insertInAscendingOrderBySize1(BlockDescriptor *& head, BlockDescriptor *& newNode)
{
	BlockDescriptor ** ppIterator = &head;

	std::cout << "***in insertAscending1 head: " << *ppIterator << " \n";
	std::cout << "***in insertAscending1 newNode: " << newNode << " \n";
	
	if (*ppIterator == nullptr) {//empty list - works
		std::cout << "***in insertAscending1 in if *ppIterator ==nullptr : " << *ppIterator << " \n";
		newNode->next = nullptr;
		newNode->prev = nullptr;
		*ppIterator = newNode;
		if (((*ppIterator)->prev == nullptr)) {
			(*ppIterator)->next = nullptr;
		}
	}
	else {
		std::cout << "***in insertAscending1 in first else before while *ppIterator : " << *ppIterator << " \n";
		//while ((*ppIterator && (newNode)->m_sizeBlock >= (*ppIterator)->m_sizeBlock) || (*ppIterator && (*ppIterator)->next != nullptr)) {
		while ((*ppIterator && (newNode)->m_sizeBlock >= (*ppIterator)->m_sizeBlock) && (*ppIterator)->next != nullptr) {//endless
			*ppIterator = (*ppIterator)->next;//should stop at first smaller node
		}
		std::cout << "***in insertAscending1 in first else after while *ppIterator : " << *ppIterator << " \n";

		if ((newNode)->m_sizeBlock <= (*ppIterator)->m_sizeBlock) {//insert before iterator
			newNode->next = *ppIterator;
			newNode->prev = (*ppIterator)->prev;
			(*ppIterator)->prev->next = newNode;
			(*ppIterator)->prev = newNode;
		}

		if ((*ppIterator)->next == nullptr) {//iterator last node - insert after iterator
			newNode->next = nullptr;
			newNode->prev = *ppIterator;
			(*ppIterator)->next = newNode;
		}

		if ((*ppIterator)->next == nullptr && (*ppIterator)->prev == nullptr) {//only one list item
			if ((*ppIterator)->m_sizeBlock >= newNode->m_sizeBlock) {//newNode becomes head
				newNode->next = *ppIterator;
				newNode->prev = nullptr;
				(*ppIterator)->prev = newNode;
			}
			else {//insert at end
				newNode->prev = *ppIterator;
				newNode->next = nullptr;
				(*ppIterator)->next = newNode;
			}
		}
	}
}

void HeapManager::insertInAscendingOrderBySize2(BlockDescriptor ** head, BlockDescriptor * newNode)
{
	BlockDescriptor * pIterator;

	//std::cout << "***in insertAscending1 head: " << pIterator << " \n";
	std::cout << "***in insertAscending1 newNode: " << newNode << " \n";

	if (*head == nullptr) {//empty list - works
		//std::cout << "***in insertAscending1 in if *ppIterator ==nullptr : " << pIterator << " \n";
		newNode->next = nullptr;
		newNode->prev = nullptr;
		*head = newNode;
	}
	else if (newNode->m_sizeBlock <= (*head)->m_sizeBlock ) {//insert at beginning
		newNode->next = *head;
		newNode->next->prev = newNode;
	}
	else {
		//std::cout << "***in insertAscending1 in first else before while *ppIterator : " << pIterator << " \n";

		pIterator = *head;
		//while ((*ppIterator && (newNode)->m_sizeBlock >= (*ppIterator)->m_sizeBlock) || (*ppIterator && (*ppIterator)->next != nullptr)) {
		while (pIterator && (newNode)->m_sizeBlock >= pIterator->m_sizeBlock && pIterator->next != nullptr) {//endless
			pIterator = pIterator->next;//should stop at first smaller node
		}
		std::cout << "***in insertAscending1 in first else after while *ppIterator : " << pIterator << " \n";
		newNode->next = pIterator->next;

		if (pIterator->next != nullptr) {
			newNode->next->prev = newNode;
		}

		pIterator->next = newNode;
		newNode->prev = pIterator;

	}
}

void HeapManager::insertInAscendingOrderBySize3(BlockDescriptor ** head, BlockDescriptor * newNode)
{
	BlockDescriptor * ppIterator;

	//std::cout << "***in insertAscending1 head: " << ppIterator << " \n";
	std::cout << "***in insertAscending1 newNode: " << newNode << " \n";

	if (*head == nullptr) {//empty list - works
		//std::cout << "***in insertAscending1 in if *ppIterator ==nullptr : " << ppIterator << " \n";
		newNode->next = nullptr;
		newNode->prev = nullptr;
		*head = newNode;
	}
	else if (newNode->m_sizeBlock <= (*head)->m_sizeBlock) {//head is smallest
		newNode->next = *head;
		newNode->next->prev = newNode;
		*head = newNode;
	}
	else {
		ppIterator = *head;
		//std::cout << "***in insertAscending1 in first else before while *ppIterator : " << ppIterator << " \n";
		//while ((*ppIterator && (newNode)->m_sizeBlock >= (*ppIterator)->m_sizeBlock) || (*ppIterator && (*ppIterator)->next != nullptr)) {
		while (ppIterator && (newNode)->m_sizeBlock >= ppIterator->m_sizeBlock && ppIterator->next != nullptr) {//endless
			ppIterator = ppIterator->next;//should stop at first smaller node
		}
		std::cout << "***in insertAscending1 in first else after while *ppIterator : " << ppIterator << " \n";

		if ((newNode)->m_sizeBlock <= ppIterator->m_sizeBlock) {//insert before iterator
			newNode->next = ppIterator;
			newNode->prev = ppIterator->prev;
			ppIterator->prev->next = newNode;
			ppIterator->prev = newNode;
		}

		if (ppIterator->next == nullptr) {//iterator last node - insert after iterator
			newNode->next = nullptr;
			newNode->prev = ppIterator;
			ppIterator->next = newNode;
		}

		if (ppIterator->next == nullptr && ppIterator->prev == nullptr) {//only one list item
			if (ppIterator->m_sizeBlock >= newNode->m_sizeBlock) {//newNode becomes head
				newNode->next = ppIterator;
				newNode->prev = nullptr;
				ppIterator->prev = newNode;
			}
			else {//insert at end
				newNode->prev = ppIterator;
				newNode->next = nullptr;
				ppIterator->next = newNode;
			}
		}
	}
}

void HeapManager::insertInAscendingOrderBySize4(BlockDescriptor ** head, BlockDescriptor * newNode)
{
	BlockDescriptor * ppIterator;

	//std::cout << "***in insertAscending1 head: " << ppIterator << " \n";
	std::cout << "***in insertAscending1 newNode: " << newNode << " \n";

	if (*head == nullptr) {//empty list - works
		//std::cout << "***in insertAscending1 in if *ppIterator ==nullptr : " << ppIterator << " \n";
		newNode->next = nullptr;
		newNode->prev = nullptr;
		*head = newNode;
	}
	else if (newNode->m_sizeBlock <= (*head)->m_sizeBlock) {
		std::cout << "***in insertAscending1 in else if *0* : \n";
		newNode->next = *head;
		newNode->next->prev = newNode;
		*head = newNode;
	}
	else {
		ppIterator = *head;
		//std::cout << "***in insertAscending1 in first else before while *ppIterator : " << ppIterator << " \n";
		//while ((*ppIterator && (newNode)->m_sizeBlock >= (*ppIterator)->m_sizeBlock) || (*ppIterator && (*ppIterator)->next != nullptr)) {
		while (ppIterator && (newNode)->m_sizeBlock >= ppIterator->m_sizeBlock && ppIterator->next != nullptr) {//endless
			ppIterator = ppIterator->next;//should stop at first smaller node
		}
		std::cout << "***in insertAscending1 in first else after while *ppIterator : " << ppIterator << " \n";

		if ((newNode)->m_sizeBlock <= ppIterator->m_sizeBlock) {//insert before iterator
			std::cout << "***in insertAscending1 in first else after while *ppIterator *A* : " << ppIterator << " \n";
			newNode->next = ppIterator;
			newNode->prev = ppIterator->prev;
			ppIterator->prev->next = newNode;
			ppIterator->prev = newNode;
		}//else if

		if (ppIterator->next == nullptr) {//iterator last node - insert after iterator
			std::cout << "***in insertAscending1 in first else after while *ppIterator *B* : " << ppIterator << " \n";
			newNode->next = nullptr;
			newNode->prev = ppIterator;
			ppIterator->next = newNode;
		}

		if (ppIterator->next == nullptr && ppIterator->prev == nullptr) {//only one list item
			if (ppIterator->m_sizeBlock >= newNode->m_sizeBlock) {//newNode becomes head
				std::cout << "***in insertAscending1 in first else after while *ppIterator *C* : " << ppIterator << " \n";
				newNode->next = ppIterator;
				newNode->prev = nullptr;
				ppIterator->prev = newNode;
			}
			else {//insert at end equivalent to iterator last node *B*
				std::cout << "***in insertAscending1 in first else after while *ppIterator *D* : " << ppIterator << " \n";
				newNode->prev = ppIterator;
				newNode->next = nullptr;
				ppIterator->next = newNode;
			}
		}
	}
}

void HeapManager::insertInAscendingOrderBySize5(BlockDescriptor ** head, BlockDescriptor * newNode)
{
	BlockDescriptor * ppIterator;

	std::cout << "***in insertAscending1 head: " << *head << " \n";
	std::cout << "***in insertAscending1 newNode: " << newNode << " \n";

	if (*head == nullptr) {//empty list - works
		//std::cout << "***in insertAscending1 in if *ppIterator ==nullptr : " << ppIterator << " \n";
		newNode->next = nullptr;
		newNode->prev = nullptr;
		*head = newNode;
	}
	else if (newNode->m_sizeBlock <= (*head)->m_sizeBlock) {
		std::cout << "***in insertAscending1 in else if *0* : \n";
		newNode->next = *head;
		newNode->next->prev = newNode;
		*head = newNode;
	}
	else {
		ppIterator = *head;
		//std::cout << "***in insertAscending1 in first else before while *ppIterator : " << ppIterator << " \n";
		//while ((*ppIterator && (newNode)->m_sizeBlock >= (*ppIterator)->m_sizeBlock) || (*ppIterator && (*ppIterator)->next != nullptr)) {
		while (ppIterator && (newNode)->m_sizeBlock >= ppIterator->m_sizeBlock && ppIterator->next != nullptr) {//endless
			ppIterator = ppIterator->next;//should stop at first smaller node
		}
		std::cout << "***in insertAscending1 in first else after while *ppIterator : " << ppIterator << " \n";

		if ((newNode)->m_sizeBlock <= ppIterator->m_sizeBlock) {//insert before iterator
			std::cout << "***in insertAscending1 in first else after while *ppIterator *A* : " << ppIterator << " \n";
			newNode->next = ppIterator;
			newNode->prev = ppIterator->prev;
			ppIterator->prev->next = newNode;
			ppIterator->prev = newNode;
		}//else if

		if (ppIterator->next == nullptr && newNode->m_sizeBlock > ppIterator->m_sizeBlock) {//iterator last node - insert after iterator
			std::cout << "***in insertAscending1 in first else after while *ppIterator *B* : " << ppIterator << " \n";
			newNode->next = nullptr;
			newNode->prev = ppIterator;
			ppIterator->next = newNode;
			std::cout << "***in *B* printing list \n";
			printList(*head);
		}

		if (ppIterator->next == nullptr && ppIterator->prev == nullptr) {//only one list item
			if (ppIterator->m_sizeBlock >= newNode->m_sizeBlock) {//newNode becomes head
				std::cout << "***in insertAscending1 in first else after while *ppIterator *C* : " << ppIterator << " \n";
				newNode->next = ppIterator;
				newNode->prev = nullptr;
				ppIterator->prev = newNode;
			}
			else {//insert at end equivalent to iterator last node *B*
				std::cout << "***in insertAscending1 in first else after while *ppIterator *D* : " << ppIterator << " \n";
				newNode->prev = ppIterator;
				newNode->next = nullptr;
				ppIterator->next = newNode;
			}
		}
	}
}


void HeapManager::insertInAscendingOrderBySize6(BlockDescriptor *& head, BlockDescriptor * newNode)
{
	BlockDescriptor * ppIterator;

	std::cout << "***in insertAscending1 head: " << head << " \n";
	std::cout << "***in insertAscending1 newNode: " << newNode << " \n";

	if (head == nullptr) {//empty list - works
		//std::cout << "***in insertAscending1 in if *ppIterator ==nullptr : " << ppIterator << " \n";
		newNode->next = nullptr;
		newNode->prev = nullptr;
		head = newNode;
	}
	else if (newNode->m_sizeBlock <= (head)->m_sizeBlock) {
		std::cout << "***in insertAscending1 in else if *0* : \n";
		newNode->next = head;
		newNode->next->prev = newNode;
		head = newNode;
	}
	else {
		ppIterator = head;
		//std::cout << "***in insertAscending1 in first else before while *ppIterator : " << ppIterator << " \n";
		//while ((*ppIterator && (newNode)->m_sizeBlock >= (*ppIterator)->m_sizeBlock) || (*ppIterator && (*ppIterator)->next != nullptr)) {
		while (ppIterator && (newNode)->m_sizeBlock >= ppIterator->m_sizeBlock && ppIterator->next != nullptr) {//endless
			ppIterator = ppIterator->next;//should stop at first smaller node
		}
		std::cout << "***in insertAscending1 in first else after while *ppIterator : " << ppIterator << " \n";

		if ((newNode)->m_sizeBlock <= ppIterator->m_sizeBlock) {//insert before iterator
			std::cout << "***in insertAscending1 in first else after while *ppIterator *A* : " << ppIterator << " \n";
			newNode->next = ppIterator;
			newNode->prev = ppIterator->prev;
			ppIterator->prev->next = newNode;
			ppIterator->prev = newNode;
		}//else if

		if (ppIterator->next == nullptr && newNode->m_sizeBlock > ppIterator->m_sizeBlock) {//iterator last node - insert after iterator
			std::cout << "***in insertAscending1 in first else after while *ppIterator *B* : " << ppIterator << " \n";
			newNode->next = nullptr;
			newNode->prev = ppIterator;
			ppIterator->next = newNode;
			std::cout << "***in *B* printing list \n";
			printList(head);
		}

		if (ppIterator->next == nullptr && ppIterator->prev == nullptr) {//only one list item
			if (ppIterator->m_sizeBlock >= newNode->m_sizeBlock) {//newNode becomes head
				std::cout << "***in insertAscending1 in first else after while *ppIterator *C* : " << ppIterator << " \n";
				newNode->next = ppIterator;
				newNode->prev = nullptr;
				ppIterator->prev = newNode;
			}
			else {//insert at end equivalent to iterator last node *B*
				std::cout << "***in insertAscending1 in first else after while *ppIterator *D* : " << ppIterator << " \n";
				newNode->prev = ppIterator;
				newNode->next = nullptr;
				ppIterator->next = newNode;
			}
		}
	}

}

void HeapManager::insertInAscendingOrderBySize7(BlockDescriptor ** head, BlockDescriptor * newNode)
{
	newNode->next = nullptr;
	newNode-> prev = nullptr;
	BlockDescriptor * ppIterator;

	std::cout << "***in insertAscending1 head: " << *head << " \n";
	std::cout << "***in insertAscending1 newNode: " << newNode << " \n";

	if (*head == nullptr) {//empty list - works
		//std::cout << "***in insertAscending1 in if *ppIterator ==nullptr : " << ppIterator << " \n";
		newNode->next = nullptr;
		newNode->prev = nullptr;
		*head = newNode;
	}
	else if (newNode->m_sizeBlock <= (*head)->m_sizeBlock) {
		std::cout << "***in insertAscending1 in else if *0* : \n";
		newNode->next = *head;
		newNode->next->prev = newNode;
		*head = newNode;
	}
	else {
		ppIterator = *head;
		//std::cout << "***in insertAscending1 in first else before while *ppIterator : " << ppIterator << " \n";
		//while ((*ppIterator && (newNode)->m_sizeBlock >= (*ppIterator)->m_sizeBlock) || (*ppIterator && (*ppIterator)->next != nullptr)) {
		while (ppIterator && (newNode)->m_sizeBlock >= ppIterator->m_sizeBlock && ppIterator->next != nullptr) {//endless
			ppIterator = ppIterator->next;//should stop at first smaller node
		}
		std::cout << "***in insertAscending1 in first else after while *ppIterator : " << ppIterator << " \n";

		if ((newNode)->m_sizeBlock <= ppIterator->m_sizeBlock) {//insert before iterator
			std::cout << "***in insertAscending1 in first else after while *ppIterator *A* : " << ppIterator << " \n";
			newNode->next = ppIterator;
			newNode->prev = ppIterator->prev;
			ppIterator->prev->next = newNode;
			ppIterator->prev = newNode;
		}//else if

		if (ppIterator->next == nullptr && newNode->m_sizeBlock > ppIterator->m_sizeBlock) {//iterator last node - insert after iterator
			std::cout << "***in insertAscending1 in first else after while *ppIterator *B* : " << ppIterator << " \n";
			newNode->next = nullptr;
			newNode->prev = ppIterator;
			ppIterator->next = newNode;
			std::cout << "***in *B* printing list \n";
			printList(*head);
		}

		if (ppIterator->next == nullptr && ppIterator->prev == nullptr) {//only one list item
			if (ppIterator->m_sizeBlock >= newNode->m_sizeBlock) {//newNode becomes head
				std::cout << "***in insertAscending1 in first else after while *ppIterator *C* : " << ppIterator << " \n";
				newNode->next = ppIterator;
				newNode->prev = nullptr;
				ppIterator->prev = newNode;
			}
			else {//insert at end equivalent to iterator last node *B*
				std::cout << "***in insertAscending1 in first else after while *ppIterator *D* : " << ppIterator << " \n";
				newNode->prev = ppIterator;
				newNode->next = nullptr;
				ppIterator->next = newNode;
			}
		}
	}
}

void HeapManager::insertInAscendingOrderByAddress(BlockDescriptor ** head, BlockDescriptor * newNode)
{
	newNode->next = nullptr;
	newNode->prev = nullptr;
	BlockDescriptor * ppIterator;

	std::cout << "***in insertAscending1 head: " << *head << " \n";
	std::cout << "***in insertAscending1 newNode: " << newNode << " \n";

	if (*head == nullptr) {//empty list 
		//std::cout << "***in insertAscending1 in if *ppIterator ==nullptr : " << ppIterator << " \n";
		newNode->next = nullptr;
		newNode->prev = nullptr;
		*head = newNode;
	}
	else if (newNode <= *head) {//newNode becomes head
		std::cout << "***in insertAscending1 in else if *0* : \n";
		newNode->next = *head;
		newNode->next->prev = newNode;
		*head = newNode;
	}
	
	else {
		ppIterator = *head;
		//std::cout << "***in insertAscending1 in first else before while *ppIterator : " << ppIterator << " \n";
		//while ((*ppIterator && (newNode)->m_sizeBlock >= (*ppIterator)->m_sizeBlock) || (*ppIterator && (*ppIterator)->next != nullptr)) {
		while (ppIterator && (newNode) >= ppIterator && ppIterator->next != nullptr) {//endless
			ppIterator = ppIterator->next;//should stop at first smaller node
		}
		std::cout << "***in insertAscending1 in first else after while *ppIterator : " << ppIterator << " \n";

		if ((newNode) <= ppIterator) {//insert before iterator
			std::cout << "***in insertAscending1 in first else after while *ppIterator *A* : " << ppIterator << " \n";
			newNode->next = ppIterator;
			newNode->prev = ppIterator->prev;
			ppIterator->prev->next = newNode;
			ppIterator->prev = newNode;
		}//else if

		if (ppIterator->next == nullptr && newNode > ppIterator) {//iterator last node - insert after iterator
			std::cout << "***in insertAscending1 in first else after while *ppIterator *B* : " << ppIterator << " \n";
			newNode->next = nullptr;
			newNode->prev = ppIterator;
			ppIterator->next = newNode;
			std::cout << "***in *B* printing list \n";
			printList(*head);
		}

		if (ppIterator->next == nullptr && ppIterator->prev == nullptr) {//only one list item
			if (ppIterator >= newNode) {//newNode becomes head
				std::cout << "***in insertAscending1 in first else after while *ppIterator *C* : " << ppIterator << " \n";
				newNode->next = ppIterator;
				newNode->prev = nullptr;
				ppIterator->prev = newNode;
			}
			else {//insert at end equivalent to iterator last node *B*
				std::cout << "***in insertAscending1 in first else after while *ppIterator *D* : " << ppIterator << " \n";
				newNode->prev = ppIterator;
				newNode->next = nullptr;
				ppIterator->next = newNode;
			}
		}
	}

}




void HeapManager::insertInAscendingOrderBySize(BlockDescriptor *& head, BlockDescriptor *& newNode)
{
	BlockDescriptor ** ppIterator = &head;
	//BlockDescriptor ** ppNewNode = &newNode;
	std::cout << "***in insertAscending head: " << *ppIterator << " \n";
	std::cout << "***in insertAscending newNode: " << newNode << " \n";
	/*
	while (((newNode)->m_sizeBlock >= (*ppIterator)->m_sizeBlock) && *ppIterator) {
		*ppIterator = (*ppIterator)->next;
	}

	/*while (*ppIterator) {//I need more exit condition
		if ((newNode)->m_sizeBlock >= (*ppIterator)->m_sizeBlock) {
			*ppIterator = (*ppIterator)->next;
			/*
			if (pIterator == nullptr && pIterator->prev == nullptr) {//empty list
				pIterator = newNode;
				pIterator->prev = nullptr;
				pIterator->next = nullptr;
			}


			if (pIterator == nullptr && pIterator->prev != nullptr) {//last node
				newNode->prev = pIterator->prev;
				pIterator = newNode;
				pIterator->next = nullptr;
			}*//*
		}
	}*/

	if (*ppIterator == nullptr) {//empty list - works
		newNode->next = nullptr;
		newNode->prev = nullptr;
		*ppIterator = newNode;
		if (((*ppIterator)->prev == nullptr)) {
			//then the list was empty and it's now the first node
			//(*ppIterator)->next = nullptr;
			(*ppIterator)->next = nullptr;
		}
	}
	else {
		//while (*ppIterator && (newNode)->m_sizeBlock >= (*ppIterator)->m_sizeBlock){
		while (*ppIterator && (newNode)->m_sizeBlock >= (*ppIterator)->m_sizeBlock && (*ppIterator)->next !=nullptr) {
			*ppIterator = (*ppIterator)->next;//first smaller node
		}

		if ((*ppIterator)->next == nullptr && (*ppIterator)->prev == nullptr) {//only one list item

		}

		if ((*ppIterator)->next == nullptr) {//ppIterator is last node
			//std::cout << "in insertAscending *ppIterator->prev " << (*ppIterator)->prev <<"\n";
			//newNode->prev = (*ppIterator)->prev;
			//*ppIterator = newNode;
			//(*ppIterator)->next = nullptr;
			newNode->next = nullptr;
			newNode->prev = *ppIterator;
			(*ppIterator)->next = newNode;

		}
		else {//middle node
			/*
			newNode->next = *ppIterator;
			newNode->prev = (*ppIterator)->prev;
			(*ppIterator)->prev = newNode;
			(*ppIterator)->prev->next = newNode;
			*/
		}
	}
		/*
		if (*ppIterator == nullptr && (*ppIterator)->prev == nullptr) {//empty list
			*ppIterator = newNode;
			(*ppIterator)->prev = nullptr;
			(*ppIterator)->next = nullptr;
		}

		if (*ppIterator == nullptr && (*ppIterator)->prev != nullptr) {//last node
			newNode->prev = (*ppIterator)->prev;
			*ppIterator = newNode;
			(*ppIterator)->next = nullptr;
		}

		if (*ppIterator != nullptr) {
			if ((*ppIterator)->next != nullptr) {//middle node
						//(*ppNewNode)->next = *ppIterator;
				newNode->next = *ppIterator;
				newNode->prev = (*ppIterator)->prev;
				(*ppIterator)->prev->next = newNode;
				(*ppIterator)->prev = newNode;
			}
		}


	//if (pIterator == nullptr){//could be last or empty list
	
	
	/*
	BlockDescriptor * pIterator = head;

	while ((newNode)->m_sizeBlock >= pIterator->m_sizeBlock) {
		pIterator = pIterator->next;
	}
	//if (pIterator == nullptr){//could be last or empty list
	if (pIterator == nullptr && pIterator->prev == nullptr) {//empty list
		pIterator = newNode;
		pIterator->prev = nullptr;
		pIterator->next = nullptr;
	}

	if (pIterator == nullptr && pIterator->prev != nullptr){//last node
		newNode->prev = pIterator->prev;
		pIterator = newNode;
		pIterator->next = nullptr;
	}

	if (pIterator->next != nullptr) {//middle node
		newNode->next = pIterator;
		newNode->prev = pIterator->prev;
		pIterator->prev->next = newNode;
		pIterator->prev = newNode;
	}
	*/
}




void HeapManager::deleteFront(BlockDescriptor ** head)
{
	BlockDescriptor *temp = (*head);
	(*head) = (*head)->next;
	temp = nullptr;
}

void HeapManager::deleteLast(BlockDescriptor ** head)
{
	
}

void HeapManager::deleteMe(BlockDescriptor ** head, BlockDescriptor * deleteMe)
{
	std::cout << "***in deleteMe *head: " << *head << " \n";
	std::cout << "***in deleteMe deleteMe: " << deleteMe << " \n";
	std::cout << "***in deleteMe deleteMe->prev: " << deleteMe->prev << " \n";
	if (*head == deleteMe) {//first
		(*head) = (*head)->next;//the next one becomes head
	}

	//if (deleteMe->next == NULL) {
	if (deleteMe->next == nullptr) {//last
		//deleteMe->prev = nullptr;
		deleteMe->prev->next = nullptr;//makes me null
	}

	
	if (deleteMe->next != nullptr) {//middle
		deleteMe->prev->next = deleteMe->next;//skips me, takes my next
		deleteMe->next->prev = deleteMe->prev;//takes my previous
	}
	
}

void HeapManager::deleteMe2(BlockDescriptor ** head, BlockDescriptor ** deleteMe)
{
	if (*head == *deleteMe) {//first
		(*head) = (*head)->next;//the next one becomes head
	}

	//if (deleteMe->next == NULL) {
	if ((*deleteMe)->next == nullptr) {//last
		//deleteMe->prev = nullptr;
		(*deleteMe)->prev->next = nullptr;//makes me null
	}


	if ((*deleteMe)->next != nullptr) {//middle
		(*deleteMe)->prev->next = (*deleteMe)->next;//skips me, takes my next
		(*deleteMe)->next->prev =(*deleteMe)->prev;//takes my previous
	}
}

void HeapManager::deleteMe3(BlockDescriptor ** head, BlockDescriptor * deleteMe)//based on 1
{
	std::cout << "***in deleteMe *head: " << *head << " \n";
	std::cout << "***in deleteMe deleteMe: " << deleteMe << " \n";
	std::cout << "***in deleteMe deleteMe->prev: " << deleteMe->prev << " \n";
	if (*head == deleteMe) {//first
		(*head) = (*head)->next;//the next one becomes head
	}

	//if (deleteMe->next == NULL) {
	if (deleteMe->next == nullptr) {//last
		//deleteMe->prev = nullptr;
		deleteMe->prev->next = nullptr;//makes me null
	}


	if (deleteMe->next != nullptr && deleteMe->prev != nullptr) {//middle
		deleteMe->prev->next = deleteMe->next;//skips me, takes my next
		deleteMe->next->prev = deleteMe->prev;//takes my previous
	}
	


}

void HeapManager::deleteMe4(BlockDescriptor ** head, BlockDescriptor * deleteMe)//based on 3
{
	std::cout << "***in deleteMe *head: " << *head << " \n";
	std::cout << "***in deleteMe deleteMe: " << deleteMe << " \n";
	//std::cout << "***in deleteMe deleteMe->prev: " << deleteMe->prev << " \n";
	if (*head == deleteMe) {//first
		(*head) = (*head)->next;//the next one becomes head
	}

	//if (deleteMe->next == NULL) {
	if (deleteMe->next == nullptr && deleteMe->prev != nullptr) {//last
		//deleteMe->prev = nullptr;
		deleteMe->prev->next = nullptr;//makes me null
	}
	
	if (deleteMe->next != nullptr && deleteMe->prev != nullptr) {//middle
		deleteMe->prev->next = deleteMe->next;//skips me, takes my next
		deleteMe->next->prev = deleteMe->prev;//takes my previous
	}
}

void HeapManager::deleteMe5(BlockDescriptor ** head, BlockDescriptor * deleteMe)//based on 4
{
	std::cout << "***in deleteMe *head: " << *head << " \n";
	std::cout << "***in deleteMe deleteMe: " << deleteMe << " \n";
	//std::cout << "***in deleteMe deleteMe->prev: " << deleteMe->prev << " \n";
	if (*head == deleteMe) {//first - TODO further distinquish between first and only one node
		(*head) = (*head)->next;//the next one becomes head
		(*head)->prev = nullptr;
	}

	//if (deleteMe->next == NULL) {
	if (deleteMe->next == nullptr && deleteMe->prev != nullptr) {//last
		//deleteMe->prev = nullptr;
		deleteMe->prev->next = nullptr;//makes me null
	}

	if (deleteMe->next != nullptr && deleteMe->prev != nullptr) {//middle
		deleteMe->prev->next = deleteMe->next;//skips me, takes my next
		deleteMe->next->prev = deleteMe->prev;//takes my previous
	}
}

void HeapManager::deleteMe6(BlockDescriptor ** head, BlockDescriptor * deleteMe)//based on 5
{
	std::cout << "***in deleteMe *head: " << *head << " \n";
	std::cout << "***in deleteMe deleteMe: " << deleteMe << " \n";
	//std::cout << "***in deleteMe deleteMe->prev: " << deleteMe->prev << " \n";
	if (*head == deleteMe) {//first
		if ((*head)->next == nullptr) {//and only node 
			*head = nullptr;//then list becomes empty
		}
		else {
			//first - TODO further distinquish between first and only one node
			(*head) = (*head)->next;//the next one becomes head
			(*head)->prev = nullptr;
		}
	}

	//if (deleteMe->next == NULL) {
	if (deleteMe->next == nullptr && deleteMe->prev != nullptr) {//last
		//deleteMe->prev = nullptr;
		deleteMe->prev->next = nullptr;//makes me null
	}

	if (deleteMe->next != nullptr && deleteMe->prev != nullptr) {//middle
		deleteMe->prev->next = deleteMe->next;//skips me, takes my next
		deleteMe->next->prev = deleteMe->prev;//takes my previous
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

void HeapManager::deleteNode(BlockDescriptor ** head, BlockDescriptor * node) {
	/* base case */
	if (*head == NULL || node == NULL)
		return;

	/* If node to be deleted is head node */
	if (*head == node)
		*head = node->next;

	/* Change next only if node to be
	deleted is NOT the last node */
	if (node->next != NULL)
		node->next->prev = node->prev;

	/* Change prev only if node to be
	deleted is NOT the first node */
	if (node->prev != NULL)
		node->prev->next = node->next;

	//delete(node);
	printList(*head);
}

void HeapManager::deleteNode1(BlockDescriptor *& head, BlockDescriptor * node) {
	/* base case */
	if (head == NULL || node == NULL)
		return;

	/* If node to be deleted is head node */
	if (head == node)
		head = node->next;

	/* Change next only if node to be
	deleted is NOT the last node */
	if (node->next != NULL)
		node->next->prev = node->prev;

	/* Change prev only if node to be
	deleted is NOT the first node */
	if (node->prev != NULL)
		node->prev->next = node->next;

	//delete(node);
	printList(head);
}


void HeapManager::removeFromList(BlockDescriptor *& head, BlockDescriptor * node) {

	BlockDescriptor ** current = &head; 
	std::cout << "\n inside removeFromList *current " << *current;
	std::cout << "\n inside removeFromList current " << current;
	std::cout << "\n inside removeFromList &(*current) " << &(*current);
	std::cout << "\n inside removeFromList &(*current)->next " << &(*current)->next;
	std::cout << "\n inside removeFromList &((*current)->next) " << &((*current)->next);
	std::cout << "\n inside removeFromList head " << head;
	std::cout << "\n inside removeFromList *&head " << *& head;
	std::cout << "\n inside removeFromList &head " << & head;
	std::cout << "\n inside removeFromList &head " << &head;
	
	while (*current) {//read access violation
		if (*current == node) {
			*current = node->next;
			node->next = nullptr;
			
		}
		current = &(*current)->next;
		
	}
	BlockDescriptor ** curr = &((*current)->next);
	std::cout << "\n inside removeFromList &(*current)->next after while " << &(*current)->next;
	std::cout << "\n inside removeFromList curr " << curr;
	std::cout << "\n printList inside removeFromList \n";

	printList(head);
}

void HeapManager::removeFromList1(BlockDescriptor ** head, BlockDescriptor * node) {

	BlockDescriptor ** current = head;

	while (*current) {
		if (*current == node) {
			*current = node->next;
			node->next = nullptr;

		}
		current = &(*current)->next;
	}
}

void HeapManager::printList(BlockDescriptor * node)
{
	BlockDescriptor * last;
	while (node != NULL) {
		std::cout << "\n inside while of print list node " << node ;
		std::cout << " size " << node->m_sizeBlock <<"\n" ;
		std::cout << " prev " << node->prev << "\n";
		std::cout << " next " << node->next << "\n";
		last = node;
		node = node->next;
	}
	if (node == NULL)
		std::cout << "NULL";
}

void HeapManager::testingDelete() {

	std::cout << "\n in testing delete \n";
	
	BlockDescriptor *node1 = m_freeBlocks;
	BlockDescriptor *firstNode = m_freeBlocks;
	BlockDescriptor *secondNode = m_freeBlocks->next;
	//BlockDescriptor *lastNode = m_freeBlocks->next->next;
	std::cout << "\n in testing node1 = " << node1 <<"\n";
	//std::cout << "\n in testing middleNode = " << middleNode->m_sizeBlock << "\n";
	//std::cout << "\n in testing middleNode->prev = " << secondNode->prev << "\n";
	//BlockDescriptor *node2 = reinterpret_cast<BlockDescriptor*>(217);
	//BlockDescriptor *node3 = reinterpret_cast<BlockDescriptor*>(233);
	   
	//insertFront(&m_freeBlocks, node1);
	//insertFront(&m_freeBlocks, node2);
	//insertFront(&m_freeBlocks, node3);
	std::cout << "in testing m_freeBlocks = " << m_freeBlocks << "\n";
	std::cout << "in testing printing after insertion" << "\n";

	//deleteMe4(&m_freeBlocks, secondNode);//m_freeBlocks->next->next
	//deleteMe3(&m_freeBlocks, firstNode);
	//deleteMe3(&m_freeBlocks, middleNode);
	//deleteMe3(&m_freeBlocks, lastNode);
	//deleteNode(&m_freeBlocks, node1);
	//deleteNode1(m_freeBlocks, node1);
	//deleteFront(&m_freeBlocks);
	//deleteMe(&m_freeBlocks, node1);
	//deleteMe(&m_freeBlocks, middleNode);
	//deleteMe(&m_freeBlocks, firstNode);
	//deleteMe2(&m_freeBlocks, &node1);
	//deleteMe(&m_freeBlocks, lastNode);
	//deleteMe(&m_freeBlocks, middleNode);
	//removeFromList1(&m_freeBlocks, node1);
	removeFromList(m_freeBlocks, node1);//not working here
	//std::cout << "\n in testing node1 after r() = " << node1 << "\n";
	//BlockDescriptor *found = find3(500, 4);
	//std::cout << "\n in testing node found after find3() = " << found << "\n";
	//remove(m_freeBlocks, node1);
	//remove(m_freeBlocks, m_freeBlocks->next);
	
	printList(m_freeBlocks);
}

void HeapManager::testingInsert()
{
	
	//BlockDescriptor *testList = find3(400, 4);
	//BlockDescriptor *testList = nullptr;
	//BlockDescriptor *testList = m_freeBlocks;
/*
	BlockDescriptor *node1 = reinterpret_cast<BlockDescriptor*>((size_t)testList + 400);
	BlockDescriptor *node2 = reinterpret_cast<BlockDescriptor*>((size_t)testList + 800);
	BlockDescriptor *node3 = reinterpret_cast<BlockDescriptor*>((size_t)testList + 1000);
	BlockDescriptor *node4 = reinterpret_cast<BlockDescriptor*>((size_t)testList + 2000);
*/

	BlockDescriptor *node1 = reinterpret_cast<BlockDescriptor*>((size_t)m_freeBlocks + 400);
	BlockDescriptor *node2 = reinterpret_cast<BlockDescriptor*>((size_t)m_freeBlocks + 800);
	BlockDescriptor *node3 = reinterpret_cast<BlockDescriptor*>((size_t)m_freeBlocks + 1000);
	BlockDescriptor *node4 = reinterpret_cast<BlockDescriptor*>((size_t)m_freeBlocks + 2000);

	BlockDescriptor *node5 = reinterpret_cast<BlockDescriptor*>((size_t)m_freeBlocks + 2200);
	BlockDescriptor *node6 = reinterpret_cast<BlockDescriptor*>((size_t)m_freeBlocks + 2400);
	BlockDescriptor *node7 = reinterpret_cast<BlockDescriptor*>((size_t)m_freeBlocks + 2600);


	std::cout << "in testingInsert m_freeBlocks = " << m_freeBlocks << "\n";
	std::cout << "**********************************************************************\n";
	std::cout << "in testingInsert printing m_freeBlocks \n";
	printList(m_freeBlocks);
	std::cout << "**********************************************************************\n";

	/*
	node1->m_sizeBlock = 20;
	node2->m_sizeBlock = 30;
	node3->m_sizeBlock = 25;
	node4->m_sizeBlock = 15;
	*/
	node1->m_sizeBlock = 10;
	node2->m_sizeBlock = 20;
	node3->m_sizeBlock = 30;
	node4->m_sizeBlock = 40;

	node5->m_sizeBlock = 25;
	node6->m_sizeBlock = 5;
	node7->m_sizeBlock = 50;

	std::cout << "\n";
	std::cout << "in testingInsert calling insert() node1, size" << node1->m_sizeBlock << "\n";
	//insertInAscendingOrderBySize(testList, node1);
	//insertInAscendingOrderBySize1(testList, node1);
	//insertInAscendingOrderBySize2(&testList, node1);
	//insertInAscendingOrderBySize3(&testList, node1);
	//insertInAscendingOrderBySize4(&testList, node1);
	insertInAscendingOrderBySize5(&m_freeBlocks, node1);
	//std::cout << "in testingInsert after insert() testList " << testList << "\n" ;
	std::cout << "in testingInsert after insert() testList " << m_freeBlocks << "\n";
	std::cout << "**********************************************************************\n";
	std::cout << "in testingInsert printing m_freeBlocks \n";
	printList(m_freeBlocks);
	std::cout << "**********************************************************************\n";

	std::cout << "\n";
	std::cout << "in testingInsert calling insert() node2, size" << node2->m_sizeBlock << "\n";
	//insertInAscendingOrderBySize(testList, node2);
	//insertInAscendingOrderBySize1(testList, node2);
	//insertInAscendingOrderBySize2(&testList, node2);
	//insertInAscendingOrderBySize3(&testList, node2);
	insertInAscendingOrderBySize5(&m_freeBlocks, node2);
	//std::cout << "in testingInsert after insert() testList " << testList << "\n" ;
	std::cout << "in testingInsert after insert() testList " << m_freeBlocks << "\n";
	std::cout << "**********************************************************************\n";
	std::cout << "in testingInsert printing m_freeBlocks \n";
	printList(m_freeBlocks);
	std::cout << "**********************************************************************\n";

	
	std::cout << "\n";
	std::cout << "in testingInsert calling insert() node3, size" << node3->m_sizeBlock << "\n";
	//insertInAscendingOrderBySize(testList, node3);
	//insertInAscendingOrderBySize1(testList, node3);
	//insertInAscendingOrderBySize2(&testList, node3);
	//insertInAscendingOrderBySize3(&testList, node3);
	insertInAscendingOrderBySize5(&m_freeBlocks, node3);
	//std::cout << "in testingInsert after insert() testList " << testList << "\n" ;
	std::cout << "in testingInsert after insert() testList " << m_freeBlocks << "\n";
	std::cout << "**********************************************************************\n";
	std::cout << "in testingInsert printing m_freeBlocks \n";
	printList(m_freeBlocks);
	std::cout << "**********************************************************************\n";

	std::cout << "\n";
	std::cout << "in testingInsert calling insert() node4, size" << node4->m_sizeBlock << "\n";
	//insertInAscendingOrderBySize(testList, node4);
	//insertInAscendingOrderBySize1(testList, node4);
	//insertInAscendingOrderBySize2(&testList, node4);
	//insertInAscendingOrderBySize3(&testList, node4);
	insertInAscendingOrderBySize5(&m_freeBlocks, node4);
	//std::cout << "in testingInsert after insert() testList " << testList << "\n" ;
	std::cout << "in testingInsert after insert() testList " << m_freeBlocks << "\n";
	std::cout << "**********************************************************************\n";
	std::cout << "in testingInsert printing m_freeBlocks \n";
	printList(m_freeBlocks);
	std::cout << "**********************************************************************\n";

	std::cout << "\n";
	std::cout << "in testingInsert calling insert() node5, size" << node5->m_sizeBlock << "\n";
	//insertInAscendingOrderBySize(testList, node4);
	//insertInAscendingOrderBySize1(testList, node5);
	//insertInAscendingOrderBySize2(&testList, node5);
	//insertInAscendingOrderBySize3(&testList, node5);
	insertInAscendingOrderBySize5(&m_freeBlocks, node5);
	//std::cout << "in testingInsert after insert() testList " << testList << "\n" ;
	std::cout << "in testingInsert after insert() testList " << m_freeBlocks << "\n";
	std::cout << "**********************************************************************\n";
	std::cout << "in testingInsert printing m_freeBlocks \n";
	printList(m_freeBlocks);
	std::cout << "**********************************************************************\n";

	std::cout << "\n";
	std::cout << "in testingInsert calling insert() node6, size" << node6->m_sizeBlock << "\n";
	//insertInAscendingOrderBySize(testList, node4);
	//insertInAscendingOrderBySize1(testList, node6);
	//insertInAscendingOrderBySize2(&testList, node6);
	//insertInAscendingOrderBySize3(&testList, node6);
	insertInAscendingOrderBySize5(&m_freeBlocks, node6);
	//std::cout << "in testingInsert after insert() testList " << testList << "\n" ;
	std::cout << "in testingInsert after insert() testList " << m_freeBlocks << "\n";
	std::cout << "**********************************************************************\n";
	std::cout << "in testingInsert printing m_freeBlocks \n";
	printList(m_freeBlocks);
	std::cout << "**********************************************************************\n";

	std::cout << "\n";
	std::cout << "in testingInsert calling insert() node7, size" << node7->m_sizeBlock << "\n";
	//insertInAscendingOrderBySize(testList, node4);
	//insertInAscendingOrderBySize1(testList, node7);
	//insertInAscendingOrderBySize2(&testList, node7);
	//insertInAscendingOrderBySize3(&testList, node7);
	insertInAscendingOrderBySize5(&m_freeBlocks, node7);
	//std::cout << "in testingInsert after insert() testList " << testList << "\n" ;
	std::cout << "in testingInsert after insert() testList " << m_freeBlocks << "\n";
	std::cout << "**********************************************************************\n";
	std::cout << "in testingInsert printing m_freeBlocks \n";
	printList(m_freeBlocks);
	std::cout << "**********************************************************************\n";


/*
	std::cout << "\n";
	std::cout << "in testingInsert printing testList" << testList << "\n";;
	printList(testList);
*/
	std::cout << "\n";
	//std::cout << "in testingInsert printing m_freeBlocks" << m_freeBlocks << "\n";;
	//printList(m_freeBlocks);

	std::cout << "\n";
	//insertInAscendingOrderBySize(m_freeBlocks, node1);

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
		std::cout << "in find() iterating thru list"<< ptr_iteration->m_sizeBlock << "\n";
		//padding = calculateAlignment((size_t)ptr_iteration, alignment);
		padding = alignSize(size);
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

HeapManager::BlockDescriptor * HeapManager::find3(size_t size, size_t alignment)
{
	std::cout << "***in found3  \n";
	BlockDescriptor* nodeFound = nullptr;
	
	BlockDescriptor* pIterator = m_freeBlocks;
	std::cout << "***in found3  pIterator" << pIterator << "\n";

	std::cout << "***in found3  pIterator size" << pIterator->m_sizeBlock << "\n";
	size_t alignedSize = alignSize(size);
	std::cout << "***in found3  aligned size" << alignedSize << "\n";

	while (pIterator != nullptr) {
		//std::cout << "***in found3 in while \n";
		if (pIterator->m_sizeBlock >= alignedSize) {
			std::cout << "***in found3  pIterator size in if" << pIterator->m_sizeBlock << "\n";
			//std::cout << "***in found3 in if  \n";
			nodeFound = pIterator;
			break;
		}
		else {
			pIterator = nullptr;
			std::cout << "within find()3: ******NOTHING FOUND******* ";
			nodeFound = pIterator;
			return pIterator;
			
		}
		pIterator = pIterator->next;
		std::cout << "***in found3  pIterator next" << pIterator->m_sizeBlock << "\n";
	}

	std::cout << "***in found3 nodeFound: " << nodeFound << " \n";
	return nodeFound;
}

HeapManager::BlockDescriptor * HeapManager::find4(size_t size, size_t alignment)
{
	std::cout << "***in found4  \n";
	BlockDescriptor* nodeFound = nullptr;

	BlockDescriptor* pIterator = m_freeBlocks;
	std::cout << "***in found4  pIterator" << pIterator << "\n";

	std::cout << "***in found4  pIterator size" << pIterator->m_sizeBlock << "\n";
	size_t alignedSize = alignSize(size);
	size_t requiredSize = alignSize(size) + sizeof(BlockDescriptor);

	std::cout << "***in found4  aligned size" << alignedSize << "\n";

	while (pIterator != nullptr) {
		
		if (pIterator->m_sizeBlock >= requiredSize) {
			std::cout << "***in found3  pIterator size in if" << pIterator->m_sizeBlock << "\n";
			//std::cout << "***in found3 in if  \n";
			nodeFound = pIterator;
			break;
		}
		else if (pIterator->next == nullptr && pIterator->m_sizeBlock <= requiredSize) {//reached last node
			pIterator = nullptr;
			std::cout << "within find()3: ******NOTHING FOUND******* ";
			nodeFound = pIterator;
			return pIterator;
		}
		
		pIterator = pIterator->next;
		std::cout << "***in found4  pIterator next" << pIterator->m_sizeBlock << "\n";
	}


	return nodeFound;
}








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
	//new find only passing freeList

	if (node != nullptr) {
		std::cout << "node in _alloc after find function call: " << node << "\n";
		std::cout << " blocksize: " << node->m_sizeBlock << "\n";
		std::cout << "previous node : " << prevNode << "\n";

		size_t blockDescriptorSize = sizeof(BlockDescriptor);
		size_t requiredSize = i_bytes + padding;
		//size_t alignedSize = i_bytes + padding;
		size_t alignedSize = padding;
		size_t sizeDifference = node->m_sizeBlock - requiredSize;
		BlockDescriptor * blockDescriptorAddress = node;

		//size_t alignmentPadding = padding - blockDescriptorSize;
		std::cout << "size of BD " << blockDescriptorSize << "\n";
		std::cout << "padding = alignedSize(will be renamed)in alloc2 " << padding << "\n";
		std::cout << "alignedSize = required bytes +padding: " << alignedSize << "\n";
		std::cout << "sizedifference: " << sizeDifference << "\n";
		std::cout << "BDaddress( is BD* node) " << blockDescriptorAddress << "\n";
		std::cout << "BDaddress(as size_t * ) " << (size_t*)node << "\n";
		//size_t * test = (size_t*)node + 16;
		//size_t * test = reinterpret_cast<size_t*>(node) + 16;
		//size_t * test = reinterpret_cast<size_t*>(node) ;
		//size_t * test = (size_t*)16;
		//size_t * test = reinterpret_cast<size_t*>(16);
		//size_t * test2 = reinterpret_cast<size_t*>(node);
		//size_t * sumTests = test + test2;
		//uint8_t * ptrTest = reinterpret_cast<uint8_t*> (m_freeBlocks->m_pBlockStartAddr);
		//void * ptrTest = m_freeBlocks->m_pBlockStartAddr;
		//uint8_t * ptrTestCast = reinterpret_cast<uint8_t*>(ptrTest);
		//uint8_t * ptrTestCast = (uint8_t*)ptrTest;
		//uint8_t * ptrTestCast = (uint8_t*)m_freeBlocks;
		//void * test3 = reinterpret_cast<void*>(node + blockDescriptorSize);
		//void * test3 = reinterpret_cast<void*>((size_t)node + blockDescriptorSize);
		BlockDescriptor * test4 = reinterpret_cast<BlockDescriptor*>((size_t)node + blockDescriptorSize);
						
		//std::cout << "test: 16 in HEX " << test << "\n";
		//std::cout << "test2: node (BDaddress) " << test2 << "\n";
		//std::cout << "ptrTest: void ptr from virtual alloc reinter " << ptrTest << "\n";
		//std::cout << "ptrTestCast: void ptr from virtual alloc reinter to uint8_t* " << ptrTestCast << "\n";
		//std::cout << "test 3 " << test3 << "\n";
		//std::cout << "test 4 " << test3 << "\n";
		//std::cout << "alignmentPadding " << alignmentPadding << "\n";
		
	    //size_t blockDescriptorAddress = (size_t)node + alignmentPadding;
		//size_t blockDescriptorAddress = (size_t)node + padding;
		//BlockDescriptor * blockDescriptorAddress = node;
		//userPtr = blockDescriptorAddress + blockDescriptorSize;//includes padding for alignment
		//userPtr = (size_t*)node + blockDescriptorSize;
		//userPtr = (size_t*)node + blockDescriptorSize;
		userPtr = reinterpret_cast<size_t*>((size_t)node + blockDescriptorSize);
		((BlockDescriptor*)blockDescriptorAddress)->m_sizeBlock = alignedSize;//found node-will be allocated
		//remove from freeList and move to outstanding list
		//std::cout << "BDaddress(node+alignment) " << blockDescriptorAddress << "\n";
		std::cout << "BDaddress(node) " << blockDescriptorAddress << "\n";//the found node
		std::cout << "userPtr(BDaddress+BDsize) " << userPtr << "\n";


		if (sizeDifference > 0) {//splitting
			//BlockDescriptor* newFreeBlock = (BlockDescriptor*)((size_t)node + requiredSize);
			//BlockDescriptor* newFreeBlock = (BlockDescriptor*)((size_t)node + requiredSize);
			//BlockDescriptor* newFreeBlock = node + blockDescriptorSize + requiredSize;
			std::cout << "in if - requiredSize = bytes +padding: " << alignedSize << "\n";
			std::cout << "in if - size of BD " << blockDescriptorSize << "\n";
			std::cout << "in if - BDaddress(node) " << blockDescriptorAddress << "\n";

			//BlockDescriptor* newFreeBlock = (BlockDescriptor*)node + blockDescriptorSize + requiredSize;
			//BlockDescriptor * test4 = reinterpret_cast<BlockDescriptor*>((size_t)node + blockDescriptorSize);
			BlockDescriptor* newFreeBlock = reinterpret_cast<BlockDescriptor*>((size_t)userPtr + alignedSize);//could split into requested and padding

			newFreeBlock->m_sizeBlock = sizeDifference;
			std::cout << "in if newFreeBlockBD's sizeDifference " << newFreeBlock->m_sizeBlock << "\n";
			//insert split free block in free list
			//s_insert(m_freeBlocks, node, newFreeBlock);
			//insertFront1(&m_freeBlocks, newFreeBlock);
			insertFront2(&m_freeBlocks, &newFreeBlock);
			std::cout << "in if just added newFreeBlock to free list " << newFreeBlock->m_sizeBlock << "\n";
			//insertFront1(&m_freeBlocks, &newFreeBlock);
			std::cout << "in if newFreeBlockBD's address " << newFreeBlock << "\n";
			insertFront2(&m_outstandingBlocks, &node);
			std::cout << "in if just added node to outstanding list " << node->m_sizeBlock << "\n";
			std::cout << "in if node's address " << node << "\n";
			//deleteMe3(&m_freeBlocks, node);
			deleteMe4(&m_freeBlocks, node);
			std::cout << "in if just deleted node from free list " << node << "\n";
			std::cout << "in if node size " << node->m_sizeBlock << "\n";
			//deleteMe2(&m_freeBlocks, &node);
			//remove(m_freeBlocks, node);
			//deleteNode(&m_freeBlocks, node);
			//removeFromList(m_freeBlocks, &(*node));
			std::cout << "in if before calling remove m_freeBlocks " << m_freeBlocks << "\n";
			std::cout << "in if before calling remove &m_freeBlocks " << &m_freeBlocks << "\n";
			std::cout << "in if before calling remove node " << node << "\n";
			std::cout << "in if before calling remove &(*node) " << &(*node);
			std::cout << "in if before calling remove &node " << &node;
			
			//removeFromList(m_freeBlocks, node);
		}
		else {//remove from free list 
			//insertFront(&m_outstandingBlocks, node);
			std::cout << "NOW IN ELSE OF ALLOC " << &node;
			insertFront2(&m_outstandingBlocks, &node);
			//deleteMe4(&m_freeBlocks, node);
			//remove(m_freeBlocks, node);-
			//deleteNode(&m_freeBlocks, node);
		
			//s_remove(m_freeBlocks, prevNode, node);
		}

		//s_insert(m_oustandingBlocks, nullptr, node);//insert at front
		//std::cout << "\n inserted to outstanding and returning as void ptr: node address: " << node->m_pBlockStartAddr << " \n size: " << node->m_sizeBlock << "\n";

		//return node ->m_pBlockStartAddr;//return user pointer to data block - therefore the return address needs to be adjusted
	}
	else {
		std::cout << "no node found " << node << "\n";
		return (void*)node;
	}
	//deleteMe4(&m_freeBlocks, node);
	return (void*)userPtr;
}

void * HeapManager::_alloc3(size_t i_bytes, unsigned int i_alignment)
{
	BlockDescriptor* blockDescriptorForUserPtr = nullptr;//set by find()//foundNode in find() since passing a ptr
	size_t *userPtr = nullptr;
	std::cout << "\n";
	std::cout << "in _alloc BDforUserPt at start of function call: " << blockDescriptorForUserPtr << "\n";
	//BlockDescriptor* prevNode = nullptr;//set by find()

	size_t padding = 0;//set by find2()
	BlockDescriptor* foundNode = find3(i_bytes, i_alignment);//=blockDescriptorForUserPtr
	//blockDescriptorForUserPtr = find3(i_bytes, i_alignment);//goes to outstanding, new free node to freelist
	//find2(i_bytes, i_alignment, padding, prevNode, node);
	//blockDescriptorForUserPtr = m_freeBlocks;//replacing with findx(i_bytes, i_alignment)
	std::cout << "in _alloc FoundNode after find(): " << foundNode << "\n";

	if (foundNode != nullptr) {
		std::cout << "\n";
		std::cout << "in _alloc in if !=null foundNode: " << foundNode << " blocksize: " << foundNode->m_sizeBlock << "\n"; 
		//std::cout << "previous node : " << prevNode << "\n";

		size_t blockDescriptorSize = sizeof(BlockDescriptor);
		//size_t requiredSize = i_bytes + padding;
		
		size_t alignedSize = alignSize(i_bytes);
		size_t sizeDifference = foundNode->m_sizeBlock - alignedSize;
		//BlockDescriptor * blockDescriptorAddress = node;
		/*
		std::cout << "size of BD " << blockDescriptorSize << "\n";
		std::cout << "padding = alignedSize(will be renamed)in alloc2 " << padding << "\n";
		std::cout << "alignedSize = required bytes +padding: " << alignedSize << "\n";
		std::cout << "sizedifference: " << sizeDifference << "\n";*/
		//std::cout << "BDaddress( is BD* node) " << blockDescriptorAddress << "\n";
		//std::cout << "BDaddress(as size_t * ) " << (size_t*)blockDescriptorForUserPtr << "\n";
		//BlockDescriptor * test4 = reinterpret_cast<BlockDescriptor*>((size_t)blockDescriptorForUserPtr + blockDescriptorSize);
		//userPtr = reinterpret_cast<size_t*>((size_t)blockDescriptorForUserPtr + blockDescriptorSize);
		userPtr = reinterpret_cast<size_t*>((size_t)foundNode + blockDescriptorSize);
		//((BlockDescriptor*)blockDescriptorAddress)->m_sizeBlock = alignedSize;//found node-will be allocated
		//std::cout << "BDaddress(node) " << blockDescriptorAddress << "\n";//the found node
		std::cout << "in _alloc in if !=null userPtr " << userPtr << "\n";


		if (sizeDifference > 0) {
			std::cout << "\n";
			std::cout << "in _alloc in if >0 aligned size: " << alignedSize << "\n";
			std::cout << "in _alloc in if >0 size of BD " << blockDescriptorSize << "\n";
			//std::cout << "in if - BDaddress(node) " << blockDescriptorAddress << "\n";

			BlockDescriptor* newFreeBlock = reinterpret_cast<BlockDescriptor*>((size_t)userPtr + alignedSize);//could split into requested and padding
			blockDescriptorForUserPtr = foundNode;
			blockDescriptorForUserPtr->m_sizeBlock = alignedSize;
			newFreeBlock->m_sizeBlock = sizeDifference;
			std::cout << "in _alloc in if >0 newFreeBlockBD " << newFreeBlock << "\n" << "in _alloc in if >0 newFreeBlockBD's sizeDifference " << newFreeBlock->m_sizeBlock << "\n";
			std::cout << "in _alloc in if >0  calling insertFront newFreeBlock to free list " << "\n";
			insertFront2(&m_freeBlocks, &newFreeBlock);
			
			std::cout << "\n";
			std::cout << "in _alloc in if >0  calling insertFront blockDescriptorForUserPtr to outstanding list> adding " << blockDescriptorForUserPtr << "\n";
			insertFront2(&m_outstandingBlocks, &blockDescriptorForUserPtr);
			//std::cout << "in if just added node to outstanding list " << blockDescriptorForUserPtr->m_sizeBlock << "\n";
			//std::cout << "in if node's address " << blockDescriptorForUserPtr << "\n";

			std::cout << "\n";
			std::cout << "in _alloc in if >0  calling deleteMe blockDescriptorForUserPtr from free list> deleting " << blockDescriptorForUserPtr <<"\n";
			deleteMe4(&m_freeBlocks, blockDescriptorForUserPtr);
			//std::cout << "in if just deleted node from free list " << blockDescriptorForUserPtr << "\n";
			//std::cout << "in if node size " << blockDescriptorForUserPtr->m_sizeBlock << "\n";

			//std::cout << "in if before calling remove m_freeBlocks " << m_freeBlocks << "\n";
			//std::cout << "in if before calling remove &m_freeBlocks " << &m_freeBlocks << "\n";
			//std::cout << "in if before calling remove node " << blockDescriptorForUserPtr << "\n";
			//std::cout << "in if before calling remove &(*node) " << &(*blockDescriptorForUserPtr);
			//std::cout << "in if before calling remove &node " << &blockDescriptorForUserPtr;

		}
		else {
			std::cout << "NOW IN ELSE OF ALLOC " << &blockDescriptorForUserPtr;
			insertFront2(&m_outstandingBlocks, &blockDescriptorForUserPtr);
		
		}

		}
	else {
		std::cout << "no node found " << blockDescriptorForUserPtr << "\n";
		return (void*)blockDescriptorForUserPtr;
	}
	
	return (void*)userPtr;
}

void * HeapManager::_alloc4(size_t i_bytes, unsigned int i_alignment)
{
	BlockDescriptor* blockDescriptorForUserPtr = nullptr;
	size_t *userPtr = nullptr;
	std::cout << "\n";
	std::cout << "in _alloc BDforUserPt at start of function call: " << blockDescriptorForUserPtr << "\n";
	//BlockDescriptor* prevNode = nullptr;//set by find()

	size_t padding = 0;//set by find2()
	BlockDescriptor* foundNode = find3(i_bytes, i_alignment);//=blockDescriptorForUserPtr
	//blockDescriptorForUserPtr = find3(i_bytes, i_alignment);//goes to outstanding, new free node to freelist
	//find2(i_bytes, i_alignment, padding, prevNode, node);
	//blockDescriptorForUserPtr = m_freeBlocks;//replacing with findx(i_bytes, i_alignment)
	std::cout << "in _alloc FoundNode after find(): " << foundNode << "\n";

	if (foundNode != nullptr) {
		std::cout << "\n";
		std::cout << "in _alloc in if !=null foundNode: " << foundNode << " blocksize: " << foundNode->m_sizeBlock << "\n";
		//std::cout << "previous node : " << prevNode << "\n";

		size_t blockDescriptorSize = sizeof(BlockDescriptor);
		//size_t requiredSize = i_bytes + padding;

		size_t alignedSize = alignSize(i_bytes);
		size_t sizeDifference = foundNode->m_sizeBlock - alignedSize;
		//BlockDescriptor * blockDescriptorAddress = node;
		/*
		std::cout << "size of BD " << blockDescriptorSize << "\n";
		std::cout << "padding = alignedSize(will be renamed)in alloc2 " << padding << "\n";
		std::cout << "alignedSize = required bytes +padding: " << alignedSize << "\n";
		std::cout << "sizedifference: " << sizeDifference << "\n";*/
		//std::cout << "BDaddress( is BD* node) " << blockDescriptorAddress << "\n";
		//std::cout << "BDaddress(as size_t * ) " << (size_t*)blockDescriptorForUserPtr << "\n";
		//BlockDescriptor * test4 = reinterpret_cast<BlockDescriptor*>((size_t)blockDescriptorForUserPtr + blockDescriptorSize);
		//userPtr = reinterpret_cast<size_t*>((size_t)blockDescriptorForUserPtr + blockDescriptorSize);
		userPtr = reinterpret_cast<size_t*>((size_t)foundNode + blockDescriptorSize);
		//((BlockDescriptor*)blockDescriptorAddress)->m_sizeBlock = alignedSize;//found node-will be allocated
		//std::cout << "BDaddress(node) " << blockDescriptorAddress << "\n";//the found node
		std::cout << "in _alloc in if !=null userPtr " << userPtr << "\n";


		if (sizeDifference > 0) {
			std::cout << "\n";
			std::cout << "in _alloc in if >0 aligned size: " << alignedSize << "\n";
			std::cout << "in _alloc in if >0 size of BD " << blockDescriptorSize << "\n";
			//std::cout << "in if - BDaddress(node) " << blockDescriptorAddress << "\n";

			BlockDescriptor* newFreeBlock = reinterpret_cast<BlockDescriptor*>((size_t)userPtr + alignedSize);//could split into requested and padding
			blockDescriptorForUserPtr = foundNode;
			blockDescriptorForUserPtr->m_sizeBlock = alignedSize;
			newFreeBlock->m_sizeBlock = sizeDifference;
			std::cout << "in _alloc in if >0 newFreeBlockBD " << newFreeBlock << "\n" << "in _alloc in if >0 newFreeBlockBD's sizeDifference " << newFreeBlock->m_sizeBlock << "\n";
			std::cout << "in _alloc in if >0  calling insertFront newFreeBlock to free list " << "\n";
			newFreeBlock->next = nullptr;
			newFreeBlock->prev = nullptr;
			insertFront2(&m_freeBlocks, &newFreeBlock);

			std::cout << "\n";
			std::cout << "in _alloc in if >0  calling insertFront blockDescriptorForUserPtr to outstanding list> adding " << blockDescriptorForUserPtr << "\n";
			blockDescriptorForUserPtr->next = nullptr;
			blockDescriptorForUserPtr->prev = nullptr;
			insertFront2(&m_outstandingBlocks, &blockDescriptorForUserPtr);
			//std::cout << "in if just added node to outstanding list " << blockDescriptorForUserPtr->m_sizeBlock << "\n";
			//std::cout << "in if node's address " << blockDescriptorForUserPtr << "\n";

			std::cout << "\n";
			std::cout << "in _alloc in if >0  calling deleteMe blockDescriptorForUserPtr from free list> deleting " << blockDescriptorForUserPtr << "\n";
			deleteMe4(&m_freeBlocks, blockDescriptorForUserPtr);
			//std::cout << "in if just deleted node from free list " << blockDescriptorForUserPtr << "\n";
			//std::cout << "in if node size " << blockDescriptorForUserPtr->m_sizeBlock << "\n";

			//std::cout << "in if before calling remove m_freeBlocks " << m_freeBlocks << "\n";
			//std::cout << "in if before calling remove &m_freeBlocks " << &m_freeBlocks << "\n";
			//std::cout << "in if before calling remove node " << blockDescriptorForUserPtr << "\n";
			//std::cout << "in if before calling remove &(*node) " << &(*blockDescriptorForUserPtr);
			//std::cout << "in if before calling remove &node " << &blockDescriptorForUserPtr;

		}
		else {
			std::cout << "NOW IN ELSE OF ALLOC " << &blockDescriptorForUserPtr;
			insertFront2(&m_outstandingBlocks, &blockDescriptorForUserPtr);

		}

	}
	else {
		std::cout << "no node found " << blockDescriptorForUserPtr << "\n";
		return (void*)blockDescriptorForUserPtr;
	}

	return (void*)userPtr;
}


void * HeapManager::_alloc5(size_t i_bytes, unsigned int i_alignment)
{
	BlockDescriptor* blockDescriptorForUserPtr = nullptr;
	size_t *userPtr = nullptr;
	std::cout << "\n";
	std::cout << "in _alloc BDforUserPt at start of function call: " << blockDescriptorForUserPtr << "\n";
	
	size_t padding = 0;//set by find2()
	BlockDescriptor* foundNode = find3(i_bytes, i_alignment);//=blockDescriptorForUserPtr
	
	std::cout << "in _alloc FoundNode after find(): " << foundNode << "\n";

	if (foundNode != nullptr) {
		std::cout << "\n";
		std::cout << "in _alloc in if !=null foundNode: " << foundNode << " blocksize: " << foundNode->m_sizeBlock << "\n";
		
		size_t blockDescriptorSize = sizeof(BlockDescriptor);
		
		size_t alignedSize = alignSize(i_bytes);
		size_t sizeDifference = foundNode->m_sizeBlock - alignedSize;
		userPtr = reinterpret_cast<size_t*>((size_t)foundNode + blockDescriptorSize);
		
		std::cout << "in _alloc in if !=null userPtr " << userPtr << "\n";

		if (sizeDifference > 0) {
			std::cout << "\n";
			
			BlockDescriptor* newFreeBlock = reinterpret_cast<BlockDescriptor*>((size_t)userPtr + alignedSize);//could split into requested and padding
			blockDescriptorForUserPtr = foundNode;
			blockDescriptorForUserPtr->m_sizeBlock = alignedSize;
			newFreeBlock->m_sizeBlock = sizeDifference;
			std::cout << "in _alloc in if >0 newFreeBlockBD " << newFreeBlock << "\n" << "in _alloc in if >0 newFreeBlockBD's sizeDifference " << newFreeBlock->m_sizeBlock << "\n";
			std::cout << "in _alloc in if >0  calling insertFront newFreeBlock to free list " << "\n";
			newFreeBlock->next = nullptr;
			newFreeBlock->prev = nullptr;
			insertFront2(&m_freeBlocks, &newFreeBlock);

			std::cout << "\n";
			std::cout << "in _alloc in if >0  calling insertFront blockDescriptorForUserPtr to outstanding list> adding " << blockDescriptorForUserPtr << "\n";
			blockDescriptorForUserPtr->next = nullptr;
			blockDescriptorForUserPtr->prev = nullptr;
			insertFront2(&m_outstandingBlocks, &blockDescriptorForUserPtr);
			
			std::cout << "\n";
			std::cout << "in _alloc in if >0  calling deleteMe blockDescriptorForUserPtr from free list> deleting " << blockDescriptorForUserPtr << "\n";
			std::cout << "in _alloc in if >0  passing free list to deleteMe() " << m_freeBlocks << "\n";
			std::cout << "\n";

			deleteMe4(&m_freeBlocks, blockDescriptorForUserPtr);
		}
		else {
			std::cout << "NOW IN ELSE OF ALLOC " << &blockDescriptorForUserPtr;
			insertFront2(&m_outstandingBlocks, &blockDescriptorForUserPtr);
		}
	}
	else {
		std::cout << "no node found " << blockDescriptorForUserPtr << "\n";
		return (void*)blockDescriptorForUserPtr;
	}
	return (void*)userPtr;
}

void * HeapManager::_alloc6(size_t i_bytes, unsigned int i_alignment)
{
	BlockDescriptor* blockDescriptorForUserPtr = nullptr;
	size_t *userPtr = nullptr;
	std::cout << "\n";
	std::cout << "in _alloc BDforUserPt at start of function call: " << blockDescriptorForUserPtr << "\n";

	size_t padding = 0;//set by find2()
	BlockDescriptor* foundNode = find3(i_bytes, i_alignment);//=blockDescriptorForUserPtr

	std::cout << "in _alloc FoundNode after find(): " << foundNode << "\n";

	if (foundNode != nullptr) {
		std::cout << "\n";
		std::cout << "in _alloc in if !=null foundNode: " << foundNode << " blocksize: " << foundNode->m_sizeBlock << "\n";

		size_t blockDescriptorSize = sizeof(BlockDescriptor);

		size_t alignedSize = alignSize(i_bytes);
		size_t sizeDifference = foundNode->m_sizeBlock - alignedSize;
		userPtr = reinterpret_cast<size_t*>((size_t)foundNode + blockDescriptorSize);

		std::cout << "in _alloc in if !=null userPtr " << userPtr << "\n";

		if (sizeDifference > 0) {
			std::cout << "\n";

			BlockDescriptor* newFreeBlock = reinterpret_cast<BlockDescriptor*>((size_t)userPtr + alignedSize);//could split into requested and padding
			blockDescriptorForUserPtr = foundNode;
			blockDescriptorForUserPtr->m_sizeBlock = alignedSize;
			newFreeBlock->m_sizeBlock = sizeDifference;
			std::cout << "in _alloc in if >0 newFreeBlockBD " << newFreeBlock << "\n" << "in _alloc in if >0 newFreeBlockBD's sizeDifference " << newFreeBlock->m_sizeBlock << "\n";
			std::cout << "in _alloc in if >0  calling insertFront newFreeBlock to free list " << newFreeBlock << "\n";
			std::cout << "in _alloc in if >0  free list>  " << m_freeBlocks << "\n";
			newFreeBlock->next = nullptr;
			newFreeBlock->prev = nullptr;
			//insertFront2(&m_freeBlocks, &newFreeBlock);
			//insertInAscendingOrderBySize1(m_freeBlocks, newFreeBlock);
			//insertInAscendingOrderBySize4(&m_freeBlocks, newFreeBlock);

			std::cout << "\n";
			std::cout << "in _alloc in if >0  calling insertFront blockDescriptorForUserPtr to outstanding list> adding " << blockDescriptorForUserPtr << "\n";
			std::cout << "in _alloc in if >0  outstanding list>  " << m_outstandingBlocks << "\n";
			blockDescriptorForUserPtr->next = nullptr;
			blockDescriptorForUserPtr->prev = nullptr;
			//insertFront2(&m_outstandingBlocks, &blockDescriptorForUserPtr);
			//insertInAscendingOrderBySize1(m_outstandingBlocks, blockDescriptorForUserPtr);
			//insertInAscendingOrderBySize4(&m_freeBlocks, newFreeBlock);

			std::cout << "\n";
			std::cout << "in _alloc in if >0  calling deleteMe blockDescriptorForUserPtr from free list> deleting " << blockDescriptorForUserPtr << "\n";
			std::cout << "in _alloc in if >0  passing free list to deleteMe() " << m_freeBlocks << "\n";
			std::cout << "\n";

			//deleteMe4(&m_freeBlocks, blockDescriptorForUserPtr);
		}
		else {
			std::cout << "NOW IN ELSE OF ALLOC " << &blockDescriptorForUserPtr;
			insertFront2(&m_outstandingBlocks, &blockDescriptorForUserPtr);
		}
	}
	else {
		std::cout << "no node found " << blockDescriptorForUserPtr << "\n";
		return (void*)blockDescriptorForUserPtr;
	}
	return (void*)userPtr;
}


void * HeapManager::_alloc7(size_t i_bytes, unsigned int i_alignment)
{
	BlockDescriptor* blockDescriptorForUserPtr = nullptr;
	size_t *userPtr = nullptr;
	std::cout << "\n";
	std::cout << "in _alloc BDforUserPt at start of function call: " << blockDescriptorForUserPtr << "\n";

	size_t padding = 0;//set by find2()
	BlockDescriptor* foundNode = find4(i_bytes, i_alignment);//=blockDescriptorForUserPtr

	std::cout << "in _alloc FoundNode after find(): " << foundNode << "\n";

	if (foundNode != nullptr) {
		std::cout << "\n";
		std::cout << "in _alloc in if !=null foundNode: " << foundNode << " blocksize: " << foundNode->m_sizeBlock << "\n";

		size_t blockDescriptorSize = sizeof(BlockDescriptor);

		size_t alignedSize = alignSize(i_bytes);
		size_t sizeDifference = foundNode->m_sizeBlock - alignedSize;
		userPtr = reinterpret_cast<size_t*>((size_t)foundNode + blockDescriptorSize);

		std::cout << "in _alloc in if !=null userPtr " << userPtr << " blocksize in blockDescriptorForUserPtr (not set yet): \n";

		if (sizeDifference > 0) {
			std::cout << "\n";

			BlockDescriptor* newFreeBlock = reinterpret_cast<BlockDescriptor*>((size_t)userPtr + alignedSize);//could split into requested and padding
			blockDescriptorForUserPtr = foundNode;
			blockDescriptorForUserPtr->m_sizeBlock = alignedSize;
			newFreeBlock->m_sizeBlock = sizeDifference;
			std::cout << "in _alloc in if >0  BD for userptr = foundNode  " << blockDescriptorForUserPtr << "\n";
			std::cout << "in _alloc in if >0  BD for userptr m_sizeBlock  " << blockDescriptorForUserPtr->m_sizeBlock << "\n";
			std::cout << "in _alloc in if >0 newFreeBlockBD " << newFreeBlock << "\n" << "in _alloc in if >0 newFreeBlockBD's m_sizeBlock " << newFreeBlock->m_sizeBlock << "\n";
			std::cout << "in _alloc in if >0  calling insertFront newFreeBlock to free list " << newFreeBlock << "\n";
			std::cout << "in _alloc in if >0  free list>  " << m_freeBlocks << "\n";
			//newFreeBlock->next = nullptr;
			//newFreeBlock->prev = nullptr;
			//insertFront2(&m_freeBlocks, &newFreeBlock);
			//insertInAscendingOrderBySize1(m_freeBlocks, newFreeBlock);
			
			//insertInAscendingOrderBySize6(m_freeBlocks, newFreeBlock);
			//insertInAscendingOrderBySize5(&m_freeBlocks, newFreeBlock);
			//insertInAscendingOrderBySize7(&m_freeBlocks, newFreeBlock);
			insertInAscendingOrderByAddress(&m_freeBlocks, newFreeBlock);
			
			std::cout << "in _alloc in if >0  printing free list after insert>  " << m_freeBlocks << "\n";
			printList(m_freeBlocks);

			std::cout << "\n";
			std::cout << "in _alloc in if >0  calling insertFront blockDescriptorForUserPtr to outstanding list> adding " << blockDescriptorForUserPtr << "\n";
			std::cout << "in _alloc in if >0  outstanding list>  " << m_outstandingBlocks << "\n";
			//blockDescriptorForUserPtr->next = nullptr;
			//blockDescriptorForUserPtr->prev = nullptr;
			//insertFront2(&m_outstandingBlocks, &blockDescriptorForUserPtr);
			//insertInAscendingOrderBySize1(m_outstandingBlocks, blockDescriptorForUserPtr);
			//insertInAscendingOrderBySize5(&m_outstandingBlocks, blockDescriptorForUserPtr);

			std::cout << "\n";
			std::cout << "in _alloc in if >0  calling deleteMe blockDescriptorForUserPtr from free list> deleting " << blockDescriptorForUserPtr << "\n";
			std::cout << "in _alloc in if >0  passing free list to deleteMe() " << m_freeBlocks << "\n";
			std::cout << "\n";

			//deleteMe4(&m_freeBlocks, blockDescriptorForUserPtr);
			//deleteMe5(&m_freeBlocks, blockDescriptorForUserPtr);
			deleteMe6(&m_freeBlocks, blockDescriptorForUserPtr);

			//insertInAscendingOrderBySize5(&m_outstandingBlocks, blockDescriptorForUserPtr);
			//insertInAscendingOrderBySize7(&m_outstandingBlocks, blockDescriptorForUserPtr);
			insertInAscendingOrderByAddress(&m_outstandingBlocks, blockDescriptorForUserPtr);
		}
		else {
			std::cout << "NOW IN ELSE OF ALLOC " << &blockDescriptorForUserPtr;
			insertFront2(&m_outstandingBlocks, &blockDescriptorForUserPtr);
		}
	}
	else {
		std::cout << "no node found " << blockDescriptorForUserPtr << "\n";
		return (void*)blockDescriptorForUserPtr;
	}
	return (void*)userPtr;
}

void HeapManager::_free(void * i_ptr)
{
	std::cout << "\n**********\n ";
	std::cout << "in _free() i_ptr " <<i_ptr<<"\n";
	std::cout << "in _free() cast to BD* (size_t) i_ptr - sizeof(BD)" << reinterpret_cast<BlockDescriptor*>( (size_t)i_ptr - sizeof(BlockDescriptor)) << "\n";
	BlockDescriptor * blockDescriptorForUserPtr = reinterpret_cast<BlockDescriptor*>((size_t)i_ptr - sizeof(BlockDescriptor));
	std::cout << "in _free() blockDescriptorForUserPtr " << blockDescriptorForUserPtr << "\n";

	//deleteMe5(&m_outstandingBlocks, blockDescriptorForUserPtr);
	deleteMe6(&m_outstandingBlocks, blockDescriptorForUserPtr);
	//insertInAscendingOrderBySize7(&m_freeBlocks, blockDescriptorForUserPtr);
	insertInAscendingOrderByAddress(&m_freeBlocks, blockDescriptorForUserPtr);

	std::cout << "in _free() printing freeList \n";
	printList(m_freeBlocks);
	std::cout << "in _free() printing outstanding list \n";
	printList(m_outstandingBlocks);

	_coalesce(blockDescriptorForUserPtr, (size_t*) i_ptr);

	//calculate BDaddress
	//delete from outstanding
	//insert in freelist
	printList(m_freeBlocks);
	printList(m_outstandingBlocks);
}


void HeapManager::_coalesce(BlockDescriptor * pThisBlock, size_t* pUserPtr)//pThisBlock is the current blockdescriptor being freed(inserted into the freeList)
{
	//called in _free()

	std::cout << "\n in _coalesce() pThisBlock " << pThisBlock <<"\n";
	std::cout << "in _coalesce() pUserPtr " << pUserPtr << "\n";
	std::cout << "in _coalesce() pUserPtr req size " << pThisBlock->m_sizeBlock << "\n";
	//if userptr+BD->m_blocksize == bd->next
		
	BlockDescriptor* pCompareBlock = reinterpret_cast<BlockDescriptor*>((size_t)pUserPtr + pThisBlock->m_sizeBlock);
	std::cout << "in _coalesce() compareBlock = pUserPtr + memoryblock " << pCompareBlock << "\n";

	BlockDescriptor * pNextBlock = pThisBlock->next;
	std::cout << "in _coalesce() pNextBlock " << pNextBlock << "\n";

	if (pNextBlock == pCompareBlock) {

		//merging thisBlock with nextBlock
		pThisBlock->m_sizeBlock = pThisBlock->m_sizeBlock + pThisBlock->next->m_sizeBlock;

		//if (pThisBlock->next->next != nullptr) {
		if (pThisBlock->next->next == nullptr) {
			pThisBlock->next = nullptr;
		} else {
			pThisBlock->next = pThisBlock->next->next;
			pThisBlock->next->next->prev = pThisBlock;
		}		
						
		deleteMe6(&m_freeBlocks, pNextBlock);
	}

	std::cout << "\n in _coalesce() pThisBlock " << pThisBlock << "\n";
	if (pThisBlock->prev != nullptr) {
		if (pThisBlock == pThisBlock->prev->next) {
			
			//merging previous Block with this block
			if (pThisBlock->next == nullptr) {
				pThisBlock->prev->next = nullptr;
			}
			else {
				pThisBlock->prev->next = pThisBlock->next;
				pThisBlock->next->prev = pThisBlock->prev;
			}
			pThisBlock->prev->m_sizeBlock = pThisBlock->prev->m_sizeBlock + pThisBlock->m_sizeBlock;
			deleteMe6(&m_freeBlocks, pThisBlock);
		}
	}

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
