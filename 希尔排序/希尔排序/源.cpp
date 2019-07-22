#include<iostream>
using namespace std;
void hillsort(int a[],int n)
{
	int gap,i,j,temp;
	int count = 0;
	for (gap = n / 2; gap >= 1; gap /= 2)
	{
		for (i = 0; i < n; i++)//��һ��gapԪ�صĿ�ʼλ��
		{
			for (j = i; j+gap < n; j += gap)//ÿ��gap��һ���������򣬲������򣬰�һ������������������У��ƶ�����������
			{
				if (a[j + gap] < a[j])//�����һ��Ԫ��С����һ��
				{
					temp = a[j + gap];//��¼�����Ԫ��
					while (j >= 0 && a[j] > temp)//������������������б����Ԫ�ش�����������ƶ�
					{
						a[j + gap] = a[j];
						j -= gap;
					}
					a[j + gap] = temp;//�����������
				}
			}
		}
		count++;
		if (count != 1)
		{
			cout << endl;
		}
		for (int i = 0; i < n; i++)
		{
			cout << a[i];
			if (i != n - 1)
				cout << " ";
		}
	}
}
int main()
{
	int a[100];
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	hillsort(a, n);
	system("pause");
	return 0;
}