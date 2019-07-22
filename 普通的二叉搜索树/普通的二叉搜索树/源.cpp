#include<iostream>
#include<Windows.h>
#include<queue>
#include<vector>
#include<functional>
#include <stdlib.h>
#include<time.h>
using namespace std;
class node {
public:
	node* leftchild=NULL;//���� ָ���ʼ��Ϊ��
	node* rightchild=NULL;//�Һ���
	int value;//�ڵ�����
};
void make(node *&root,node *k)//����ڵ�
{
	if (root == NULL)//������ڵ�Ϊ�գ���ֱ�Ӳ嵽���ڵ�
	{
		root = k;
	}
	else//��Ϊ�� ���õݹ�Ѱ�Һ��ʵ�λ�ò���
	{
		if (k->value  < root->value)//������������С�ڵ�ǰ�ڵ�����ݣ����������в��������
		{
			make(root->leftchild, k);
		}
		else if (k->value  > root->value)//��֮��������������
			make(root->rightchild, k);
	}
}
node *find(node *root,int k,node *&parent)//�����ڵ� ���ظýڵ���丸��
{
	node*o;
	if (root == NULL)//������ڵ�Ϊ�գ���Ѱ�ҵ��Ľڵ�Ϊ�գ��丸��ΪΪ��
	{
		parent = NULL;
		return NULL;
	}
	else//�Ӹ���ʼ����
	{
		if (k < root->value)//����С��root�ģ���root����parent����root����������Ѱ�Ҹ�����
		{
			parent = root;
			find(root->leftchild, k,parent);
		}
		else if (k > root->value)//���ݴ���root�ģ���root����parent����root����������Ѱ�Ҹ�����
		{
			parent = root;
			find(root->rightchild, k,parent);
		}
		else if(k==root->value )//��ȣ����ظýڵ�
			return root;
	}
}
node *findmax(node *root)//Ѱ�Ҵ������ڵ�
{
	if (root->rightchild == NULL)//����ýڵ�������������ڣ���ýڵ�������ڵ�
		return root;
	else//����һֱѰ�ҵ��ýڵ������������ҽڵ㼴Ϊ��rootΪ�����������ڵ�
	{
		while (root)
		{
			root = root->rightchild;
		}
	}
	return root;
}
node *findmin(node*root,node *&parent)//Ѱ�Ҵ�����С�ڵ�
{
	if (root->leftchild == NULL)//����ýڵ�������������ڣ���ýڵ������С�ڵ�
	{
		return root;
	}
	else//����һֱѰ�ҵ��ýڵ�������������ڵ㼴Ϊ��rootΪ����������С�ڵ�
	{
		while (root->leftchild)
		{
			parent = root;
			root = root->leftchild;
		}
	}
	return root;
}
node * deletenode(node *k)//ɾ���ڵ�
{
	if (k->rightchild!=NULL&&k->leftchild!=NULL)//k��2������
	{
		node *p = NULL;
		int flag = 1;
		node *parent = k;
		p = findmin(k->rightchild,parent);//�ҵ�������������ڵ�p
		if (parent->rightchild == p)
			flag = 1;//�Һ���
		else
			flag = 0;
		k->value = p->value;//��p��ֵ�滻k��ֵ
		p=deletenode(p); //ת��Ϊɾ��������ڵ�p
		if (flag == 1)
		{
			parent->rightchild = p;
		}
		else if (flag == 0)
			parent->leftchild = p;
		return k;
	}
	else if (k->leftchild ||k->rightchild )//k��1������
	{
		if (k->rightchild)//���Һ��� ���Һ�������ýڵ�
			k = k->rightchild;
		else//�����ӣ�����������ýڵ�
			k = k->leftchild;
		return k;//���������ɵĽڵ�
	}
	else
	{
		return NULL;//�޺��ӣ���NULL����ýڵ�
	}
}
void print(node *root)//�������
//���������һ��������˳�����BST���нڵ�ı�����ʽ��Ҳ���Ǵ�С�����˳��������нڵ㡣
//���������һ��Ӧ�þ��Ƕ�����������������������Ǵ�С��������е���
{
	if (!root) {
		return;
	}
	else
	{
		print(root->leftchild);//���������
		cout << root->value<<" ";//�������
		print(root->rightchild);//������Һ���
	}
}
void swap(int a[],int i,int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
int main()
{
	int size = 5000;//size��Χ1000~100000
	for (size = 1000; size <= 10000; size += 1000)
	{
		int *up = new int[size];//����
		int *down = new int[size];//����
		int *m = new int[size];//���
		int *n = new int[size];//���
		for (int i = 0; i < size; i++)
		{
			up[i] = i + 1;
			down[i] = size - i;
			m[i] = i + 1;  //���ν����鸳ֵΪ1~N 
			n[i] = i + 1;
		}
		for (int i = size - 1; i >= 1; --i) {
			swap(m,i, rand() % i);  //���������������˳�� 
			swap(n, i, rand() % i);
		}
		for (int i = size - 1; i >= 1; --i) {
		//���������������˳�� 
			swap(n, i, rand() % i);
		}

		node *root = NULL;
		//��ʱ����
		LARGE_INTEGER t1, t2, tc;
		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);

		//BST-1 �������� ��ͬ˳��ɾ��
		for (int i = 0; i < size; i++)
		{
			node*k = new node;
			k->value=up[i];
			make(root, k);
		}
		for (int j = 0; j < size; j++)
		{
			node *r = new node;
			r->value = up[j];
			node *parent = NULL;
			r = find(root, r->value,parent);
			if (r == NULL)
				cout << "erro";
			else
			{
				if (parent)
				{
					if (parent->leftchild == r)
					{
						parent->leftchild = deletenode(r);
					}
					else if (parent->rightchild == r)
					{
						parent->rightchild = deletenode(r);
					}
				}
				else
				{
					root= deletenode(r);
				}
			}
		}
		
		//BST-2 �������� �෴˳��ɾ��

		/*for (int i = 0; i < size; i++)
		{
			node*k = new node;
			k->value = up[i];
			make(root, k);
		}
		for (int j = 0; j < size; j++)
		{
			node *r = new node;
			r->value = down[j];
			node *parent = NULL;
			r = find(root, r->value, parent);
			if (r == NULL)
				cout << "erro";
			else
			{
				if (parent)
				{
					if (parent->leftchild == r)
					{
						parent->leftchild = deletenode(r);
					}
					else if (parent->rightchild == r)
					{
						parent->rightchild = deletenode(r);
					}
				}
				else
				{
					root = deletenode(r);
				}
			}
		}
		*/


		//BST-3 ������� ���˳��ɾ��
		/*for (int i = 0; i < size; i++)
		{
			node*k = new node;
			k->value = m[i];
			make(root, k);
		}
		for (int j = 0; j < size; j++)
		{
			node *r = new node;
			r->value =n[j];
			node *parent = NULL;
			r = find(root, r->value, parent);
			if (r == NULL)
				cout << "erro";
			else
			{
				if (parent)
				{
					if (parent->leftchild == r)
					{
						parent->leftchild = deletenode(r);
					}
					else if (parent->rightchild == r)
					{
						parent->rightchild = deletenode(r);
					}
				}
				else
				{
					root = deletenode(r);
				}
			}
		}*/
		QueryPerformanceCounter(&t2);
		printf("%d,Use Time:%f\n", size,(t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart);
		cout << endl;
	}
	system("pause");
	return 0;
}
//bool* empty1=new bool[5*size+1];
//for (int i = 0; i < 5 * size; i++)
//{
//	empty1[i] = true;
//}
//bool *empty2=new bool[size+1];
//for (int i = 0; i < size; i++)
//{
//	empty2[i] = true;
//}
//priority_queue<int, vector<int>, greater<int>> pq1, pq11;//��������
//priority_queue<int> pq2, pq22;//�������� 
//vector<int> v0, v1;//������У�v0�洢�������v1�洢���������v0���±� 
////���������
//srand((unsigned)time(NULL));
//for (int i = 0; i < size; i++)
//{
//	int t = rand() % (5 * size);
//	if (empty1[t]==true)
//	{
//		empty1[t] = false;
//		v0.push_back(t);
//		pq1.push(t);
//		pq2.push(t);
//	}
//	else
//		i--;
//}
//srand((unsigned)time(NULL));
//for (int i = 0; i < size; i++)
//{
//	int t = rand() % size;
//	if (empty2[t] == true)
//	{
//		empty2[t] = false;
//		v1.push_back(t);
//	}
//	else
//		i--;
//}
//pq11 = pq1;
//pq22 = pq2;