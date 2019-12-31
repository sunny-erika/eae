#pragma once

class HeapManager
{
	void* m_pHeapMemory;
	size_t m_HeapMemorySize;
	unsigned int m_numDescriptors;
	//List of allocated blocks
	//list of block descriptors
	//list of free blocks


public:

	HeapManager();
	HeapManager(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors);

	static HeapManager* create(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors);

	// allocation
	//allocates memory. named with a underscore to resolve name clash 
	void* _alloc(size_t i_bytes);

	// allocation with alignment. returns a block of memory with a given alignment
	void* _alloc(size_t i_bytes, unsigned int i_alignment);


	// frees an allocation
	void _free(void* i_ptr);

	// attempt to merge abutting blocks.
	void collect();

	//tells us
	//size of the largest free block
	size_t getLargestFreeBlock();

	//how much total memory is available
	size_t getTotalFreeMemory();

	//if a pointer is within this HeapManagers managed memory
	bool Contains(void * i_ptr);

	//if this pointer is an outstanding allocation from this block
	bool IsAllocated(void* i_ptr);


	//debugging helper functions 
	//to show us all the free blocks.
	void ShowFreeBlocks();

	//to show us all the outstanding blocks.
	void ShowOutstandingAllocations(const HeapManager * i_pManager);

};

