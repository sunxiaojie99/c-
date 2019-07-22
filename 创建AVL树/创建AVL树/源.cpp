//https://www.cnblogs.com/skywang12345/p/3577360.html#a1
//��AVL���У��κνڵ�����������ĸ߶�������1��������Ǹ߶���ֹ1������Ҫ����ƽ���Իָ��������ԡ�
//���ڸ���һ���������У� һ��һ���ؽ���ֵ�����ʼΪ�յ�AVL���У�����õ���AVL���Ĳ��˳��������У�
//���ж����Ƿ���һ����ȫ��������
//�����ʽ��
//��һ�а���һ��������N(<= 20)��Ȼ������һ�и���N����ͬ�����������������ֶ��ÿո������
//
//�����ʽ��
//��һ�д�ӡ�õ���AVL���Ĳ��˳��������С��������ֶ������ÿո������������β����û�ж���Ŀո�
//Ȼ������һ���У������Ϊ��ȫ�����������ӡ��Yes��;������ǣ����ӡ��No����
//ʾ�����Լ�:
//- ��1��
//���룺
//5
//
//88 70 61 63 65
//�����
//70 63 88 61 65
//
//Yes
//- ��2��
//���룺
//10
//
//62 88 58 47 35 73 51 99 37 93
//�����
//62 47 88 35 58 73 99 37 51 93
//
//No
//
#include<iostream>
#include<Queue>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<functional>
#include<Windows.h>

