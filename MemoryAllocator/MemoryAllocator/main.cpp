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

	
	const size_t sizeHeap = 1024 * 1024;
	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	assert(SysInfo.dwPageSize > 0);
	size_t sizeHeapInPageMultiples = SysInfo.dwPageSize * ((sizeHeap + SysInfo.dwPageSize) / SysInfo.dwPageSize);
	void* pHeapMemory = VirtualAlloc(NULL, sizeHeapInPageMultiples, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	
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

	HeapManager * pHeapManagerNew = new HeapManager(pHeapMemory, sizeHeapInPageMultiples);
	//HeapManager * pHeapManager = HeapManager::create(pHeapMemory, sizeHeap, numDescriptors);//from unit test


	std::cout << sizeHeapInPageMultiples << "\n";
	std::cout << pHeapManagerNew->m_pHeapMemory << "\n";
	std::cout << pHeapManagerNew->m_freeBlocks->m_pBlockStartAddr << "\n";
	std::cout << pHeapManagerNew->m_freeBlocks->m_sizeBlock << "\n";
	std::cout << "call to malloc:\n";

	//pHeapManagerNew->_alloc(20, 4);// void * HeapManager::_alloc(size_t i_bytes, unsigned int i_alignment)//cpp
	//void * pPtr = pHeapManager->_alloc(pHeapManager, sizeAlloc, alignment);//from unit test
	//pHeapManagerNew->_alloc(1052674, 4);
	//pHeapManagerNew->_alloc1(1052674, 4);
	//pHeapManagerNew->_alloc1(20, 4);

	//void* allocatedMemoryPtr = pHeapManagerNew->_alloc1(20, 4);
	void* allocatedMemoryPtr = pHeapManagerNew->_alloc1(1052674, 4);
	std::cout << "in main - returned pointer " << allocatedMemoryPtr << "\n";


	//void * pT1 = malloc(1);
	//void * pT2 = malloc(1);
	//std::cout << pT1;
	//std::cout << pT2;
	//pT1 = pT2;
	//std::cout << pT1;
	//std::cout << pT2;



	/*
	HeapManager* heapMgr = new HeapManager (4);
	std::cout << heapMgr->test;
	heapMgr->test = 5;
	std::cout << heapMgr->test;
	std::cout << heapMgr;
	*/

	/*
	HeapManager* heapMgr = new HeapManager();
	std::cout << heapMgr->test;
	*/

	

	_getch();
	
}