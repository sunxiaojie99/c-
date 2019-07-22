//Kruskal�㷨
#include<iostream>
using namespace std;
class road
{
public:
	int start;
	int end;
	int weight;
};
void sort(road a[], int m)//�ȶ�����������·�����򣬴���С�����μ���
{
	for (int i = 0; i<m; i++)
	{
		for (int j = i+1; j<m; j++)
		{
			if (a[i].weight >a[j].weight)
			{
				road t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
		}
	}
}
int findroot(int root[], int x)//�ҵ�ĳ��λ�õĸ��ڵ� ��root�����е�ֵ����������ֵ
{
	if (root[x] == x)
	{
		return x;
	}
	else
	{
		x = root[x];
		findroot(root, x);
	}
}
void minroad(road a[], int n, int m, int root[])//����С·�����ܺ���
{
	int i = 0;
	int sum = 0; 
	int count = 0;
	for (i = 0; i<m; i++)
	{
		int a1 = findroot(root, a[i].start);
		int a2 = findroot(root, a[i].end);
		if (a1 != a2)//�����������������������ǵĸ���һ������ͬԴ����ѵ�һ�����ĸ���ֵ��ֵ���ڶ���������rootֵ
		{
			root[a2] = a1;
			sum = sum + a[i].weight;//���ýڵ�ĳ����ɵ�·������
			count++;
		}
	}
	if (count == n - 1)//�����n-1��·���ˣ��������г��У�n��������������
	{
		cout <<sum;
	}
	else
		cout << "Impossible";
}
int main()
{
	road a[100] = {};
	int root[100];//���鼯
	int n, m;
	cin >> n >> m;
	for (int i = 0; i<m; i++)
	{
		cin >> a[i].start >> a[i].end >> a[i].weight;
	}
	for (int i = 1; i <= n; i++)
	{
		root[i] = i;
	}
	sort(a, m);
	minroad(a, n, m, root);
	system("pause");
	return 0;
}