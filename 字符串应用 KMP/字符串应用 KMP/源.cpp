/*
����һ������S���Ӵ�P��ʹ��KMP�㷨�����Ӵ�P������S�д��ڵ�λ�ã����Ӵ�P������S�д��ڣ�
��������Ӵ�P�е�һ�ַ���ȵ��ַ�������S�е���ţ����������������no��
���������ʽ������S �Ӵ�P��
���������ʽ��������Ӵ�P�е�һ�ַ���ȵ��ַ�������S�е���ţ�
����������ababcabcacbab abcac
���������5
*/
#include<iostream>
#include<string>
using namespace std;
//void next(char T[], int Next[], int len) //�����㷨
//{
//	int k = 0, j = 1; //k��ǰ׺ j�Ǻ�׺
//	Next[1] = 0;
//	while (j<len)
//	{
//		if (k == 0 || T[k] == T[j])//���j�Ǳȵ����һ��,��ôӦ����j�����һ����nextλ�ø�Ϊk+1(kΪ�غ϶�)
//		{
//			k++;
//			j++;
//			Next[j] = k;
//		}
//		else k = Next[k];
//	}
//}
void next(char T[],int Next[], int len)//�˳����������1 ��ʼ����
{
	int i = 3,j,k;//i��next�����λ�� j����i��ǰ���ҵ��ĵ�һ����i-1��ȵ�ֵ��λ��
	int yes=0;
	Next[1] = 0;
	Next[2] = 1;
	for (i = 3; i <=len ; i++)
	{
		k = i;//i�ܱ䣬Ҫ�䵱next�����ָ�������Ե�����һ������k
		j = k - 2;//j������i��ǰ���ҵ��ĵ�һ����i-1��ȵ�ֵ��λ�ã���ʼ����i-1ǰһ����ʼ����i-2��
		while(j>0)
		{
			if (T[k - 1] == T[j])//����ҵ���i-1��ȵĵ�һ��λ�ã���ȥ��k-1��j����ǰ��������һ���Ƿ���ȣ������ȼ�¼yes++
			{
				k--;
				j--;
				yes++;
			}
			else { j--;yes = 0; }//�������ȣ�������ǰѰ����һ����i-1��ȵ�λ�ã����ôμ�����yes��������Ϊ0
		}
		if (yes == 0) Next[i] = 1;//���yesΪ0������û����ȵ�ǰ׺�ͺ�׺��next[i]=0+1
		if(yes!=0)//���yes������0����������ȵ�ǰ׺�ͺ�׺��next[i]=yes+1
		{ Next[i] = yes + 1;
		yes = 0;
		}
	}

}
int main()
{
	string T, S;
	cin >> S >> T;
	char ss[100], tt[100];
	int Next[100];
	int lens = S.length();
	int lent = T.length();
	for (int i = 1; i <= lens; i++)
	{
		ss[i] = S[i - 1];
	}
	for (int i = 1; i <= lent; i++)
	{
		tt[i] = T[i - 1];
	}
	next(tt, Next, lent);
	int p = 1;
	int j = 1;
	int flag = 1;
	while (p <= lens&&j <= lent)
	{
		if (ss[p] == tt[j])
		{
			p++;
			j++;
			flag = 1;
		}
		else
		{
			flag = 0;
			j = Next[j];
			if (p >= lens - lent + 1) { cout << "no"; break; }
		}

		if (j > lent&&flag == 1) { cout << p - lent-1 << endl; break; }
		if (j == 0) { j = 1; p++; };
	}
	system("pause");
	return 0;
}