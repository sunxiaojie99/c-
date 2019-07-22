#include<iostream>
#include<Queue>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<functional>
#include<Windows.h>
using namespace std;
enum nodecolor {red,black};
class node {
public:
	node *leftchild=NULL;//����
	node *rightchild=NULL;//�Һ���
	node *parent=NULL;//���ڵ�
	nodecolor color;//��ɫ
	int key;//�ؼ���
};
/*
* �Ժ�����Ľڵ�(x)��������ת
*
* ����ʾ��ͼ(�Խڵ�x��������)��
*      px                              px
*     /                               /
*    x                               y
*   /  \      --(����)-->           / \                #
*  lx   y                          x  ry
*     /   \                       /  \
*    ly   ry                     lx  ly
*
*
*/

void leftroate (node *&root,node *x)//����
{
	node *y = x->rightchild;//��x���Һ�����Ϊy
	if (x->parent == NULL)//���xΪroot������y����root
	{
		root = y;
	}
	else
	{
		if (x->parent->leftchild == x)//���x����x���ڵ������
		{
			x->parent->leftchild = y;//��x���׵�����Ϊy
			y->parent = x->parent;//x�ĸ���Ϊy�ĸ���
		}
		else//���x����x���׵��Һ���
		{
			x->parent->rightchild = y;//��x���׵��Һ���ָ��y
			y->parent = x->parent;//��y�ĸ���ָ��x�ĸ���
		}
	}
	x->rightchild = y->leftchild;//y��������Ϊx���Һ���
	if (y->leftchild != NULL)//���y�����ӷǿ�
	{
		y->leftchild->parent = x;//y���ӵĸ�����Ϊx
	}
	y->leftchild = x;//y��������Ϊx
	x->parent = y;//x�ĸ�����Ϊy
}
/*
* �Ժ�����Ľڵ�(y)��������ת
*
* ����ʾ��ͼ(�Խڵ�y��������)��
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(����)-->            /  \                     #
*        x   ry                           lx   y
*       / \                                   / \                   #
*      lx  rx                                rx  ry
*
*/
void rightroate(node *&root,node *y)//��avl���� ����parent��㣬Ҫ˫��ֵ ����
{
	node *x = y->leftchild;//����xΪ��ǰ�ڵ�y������
	if (y->parent == NULL)//���y�Ǹ��ڵ�
	{
		root = x;//�Ѹ���Ϊx
	}
	else
	{
		if (y->parent->leftchild == y)//���y���丸�׽ڵ������
		{
			y->parent->leftchild = x;//��y���׵�������Ϊx
			x->parent = y->parent;//y�ĸ�����Ϊx�ĸ���
		}
		else//���y���丸�׵��Һ���
		{
			y->parent->rightchild = x;//���丸�׵��Һ�������Ϊx
			x->parent = y->parent;//x�ĸ�������Ϊy�ĸ���
		}
	}
	y->leftchild = x->rightchild;//x���Һ�����Ϊy������
	if (x->rightchild != NULL)//���x���Һ��ӷǿ�
	{
		x->rightchild->parent = y;//x�Һ��ӵĸ���Ϊy
	}
	x->rightchild = y;//x���Һ�������Ϊy
	y->parent = x;//y�ĸ�������Ϊx
}
void printtree(node *root)//ʹ�ö��а����ӡ��ÿ����һ����㣬�ͽ������������ڵ�ѹ��ջ  �����ӡ��
{
	queue<node *>a;
	a.push(root);
	while (!a.empty())
	{
		cout << a.front()->key;
		node *f;
		f = a.front();
		a.pop();
		if (f->leftchild != NULL)
		{
			a.push(f->leftchild);
		}
		if (f->rightchild != NULL)
		{
			a.push(f->rightchild);
		}
		if (!a.empty())
			cout << " ";
	}
}
void print(node *root)//�������
{
	if (root == NULL)
	{
		return;
	}
	print(root->leftchild);
	cout << root->key << " ";
	print(root->rightchild);
	return;
}
void printfront(node *root,node *a)//ǰ�����
{
	char d;
	int p,f;
	if (root)
	{
		if (a == NULL)
		{
			return;
		}
		if (a->color == black)
			d = 'B';
		else
			d = 'R';
		if (a != root)
			cout << " ";
		cout << a->key << "(" << d << ")";

		printfront(root, a->leftchild);
		printfront(root, a->rightchild);
	}
	else
		cout << "Null";
	return;
}
node * findbrother(node *&root, node *x)//Ѱ��ĳ���ڵ���ֵܽڵ�
{
	node *r = x;
	if (r == root)//����ýڵ�Ϊ���ڵ㣬���ֵܽڵ�ΪNULL
	{
		return NULL;
	}
	else
	{
		if (r == r->parent->leftchild)//����ýڵ�Ϊ�丸�׽ڵ������
		{
			return (r->parent->rightchild);
		}
		else if (r == r->parent->rightchild)//����ýڵ�Ϊ�丸�׽ڵ���Һ���
		{
			return r->parent->leftchild;
		}
	}
}
void rbinsertfixup(node *&root, node *nn)//���������
{
	if (nn == root)//����ڵ�Ϊ�����ı�����ɫΪ��ɫ
	{
		nn->color = black;
	}
	else if (nn->parent->color == black)//�����ڵ��Ǻ�ɫ ���ò���
	{

	}
	else if (nn->parent->color == red)//������ڵ�Ϊ��ɫ
	{
		if (nn->parent == nn->parent->parent->leftchild)//������ڵ����游�ڵ������
		{
			//case1 ����������ڵ�Ϊ��ɫ
			if (findbrother(root, nn->parent) != NULL&&findbrother(root, nn->parent)->color == red)
			{
				nn->parent->color = black;
				findbrother(root, nn->parent)->color = black;
				nn->parent->parent->color = red;
				rbinsertfixup(root, nn->parent->parent);
			}
			else if (findbrother(root, nn->parent) == NULL || findbrother(root, nn->parent)->color == black)
			{
				//case2 ����������ڵ�Ϊ��ɫ���ҵ�ǰ�ڵ�Ϊ�Һ���
				if (nn == nn->parent->rightchild)
				{
					node *t = nn->parent;
					leftroate(root, t);
					rbinsertfixup(root, t);
				}
				//case3 ����������ڵ�Ϊ��ɫ���ҵ�ǰ�ڵ�Ϊ����
				else if (nn == nn->parent->leftchild)
				{
					node *b = NULL;
					nn->parent->color = black;
					nn->parent->parent->color = red;
					b = nn->parent->parent;
					rightroate(root, b);
				}
			}
		}
		else if (nn->parent == nn->parent->parent->rightchild)//�����ڵ����游�ڵ���Һ���
		{
			//case1 ����������ڵ��Ǻ�ɫ
			if (findbrother(root, nn->parent) != NULL&&findbrother(root, nn->parent)->color == red)
			{
				nn->parent->color = black;
				findbrother(root, nn->parent)->color = black;
				nn->parent->parent->color = red;
				rbinsertfixup(root, nn->parent->parent);
			}
			else if (findbrother(root, nn->parent) == NULL || findbrother(root, nn->parent)->color == black)
			{
				//case2������ �����Ǻ�ɫ���ҵ�ǰ�ڵ����Һ���
				if (nn == nn->parent->rightchild)
				{
					node *b = NULL;
					nn->parent->color = black;
					nn->parent->parent->color = red;
					b = nn->parent->parent;
					leftroate(root, b);
				}
				//case3������ �����Ǻ�ɫ���ҵ�ǰ�ڵ�������
				else if (nn == nn->parent->leftchild)
				{
					node *t = nn->parent;
					rightroate(root, t);
					rbinsertfixup(root, t);
				}
			}
		}
	}
	//�����ڵ���Ϊ��ɫ
	root->color = black;
}

