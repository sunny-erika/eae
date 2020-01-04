#pragma once
#ifndef HEAP_MANAGER_H
#define HEAP_MANAGER_H

class HeapManager
{
	void* m_pHeapMemory;
	size_t m_HeapMemorySize;


	struct BlockDescriptor
	{
		void* m_pBlockStartAddr; // pointer to the block of memory this BlockDescriptor describes
		size_t m_sizeBlock; // size of that block of memory
		BlockDescriptor* next;
		BlockDescriptor* prev;
	};

	//BlockDescriptor * m_freeBlocks;//freelist
	//BlockDescriptor * m_oustandingBlocks;//allocated
	//list of block descriptors - 
	//need block descriptors for free blocks & outstanding(allocated) blocks

	HeapManager() {};

public:

	BlockDescriptor * m_freeBlocks;//freelist
	BlockDescriptor * m_oustandingBlocks;

	~HeapManager();
	   
	static HeapManager* create(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors);

	void initialize(void* i_pHeapMemory, size_t i_HeapMemorySize);

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

	
		// Setter
	void setMemory(void* mAddress) {
		m_pHeapMemory = mAddress;
	}
	// Getter
	void* getMemory() {
		return m_pHeapMemory;
	}

};

#endif