using namespace std;
class node
{
public:
	int value;//����
	node *leftnode;//����
	node *rightnode;//�Һ���
};
int findheight(node *t)//��ǰ�ڵ�ĸ߶�
{
	if (!t)return 0;//��Ϊ��ָ�룬����߶�Ϊ0
	else//��Ϊ�գ����������������߶ȵ����ֵ+1
	{
		int hl = findheight(t->leftnode);
		int hr = findheight(t->rightnode);
		if (hl>hr)
			return ++hl;
		else
			return ++hr;
	}
}
node * LL(node *T)//����Ԫ��λ������������ӣ�ΪL�Ͳ�ƽ�⣬Ӧ����
{
	node *temp;
	temp = T->leftnode;
	T->leftnode = temp->rightnode;
	temp->rightnode = T;

	return temp;
}
node *RR(node *T)//����Ԫ��λ���������Ҷ��ӣ���ΪR�Ͳ�ƽ�⣬Ӧ���� 
{
	node *temp;
	temp = T->rightnode;
	T->rightnode = temp->leftnode;
	temp->leftnode = T;
	return temp;
}
node *LR(node *T)//����Ԫ��λ���������Ҷ��ӣ�LR�Ͳ�ƽ�⣬������������ 
{
	node *temp1,*temp2;
	temp1=RR(T->leftnode);
	T->leftnode = temp1;
	temp2=LL(T);
	return temp2;
}
node *RL(node *T)//����Ԫ��λ������������ӣ�RL�Ͳ�ƽ�⣬������������
{
	node *temp1, *temp2;
	temp1 = LL(T->rightnode);
	T->rightnode = temp1;
	temp2 = RR(T);
	return temp2;
}
node *insert_in_AVL(int num, node *T)//�ݹ�����½ڵ�
{
	if (T==NULL)//���ԭ����Ϊ�գ���ֱ�Ӳ��ڸ��ڵ�
	{
		T = new node;
		T->value = num;
		T->leftnode = NULL;
		T->rightnode = NULL;
	}
	else
	{
		if (num<T->value)//������ֵС�ڵ�ǰ���ڵ�t
		{
			T->leftnode =insert_in_AVL(num, T->leftnode);//�ݹ飬������t����������
			if (findheight(T->leftnode) - findheight(T->rightnode) == 2) //����ƽ������Ϊ2 
			{
				if (num<T->leftnode->value)//������������������ڵ�
				{
					T=LL(T);
				}
				else if (num > T->leftnode->value)//�����������������ҽڵ�
				{
					T = LR(T);
				}
			}
		}
		else if (num > T->value)//������ֵ���ڵ�ǰ���ڵ�t
		{
			T->rightnode =insert_in_AVL(num, T->rightnode);//�ݹ飬������t����������
			if (findheight(T->leftnode) - findheight(T->rightnode) == -2) //����ƽ������Ϊ2 
			{
				if (num > T->rightnode->value)//���������������ҽڵ�
				{
					T = RR(T);
				}
				else if (num < T->rightnode->value)//����������������ڵ�
				{
					T = RL(T);
				}
			}
		}
	}
	return T;
}
void printtree(node *t)//ʹ�ö��а����ӡ��ÿ����һ����㣬�ͽ������������ڵ�ѹ��ջ
{
	queue<node *>a;
	a.push(t); 
	while (!a.empty())
	{
		cout << a.front()->value;
		node *f; 
		f = a.front();
		a.pop();
		if (f->leftnode != NULL)
		{
			a.push(f->leftnode);
		}
		if (f->rightnode != NULL)
		{
			a.push(f->rightnode);
		}
		if (!a.empty())
			cout << " ";
	}
}
bool check(node *t)//�ж��Ƿ�Ϊ��ȫ������
{
	queue <node *>a;
	a.push(t);
	while (!a.empty())
	{
		node *f = a.front();
		a.pop();
		if (f->leftnode == NULL&&f->rightnode !=NULL)
		{
			return false;
		}
		else if (f->leftnode == NULL||f->rightnode == NULL)
		{
			while (!a.empty())
			{
				node *j = a.front();
				a.pop();
				if (j->leftnode != NULL || j->rightnode != NULL)
					return false;
			}
			return true;
		}
		else
		{
			a.push(f->leftnode);
			a.push(f->rightnode);
		}
	}
}
node *findmax(node *root)//Ѱ���Ե�ǰ�ڵ�Ϊ�����������ڵ�
{
	if (root == NULL)//����Ϊ�� ���ؿ�
		return NULL;
	else
	{
		while (root->rightnode)
		{
			root = root->rightnode;
		}
	}
	return root;
}
node *findmin(node *root)//Ѱ���Ե�ǰ�ڵ�Ϊ����������С�ڵ�
{
	if (root == NULL)
		return NULL;
	else
	{
		while (root->leftnode)
		{
			root = root->leftnode;
		}
	}
	return root;
}
node *search(node *root,int k)//�ڸ�Ϊroot������Ѱ��ֵΪk�Ľڵ�
{
	if (root == NULL)//�����Ϊ�գ����ؿ�
		return NULL;
	if (root->value == k)
		return root;
	else if (k > root->value)//������ִ��ڵ�ǰ�ڵ㣬����������������
	{
		return search(root->rightnode, k);
	}
	else if (k < root->value)//�������С�ڵ�ǰ�ڵ㣬����������������
	{
		return search(root->leftnode, k);
	}
}
node * delete_avl(node *root,node *z)//ɾ���ڵ�
{
	if (root == NULL || z == NULL)//������ǿջ���ɾ���Ľڵ��ǿ� ���ؿ�
	{
		return NULL;
	}
	else
	{
		if (z->value < root->value)//����ýڵ�ȸ��ڵ�С���ݹ飬��root����������ɾ��
		{
			root->leftnode = delete_avl(root->leftnode, z);
			if (findheight(root->rightnode) - findheight(root->leftnode) == 2)//���ɾ���꣬��������ƽ�����ӵ���2
			{
				node *r = root->rightnode;
				if (findheight(r->rightnode )>findheight(r->leftnode ))//�������RR�Ͳ�ƽ��
				{
					root=RR(root);
				}
				else//����RL�Ͳ�ƽ��
				{
					root = RL(root);
				}
			}
		}
		else if (z->value > root->value)//����ýڵ���ڡ������ڵ㣬�ݹ飬��root����������ɾ��
		{
			root->rightnode = delete_avl(root->rightnode, z);
			if (findheight(root->leftnode) - findheight(root->rightnode) == 2)//ɾ���ꡰ������ƽ�����ӱ��2
			{
				node *l = root->leftnode;
				if (findheight(l->leftnode) > findheight(l->rightnode))//�����LL�Ͳ�ƽ��
				{
					root = LL(root);
				}
				else//�����LR�Ͳ�ƽ��
					root = LR(root);
			}
		}
		else if (z->value == root->value)//����ýڵ���ڵ�ǰ�������ڵ�ֵ
		{
			if (root->leftnode &&root->rightnode)//����ǰ�������ڵ����������������
			{
				if (findheight(root->leftnode) > findheight(root->rightnode))//���������Ƚϸߣ���ѡ������������ң��ڵ㡰�����Ҫɾ���Ľڵ�  
				{
					node *replace = findmax(root->leftnode);
					root->value = replace->value;//������ڵ��ֵ����ɾ���ڵ�
					root->leftnode  = delete_avl(root->leftnode , replace);//����������ɾ������ڵ�
				}
				else//���������Ƚϸߣ�ѡ������������С���󣩽ڵ������ǰɾ���ڵ�
				{
					node *replace = findmin(root->rightnode);
					root->value = replace->value;//������ڵ��ֵ����ɾ���ڵ�
					root->rightnode  = delete_avl(root->rightnode , replace);//����������ɾ������ڵ�
				}
			}
			else//��ǰ�ڵ���1������û�к��� ��ӽڵ����ɾ���ڵ㼴��
			{
				node *tmp=root;
				root = (root->leftnode != NULL) ? root->leftnode : root->rightnode;
				delete tmp;
			}
		}
	}
	return root;
}
void swap(int a[],int i,int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
int main()
{
	int size = 1000;//size��Χ1000~100000
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
			swap(m, i, rand() % i);  //���������������˳�� 
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
		node *T;
		T = NULL;
		//AVL1 �������� ��ͬ˳��ɾ��
		/*
		for (int j = 0; j < size; j++)
		{
			T = insert_in_AVL(up[j], T);
		}
		for (int i = 0; i < size; i++)
		{
			node *e = new node;
			e = search(T, up[i]);
			T = delete_avl(T, e);
		}
		*/

		//AVL2 �������룬�෴˳��ɾ��
		
		for (int j = 0; j < size; j++)
		{
			T = insert_in_AVL(up[j], T);
		}
		for (int i = 0; i < size; i++)
		{
			node *e = new node;
			e = search(T, down[i]);
			T = delete_avl(T, e);
		}
		
		

		//AVL3 ����������ɾ��
		/*
		for (int j = 0; j < size; j++)
		{
			T = insert_in_AVL(m[j], T);
		}
		for (int i = 0; i < size; i++)
		{
			node *e = new node;
			e = search(T,n[i]);
			T = delete_avl(T, e);
		}*/
		
		QueryPerformanceCounter(&t2);
		printf("%f", (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart);
		cout << endl;
	}
	system("pause");
	return 0;
}


