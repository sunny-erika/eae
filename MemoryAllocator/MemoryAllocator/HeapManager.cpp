
#include "HeapManager.h"

HeapManager::~HeapManager()
{
}

void HeapManager::initialize(void * i_pHeapMemory, size_t i_HeapMemorySize)
{
}

void * HeapManager::_alloc(size_t i_bytes)
{
	return nullptr;
}

void * HeapManager::_alloc(size_t i_bytes, unsigned int i_alignment)
{
	return nullptr;
}

void HeapManager::_free(void * i_ptr)
{
}

void HeapManager::collect()
{
}

size_t HeapManager::getLargestFreeBlock()
{
	return size_t();
}

size_t HeapManager::getTotalFreeMemory()
{
	return size_t();
}

bool HeapManager::Contains(void * i_ptr)
{
	return false;
}

bool HeapManager::IsAllocated(void * i_ptr)
{
	return false;
}

void HeapManager::ShowFreeBlocks()
{
}

void HeapManager::ShowOutstandingAllocations(const HeapManager * i_pManager)
{
}
