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
	int Allocate(); //����һ���ڵ�
	void Deallocate(int& i); //�ͷŽڵ�i
	template<class T>
	class SimNode   //�տ�ʼ����֪����SimNode����ΪSimSpace���Ƕ���࣬
					//��������˴������ã���˭�ŵ�ǰ�涼�����ʡ�
	{
		friend class SimSpace<T>;
		friend class SimChain<T>;
	private:
		T data;
		int link;
	};

private:
	int NumberOfNodes, first;
	SimNode<T> *node;//�ڵ�����
};

template<class T>
SimSpace<T>::SimSpace(int MaxSpaceSize)
{
	// ���캯��
	NumberOfNodes = MaxSpaceSize;
	node = new SimNode<T>[NumberOfNodes];
	// ��ʼ�����ÿռ��
	// ����һ���ڵ�����
	for (int i = 0; i < NumberOfNodes - 1; i++)
		node[i].link = i + 1;     //�ڣ�i��0���ڵ��link��1�����һ���ڵ��link��-1
								  //link��i֮�����ϵ���ǣ�����ڵ��link���¸��ڵ��i
	// ��������һ���ڵ�
	node[NumberOfNodes - 1].link = -1;
	// ����ĵ�һ���ڵ�
	first = 0;
};

template<class T>
int SimSpace<T>::Allocate()
{
	//��������൱��ɾ�����ÿռ���еĵ�һ���ڵ㣬�ó�������
	// ����һ�����ɽڵ�
	if (first == -1) throw NoMem();
	int i = first; //�����һ���ڵ�
	first = node[i].link; //firstָ����һ�����ɽڵ�
	return i;
};

template<class T>
void SimSpace<T>::Deallocate(int& i)
{
	//��������൱���ڿ��ÿռ�������һ���ڵ㣬���ȥ��
	// �ͷŽڵ�i .
	// ʹi ��Ϊ���ÿռ��ĵ�һ���ڵ�
	node[i].link = first;   //first��ʱָ����ÿռ��ĵ�һ���ڵ�
	first = i;
	//i = -1;  //��һ����Ϊʲô�����ע������Ŀǰ�Ĳ��Դ���Ľ��������û��Ӱ�졣
};


//ʹ�������ռ��Ĳ��ֺ����汾����Ҫ��first1��first2����λSimSpace��˽�г�Ա
//template<class T>
//SimSpace<T>::SimSpace(int MaxSpaceSize)
//{ 
//	// ʹ���������ÿռ��Ĺ��캯��
//	NumberOfNodes = MaxSpaceSize;
//	node = new SimNode<T>[NumberOfNodes];
//	// ��ʼ�����ÿռ��
//	firstl = 0;
//	first2 = -1;      //ģ��ָ���C++ָ�������
//};
//
//template<class T>
//int SimSpace<T>::Allocate()
//{
//	// ����һ�����ɽڵ�
//	if (first2 == -1) {// ��2����Ϊ��
//		if (firstl == NumberOfNodes) throw NoMem();
//		return firstl++;
//		}
//	// ���������еĵ�һ���ڵ�
//	int i = first2;
//	first2 = node[i].link;
//	return i;
//}

//template<class T>
//void SimSpace<T>::DeallocateCircular(int& c)
//{
//	 �ͷ�һ��ѭ������c
//	if (c != -1) {
//		int next = node[c].link;
//		node[c].link = first;
//		first = next;
//		c = -1;
//	}
//};