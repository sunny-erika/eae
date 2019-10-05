#pragma once

#include "Allocator.h"
#include <cassert> //assert

class Allocator
{

private: 
	m_totalSize;
	m_used = 0;

public:
	Allocator();
	~Allocator();
};



