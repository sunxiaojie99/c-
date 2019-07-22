//�� ��ʼ���ѣ�������a[1...n]��������ѡ�
//�� �������ݣ���a[1]��a[n]������ʹa[n]��a[1...n]�е����ֵ��Ȼ��a[1...n - 1]���µ���Ϊ���ѡ� ���ţ���a[1]��a[n - 1]������ʹa[n - 1]��a[1...n - 1]�е����ֵ��Ȼ��a[1...n - 2]���µ���Ϊ���ֵ�� �������ƣ�ֱ���������ж�������ġ�
#include<iostream>
using namespace std;
void swap(int a[],int i,int j)
{
	int temp;
	temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
void maxheap(int a[],int start,int end)//���³�
{
	int cur = start;
	int l = 2 * cur + 1;
	for (; l <= end; cur=l,l = 2 * l + 1)
	{
		if (l < end&&a[l] < a[l + 1])
			l++;
		if (a[l] > a[cur])
			swap(a, l, cur);
	}
}
void heapsort(int a[],int n)
{
	int k = (n - 1) / 2;
	for (int i = k; i >= 0; i--)
	{
		maxheap(a, i, n - 1);
	}

	for (int j = n - 1; j >= 0; j--)
	{
		swap(a, 0, j);
		maxheap(a, 0, j - 1);
	}
}
int main()
{
	int n;
	int a[100];
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	heapsort(a, n);
	for (int i = 0; i < n; i++)
	{
		cout<< a[i]<<" ";
	}
	system("pause");
	return 0;
}