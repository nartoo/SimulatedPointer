#pragma once
#include <iostream>
using namespace std;
// 内存不足
class NoMem
{
public:
	NoMem() {}
};
// 使new引发NoMem异常而不是xalloc异常
void my_new_handler()
{
	throw NoMem();  //什么意思
}
new_handler Old_Handler_ = set_new_handler(my_new_handler);

class OutOfBounds
{
public:
	OutOfBounds() {}
};