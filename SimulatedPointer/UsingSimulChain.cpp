//ͷ�ļ�������˳�����Ҫ��������ͷ�ļ��зֱ𲻰����˴˵����໥����
//������£�Space.h��Chain.h�������ȷ�֮��ǿ����Ŀǰ���ְ�����ϵ�£�����
//�����Ĵ����֮ǰ�Ĵ���һ������������ͷ�ļ����˴˰���������±�������Ĵ���
//��Ҳ����˵����ͷ�ļ���Դ�ļ�������������ļ�������£�������ѡ���˰�Դ�ļ��еİ���˳��
//��ִ�У��������ڰ�Դ�ļ��е����ͷ�ļ�ע�͵���Ȼ���������Ա�ͷ�ļ��а����˴ˣ�����ô����
//ԭ�ļ�һע�͵��ͻ����ߣ����Բ������������ڸ������һ����ϵ��ͬһ����Ŀ�е�ͷ�ļ���ֻ��Ҫ
//��Դ�ļ��а��������ˣ�����Ҫע��˳��

//���ò�ע�⣬SimChain���SimSpace���ж���һ��first������Ӧ�����������
//SimChaim.first��ʼ��Ϊ-1��SimSpace��ʼ��Ϊ0��
//���Ǻ���Ȼ�ģ��Ӹ�����Ľṹ�п���ʵ�����󣬿��ÿռ�������ɽڵ㣬
//����first��Ӧָ���һ���ڵ㣨first=0������SimChain����û�нڵ㣬��������first=-1��

#include <iostream>
#include "SimulChain.h"
#include "SimulSpace.h"
#include "Xcept.h"

using namespace std;

SimSpace<int> SimChain<int>::S; //ʵ�������ÿռ�S������SimSpace�๹�캯������
								//��ʱ����һ���㹻������飬��źܶ�ڵ�,
								//ÿ���ڵ��link�Ѿ��ڹ��캯����ָ����
								//��0���ڵ�node[0]��link������1��...

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
	cout << "Position of 2 is" << c.Search(2) << endl; //�˴�������0����ʾ���Ѿ���������
	cout << "Position of 6 is" << c.Search(6) << endl;
	c.Insert(0, 9).Insert(1, 8).Insert(2, 7);
	cout << "Current chain is" << c << endl;
	cout << "Its length is" << c.Length() << endl;
	cout << "Position of 2 is" << c.Search(2) << endl;
	cout << "Position of 6 is" << c.Search(6) << endl;
}