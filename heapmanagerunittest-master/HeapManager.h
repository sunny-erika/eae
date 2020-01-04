#pragma once

class HeapManager
{
	void* m_pHeapMemory;
	size_t m_HeapMemorySize;
	unsigned int m_numDescriptors;

	struct BlockDescriptor
	{
		//void* m_pBlockStartAddr; // pointer to the block of memory this BlockDescriptor describes - only needed for pool of blockdescriptors
		size_t m_sizeBlock; // size of that block of memory
		BlockDescriptor* next; 
		BlockDescriptor* prev;
	};

	BlockDescriptor * m_freeBlocks;
	BlockDescriptor * m_oustandingBlocks;
	//list of block descriptors - 
	//need block descriptors for free blocks & outstanding(allocated) blocks
	


public:

	HeapManager();
	HeapManager(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors);
	~HeapManager();

	HeapManager(void * i_pHeapMemory, size_t i_HeapMemorySize);

	//static HeapManager* create(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors);
	static HeapManager* create(void* i_pHeapMemory, size_t i_HeapMemorySize);

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

