/*
�����ض��ķָ���ţ����ַ������зָ��������ָ����ַ�����
���룺��һ��Ϊ����һ���ָ���ţ��ڶ���Ϊ��Ҫ�ָ���ַ���
��������ÿ���ָ����ַ�����ÿ���ַ���ռһ��
ʾ����
���룺|
|AB|CD|
�����AB
CD
���룺;
AB;CD
�����AB
CD
*/
#include<iostream>
#include<sstream>
#include<stdio.h>
#include<string>
using namespace std;
int main()
{
	char c;
	c=getchar();
	string s;
	stringstream ss;
	getline(cin, s);//��ȡ����
	getline(cin, s);
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == c)
		{
			s[i] = ' ';
		}
	}
	ss << s;//��s cout��
	string s1;
	int flag = 0;
	while (ss >> s1)
	{ 
		if (flag != 0)
		{
			cout << endl;
		}
		cout << s1;
		flag++;
	}
	system("pause");
	return 0;
}