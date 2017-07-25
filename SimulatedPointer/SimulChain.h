#pragma once
#include<iostream>
//#include"SimulSpace.h"  //这里包不包含都对下面SimChain类使用SimSpace类无帮助
                          //一直都是不会划红线但是编译会报奇怪的错误，
using namespace std;

template<class T> class SimSpace;	//在这里添加了这句，编译就没有报出那个错误了
									//但是类模板声明和定义不是应该放在一起的吗？

template<class T>
class SimChain 
{
public:
	SimChain() { first = -1; }
	~SimChain() { Destroy(); }
	void Destroy(); // 使表为空
	int Length() const;
	bool Find(int k, T& x) const;
	int Search(const T& x) const;
	SimChain<T>& Delete(int k, T& x);
	SimChain<T>& Insert(int k, const T& x);
	void Output(ostream& out) const;
private:
	int first; // 第一个节点的索引
	static SimSpace<T> S;
};

template<class T>
void SimChain<T>::Destroy()
{
	// 释放链表节点
	int next;
	while (first != -1)
	{
		next = S.node[first].link;  //next指向第二个节点
		S.Deallocate(first);
		first = next;
	}
}

template<class T>
int SimChain<T>::Length() const
{
	// 返回链表的长度。我们可以算出链表的长度，
	//但是无法计算出可用空间的长度？计算可用空间的长度也没有意义？
	int current = first, // 链节点的当前位置
		len = 0; //元素计数
	while (current != -1) 
	{
		current = S.node[current].link;
		len++;
	}
	return len;
}

template<class T>
bool SimChain<T>::Find(int k, T& x) const
{
	// 取第k个元素至x
	// 如果不存在第k个元素，函数返回false，否则返回true
	if (k < 1) return false;
	int current = first, // 链节点的当前位置
		index = 1; //当前节点的索引
	// 移动current至第k个节点
	while (index < k && current != -1) 
	{
		current = S.node[current].link;
		index++;
	}
	// 验证是否到达了第k个节点
	if (current != -1)
	{
		x = S.node[current].data;
		return true;
	}
	return false; // 不存在第k个元素
}

template<class T>
SimChain<T>& SimChain<T>::Delete(int k, T& x)
{
	// 把第k个元素取至x，然后删除第k个元素
	// 如果不存在第k个元素，则引发异常OutOfBounds
	if (k < 1 || first == -1)
		throw OutOfBounds(); // 不存在第k个元素
	// p最终将指向第k个节点
	int p = first;
	// 将p移动至第k个节点，并从链表中删除该节点
	if (k == 1) // p已经指向第k个节点
		first = S.node[first].link; // 从链表中删除
									//这里表明k与数值node中的下标i是没有必然联系的。
									//k==1定位到SimChain链表中的第一个节点，first指向这个链表
									//中的第一个节点，但是node[first]可以是数组中的任何位置的元素
	else 
	{ 
		// 使用q指向第k - 1个元素
		int q = first;
		for (int index = 1; index < k - 1 && q != -1; index++)
			q = S.node[q].link;
		// 验证第k个元素的存在性
		if (q == -1 || S.node[q].link == -1)
			throw OutOfBounds(); // 不存在第k个元素
		// 使p指向第k个元素
		p = S.node[q].link;
		// 从链表中删除第k个元素
		S.node[q].link = S.node[p].link;//再次强调，这里用p、q的目的之一是取出所要的节点在node
										//数组中的下标，传给Deallocate函数的也是这个下标,
										//从这里可以得到一条经验：传给SimSpace表相关操作
										//的参数应该都是node数组的下标。而k这里是SimChain链表
										//索引。
	}
		// 保存第k个元素并释放节点p
		x = S.node[p].data;
		S.Deallocate(p);  //释放这个已经删除的节点的目的就是为了让这个节点回归到
						  //可用空间表中。否则，它就处于“游离”状态，下次就没法使用，
						  //相当于“内存泄漏”了。
		return *this;
}

template<class T>
SimChain<T>& SimChain<T>::Insert(int k, const T& x)
{
	// 在第k个元素之后插入x
	// 如果不存在第k个元素，则引发异常OutOfBounds
	// 如果没有足够的空间，则传递NoMem异常
	if (k < 0)
		throw OutOfBounds();
	// 定义一个指针p，p最终将指向第k个节点
	int p = first;
	// 将p移向第k个节点
	for (int index = 1; index < k && p != -1; index++)
		p = S.node[p].link;
	// 验证第k个节点的存在性
	if (k > 0 && p == -1)
		throw OutOfBounds();
	// 为插入操作分配一个新节点
	int y = S.Allocate();
	S.node[y].data = x;
	// 向链表中插入新节点
	// 首先检查新节点是否要插到链表的首部
	if (k) 
	{
		//在p之后插入
		S.node[y].link = S.node[p].link;
		S.node[p].link = y;
	}
	else 
	{
		// 作为链表首节点
		S.node[y].link = first; first = y;
	}
	return *this;
}

template<class T>
int SimChain<T>::Search(const T& x) const
{
	// 寻找x，如果发现x，则返回x的地址
	// 如果x不在链表中，则返回0
	int current = first,  //链节点的当前位置
		index = 1; // current的索引
	while (current != -1 && S.node[current].data != x)
	{
		current = S.node[current].link;
		index++;
	}
	if (current != -1)
		return index;
	return 0;
}

template<class T>
void SimChain<T>::Output(ostream& out) const
{
	// 将链表元素送至输出流
	int current;
	for (current = first; current != -1; current = S.node[current].link)
		out << S.node[current].link <<":"<<S.node[current].data << " ";//输出link是为了方便
					                                        //比较link与插入序位k之间的不同
}

// 重载<<
template <class T>
ostream& operator<<(ostream& out, const SimChain<T>& x)
{
	x.Output(out);
	return out;
}