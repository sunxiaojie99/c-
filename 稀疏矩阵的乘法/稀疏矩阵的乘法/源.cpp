///*
//����������Ԫ���ʾ��ϡ�������г˷�����
//���룺
//��һ��Ϊ��������row��column��count���ÿո�ָ����ֱ��ʾϡ����������������������Ԫ�صĸ�����
//�ڶ��п�ʼ�����ϡ��������Ԫ�飬ÿ�������������ո�ָ����ֱ����һ������Ԫ�ص��бꡢ�бꡢֵ��������count�С�
//��һ�к�ʼ����ڶ���ϡ������row��column��count������Ԫ�顣
//�����
//���������Ϊ����������The answer is a Zero Matrix��,������Ϊ�������
//����������Ԫ���ʾ��Ҫ�������Ԫ����������޷��������˷��������ERROR����
//*/
//#include<iostream>
//using namespace std;
//class term {
//public:
//	int row, col;
//	int value;
//};//ÿһ��СԪ��
//class sparsematrix {
//public:
//	int row, col;
//	int nonzero;
//	term a[100];
//};
//int main()
//{
//	sparsematrix m1, m2,m3;
//	int count = 1,s;
//	cin >> m1.row >> m1.col >> m1.nonzero;
//	for (int i = 1; i <= m1.nonzero; i++)
//	{
//		cin >> m1.a[i].row >> m1.a[i].col >> m1.a[i].value;
//	}
//	cin >> m2.row >> m2.col >> m2.nonzero;
//	for (int i = 1; i <= m2.nonzero; i++)
//	{
//		cin >> m2.a[i].row >> m2.a[i].col >> m2.a[i].value;
//	}
//	int res[100][100];//�˷�������õ��ľ���
//	if (m1.col != m2.row) {
//		cout << "ERROR";
//	}
//	else {
//		for (int i = 1; i <= m1.row; i++)//i=1
//		{
//			for (int j = 1; j <= m2.col; j++)//j=1
//			{
//				i = 1;
//					for (int d = 1; d <= m1.nonzero; d++)//d=1 d=3 d=5
//					{
//						m3.a[count].value = 0; 
//						if (m1.a[d].row == i)//d=1 d=3
//						{
//							for (s = 1; s <= m2.nonzero; s++)//s=1 s=2 s=3
//							{
//								if (m2.a[s].col == j)//s=1 s=2 s=1
//								{
//									if (m1.a[d].col == m2.a[s].row)//yes  yes
//									{
//										m3.a[count].row = i;//1 2
//										m3.a[count].col = j;//1 1
//										m3.a[count].value += m1.a[d].value*m2.a[s].value;//1 2 ;1
//										d++;//d=2 3 4
//										if(m1.a[d].row!=i)//
//										{
//											d--;
//											i++;//i=2
//											count++;//count=2
//											break;
//										}
//									}
//								}
//							}
//							if (s > m2.nonzero)
//							{
//								if (m1.a[d].row == i)
//								{
//									count++;
//								}
//								break;
//							}
//						}
//						else {
//							i++;
//							j = 0;
//							break;
//						}
//				}
//			}
//		}
//	}
//	for (int u = 1; u <=20; u++)
//	{
//		cout << m3.a[u].row << m3.a[u].col << m3.a[u].value << endl;
//	}
//	system("pause");
//	return 0;
//}
///*
//2 3 4
//1 1 1
//1 3 1
//2 1 1
//2 2 1
//
//3 2 4
//1 1 1
//1 2 1
//3 1 1
//3 2 1
//*/

#include<iostream>
using namespace std;
int main()
{
	int a1[100][100] = {};
	int a2[100][100] = {};
	int row, col, non;
	int row1, col1, non1;
	int r, c, v;
	int k=1,sum=0;
	cin >> row >> col >> non;
	for (int i = 0; i < non; i++)
	{
		cin >> r >> c >> v;
		a1[r][c] = v;
	}
	cin >> row1 >> col1 >> non1;
	for (int i = 0; i < non1; i++)
	{
		cin >> r >> c >> v;
		a2[r][c] = v;
	}
	int count=0;
	int oldcount=0;
	if (col != row1)
		cout << "ERROR";
	else {
		for (int m = 1; m <= row; m++)
		{
			for (int n = 1; n <= col1; n++)
			{
				for (int k = 1; k <= non; k++)
				{
					sum = sum + a1[m][k] * a2[k][n];
				}
				if (sum != 0)
				{
					count++;
					if(count!=1&&count>oldcount)
					{
						cout << endl;
					}
					cout << m << " " << n << " " << sum ;
					sum = 0;
					oldcount = count;
				}
			}
		}
		if (count == 0)
			cout << "The answer is a Zero Matrix";
	}

	system("pause");
	return 0;
}