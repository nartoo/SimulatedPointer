#pragma once
#include<iostream>
//#include"SimulChain.h"
using namespace std;

template <class T>
class SimSpace 
{
	friend class SimChain<T>;
public:
	SimSpace(int MaxSpaceSize = 100);
	~SimSpace() { delete[] node; }
	int Allocate(); //分配一个节点
	void Deallocate(int& i); //释放节点i
	template<class T>
	class SimNode   //刚开始并不知道把SimNode类作为SimSpace类的嵌套类，
					//这两个类彼此有利用，把谁放到前面都不合适。
	{
		friend class SimSpace<T>;
		friend class SimChain<T>;
	private:
		T data;
		int link;
	};

private:
	int NumberOfNodes, first;
	SimNode<T> *node;//节点数组
};

template<class T>
SimSpace<T>::SimSpace(int MaxSpaceSize)
{
	// 构造函数
	NumberOfNodes = MaxSpaceSize;
	node = new SimNode<T>[NumberOfNodes];
	// 初始化可用空间表
	// 创建一个节点链表
	for (int i = 0; i < NumberOfNodes - 1; i++)
		node[i].link = i + 1;     //第（i）0个节点的link是1，最后一个节点的link是-1
								  //link和i之间的联系就是，这个节点的link是下个节点的i
	// 链表的最后一个节点
	node[NumberOfNodes - 1].link = -1;
	// 链表的第一个节点
	first = 0;
};

template<class T>
int SimSpace<T>::Allocate()
{
	//这个操作相当于删除可用空间表中的第一个节点，拿出来用了
	// 分配一个自由节点
	if (first == -1) throw NoMem();
	int i = first; //分配第一个节点
	first = node[i].link; //first指向下一个自由节点
	return i;
};

template<class T>
void SimSpace<T>::Deallocate(int& i)
{
	//这个函数相当于在可用空间表中添加一个节点，存进去了
	// 释放节点i .
	// 使i 成为可用空间表的第一个节点
	node[i].link = first;   //first此时指向可用空间表的第一个节点
	first = i;
	//i = -1;  //这一步是为什么？这个注释与否对目前的测试代码的结果表面上没有影响。
};


//使用两个空间表的部分函数版本，需要把first1和first2设置位SimSpace的私有成员
//template<class T>
//SimSpace<T>::SimSpace(int MaxSpaceSize)
//{ 
//	// 使用两个可用空间表的构造函数
//	NumberOfNodes = MaxSpaceSize;
//	node = new SimNode<T>[NumberOfNodes];
//	// 初始化可用空间表
//	firstl = 0;
//	first2 = -1;      //模拟指针和C++指针的区别
//};
//
//template<class T>
//int SimSpace<T>::Allocate()
//{
//	// 分配一个自由节点
//	if (first2 == -1) {// 第2个表为空
//		if (firstl == NumberOfNodes) throw NoMem();
//		return firstl++;
//		}
//	// 分配链表中的第一个节点
//	int i = first2;
//	first2 = node[i].link;
//	return i;
//}

//template<class T>
//void SimSpace<T>::DeallocateCircular(int& c)
//{
//	 释放一个循环链表c
//	if (c != -1) {
//		int next = node[c].link;
//		node[c].link = first;
//		first = next;
//		c = -1;
//	}
//};