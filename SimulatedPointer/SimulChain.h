#pragma once
#include<iostream>
//#include"SimulSpace.h"  //�������������������SimChain��ʹ��SimSpace���ް���
                          //һֱ���ǲ��Ữ���ߵ��Ǳ���ᱨ��ֵĴ���
using namespace std;

template<class T> class SimSpace;	//�������������䣬�����û�б����Ǹ�������
									//������ģ�������Ͷ��岻��Ӧ�÷���һ�����

template<class T>
class SimChain 
{
public:
	SimChain() { first = -1; }
	~SimChain() { Destroy(); }
	void Destroy(); // ʹ��Ϊ��
	int Length() const;
	bool Find(int k, T& x) const;
	int Search(const T& x) const;
	SimChain<T>& Delete(int k, T& x);
	SimChain<T>& Insert(int k, const T& x);
	void Output(ostream& out) const;
private:
	int first; // ��һ���ڵ������
	static SimSpace<T> S;
};

template<class T>
void SimChain<T>::Destroy()
{
	// �ͷ�����ڵ�
	int next;
	while (first != -1)
	{
		next = S.node[first].link;  //nextָ��ڶ����ڵ�
		S.Deallocate(first);
		first = next;
	}
}

template<class T>
int SimChain<T>::Length() const
{
	// ��������ĳ��ȡ����ǿ����������ĳ��ȣ�
	//�����޷���������ÿռ�ĳ��ȣ�������ÿռ�ĳ���Ҳû�����壿
	int current = first, // ���ڵ�ĵ�ǰλ��
		len = 0; //Ԫ�ؼ���
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
	// ȡ��k��Ԫ����x
	// ��������ڵ�k��Ԫ�أ���������false�����򷵻�true
	if (k < 1) return false;
	int current = first, // ���ڵ�ĵ�ǰλ��
		index = 1; //��ǰ�ڵ������
	// �ƶ�current����k���ڵ�
	while (index < k && current != -1) 
	{
		current = S.node[current].link;
		index++;
	}
	// ��֤�Ƿ񵽴��˵�k���ڵ�
	if (current != -1)
	{
		x = S.node[current].data;
		return true;
	}
	return false; // �����ڵ�k��Ԫ��
}

template<class T>
SimChain<T>& SimChain<T>::Delete(int k, T& x)
{
	// �ѵ�k��Ԫ��ȡ��x��Ȼ��ɾ����k��Ԫ��
	// ��������ڵ�k��Ԫ�أ��������쳣OutOfBounds
	if (k < 1 || first == -1)
		throw OutOfBounds(); // �����ڵ�k��Ԫ��
	// p���ս�ָ���k���ڵ�
	int p = first;
	// ��p�ƶ�����k���ڵ㣬����������ɾ���ýڵ�
	if (k == 1) // p�Ѿ�ָ���k���ڵ�
		first = S.node[first].link; // ��������ɾ��
									//�������k����ֵnode�е��±�i��û�б�Ȼ��ϵ�ġ�
									//k==1��λ��SimChain�����еĵ�һ���ڵ㣬firstָ���������
									//�еĵ�һ���ڵ㣬����node[first]�����������е��κ�λ�õ�Ԫ��
	else 
	{ 
		// ʹ��qָ���k - 1��Ԫ��
		int q = first;
		for (int index = 1; index < k - 1 && q != -1; index++)
			q = S.node[q].link;
		// ��֤��k��Ԫ�صĴ�����
		if (q == -1 || S.node[q].link == -1)
			throw OutOfBounds(); // �����ڵ�k��Ԫ��
		// ʹpָ���k��Ԫ��
		p = S.node[q].link;
		// ��������ɾ����k��Ԫ��
		S.node[q].link = S.node[p].link;//�ٴ�ǿ����������p��q��Ŀ��֮һ��ȡ����Ҫ�Ľڵ���node
										//�����е��±꣬����Deallocate������Ҳ������±�,
										//��������Եõ�һ�����飺����SimSpace����ز���
										//�Ĳ���Ӧ�ö���node������±ꡣ��k������SimChain����
										//������
	}
		// �����k��Ԫ�ز��ͷŽڵ�p
		x = S.node[p].data;
		S.Deallocate(p);  //�ͷ�����Ѿ�ɾ���Ľڵ��Ŀ�ľ���Ϊ��������ڵ�ع鵽
						  //���ÿռ���С��������ʹ��ڡ����롱״̬���´ξ�û��ʹ�ã�
						  //�൱�ڡ��ڴ�й©���ˡ�
		return *this;
}

template<class T>
SimChain<T>& SimChain<T>::Insert(int k, const T& x)
{
	// �ڵ�k��Ԫ��֮�����x
	// ��������ڵ�k��Ԫ�أ��������쳣OutOfBounds
	// ���û���㹻�Ŀռ䣬�򴫵�NoMem�쳣
	if (k < 0)
		throw OutOfBounds();
	// ����һ��ָ��p��p���ս�ָ���k���ڵ�
	int p = first;
	// ��p�����k���ڵ�
	for (int index = 1; index < k && p != -1; index++)
		p = S.node[p].link;
	// ��֤��k���ڵ�Ĵ�����
	if (k > 0 && p == -1)
		throw OutOfBounds();
	// Ϊ�����������һ���½ڵ�
	int y = S.Allocate();
	S.node[y].data = x;
	// �������в����½ڵ�
	// ���ȼ���½ڵ��Ƿ�Ҫ�嵽������ײ�
	if (k) 
	{
		//��p֮�����
		S.node[y].link = S.node[p].link;
		S.node[p].link = y;
	}
	else 
	{
		// ��Ϊ�����׽ڵ�
		S.node[y].link = first; first = y;
	}
	return *this;
}

template<class T>
int SimChain<T>::Search(const T& x) const
{
	// Ѱ��x���������x���򷵻�x�ĵ�ַ
	// ���x���������У��򷵻�0
	int current = first,  //���ڵ�ĵ�ǰλ��
		index = 1; // current������
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
	// ������Ԫ�����������
	int current;
	for (current = first; current != -1; current = S.node[current].link)
		out << S.node[current].link <<":"<<S.node[current].data << " ";//���link��Ϊ�˷���
					                                        //�Ƚ�link�������λk֮��Ĳ�ͬ
}

// ����<<
template <class T>
ostream& operator<<(ostream& out, const SimChain<T>& x)
{
	x.Output(out);
	return out;
}