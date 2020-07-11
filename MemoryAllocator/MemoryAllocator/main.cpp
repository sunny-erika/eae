#include <conio.h>
#include "HeapManager.h"
#include <iostream>
#include <Windows.h>
#include <assert.h>

//void main(int i_argc, char ** i_argl)
int main()
{
	//HeapManager_UnitTest();
	//HeapManager * heapMgr = HeapManager::create(NULL, 100, 0);

	
	
	//const size_t sizeHeap = 1024 * 1024;
	const size_t sizeHeap = 256;
	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	assert(SysInfo.dwPageSize > 0);
	size_t sizeHeapInPageMultiples = SysInfo.dwPageSize * ((sizeHeap + SysInfo.dwPageSize) / SysInfo.dwPageSize);
	//void* pHeapMemory = VirtualAlloc(NULL, sizeHeapInPageMultiples, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	

	//HeapManager * pHeapManager = HeapManager::create(pHeapMemory, 512, 0);
	//HeapManager * pHeapManager = HeapManager::create(pHeapMemory, sizeHeapInPageMultiples, 0);
	//static HeapManager* create(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors);

	//std::cout << pHeapManager->test
	//std::cout << pHeapManager->m_freeBlocks;

	//std::cout << pHeapManager->m_HeapMemorySize;
	/*
    std::cout << pHeapManager->m_pHeapMemory;
    std::cout << pHeapMemory;
	std::cout << pHeapManager->m_freeBlocks->m_pBlockStartAddr;
	*/
	//pHeapManager->_alloc(20, 4);

	//HeapManager * pHeapManagerNew = new HeapManager(pHeapMemory, sizeHeapInPageMultiples);
	HeapManager * pHeapManagerNew = HeapManager::_create1(sizeHeap);//from unit test
	//HeapManager hmgr(sizeHeap, ++pHeapManagerNew, sizeHeapInPageMultiples);

	std::cout << "\n in main\n";

	//std::cout << "\n in main pHeapMemory " << pHeapMemory;
	std::cout << "\n in main pHeapManagerNew " << pHeapManagerNew;
	std::cout << "\n in main sizeHeapInPageMultiples " << sizeHeapInPageMultiples;
	std::cout << "\n in main pHeapManagerNew->m_pHeapMemory " <<pHeapManagerNew->m_pHeapMemory ;
	std::cout << "\n in main pHeapManagerNew->m_freeBlocks " << pHeapManagerNew->m_freeBlocks;
	std::cout << "\n in main pHeapManagerNew->m_freeBlocks->m_pBlockStartAddr "<< pHeapManagerNew->m_freeBlocks->m_pBlockStartAddr ;
	std::cout << "\n in main HeapManagerNew->m_freeBlocks->m_sizeBlock " << pHeapManagerNew->m_freeBlocks->m_sizeBlock;
	std::cout << "\n*********************************\n";
	std::cout << "\n";

	//pHeapManagerNew->_alloc(20, 4);// void * HeapManager::_alloc(size_t i_bytes, unsigned int i_alignment)//cpp
	//void * pPtr = pHeapManager->_alloc(pHeapManager, sizeAlloc, alignment);//from unit test
	//pHeapManagerNew->_alloc(1052674, 4);
	//pHeapManagerNew->_alloc1(1052674, 4);
	//pHeapManagerNew->_alloc1(20, 4);

	//pHeapManagerNew->testingInsert();
	std::cout << "\n";
	//pHeapManagerNew->testingDelete();
	std::cout << "\n";


	
	
	
	
	//*****************************************
	//1st alloc
	std::cout << "1st alloc call - requested size is 26" << "\n";
	void* allocatedMemoryPtr = pHeapManagerNew->_alloc7(26, 4);
	std::cout << "in main - returned pointer of 1st alloc call " << allocatedMemoryPtr << "\n";
	std::cout << "****************** " << "\n";
	std::cout << "\n";
	std::cout << "\n ****************** " << "\n";
	std::cout << "printing free list " << "\n";
	pHeapManagerNew->printList(pHeapManagerNew->m_freeBlocks);
	std::cout << "\n printing outstanding list " << "\n";
	pHeapManagerNew->printList(pHeapManagerNew->m_outstandingBlocks);
	
	std::cout << "\n in main m_pBlockstartAddr " << pHeapManagerNew->m_freeBlocks->m_pBlockStartAddr ;
	std::cout << "\n in main m_sizeBlock " << pHeapManagerNew->m_freeBlocks->m_sizeBlock;
	
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "*********************************\n";
	//*****************************************
	//2nd alloc
	std::cout << "2nd alloc call - requested size is 2" << "\n";

	void* allocatedMemoryPtr2 = pHeapManagerNew->_alloc7(2, 4);
	std::cout << "in main - returned pointer of 2nd alloc call " << allocatedMemoryPtr2 << "\n";
	std::cout << "*********************************\n";
	std::cout << "\n";

	std::cout << "\n ****************** " << "\n";
	std::cout << "printing free list " << "\n";
	pHeapManagerNew->printList(pHeapManagerNew->m_freeBlocks);
	std::cout << "\n printing outstanding list " << "\n";
	pHeapManagerNew->printList(pHeapManagerNew->m_outstandingBlocks);
	std::cout << "\n in main m_pBlockstartAddr " << pHeapManagerNew->m_freeBlocks->m_pBlockStartAddr;
	std::cout << "\n in main m_sizeBlock " << pHeapManagerNew->m_freeBlocks->m_sizeBlock;
	
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "*********************************\n";
	//*****************************************
	//3rd alloc
	std::cout << "\n 3rd alloc call - requested size is 31" << "\n";

	void* allocatedMemoryPtr3 = pHeapManagerNew->_alloc7(31, 4);
	std::cout << "in main - returned pointer of 3rd alloc call " << allocatedMemoryPtr3 << "\n";
	std::cout << "*********************************\n";
	std::cout << "\n";

	std::cout << "\n ****************** " << "\n";
	std::cout << "printing free list " << "\n";
	pHeapManagerNew->printList(pHeapManagerNew->m_freeBlocks);
	std::cout << "\n printing outstanding list " << "\n";
	pHeapManagerNew->printList(pHeapManagerNew->m_outstandingBlocks);

	std::cout << "\n ****************** " << "\n";
	//*****************************************
	//freeing
	pHeapManagerNew->_free(allocatedMemoryPtr);//28
	//pHeapManagerNew->_free(allocatedMemoryPtr2);//4
	pHeapManagerNew->_free(allocatedMemoryPtr3);//32

	pHeapManagerNew->_free(allocatedMemoryPtr2);//4

	//pHeapManagerNew->removeFromList(pHeapManagerNew->m_freeBlocks, pHeapManagerNew->m_freeBlocks->next);
	//std::cout << "\n again printing free list " << "\n";
	//pHeapManagerNew->printList(pHeapManagerNew->m_freeBlocks);
	
	//std::cout << "\ntesting free list " << "\n";
	//pHeapManagerNew->testingDelete();
	//pHeapManagerNew->find3(20, 4);
	

	//void * pT1 = malloc(1);
	//void * pT2 = malloc(1);
	//std::cout << pT1;
	//std::cout << pT2;
	//pT1 = pT2;
	//std::cout << pT1;
	//std::cout << pT2;



	/*
	HeapManager* heapMgr = new HeapManager (4);
	std::cout << heapMgr->test << "\n";
	heapMgr->test = 5;
	std::cout << heapMgr->test << "\n";
	std::cout << heapMgr << "\n";
	*/

	/*
	HeapManager* heapMgr = new HeapManager();
	std::cout << heapMgr->test << "\n";
	*/

	
	

	_getch();
	
}