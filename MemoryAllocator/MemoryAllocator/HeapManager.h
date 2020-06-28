#pragma once
#ifndef HEAP_MANAGER_H
#define HEAP_MANAGER_H

#define ALIGNMENT 4
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))
#define SIZE_T_SIZE (ALIGN(sizeof(size_t))) // header size

class HeapManager

	
{
	//BlockDescriptor * m_freeBlocks;//freelist
	//BlockDescriptor * m_oustandingBlocks;//allocated
	//list of block descriptors - 
	//need block descriptors for free blocks & outstanding(allocated) blocks

	//HeapManager() {};

public:
	void* m_pHeapMemory = nullptr;
	size_t m_HeapMemorySize;
	int test =8;

	
	struct BlockDescriptor
	{
		void* m_pBlockStartAddr; // pointer to the block of memory this BlockDescriptor describes (not needed since block is right next to it
		size_t m_sizeBlock; // size of that block of memory
		BlockDescriptor* next;
		BlockDescriptor* prev;
	};
	
	/*
	typedef struct BlockDescriptor
	{
		void* m_pBlockStartAddr; // pointer to the block of memory this BlockDescriptor describes
		size_t m_sizeBlock; // size of that block of memory
		BlockDescriptor* next;
		BlockDescriptor* prev;
	}BlockDescriptor1;
	*/

	BlockDescriptor * m_freeBlocks = nullptr;//freelist - queried in main
	BlockDescriptor * m_outstandingBlocks;//allocated 
	
	HeapManager();
	HeapManager(void* i_pHeapMemory, size_t i_HeapMemorySize);
	HeapManager(int test);
	~HeapManager();
	   
	static HeapManager* create(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors);

	void initialize(void* i_pHeapMemory, size_t i_HeapMemorySize);
	void find(size_t size, size_t alignment, size_t &padding, BlockDescriptor* &previousNode, BlockDescriptor* &foundNode);
	void find1(size_t size, size_t alignment, size_t &padding, BlockDescriptor* &previousNode, BlockDescriptor* &foundNode);
	void find2(size_t size, size_t alignment, size_t &padding, BlockDescriptor* &previousNode, BlockDescriptor* &foundNode);
	BlockDescriptor * find3(size_t size, size_t alignment);
	BlockDescriptor * find4(size_t size, size_t alignment);

	//size_t * find4();
	size_t calculateAlignment(size_t baseAddress, size_t alignment);
	size_t alignSize(size_t requiredBytes);

	
	//doubly
	void insert(BlockDescriptor* head, BlockDescriptor* previousNode, BlockDescriptor* newNode);
	void remove(BlockDescriptor* head, BlockDescriptor* deleteNode);


	void insertFront(BlockDescriptor ** head, BlockDescriptor* newNode);
	void insertFront1(BlockDescriptor ** head, BlockDescriptor** newNode);
	void insertFront2(BlockDescriptor ** head, BlockDescriptor** newNode);
	//void insertInAscendingOrderBySize(BlockDescriptor ** head, BlockDescriptor ** newNode);
	void insertInAscendingOrderBySize(BlockDescriptor *& head, BlockDescriptor *& newNode);
	void insertInAscendingOrderBySize1(BlockDescriptor *& head, BlockDescriptor *& newNode);
	void insertInAscendingOrderBySize2(BlockDescriptor ** head, BlockDescriptor * newNode);
	void insertInAscendingOrderBySize3(BlockDescriptor ** head, BlockDescriptor * newNode);
	void insertInAscendingOrderBySize4(BlockDescriptor ** head, BlockDescriptor * newNode);
	void insertInAscendingOrderBySize5(BlockDescriptor ** head, BlockDescriptor * newNode);
	void insertInAscendingOrderBySize6(BlockDescriptor *& head, BlockDescriptor * newNode);

	void deleteFront(BlockDescriptor ** head);
	void deleteLast(BlockDescriptor ** head);
	void deleteMe(BlockDescriptor ** head, BlockDescriptor *deleteMe);
	void deleteMe2(BlockDescriptor ** head, BlockDescriptor **deleteMe);
	void deleteMe3(BlockDescriptor ** head, BlockDescriptor *deleteMe);
	void deleteMe4(BlockDescriptor ** head, BlockDescriptor *deleteMe);
	void deleteMe5(BlockDescriptor ** head, BlockDescriptor *deleteMe);
	void deleteNode(BlockDescriptor** head, BlockDescriptor * node);
	void deleteNode1(BlockDescriptor*& head, BlockDescriptor * node);
	void printList(BlockDescriptor* node);
	void testingDelete();
	void testingInsert();
	void removeFromList(BlockDescriptor*& head, BlockDescriptor * node);
	void removeFromList1(BlockDescriptor** head, BlockDescriptor * node);
	
	//singly
	void s_insert(BlockDescriptor* head, BlockDescriptor* previousNode, BlockDescriptor* newNode);
	void s_remove(BlockDescriptor* head, BlockDescriptor* previousNode, BlockDescriptor* deleteNode);

	
	// allocation
	//allocates memory. named with a underscore to resolve name clash 
	void* _alloc(size_t i_bytes);

	// allocation with alignment. returns a block of memory with a given alignment
	void* _alloc(size_t i_bytes, unsigned int i_alignment);
	void* _alloc1(size_t i_bytes, unsigned int i_alignment);
	void* _alloc2(size_t i_bytes, unsigned int i_alignment);
	void* _alloc3(size_t i_bytes, unsigned int i_alignment);
	void* _alloc4(size_t i_bytes, unsigned int i_alignment);
	void* _alloc5(size_t i_bytes, unsigned int i_alignment);
	void* _alloc6(size_t i_bytes, unsigned int i_alignment);
	void* _alloc7(size_t i_bytes, unsigned int i_alignment);
	void* _alloc(HeapManager * i_heapManager, size_t i_bytes, unsigned int i_alignment);
	void * alloc(HeapManager * i_pManager, size_t i_size);
	void * alloc(HeapManager * i_pManager, size_t i_size, unsigned int i_alignment);

	void Destroy(HeapManager * i_pManager);

	// frees an allocation
	void _free(void* i_ptr);
	bool free(HeapManager * i_pManager, void * i_ptr);

	// attempt to merge abutting blocks.
	void collect();
	void Collect(HeapManager * i_pManager);

	//tells us
	//size of the largest free block
	size_t getLargestFreeBlock();
	size_t GetLargestFreeBlock(const HeapManager * i_pManager);

	//how much total memory is available
	size_t getTotalFreeMemory();
	size_t GetTotalFreeMemory(const HeapManager * i_pManager);

	//if a pointer is within this HeapManagers managed memory
	bool Contains(void * i_ptr);
	bool Contains(const HeapManager * i_pManager, void * i_ptr);

	//if this pointer is an outstanding allocation from this block
	bool IsAllocated(void* i_ptr);
	bool IsAllocated(const HeapManager * i_pManager, void * i_ptr);


	//debugging helper functions 
	//to show us all the free blocks.
	void ShowFreeBlocks();
	void ShowFreeBlocks(const HeapManager * i_pManager);

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