void insert(node * &root, node* nn)//newnode  ����ڵ�
{
	node *y = NULL;
	node *x = root;
	//1.�����������һ����ͨ�Ķ��������������ڵ���뵽��������

	//�ҳ�Ҫ����Ľ��nn�ڶ�����T�еĸ���y
	while (x != NULL)
	{
		y = x;
		if (nn->key < x->key)
		{
			x = x->leftchild;
		}
		else
			x = x->rightchild;
	}
	nn->parent = y;// ���� ��nn�ĸ��ס� Ϊ ��y��
	if (y == NULL)
	{
		root = nn;
	}
	else if (nn->key < y->key)//nnС�ڸ��׵�ֵ
	{
		y->leftchild = nn;//���׵�������Ϊnn
	}
	else if (nn->key > y->key)//nn���ڸ��׵�ֵ
	{
		y->rightchild = nn;//���׵��Һ�����Ϊnn
	}
	nn->leftchild = NULL;
	nn->rightchild = NULL;

	//2���ýڵ���ɫΪ��ɫ
	nn->color = red;
	//3��������Ϊһ�Ŷ���������
	rbinsertfixup(root, nn);
	//printfront(root);
	//cout <<"#"<< endl;
}

//��̽ڵ㣺�ڶ�������������������У�node����һ���ڵ����node�ĺ�̽ڵ�
//1.������������������һ���ڵ������������������Ľڵ㣨������������û�����������Ǿ�������������
//2.û����������������ĳһ�������������һ���ڵ㣬Ȼ���ҵ������������parent���ɣ�������parent��ֱ����ǰ�ڵ���parent��������Ϊֹ

