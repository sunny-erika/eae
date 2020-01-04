
#include "HeapManager.h"
#include <Windows.h>
#include <malloc.h>
#include <stdio.h>

#include <algorithm>
#include <stdint.h>



//constructor




//destructor
HeapManager::~HeapManager() {
	//TODO
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
	HeapManager* o_pHeapManager = (HeapManager*) pHeapMemory;
	o_pHeapManager->initialize(i_pHeapMemory, i_HeapMemorySize);
	
	return o_pHeapManager;

	/*
	MyClass *objp = (MyClass*)malloc(sizeof(MyClass));*objp = MyClass();
*/
	
}

void HeapManager::initialize(void * i_pHeapMemory, size_t i_HeapMemorySize)
{
	m_pHeapMemory = i_pHeapMemory;
	m_HeapMemorySize = i_HeapMemorySize;
	m_freeBlocks = nullptr;
	m_oustandingBlocks = nullptr;
}





//doubly linked list
	//inserts node at the front of the list
/*
void insert_front(struct Node** head, int new_data)
{
	//allocate memory for New node
	struct Node* newNode = new Node();

	//assign data to new node
	newNode->data = new_data;

	//new node is head and previous is null, since we are adding at the front
	newNode->next = (*head);
	newNode->prev = NULL;

	//previous of head is new node
	if ((*head) != NULL)
		(*head)->prev = newNode;
	//head points to new node
	(*head) = newNode;
}
*/

/*
//insert a new node at the end of the list
void insert_end(struct Node** head, int new_data)
{
	//allocate memory for node
	struct Node* newNode = new Node;
	struct Node* last = *head; //set last node value to head

	//set data for new node
	newNode->data = new_data;

	//new node is the last node , so set next of new node to null
	newNode->next = NULL;

	//check if list is empty, if yes make new node the head of list
	if (*head == NULL) {
		newNode->prev = NULL;
		*head = newNode;
		return;
	}

	//otherwise traverse the list to go to last node
	while (last->next != NULL)
	last = last->next;

	//set next of last to new node
	last->next = newNode;

	//set last to prev of new node
	newNode->prev = last;
	return;
}*/



/* Given a node as prev_node, insert a new node after the given node */
/*
void insert_After(struct Node* prev_node, int new_data)
{

	//check if prev node is null
	if (prev_node == NULL) {
		cout << "Previous node is required , it cannot be NULL";
		return;
	}

	//allocate memory for new node
	struct Node* newNode = new Node;

	//assign data to new node
	newNode->data = new_data;

	//set next of newnode to next of prev node
	newNode->next = prev_node->next;

	//set next of prev node to newnode
	prev_node->next = newNode;

	//now set prev of newnode to prev node
	newNode->prev = prev_node;

	//set prev of new node's next to newnode
	if (newNode->next != NULL)
		newNode->next->prev = newNode;
}
*/

/* Given a node as next_node, insert a new node before the given node */
/*
void insertBefore(struct Node** head_ref, struct Node* next_node, int new_data)
{
	/*1. check if the given next_node is NULL 
	if (next_node == NULL) {
		printf("the given next node cannot be NULL");
		return;
	}

	/* 2. allocate new node 
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

	/* 3. put in the data 
	new_node->data = new_data;

	/* 4. Make prev of new node as prev of next_node 
	new_node->prev = next_node->prev;

	/* 5. Make the prev of next_node as new_node 
	next_node->prev = new_node;

	/* 6. Make next_node as next of new_node 
	new_node->next = next_node;

	/* 7. Change next of new_node's previous node 
	if (new_node->prev != NULL)
		new_node->prev->next = new_node;
	/* 8. If the prev of new_node is NULL, it will be
	   the new head node 
	else
		(*head_ref) = new_node;

}*/


/* Function to delete a node in a Doubly Linked List.
head_ref --> pointer to head node pointer.
del --> pointer to node to be deleted. */
/*
void deleteNode(Node** head_ref, Node* del)
{
	/* base case 
	if (*head_ref == NULL || del == NULL)
		return;

	/* If node to be deleted is head node 
	if (*head_ref == del)
		*head_ref = del->next;

	/* Change next only if node to be
	deleted is NOT the last node 
	if (del->next != NULL)
		del->next->prev = del->prev;

	/* Change prev only if node to be
	deleted is NOT the first node 
	if (del->prev != NULL)
		del->prev->next = del->next;

	/* Finally, free the memory occupied by del
	free(del);
	return;
}
*/

/*
void displayList(struct Node* node) {
	struct Node* last;

	while (node != NULL) {
		cout << node->data << "<==>";
		last = node;
		node = node->next;
	}

	if (node == NULL)
		cout << "NULL";
}*/

//takes as input a number of bytes, returns a pointer to a block of memory of that size
/*
void* HeapManager::_alloc(size_t i_bytes) {

	//TODO
	//first-fit allocation
	//returns the first free block which fits the size
	/*
	m_freeBlocks = m_pHeapMemory;

	while(block !=0 nullptr){
	    if (block->size < i_bytes){
		   block = block -> next;
		   continue;
		}
		//found block
		return block;
	}
	return nullptr;
	

}*/



