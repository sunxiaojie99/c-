/*
���壺m��B-����B-Tree of order m����һ��m�������������B-���ǿգ���ô��Ӧ����������������������
�̸��ڵ�������2������
�̳����ڵ��⣬�����ڲ��ڵ�������ceil[m/2]������ (ceil(m/2)-1��Ԫ��)
�������ⲿ�ڵ㣨Ҷ�ڵ㣩λ��ͬһ����

����B-������������ //����Ҷ�ڵ���ͬһ�㣬��������������
����B-����2-3�� //������2��3���� ����
�Ľ�B-����2-3-4��

B ���ֽ�ƽ���·��������һ��m�׵�B �� (m����)���������£�
	����ÿ�������ຬ��m�����ӣ�m>=2����
	��������Ҷ�ӽ���⣬����ÿ�����������[ceil(m / 2)]�����ӣ�����ceil(x)��һ��ȡ���޵ĺ�������
	������㲻��Ҷ�ӽ�㣬��������2�����ӣ����������û�к��ӵĸ���㣬�������ΪҶ�ӽ�㣬������ֻ��һ�����ڵ㣩��
	����Ҷ�ӽ�㶼������ͬһ�㣬Ҷ�ӽ�㲻�����κιؼ�����Ϣ(���Կ������ⲿ�ӵ���ѯʧ�ܵĽӵ㣬ʵ������Щ��㲻���ڣ�
ָ����Щ����ָ�붼Ϊnull)��
	ÿ�����ն˽���а�����n���ؼ�����Ϣ�� (n��P0��K1��P1��K2��P2��......��Kn��Pn)�����У�
a)   Ki (i=1...n)Ϊ�ؼ��֣��ҹؼ��ְ�˳����������K(i-1)< Ki��
b)   PiΪָ���������Ľӵ㣬��ָ��P(i-1)ָ�����������н��Ĺؼ��־�С��Ki����������K(i-1)��
c)   �ؼ��ֵĸ���n�������㣺 [ceil(m / 2)-1]<= n <= m-1��
https://blog.csdn.net/jesseshen/article/details/6643747
*/
/*
typedef struct Student
��������{
	��������int a;
		��������}Stu;
			������������������������ʱ��Ϳɣ�Stu stu1;(���û��typedef�ͱ�����struct Student stu1;������)
				�������������Stuʵ���Ͼ���struct Student�ı�����Stu==struct Student
*/
#include<iostream>
#include<Queue>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<functional>
#include<Windows.h>
#define Keytype int
#define Record string
using namespace std;
const int m = 4;//����
typedef struct btnode {
public:
	int keynum;//�ڵ�ؼ��ָ���
	Keytype key[m + 1];//�ؼ������� key[0]δ�� 4�� �����3��Ԫ��
	//1<=n<=3
	struct btnode *parent;//˫�׽��ָ��
	struct btnode *ptr[m + 1];//���ӽ��ָ������ �����4������ָ�� ��0��ʼ
	Record *recptr[m + 1];
	btnode()
	{
		keynum = 0;
		parent = NULL;
		for (int i = 0; i < m + 1; i++)
		{
			ptr[i] = NULL;
		}
	}
}btnode,*btree;
btree t = NULL;
class result {//b�����ҵĽ������
public:
	btree pt;//ָ���ҵ��Ľڵ�
	int i;//1<=i<=m �ڽڵ��йؼ���λ��
	int tag;//1 ���ҳɹ� 0����ʧ��
};
int search(btree p,int k)//��p->key[1..p->keynum]��k 
{
	int i = 1;
	while (i <= p->keynum &&k > p->key[i])i++;
	return i;
}
void searchbtree(btree t,int k,result &r)
{
	//��m��B��t�ϲ��ҹؼ���k����r����(pt,i,tag).
	//�����ҳɹ�������tag=1��ָ��pt��ָ����е�i���ؼ��ֵ���k��
	//����tag=0����Ҫ����ؼ���Ϊk�ļ�¼��Ӧλ��pt����е�i-1���͵�i���ؼ���֮��
	int i = 0,found = 0;
	btree p = t, q = NULL;
	//��ʼ��pָ����ڵ㣬p������ָ������ҽ�㣬qָ����˫��
	while (p != NULL && found == 0)
	{
		i = search(p, k);
		if (i <= p->keynum &&p->key[i] == k)//�ڹؼ��ַ�Χ�� ����ֵ���
		{
			found = 1;
		}
		else
		{
			q = p;
			p = p->ptr[i - 1];//ָ������
		}
	}
	if (found == 1)
	{
		r = { p,i,1 };
	}
	else
	{
		r = { q,i,0 };
	}
}
void split(btree &q, int s, btree &ap) {
	//��q�����ѳ�������㣬ǰһ�뱣����ԭ��㣬
	//��һ������ap��ָ�½��
	int n = q->keynum;
	ap = (btnode*)malloc(sizeof(btnode));//�����µĽڵ�
	ap->ptr[0] = q->ptr[s];
	for (int i = 1, j = s + 1; j <= n; j++, i++)//��һ������ap
	{
		ap->ptr[i] = q->ptr[j];
		ap->key[i] = q->key[j];
	}
	ap->keynum = n - s;
	q->keynum = s - 1;
	ap->parent = q->parent;//�½ڵ�ĸ���ָ��
	for (int i = 0; i <= ap->keynum; i++)//���ӽڵ�ĸ������¸�ֵ
	{
		if (ap->ptr[i]!=NULL)
		{
			ap->ptr[i]->parent = ap;
		}
	}
}
void newroot(btree &t, btree p,int x, btree ap)//�����µĸ� ֻ��2������
{
	t = (btnode*)malloc(sizeof(btnode));
	t->keynum = 1; t->ptr[0] = p; t->ptr[1] = ap;
	t->key[1] = x;
	if (p!=NULL)p->parent = t;
	if (ap!=NULL)ap->parent = t;
	t->parent = NULL;
}
void insert(btree &q, int i, int x, btree ap)
{
	//�ؼ���x���½��ָ��ap�ֱ�嵽q->key[i]��q->ptr[i]
	int n = q->keynum;
	for (int j = n; j >= i; j--)
	{
		q->key[j + 1] = q->key[j];
		q->ptr[j + 1] = q->ptr[j + 1];
	}
	q->key[i] = x;
	q->ptr[i] = ap;
	if (ap!=NULL)ap->parent = q;
	q->keynum++;
}
void insertbtree(btree &t,int k, btree q,int i)
{
	//��B����q����key[i-1]��key[i]֮�����ؼ���k
	//���������ؼ��ָ�������b���Ľף�������˫��ָ�������н����ѣ�ʹ��t����m��B��
	int x, s, finished = 0, neednewroot = 0;
	btree ap;
	if (q == NULL)
		newroot(t, NULL, k, NULL);
	else
	{
		x = k; ap =NULL;
		while (neednewroot == 0 && finished == 0)
		{
			insert(q, i, x, ap);//x��ap�ֱ�嵽q->key[i]��q->ptr[i]
			if (q->keynum < m)finished = 1;//�������
			else
			{
				s = (m + 1) / 2;//��СԪ�ظ���
				split(q, s, ap);
				x = q->key[s];
				if (q->parent!=NULL)
				{
					q = q->parent;
					i = search(q, x);
					//��˫�׽���в���x�Ĳ���λ��
				}
				else
				{
					neednewroot = 1;
				}
			}
		}
		if (neednewroot == 1)
		{
			//t�ǿ������߸�����Ѿ����ѳ�Ϊq��ap���
			newroot(t, q, x, ap);
		}
	}
}
void successor(btree &p,int i)//�ɺ�����²���ն˽�����С�ؼ��ִ������йؼ���key[i]
{
	btree child = p->ptr[i];
	while (p->ptr[0]!=NULL)child = child->ptr[0];
	p->key[i] = child->key[i];
	p = child;
}
void remove(btree &p,int i)
{
	int j, n = p->keynum;
	for (j = i; j < n; j++)
	{
		p->key[j] = p->key[j + 1];
		p->ptr[j] = p->ptr[j + 1];
	}
	p->keynum--;
}
void restore(btree &p, int i, btree &t)//��b�����е���
{
	int j;
	btree ap = p->parent;
	if (ap == NULL)//�����������ֿյĸ��ڵ㣬��ɾ���ø��ڵ㣬���߼�1
	{
		t = p; //���ڵ�������
		p = p->parent;
		return;
	}
	btree lc, rc, pr;//���ֵ����ֵ�
	int finished = 0, r = 0;
	while (!finished)
	{
		r = 0;
		while (ap->ptr[r] != p)r++;//ȷ��p��ap�����е�λ��
		if (r == 0)
		{
			r++;
			lc = NULL; rc = ap->ptr[r];
		}
		else if (r == ap->keynum)
		{
			rc = NULL; lc = ap->ptr[r - 1];
		}
		else
		{
			lc = ap->ptr[r - 1];
			rc = ap->ptr[r + 1];
		}
		if (r > 0 && lc != NULL && (lc->keynum > (m - 1) / 2))//�����ֵܽ�ؼ���
		{
			p->keynum++;
			for (j = p->keynum; j > 1; j--)//�ؼ�������
			{
				p->key[j] = p->key[j - 1];
				p->ptr[j] = p->ptr[j - 1];
			}
			p->key[1] = ap->key[r];//���ײ��뵽�ڵ�
			p->ptr[1] = p->ptr[0];
			p->ptr[0] = lc->ptr[lc->keynum];//�����ֵܵ����Һ��Ӹ����ڵ��������
			if (p->ptr[0]!=NULL)//�޸�p�е���Ů�ĸ��ڵ�Ϊp
				p->ptr[0]->parent = p;
			ap->key[r] = lc->key[lc->keynum];//���ֵ����Ƶ�����λ��
			lc->keynum--;
			finished = 1;
			break;
		}
		else if(ap->keynum >r&&rc!=NULL&&(rc->keynum >(m-1)/2))//���ҽڵ��
		{
			p->keynum++;
			rc->ptr[0] = rc->ptr[1];//key�Ǵ�1 ��ʼ�ģ����Ե�����ptr0�����
			for (j = 1; j < rc->keynum; j++)//���ֵܽڵ�ؼ�������
			{
				p->key[j] = p->key[j+1];
				p->ptr[j] = p->ptr[j + 1];
			}
			p->key[p->keynum] = ap->key[r];//���ײ��뵽�ڵ�
			p->ptr[p->keynum] = rc->ptr[0];//���ֵܽڵ������Ӹ�ֵ���ýڵ�����Һ���
			if (p->ptr[p->keynum]!=NULL)//�޸�p����Ů�ĸ��ڵ�
			{
				p->ptr[p->keynum]->parent = p;
			}
			ap->key[r] = rc->key[1];//���ֵ����Ƶ�����λ��
			rc->keynum--;
			finished = 1;
			break;
		}
		r = 0;
		while (ap->ptr[r] != p)//����ȷ��p��ap�е�λ��
			r++;
		if (r > 0 && (ap->ptr[r - 1]->keynum <= (m - 1) / 2))//�����ֵܺϲ�
		{
			lc = ap->ptr[r - 1];
			p->keynum++;
			for (j = p->keynum; j > 1; j--)//��p���ؼ��ֺ�ָ������һλ
			{
				p->key[j] = p->key[j - 1];
				p->ptr[j] = p->ptr[j - 1];
			}
			p->ptr[1] = p->ptr[0];
			p->key[1] = ap->key[r];
			ap->ptr[r] = lc;
			for (j = 1; j <= lc->keynum + p->keynum; j++) //�����p�йؼ��ֺ�ָ���Ƶ�p���ֵ���
			{
				lc->key[lc->keynum + j] = p->key[j];
				lc->ptr[lc->keynum + j] = p->ptr[j];
			}
			if (p->ptr[0])//�޸�p����Ů�ĸ��ڵ�lc
			{
				for (j = 1; j <= p->keynum; j++)//////////////////////////////////
					if (p->ptr[p->keynum + j])
						p->ptr[p->keynum + j]->parent = lc;
			}
			ap->keynum--;
			pr = p;
			free(pr);
			pr = NULL;
			p = lc;
		}
		else//�����ֵܺϲ�
		{
			rc = ap->ptr[r + 1];
			if (r == 0)
				r++;
			p->keynum++;
			p->key[p->keynum] = ap->key[r];//�����Ĺؼ�����p�ϲ�
			p->ptr[p->keynum] = rc->ptr[0]; //�����ֵ�����һ��ָ��
			rc->keynum = p->keynum + rc->keynum;//�ϲ���ؼ��ֵĸ���
			ap->ptr[r - 1] = rc;
			for (j = 1; j <= (rc->keynum - p->keynum); j++)//��p���ֵܹؼ��ֺ�ָ������
			{
				rc->key[p->keynum + j] = rc->key[j];
				rc->ptr[p->keynum + j] = rc->ptr[j];
			}
			for (j = 1; j <= p->keynum; j++)//�����p�йؼ��ֺ�ָ���Ƶ�p���ֵ�
			{
				rc->key[j] = p->key[j];
				rc->ptr[j] = p->ptr[j];
			}
			rc->ptr[0] = p->ptr[0];//�޸�p����Ů���ڵ�Ϊrc
			if (p->ptr[0])
			{
				for (j = 1; j <= p->keynum; j++)//////////////////////////////////////
				{
					if (p->ptr[p->keynum + j])
						p->ptr[p->keynum + j]->parent = rc;
				}
			}
			for (j = r; j<ap->keynum; j++)//��������йؼ��ֺ�ָ������
			{
				ap->key[j] = ap->key[j + 1];
				ap->ptr[j] = ap->ptr[j + 1];
			}
			ap->keynum--;//�����Ĺؼ��ָ�����1
			pr = p;
			free(pr);
			pr = NULL;
			p = rc;
		}
		ap = ap->parent;
		if (p->parent->keynum >= (m - 1) / 2 || (NULL == ap&&p->parent->keynum > 0))
		{
			finished = 1;
		}
		else if (ap == NULL)//����������ֿյĸ���㣬��ɾ���ø���㣬���߼�1
		{
			pr = t;
			t = p;//���������
			free(pr);
			pr = NULL;
			finished = 1;
		}
		p = p->parent;
	}
}
void deletebtree(btree &p,int i, btree &t)//ɾ��B����p���ĵ�i���ؼ���
{
	if (p->ptr[i] != NULL)//�����������²���ն˽��
	{
		successor(p, i);//��Ai�������ҳ����²���ն˽�����С�ؼ������ki
		deletebtree(p, 1, t);//ת��Ϊɾ�����²���ն˽�����С�ؼ���
	}
	else {//�������²���ն˽��
		remove(p, i);
		if (p->keynum<(m - 1) / 2)//ɾ����ؼ��ָ���С��(m-1)/2
			restore(p, i, t);//����B��
	}
}
void show_Btree(btree &p)
{
	if (p == NULL) { puts("B tree does not exist"); return; }
	bool have_child = false;
	cout << "[";
	for (int i = 1; i <= p->keynum; i++)
	{
		if (i == 1);
		else cout << " ";
		cout << p->key[i];
	}
	cout << "]";
	for (int i = 0; i <= p->keynum; i++)
	{
		if (p->ptr[i] != NULL)
		{
			if (i == 0) cout << "<";
			else cout << ",";
			show_Btree(p->ptr[i]);
			have_child = true;
		}
	}
	if (have_child) cout<< ">";
}
void show_Btree2(btree &p, int deep)
{
	if (p == NULL) { return; }
	int i;
	for (i = 0; i < p->keynum; i++)
	{
		show_Btree2(p->ptr[i], deep + 1);
		for (int i = 0; i<deep; i++)
		{
			printf("\t");
		}
		printf("%d\n", p->key[i + 1]);
	}
	show_Btree2(p->ptr[i], deep + 1);

}
void destory(btree &t)
{
	int i = 0;
	if (t!=NULL)
	{
		while (i < t->keynum)
		{
			destory(t->ptr[i]);
			free(t->ptr[i]);
			i++;
		}
	}
	free(t);
	t = NULL;
}
void insert_keytype()
{
	Keytype temp;
	cin >> temp;
	result p;
	searchbtree(t, temp, p);
	if (p.tag == 0)
	{
		insertbtree(t, temp, p.pt, p.i);
		puts("Insert success"); show_Btree(t);
		puts("");
	}
	else
		puts("The element is already in the B tree.");
}
void find_keytype()
{
	puts("enter an element to find");
	Keytype temp;
	cin >> temp;
	result p;
	searchbtree(t, temp, p);
	if (p.tag)
	{
		puts("find success");
	}
	else
		puts("lookup failure");
}
void delete_keytype()
{
	puts("enter an element to be deleted");
	Keytype temp;
	cin >> temp;
	result p;
	searchbtree(t, temp, p);
	if (p.tag)
	{
		deletebtree(p.pt, p.i, t);
		puts("delete success");
		show_Btree(t);
		puts("");
	}
	else
		puts("The element does not exist in the B tree.");
}
void swap(int a[], int i, int j)
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
		//��ʱ����

		LARGE_INTEGER t1, t2, tc;
		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);

		btree T = new btnode;
		T->keynum = 0;
		result p;
		//BTree1 �������� ��ͬ˳��ɾ��
		for (int i = 0; i < size; i++)
		{
			searchbtree(t, up[i], p);
			insertbtree(t, up[i], p.pt, p.i);
		}
		for (int i = 0; i<size; i++)
		{
			searchbtree(T, up[i], p);
			if (p.tag)
			{
				deletebtree(p.pt, p.i, T);
			}
			else
			{
				printf("%d is not in the tree\n", up[i]);
			}
		}
		//BTree2 �������룬�෴˳��ɾ��
		for (int i = 0; i < size; i++)
		{
			searchbtree(t, up[i], p);
			insertbtree(t, up[i], p.pt, p.i);
		}
		for (int i = 0; i<size; i++)
		{
			searchbtree(T, down[i], p);
			if (p.tag)
			{
				deletebtree(p.pt, p.i, T);
			}
			else
			{
				printf("%d is not in the tree\n", down[i]);
			}
		}
		//BTree3 ����������ɾ��
		for (int i = 0; i < size; i++)
		{
			searchbtree(t, m[i], p);
			insertbtree(t, m[i], p.pt, p.i);
		}
		for (int i = 0; i<size; i++)
		{
			searchbtree(T, n[i], p);
			if (p.tag)
			{
				deletebtree(p.pt, p.i, T);
			}
			else
			{
				printf("%d is not in the tree\n", n[i]);
			}
		}

		QueryPerformanceCounter(&t2);
		printf("%f", (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart);
		cout << endl;
	}
	system("pause");
	return 0;
}