node *findleft(node *p) //Ѱ������ڵ�
{
	while (p->leftchild != NULL)
	{
		p = p->leftchild;
	}
	return p;
}
node *findpostnode(node *p)//Ѱ�Һ�̽ڵ�
{
	node *parent_p;
	if (p->rightchild != NULL)
	{
		return (findleft(p->rightchild ));
	}
	else
	{
		parent_p = p->parent;
		while (parent_p != NULL)
		{
			if (parent_p->leftchild == p)return parent_p;
			p=parent_p;
			parent_p = p->parent;
		}
		return parent_p;
	}
}
void rbdeletefixup(node *&root, node *x, node *pa)//ɾ������
{
	node *z1;
	if (x != root && (x == NULL || x->color == black))//���x���Ǹ��ڵ㲢��x�Ǻ�ɫ�����߲����ڣ�
	{
		if (pa->leftchild == x)//��ǰ�ڵ��Ǹ��׵�����
		{
			//case1��x���ֶȽڵ��Ǻ�ɫ
			if (pa->rightchild != NULL&&pa->rightchild->color == red)//x��"��+��"�ڵ㣬x���ֵܽڵ��Ǻ�ɫ,����Case 1��ת��Ϊ��Case 2������Case 3����Case 4��
			{
				pa->rightchild->color = black;
				pa->color = red;
				if (root) {
					root->parent = NULL;
				}
				leftroate(root, pa);
				rbdeletefixup(root, x, pa);
			}
			else if (pa->rightchild != NULL&&pa->rightchild->color == black && (pa->rightchild->leftchild == NULL || pa->rightchild->leftchild->color == black) && (pa->rightchild->rightchild == NULL || pa->rightchild->rightchild->color == black))
			{//case2��x�ǡ���+�ڡ��ڵ㣬x���ֵܽڵ��Ǻ�ɫ��x���ֵܽڵ���������Ӷ��Ǻ�ɫ��
					//����x�ж����һ����ɫ��������(���������ƶ�)��
				pa->rightchild->color = red;
				z1 = pa;
				pa = z1->parent;
				rbdeletefixup(root, z1, pa);
			}
			else if (pa->rightchild != NULL&&pa->rightchild->color == black&&pa->rightchild ->leftchild !=NULL&&pa->rightchild->leftchild->color == red && (pa->rightchild->rightchild == NULL || pa->rightchild->rightchild->color == black))
				//case3��x�ǡ���+�ڡ��ڵ㣬x���ֵܽڵ��Ǻ�ɫ��x���ֵܽڵ�������Ǻ�ɫ���Һ����Ǻ�ɫ�ġ�
				//����Case 3������ת����ת���ɡ�Case 4��
			{
				pa->rightchild->leftchild->color = black;
				pa->rightchild->color = red;
				if (root) {
					root->parent = NULL;
				}
				rightroate(root, pa->rightchild);
				rbdeletefixup(root, x, pa);
			}
			else if (pa->rightchild != NULL&&pa->rightchild->color == black&&pa->rightchild ->rightchild !=NULL&&pa->rightchild->rightchild->color == red)
			{//case4��x���ֵܽڵ��Ǻ�ɫ���ֵܽڵ���Һ����Ǻ�ɫ
				pa->rightchild->color = pa->color;
				pa->color = black;
				pa->rightchild->rightchild->color = black;
				if (root) {
					root->parent = NULL;
				}
				leftroate(root, pa);
				x = root;
				rbdeletefixup(root, x, pa);
			}

		}
		else if (pa->rightchild == x)//x���丸�׵��Һ���
		{
			//case1��//x��"��+��"�ڵ㣬x���ֵܽڵ��Ǻ�ɫ,����Case 1��ת��Ϊ��Case 2������Case 3����Case 4��
			if (pa->leftchild != NULL&&pa->leftchild->color == red)
			{
				pa->leftchild->color = black;
				pa->color = red;
				if (root) {
					root->parent = NULL;
				}
				rightroate(root, pa);
				rbdeletefixup(root, x, pa);
			}
			else if (pa->leftchild != NULL&&pa->leftchild->color == black &&  (pa->leftchild->leftchild == NULL || pa->leftchild->leftchild->color == black)&& (pa->leftchild->rightchild == NULL || pa->leftchild->rightchild->color == black))
			{//case2��x�ǡ���+�ڡ��ڵ㣬x���ֵܽڵ��Ǻ�ɫ��x���ֵܽڵ���������Ӷ��Ǻ�ɫ��																									   //����x�ж����һ����ɫ��������(���������ƶ�)��

				pa->leftchild->color = red;
				z1 = pa;
				pa = pa->parent;;
				rbdeletefixup(root, z1, pa);

			}
			else if (pa->leftchild != NULL&&pa->leftchild->color == black &&pa->leftchild ->rightchild !=NULL&&pa->leftchild->rightchild->color == red && (pa->leftchild->leftchild == NULL || pa->leftchild->leftchild->color == black))
				//case3��x�ǡ���+�ڡ��ڵ㣬x���ֵܽڵ��Ǻ�ɫ��x���ֵܽڵ���Һ����Ǻ�ɫ�������Ǻ�ɫ�ġ�	
				//����Case 3������ת����ת���ɡ�Case 4��
			{
				pa->leftchild->rightchild->color = black;
				pa->leftchild->color = red;
				if (root) {
					root->parent = NULL;
				}
				leftroate(root, pa->leftchild);
				rbdeletefixup(root, x, pa);
			}
			else if (pa->leftchild != NULL&&pa->leftchild->color == black &&pa->leftchild ->leftchild !=NULL&&pa->leftchild->leftchild->color == red)
			{//case4���ֵܽڵ�Ϊ��ɫ���ֵܽڵ�����Ϊ��ɫ���Һ�������
				pa->leftchild->color = pa->color;
				pa->color = black;
				pa->leftchild->leftchild->color = black;
				if (root) {
					root->parent = NULL;
				}
				rightroate(root, pa);
				x = root;
				rbdeletefixup(root, x, pa);
			}
		}
	}
	if (x)
	{
		x->color = black;
	}
}
void rbdelete(node * &root,node * z)
{
	node *child,*parent;
	nodecolor col;
	if (z->leftchild == NULL || z->rightchild == NULL)//��1�����ӻ���û�к���
	{
		parent = z->parent;
		if (z->leftchild != NULL)//������ڷǿպ��ӣ�Ѱ�Һ��Ӹ���child
		{
			child = z->leftchild;
		}
		else
		{
			child = z->rightchild;
		}
		if (child)//������Ӵ��ڣ���z�ĸ�������Ϊchild�ĸ���
		{
			child->parent = z->parent;
		}
		if (z->parent)//z�ĸ��״��ڣ���z���׵ĺ�������Ϊchild
		{
			if (z == z->parent->leftchild)
			{
				z->parent->leftchild = child;
			}
			else
				z->parent->rightchild = child;
			
		}
		else//���zΪ���ڵ㣬��child����Ϊ��
		{
			root = child;
		}
		if (root) {
			root->parent = NULL;
		}
		if (z->color == black)//���z�Ǻ�ɫ�ģ�������ɫ
		{
				rbdeletefixup(root, child,parent);
		}
		delete z;
	}
	else//��˫�ӽڵ�  �ú�̽ڵ�y�滻z Ȼ���yɾ��
	{
		node *y= findpostnode(z);//y�Ǻ�̽ڵ�
		if (z!=root)//z���Ǹ�������z���׵���Ӧ����Ϊy
		{
			if (z == z->parent->leftchild)
			{
				z->parent->leftchild = y;
			}
			else
				z->parent->rightchild = y;
		}
		else//z�Ǹ�����������Ϊy
		{
			root = y;
		}
		
		child = y->rightchild;//child ������ڵ���Һ��ӣ�
		//��̽ڵ����ֻ���ҽڵ� �϶����������ӣ���Ϊ����һ����̽ڵ㣬������ڣ���ôһ���ȼ��������ӣ�������������С�ڵ�
		col = y->color;//����ڵ���ɫ
		parent = y->parent;//���childΪ�գ������������ĸ������Ҳ�����
		//ɾ������ڵ� y
		if (y->parent == z)//��ɾ���ڵ�������̽ڵ�ĸ��ڵ�
		{
			parent = y;
		}
		else
		{
			if (child)//��̽ڵ�Ҫôû�ж���Ҫôֻ��һ���������1�����ӣ�ֱ��ɾ���ýڵ㣬���øýڵ��Ψһ�ӽڵ㶥������λ�á�
			{
				child->parent = y->parent;
			}
			y->parent->leftchild = child;
			y->rightchild = z->rightchild;
			z->rightchild->parent = y;
		}
		//�滻�ڵ�y���ɾ���ڵ�
		y->parent = z->parent;
		y->color = z->color;
		y->leftchild = z->leftchild;
		z->leftchild->parent = y; 
		if (root) {
			root->parent = NULL;
		}
		if (col == black)
				rbdeletefixup(root, child,parent);

		delete z;
	}
}
node *search(node *&root,int a)//���ҹؼ���Ϊa�Ľڵ�
{//ʹ�ò�������ķ��������ȽϽڵ�Ĺؼ�ֵ
	queue<node *>u;
	if (root != NULL)
	{
		u.push(root);
		while (!u.empty())
		{
			if (a == u.front()->key)
			{
				return u.front();
			}
			node *o = u.front();
			u.pop();
			if (o->leftchild != NULL)
			{
				u.push(o->leftchild);
			}
			if (o->rightchild != NULL)
			{
				u.push(o->rightchild);
			}
		}
	}
	return NULL;
}
void rbremovekey(node *&root,node *p)//����p->value��Ӧ�Ľڵ㣬�ҵ���ɾ��
{
	node *z=new node;
	if ((z = search(root, p->key)) != NULL)
	{
		rbdelete(root, z);
	}
}
void findmax(node *root)//Ѱ�����ֵ
{
	int max = root->key;
	queue<node *>a;
	a.push(root);
	while (!a.empty())
	{
		if (a.front()->key > max)
		{
			max = a.front()->key;
		}
		node *f;
		f = a.front();
		a.pop();
		if (f->leftchild != NULL)
		{
			a.push(f->leftchild);
		}
		if (f->rightchild != NULL)
		{
			a.push(f->rightchild);
		}
	}
	cout << max;
}
void findmin(node *root)//Ѱ����Сֵ
{
	int min = root->key;
	queue<node *>a;
	a.push(root);
	while (!a.empty())
	{
		if (a.front()->key < min)
		{
			min = a.front()->key;
		}
		node *f;
		f = a.front();
		a.pop();
		if (f->leftchild != NULL)
		{
			a.push(f->leftchild);
		}
		if (f->rightchild != NULL)
		{
			a.push(f->rightchild);
		}
	}
	cout << min;
}
void swap(int a[], int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
int main()
{
	int size;
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
			m[i] = i + 1;
			n[i] = i + 1;
		}
		for (int i = size - 1; i >= 1; --i) {
			swap(m, i, rand() % i);
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
		//RB��1 �������� ��ͬ˳��ɾ��
		/*for (int i = 0; i < size; i++)
		{
			node *p = new node;
			p->key = up[i];
			insert(root, p);
		}
		for (int i = 0; i < size; i++)
		{
			node *p = new node;
			p->key = up[i];
			rbremovekey(root, p);
		}*/
		//RB��2 ���������෴ɾ��
		for (int i = 0; i < size; i++)
		{
			node *p = new node;
			p->key = up[i];
			insert(root, p);
		}
		for (int i = 0; i < size; i++)
		{
			node *p = new node;
			p->key = down[i];
			rbremovekey(root, p);
		}
		//RB��3 ����������ɾ�� 10000Use Time:139.314663
		/*
		for (int i = 0; i < size; i++)
		{
			node *p = new node;
			p->key = m[i];
			if (root)
				root->parent = NULL;
			insert(root, p);
		}
		for (int i = 0; i < size; i++)
		{
			node *p = new node;
			p->key = n[i];
			if (root)
				root->parent = NULL;
			rbremovekey(root, p);
		}*/
		QueryPerformanceCounter(&t2);
		printf("%f", (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart);
		cout << endl;
	}
	system("pause");
	return 0;
}