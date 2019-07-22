/*
��n�����m������ߡ�ÿ���ߵĳ�����d��������p���������s���յ�t�����������s��t��̵ľ�����?
������Ҫ�������ĳɱ��������̵ľ����ж��ѡ����Ӧ��ѡ�񻨷����ٵ�·�ߡ�
input
There are multiple test cases. For each test case, the first line has two integers n and m, 
which are mentioned above, followed by m lines. For each line, there are four integers a, b, d and p, which means there is an edge between a and b. The length of the edge is d, and the cost is p. Then the last line has the two integers s and t as mentioned above. 
When n and m are 0, the input ends.
Output
Output the shortest distance and its cost in one line, separated by space.
���룺
3 2
1 2 5 6
2 3 4 5
1 3
0 0
�����
9 11
*/
#include<iostream>
using namespace std;
void init(int a[100][100],int n)
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			a[i][j] = 1000000;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		a[i][i] = 0;
	}
}
int findmin(int dis[100],int s,int cost[100][100],int flag[100],int n)
{
	int min = 1000000;
	int index;
	int i;
	for (i = 1; i <= n; i++)
	{
		if (dis[i] < min&&flag[i]==0)
		{
			min = dis[i];
			index = i;
		}
		/*if (dis[i] == min&&flag[i] == 0)
		{
			if (cost[s][i] < cost[s][index])
			{
				index = i;
			}
		}*/
	}
	return index;
}
int ifempty(int flag[100],int n)
{
	for (int i = 1; i <= n; i++)
	{
		if (flag[i] != 1)
		{
			return 0;
		}
	}
	return 1;//ȫ������ѡ�����
}
int dijkstra(int road[100][100],int cost[100][100],int dis[100],int s,int n,int m,int t)//��sΪԴ����С��·��������С�ķ�
{
	int money = 0;
	int pre[100] = {};
	int flag[100];
	for (int i = 1; i <= n; i++)//��ʼ��flag
	{
		flag[i] = 0;
	}
	flag[s] = 1;
	for (int i = 1; i <= n; i++)//��ʼ��dis����
	{
		dis[i] = road[s][i];
	}
	for (int i = 1; i <= n; i++)//��ʼ��pre���� s��preҲ���Լ�
	{
		if (dis[i] != 1000000)
		{
			pre[i] = s;
		}
	}
	while (!ifempty(flag, n))
	{
		int v = findmin(dis, s, cost, flag, n);
		flag[v] = 1;
		for (int i = 1; i <= n; i++)
		{
			if (road[v][i] != 0 && road[v][i] != 1000000)
			{
				if (dis[v] + road[v][i] < dis[i])
				{
					dis[i] = dis[v] + road[v][i];
					pre[i] = v;
				}
			}
		}
	}
	int p = t;
	while (pre[p] != p)
	{
		int u = pre[p];
		money += cost[u][p];
		p = u;
	}
	return money;
}
int main()
{
	int road[100][100];
	int dis[100];//ÿ���� ����Դ�����С����
	int cost[100][100];
	int s, t;//Դ��ͳ�ʼ��
	int m, n;//n���㣬m����
	int a, b, c, d;//a��b֮����һ���ߣ������ߵĳ�����d��������p
	while (1)
	{
		cin >> n >> m;
		if (m == 0 && n == 0)
		{
			break;
		}
		init(road, n);
		init(cost, n);
		for (int i = 1; i <= m; i++)
		{
			cin >> a >> b >> c >> d;
			road[a][b] = c;
			road[b][a] = c;
			cost[a][b] = d;
			cost[b][a] = d;
		}
		cin >> s >> t;
		int money=dijkstra(road, cost, dis, s,n,m,t);
		cout << dis[t] << " " << money;
		cout << endl;
	}
	return 0;
}
//
//#include<iostream>
//using namespace std;
//void init(int a[100][100],int n)
//{
//	for (int i = 1; i <= n; i++)
//	{
//		for (int j = 1; j <= n; j++)
//		{
//			a[i][j] = 1000000;
//		}
//	}
//	for (int i = 1; i <= n; i++)
//	{
//		a[i][i] = 0;
//	}
//}
//int main(){
//		int road[100][100];
//		int dis[100];//ÿ���� ����Դ�����С����
//		int cost[100][100];
//		int s, t;//Դ��ͳ�ʼ��
//		int m, n;//n���㣬m����
//		int a, b, c, d;//a��b֮����һ���ߣ������ߵĳ�����d��������p
//		while (1)
//		{
//			cin >> n >> m;
//			if (m == 0 && n == 0)
//			{
//				break;
//			}
//			init(road, n);
//			init(cost, n);
//			for (int i = 1; i <= m; i++)
//			{
//				cin >> a >> b >> c >> d;
//				road[a][b] = c;
//				road[b][a] = c;
//				cost[a][b] = d;
//				cost[b][a] = d;
//			}
//			cin >> s >> t;
//			for (int k = 1; k <= n; k++)
//			{
//				for (int i = 1; i <= n; i++)
//				{
//					for (int j = 1; j <= n; j++)
//					{
//						if (road[i][j] > road[i][k] + road[k][j])
//						{
//							road[i][j] = road[i][k] + road[k][j];
//							cost[i][j] = cost[i][k] + cost[k][j];
//						}
//						else if (road[i][j] == road[i][k] + road[k][j])
//						{
//							if (cost[i][j] > cost[i][k] + cost[k][j])
//							{
//								cost[i][j] = cost[i][k] + cost[k][j];
//							}
//						}
//					}
//				}
//			}
//			cout << road[s][t] << " " << cost[s][t]<<endl;
//		}
//		return 0;
//}