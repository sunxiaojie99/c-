/*���̿��Է�ΪN���׶Ρ�ÿ���׶ζ����Բ��У�������������ϵ���Լ��㹤�̵��������ʱ�䡣
���������ʽ�������һ��Ϊ����N������׶θ������������N�У��ֱ�����׶α�š���ʱ���Լ�������ϵ����ͬ����ʹ��";"�ָ
���������ʽ�����̵��������ʱ��
����������
4
1 3
2 4
3 5 1;2;
4 3 3;
���������
12

���룺
4
1 3
2 4 3;
3 5 1;2;
4 3 3;
�����
error
*/


#include<iostream>
#include<string>
#include<sstream>
#include<stack>
using namespace std;
//�㷨û��ʧ�ܣ���theorder��һ��������������㷨ʧ�ܣ�����ͼû���������򣬲�������ͼ���л�·
//��һά�����ʾtheorder����һ��ջ������ɼ��뵽theorder�ĺ�ѡ���㣻��һ��һά����indegree������indegree[j]
//��ʾ����theorder�е��ڽ�������j�Ķ�����Ŀ����������theorder�ڵ����ȣ�����indegree[j]��Ϊ0ʱ�򣬶���j�ͳ�Ϊһ����ѡ����
//ÿ����theorder�м���һ������ʱ�������ڽ��ڸö���Ķ���j����indegree[j]-1
bool checkinout(int a[],int n,int t)
{
	for (int i = 0; i < n; i++)
	{
		if (a[i] == t)
			return true;
	}
	return false;
}
bool topologicalorder(int graph[100][100],int theorder[100],int n)//�������������ж��Ƿ��л�·
{
	int indegree[100] = {};
	int flag[100] = {};
	int t=0;
	stack<int> a;//��ѡ��
	for (int j = 0; j < n + 2; j++)//�������
	{
		for (int i = 0; i < n + 2; i++)
		{
			if (graph[i][j] != 10000)
			{
				indegree[j]++;
			}
		}
	}
	for (int i = 0; i < n + 2; i++)
	{
		if (indegree[i] == 0)
		{
			a.push(i);//ѹ��������ѡ��
			flag[i] = 1;
		}
	}
	while (!a.empty())
	{
		int d;
		d = a.top();//ɾ���ڼ����ڵ�
		theorder[t++] = d;
		a.pop();
		for (int i = 0; i < n + 2; i++)
		{
			if (graph[d][i] != 10000)
			{
				indegree[i]--;
			}
			if (indegree[i] == 0&&flag[i]==0)
			{
				a.push(i);
				flag[i] = 1;
			}
		}
	}
	if (t == n + 2)
	{
		return true;
	}
	return false;
}
int mintime(int graph[100][100],int x,int n)//�󶥵�x����Сʱ��
{
	int max=-1;
	int i;
	if (x == 0)return 0;
	else
	{
		for (i = 0; i < n + 2; i++)
		{
			if (graph[i][x] != 10000)
			{
				if (graph[i][x] + mintime(graph, i, n) > max)
					max = graph[i][x] + mintime(graph, i, n);
			}
		}
	}
	return max;
}
int main()
{
	int graph[100][100];
	int theorder[100];
	int n;
	cin >> n;
	string s;
	getline(cin, s);//��ȡ���У�����
	//��ʼ������
	int m = n + 2;
	for (int i = 0; i < n+2; i++)//�Ӵ�һ�����Ϊ0�ĵ� ��0�� ��һ������Ϊ0�ĵ� ��n+1��
	{
		for (int j = 0; j < n + 2; j++)
		{
			graph[i][j] = 10000;
		}
	}
	for (int i = 0; i < n; i++)//��ȡ����
	{
		getline(cin, s);
		stringstream ss;
		ss << s;
		int end, value;
		ss >> end >> value;
		string a;//������
		ss >> a;
		if (a.length() != 0)
		{
			for (int i = 0; i < a.length(); i++)
			{
				if (a[i] == ';')
					a[i] = ' ';
			}
			ss.clear();//���������ַ���
			ss.str(a);
			int d;
			while (ss>>d)
			{
				graph[d][end] = value;
			}
		}
		else
		{
			graph[0][end] = value;
		}
	}
	int flag = 1;
	//����û�г��ȵıߣ�����һ�����ȵ�����0���ȵ�
	for (int i = 0; i < n + 1; i++)//���һ�����ӵ㲻�ò��� ȫΪ10000�����ĸ��㶼û�б�
	{
		for (int j = 0; j < n + 2; j++)
		{
			if (graph[i][j] != 10000)
			{
				flag = 0;
			}
		}
		if (flag == 1)
		{
			graph[i][n + 1] = 0;
		}
		flag = 1;
	}
	if (topologicalorder(graph, theorder, n) == false)
	{
		cout << "error";
	}
	else
	{
		cout << mintime(graph, n+1, n);
	}
	system("pause");
	return 0;
}