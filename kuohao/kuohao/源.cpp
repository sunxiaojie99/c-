/*
���ܣ�����ջ�����һ���ַ����е������Ƿ�����ƥ�䡣�ַ������Ȳ�����100��������������(),[],{},��ĸ���������š�
�涨�κ�һ�������Ŷ����ڵ����������ұ��Ҿ�������Ķ�Ӧ��������ƥ�䡣
�������룺һ�������ŵ��ַ�����������100���ַ�
������������������ַ���������ƥ�䣬���1�������ƥ�䣬���0��
Ҫ������ջ���ж������Ƿ�ƥ��
ע�⣺��ջʱ������ջ�Ƿ�Ϊ�գ����ƥ��Ľ��Ӧ����ջΪ�ա�
ʾ�����Լ�:
- ��1��
���룺
{ab[c(de)f]g}hi
�����
1
- ��2��
���룺
while(){i++[a=3;(C++]);};)
�����
0
- ��3��
���룺
{ab{c[d[(h(i)j)k]l}}{
�����
0
*/

#include<iostream>
#include<stack>
#include<string>
#include<cstdlib>
using namespace std;
int main()
{
	stack<char> skuohao;
	stack<char> mkuohao;
	stack<char> bkuohao;
	skuohao.push('#');
	mkuohao.push('#');
	bkuohao.push('#');
	string a;
	int res0 = 1, res1 = 1, res2 = 1;
	cin >> a;
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == '(')
		{
			skuohao.push('(');
		}
		if (a[i] == ')')
		{
			if (skuohao.top() == '(')
			{
				skuohao.pop();
			}
			else if (skuohao.top() == '#')
			{
				res1 = 0;
				break;
			}
		}
	}
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == '[')
		{
			mkuohao.push('[');
		}
		if (a[i] == ']')
		{
			if (mkuohao.top() == '[')
			{
				mkuohao.pop();
			}
		 else if (mkuohao.top() == '#')
			{
				res1 = 0;
				break;
			}
		}
	}
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == '{')
		{
			bkuohao.push('{');
		}
		if (a[i] == '}')
		{
			if (bkuohao.top() == '{')
			{
				bkuohao.pop();
			}
		    else if (bkuohao.top() == '#')
			{
				res2 = 0;
				break;
			}
		}
	}
	if (res0 == 0||res1==0||res2==0||skuohao.top() != '#' || mkuohao.top() != '#' || bkuohao.top() != '#')
		cout << 0;
	else cout << 1;
	system("pause");
	return 0;
}