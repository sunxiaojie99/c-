#include<iostream>
using namespace std;
const int inf = 1e9;
int min(int a,int b)
{
	if (a > b)
		return b;
	else return a;
}
int main()
{
	int n,s;
	cin >> n>>s;
	int time[6000];
	int cost[6000];
	int f[6000];
	for (int j = 0; j <= n; j++)//��ʼ��f
	{
		f[j] = inf;
	}
	for (int i = 1; i <= n; i++)
	{
		cin >> time[i] >> cost[i];
	}
	for (int i = 2; i <= n; i++)//time[i]��ʾ����1��i��ʱ����ۼ�(ǰ׺��)�� cost[i]��ʾ����1��i�ķ���ϵ�����ۼ�(ǰ׺��)��
	{
		time[i] = time[i - 1] + time[i];
		cost[i] = cost[i - 1] + cost[i];
	}
	//f[i]��ʾ(��ɹ���1��i�ķ���)+(��������S���µĺ���Ĺ������ӵķ���)���ܺ͵���Сֵ
	f[0] = 0; cost[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			f[i] = min(f[i],f[j]+time[i]*(cost[i]-cost[j])+s*(cost[n]-cost[j]));
		}
	}
	/*
	j�������飬��ʾ�ѹ���j+1������i�ֵ�ͬһ���С�
	t[i]*(f[i]-f[j]) ��ʾ���j+1��i��һ�鹤���ķ���
	s*(f[n]-f[j])��ʾ��Ϊ������һ�ο��������´ӹ���j+1������n���ӵķ��á� 
	*/
	cout << f[n];
	system("pause");
	return 0;
}