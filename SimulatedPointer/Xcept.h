#pragma once
#include <iostream>
using namespace std;
// �ڴ治��
class NoMem
{
public:
	NoMem() {}
};
// ʹnew����NoMem�쳣������xalloc�쳣
void my_new_handler()
{
	throw NoMem();  //ʲô��˼
}
new_handler Old_Handler_ = set_new_handler(my_new_handler);

class OutOfBounds
{
public:
	OutOfBounds() {}
};