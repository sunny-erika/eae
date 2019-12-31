#include "HeapManager.h"
#include <malloc.h>
#include <stdio.h>


//constructor
HeapManager::HeapManager(){
	m_pHeapMemory = nullptr;
	m_HeapMemorySize = 0;
	m_numDescriptors = 0;
}

HeapManager::HeapManager(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors) {
	m_pHeapMemory = i_pHeapMemory;
	m_HeapMemorySize = i_HeapMemorySize;
	m_numDescriptors = i_numDescriptors;
}

//destructor


//block descriptor
struct BlockDescriptor
{
	void * m_pBlockStartAddr; // pointer to the block of memory this BlockDescriptor describes
	size_t m_sizeBlock; // size of that block of memory
};

//TODO
/*
static HeapManager* create(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors);
void* _alloc(size_t i_bytes);
void* _alloc(size_t i_bytes, unsigned int i_alignment);
void _free(void* i_ptr);
void collect();
size_t getLargestFreeBlock();
size_t getTotalFreeMemory();
bool Contains(void * i_ptr);
bool IsAllocated(void* i_ptr);
void ShowFreeBlocks();
void ShowOutstandingAllocations(const HeapManager * i_pManager);
*/

//constructor,destructor
//functions


static HeapManager* create(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors) {
		
	//TODO
}



//takes as input a number of bytes, returns a pointer to a block of memory of that size
void* _alloc(size_t i_bytes) {

	//TODO

}

void* _alloc(size_t i_bytes, unsigned int i_alignment) {
	//TODO
}

void _free(void* i_ptr) {
	//TODO
}

void collect() {
	//TODO
}

size_t getLargestFreeBlock() {
	//TODO
}

size_t getTotalFreeMemory() {
	//TODO
}

bool Contains(void * i_ptr) {
	//TODO
}

bool IsAllocated(void* i_ptr) {
	//TODO
}

void ShowFreeBlocks() {
	//TODO
}

void ShowOutstandingAllocations(const HeapManager * i_pManager) {
	//TODO
}


