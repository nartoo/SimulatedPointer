//头文件包含的顺序很重要，在两个头文件中分别不包含彼此但有相互引用
//的情况下，Space.h对Chain.h的依赖比反之更强。在目前这种包含关系下，编译
//产生的错误跟之前的错误一样，即在两个头文件都彼此包含的情况下编译产生的错误。
//这也就是说，在头文件和源文件都包含了相关文件的情况下，编译器选择了按源文件中的包含顺序
//来执行？那我现在把源文件中的相关头文件注释掉，然后在两个自编头文件中包含彼此，会怎么样？
//原文件一注释掉就划红线，所以不能这样。现在搞清楚了一个关系，同一个项目中的头文件，只需要
//在源文件中包含就行了，但这要注意顺序！

//不得不注意，SimChain类和SimSpace类中都有一个first变量，应该区分清楚，
//SimChaim.first初始化为-1，SimSpace初始化为0。
//这是很自然的，从各个类的结构中看，实例化后，可用空间充满自由节点，
//它的first理应指向第一个节点（first=0）；而SimChain链表还没有节点，所以它的first=-1。

#include <iostream>
#include "SimulChain.h"
#include "SimulSpace.h"
#include "Xcept.h"

using namespace std;

SimSpace<int> SimChain<int>::S; //实例化可用空间S（调用SimSpace类构造函数），
								//这时存在一个足够大的数组，存放很多节点,
								//每个节点的link已经在构造函数中指定，
								//第0个节点node[0]的link部分是1，...

void main(void)
{
	int x;
	SimChain<int> c;
	cout << "Chain length is" << c.Length() << endl;
	c.Insert(0, 2).Insert(1, 6);
	cout << "Chain length is" << c.Length() << endl;
	c.Find(1, x);
	cout << "First element is" << x << endl;
	c.Delete(1, x);
	cout << "Deleted" << x << endl;
	cout << "New length is" << c.Length() << endl;
	cout << "Position of 2 is" << c.Search(2) << endl; //此处返回了0，表示不已经在链表中
	cout << "Position of 6 is" << c.Search(6) << endl;
	c.Insert(0, 9).Insert(1, 8).Insert(2, 7);
	cout << "Current chain is" << c << endl;
	cout << "Its length is" << c.Length() << endl;
	cout << "Position of 2 is" << c.Search(2) << endl;
	cout << "Position of 6 is" << c.Search(6) << endl;
}