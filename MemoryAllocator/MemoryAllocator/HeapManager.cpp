
#include "HeapManager.h"
#include <Windows.h>

HeapManager::~HeapManager()
{
	m_pHeapMemory = nullptr;
	m_freeBlocks = nullptr;
	m_oustandingBlocks = nullptr;
}

HeapManager * HeapManager::create(void * i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors)
{
	const size_t 		sizeHeapManager = sizeof(HeapManager);//
	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	size_t sizeHeapInPageMultiples = SysInfo.dwPageSize * ((sizeHeapManager + SysInfo.dwPageSize) / SysInfo.dwPageSize);
	void* pHeapMemory = VirtualAlloc(NULL, sizeHeapInPageMultiples, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	HeapManager* o_pHeapManager = (HeapManager*)pHeapMemory;
	o_pHeapManager->initialize(i_pHeapMemory, i_HeapMemorySize);

	return o_pHeapManager;
}

void HeapManager::initialize(void * i_pHeapMemory, size_t i_HeapMemorySize)
{
	//m_pHeapMemory = i_pHeapMemory;
	//m_HeapMemorySize = i_HeapMemorySize;
	m_freeBlocks = nullptr;
	m_oustandingBlocks = nullptr;
}

void * HeapManager::_alloc(size_t i_bytes)
{
	return nullptr;
}

void * HeapManager::_alloc(size_t i_bytes, unsigned int i_alignment)
{
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
