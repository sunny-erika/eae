#include <conio.h>
#include "../HeapManager.h"
// yes, i'm too lazy to put this in a header file
extern bool HeapManager_UnitTest();



void main(int i_argc, char ** i_argl)
{

	HeapManager * heapMgr = HeapManager::create(NULL, 100, 0);
	//HeapManager_UnitTest();
	_getch();
}