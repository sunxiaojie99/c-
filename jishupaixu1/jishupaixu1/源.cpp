#include<iostream>
using namespace std;
int findmax(int a[],int num)//�ҳ����Ԫ��
{
	int max;
	max = a[0];
	for (int i = 0; i < num; i++)
	{
		if (a[i] > max)
			max = a[i];
	}
	return max;
}
int findlength(int x)//�ҳ�Ԫ�ص�λ��
{
	int len=1;
	while (x >= 10)
	{
		x /= 10;
		len++;
	}
	return len;
}
void sort(int a[],int len,int num)//lenΪ�������λ����numΪ����Ԫ�ظ���
{
	int bucket[10][100] = {0};//���ո�λ�����Ͱ����
	int num10=1;
	for (int h = 1; h < len; h++)//10��len�η�
	{
		num10 = num10 * 10;
	}
	//cout << len << endl;
	//cout << num10<<endl;
	for (int l = 1; l <= num10; l *= 10)//���������λ��ˢ��Ͱ��˳��
	{
			for (int k = 0; k < 10; k++)//Ͱ������ָ��
			{
				int g = 0;//��ά����ÿһ���ָ��
				for (int j = 0; j < num; j++)//ԭ����ָ��
				{
					if (((a[j] / l)%10) == k)
					{
						bucket[k][g] = a[j];
						//cout << bucket[k][g] << " ";
						g++;
					}
				}
				//cout << endl;
			}
		
		for (int j = 0, i = 0; j < 10; j++)//���� ˢ��ԭ���飬jΪbucket�����꣬mΪ������
		{
			for (int m=0; m < 100; m++)
			{
				
				if (bucket[j][m] != 0)
				{
					//cout << bucket[j][m]<<" ";
					a[i] = bucket[j][m];
					bucket[j][m] = 0;//�ٴ��ÿ�
					i++;
				}
			}
			//cout << endl;
		}
		for (int h = 0; h < num; h++)
		{
			cout << a[h] << " ";
		}
		cout << endl;
	}
}
int main()
{
	int n,max,len;
	cin >> n;
	int a[100];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	max = findmax(a, n);
	len=findlength(max);
	sort(a, len, n);
	/*for (int h = 0; h < n; h++)
	{
		cout << a[h]<<" ";
	}*/
	system("pause");
	return 0;
}
