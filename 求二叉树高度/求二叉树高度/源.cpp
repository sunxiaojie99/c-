/*
����:
����һ�ö��������������������������У�����ö������ĸ߶ȡ�
���У�������������������������Ϊ�������ظ�Ӣ����ĸ�������Сд�����ַ�����

�����ʽ��
�����������ܸ���n<=50��Ȼ���������������������У��������г��Ⱦ�Ϊn��

�����ʽ��
�������߶ȣ�������
ʾ�����Լ�:
- ��1��
���룺
9

ABDGHCEIF

GDHBAEICF
�����
4
*/

#include<iostream>
using namespace std;
class node {
public:
	node *leftchild, *rightchild;
	char root;
};
int findlength(node *t)//��߶�
{
	if (t==NULL) return 0;
	int hl = findlength(t->leftchild);
	int hr = findlength(t->rightchild);
	if (hl > hr)
		return ++hl;
	else
		return ++hr;
}
node* hy(char xx[], char zx[], int n)//�������
{
	node *m=new node;
	int i = 0;
	if (n == 0) return NULL;
	else {
		m->root = xx[0];
		while (zx[i] != xx[0])
		{
			i++;
		}
		m->leftchild = hy(xx + 1, zx, i);
		m->rightchild = hy(xx + i + 1, zx + i+1, n - i-1);
	}
	return m;
}
int main()
{
	int n;
	cin >> n;
	char xx[100], zx[100];
	node *k;
	for (int i = 0; i < n; i++)
	{
		cin >> xx[i];
	}
	for (int j = 0; j < n; j++)
	{
		cin >> zx[j];
	}
	k=hy(xx, zx, n);
	cout << findlength(k);
	system("pause");
	return 0;
}
