/*
����:
���һ�����ʽ��ֵ�ĳ��򡣸ó��������Խ��ܰ�����������+��-��*��/��%��^(����)����׺���ʽ������������������ʽ��ȷ����������ʽ��ֵ��������ʽ�Ƿ��������������Ϣ��
ע��2^2^3תΪ��׺ӦΪ223^^
����Ҫ��
������ʽ��ÿ�����ʽռһ�С�
���Ҫ��
��ÿ�����ʽ�����Ϊ��ȷ���ʽ������������ȷ��С�������λ�������Ϊ������ʽ�������ERROR IN INFIX NOTATION��.

ʾ�����Լ�:
- ��1��
���룺
(2-4)^3
�����
-8.00
*/
//1.double atof(const char *nptr);
//���ַ���ת���ɸ�����ֵ��
//<math.h>��<stdlib.h>
//nptr����ת�����ַ�����
//��������������ַ�����˫���ȸ�����ֵ��
//
//int atoi(const char* nptr);
//���ַ���ת������������
//<stdlib.h>
//nptr:��ת�����ַ�����
//	�ɹ�ת���������ַ���������ֵ�����޷�ת������0.
//
/*
2.����ת��Ϊ�ַ���
�� itoa()��������ֵת��Ϊ�ַ�����
�� ltoa()����������ֵת��Ϊ�ַ�����
�� ultoa()�����޷��ų�����ֵת��Ϊ�ַ�����
�� gcvt()������������ת��Ϊ�ַ�����ȡ�������롣
�� ecvt()����˫���ȸ�����ֵת��Ϊ�ַ�����ת������в�����ʮ����С���㡣
�� fcvt()��ָ��λ��Ϊת�����ȣ�����ͬecvt()��
*/
#include<iostream>
#include<stack>
#include<string>
#include<cmath>
#include<queue>
#include<iomanip>//����2λ���ͷ�ļ�
using namespace std;
int judge(char a1, char a2)//a1Ϊջ�ڵĲ�������ջ��Ԫ�أ���a2Ϊջ��ģ�1Ϊ<��-1Ϊ>=,ջ�ڵ������������ڵ���ջ�������Ҫ������Ȼ��С��ѹջ
{
	int x1, x2;
	if (a1 == '+' || a1 == '-')
		x1 = 1;
	else if (a1 == '*' || a1 == '/' || a1 == '%')
		x1 = 3;
	else if (a1 == '^')
		x1 = 5;
	else if (a1 == '(')
		x1 = -2;
	else if (a1 == '#')
		x1 = -3;

	if (a2 == '+' || a2 == '-')
		x2 = 1;
	else if (a2 == '*' || a2 == '/' || a2 == '%')
		x2 = 3;
	else if (a2 == '^')
		x2 = 5;

	if (x2 <= x1) return -1;//�Ƿ������жϺ�ջ�����ŵ����ȼ����������Ż������ȼ������ڣ�С�ڵ��ڣ�ջ��������ջ��Ԫ��һ�γ�ջ�����
	else if (x1<x2)return 1;//���ȼ�����ջ��Ԫ��
}
//(6+7)/1.3-2^0.5*4
//(90-88)/2*3
//��������
double run(char c, double d1, double d2)
{
	double d=0.0;
	if (c == '+')
		d = d1 + d2;
	if (c == '-')
		d = d1 - d2;
	if (c == '*')
		d = d1*d2;
	if (c == '/')
		d = d1 / d2;
	if (c == '%')
		d = int(d1) % int(d2);
	if (c == '^')
	{
		d = pow(d1, d2);
	}
	return d;	
}
int main()
{
	string str;
	while(cin >> str)
	{
		queue<char>back;
		stack<char>fuhao;
		int length = str.length();
		fuhao.push('#');
		int i = 0, j = 0;
		int flag = 1;

		//��������ƥ������
		stack<char>skuohao;
		skuohao.push('#');
		int w = 0;
		int res1 = 1;
		for (w = 0; w < length; w++)
		{
			if (str[w] == '(')
			{
				skuohao.push('(');
			}
			else if (str[w] == ')')
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
		if (res1 == 0 || skuohao.top() != '#')
		{
			cout << "ERROR IN INFIX NOTATION"<<endl;
			flag = 0;
		}

		if (flag != 0)//a/b b����Ϊ0  a%b b����Ϊ0  0��0�η�û������
		{
			for (int y = 0; y < length; y++)
			{
				if (str[y] == '/')
				{
					if (str[y + 1] == '0')
					{
						cout << "ERROR IN INFIX NOTATION" << endl;
						flag = 0;
						break;
					}
				}
				if (str[y] == '%')
				{
					if (str[y + 1] == '0')
					{
						cout << "ERROR IN INFIX NOTATION" << endl;
						flag = 0;
						break;
					}
				}
				if (str[y] == '^')
				{
					if (str[y - 1] == '0')
					{
						cout << "ERROR IN INFIX NOTATION" << endl;
						flag = 0;
						break;
					}
				}
			}
		}
		//����Ƿ����������������
		if (flag != 0)
		{
			int count = 0;
			for (int p = 0; p < length; p++)
			{
				if (str[p] == '+' || str[p] == '-' || str[p] == '*' || str[p] == '/' || str[p] == '%' || str[p] == '^')
				{
					count++;
				}
				else if (str[p] >= '0'&&str[p] <= '9')
				{
					count = 0;
				}
				else if (str[p] != '.'&&str[p] != '('&&str[p] != ')') //�Ƿ��в���������������
				{
					cout << "ERROR IN INFIX NOTATION"<<endl;
					flag = 0;
					break;
				}

				if (str[p] == '(')//����4+(-2)������������������������������
				{
					if (str[p + 1] == '-')
					{
						count--;
					}
				}
				if (count == 2)
				{
					cout << "ERROR IN INFIX NOTATION"<<endl;
					flag = 0;
				}
			}
		}
		//����һ���Ƿ�Ϊ���ֻ�������
		if (flag != 0)
		{
			if (str[0] != '('&&str[0] != '+'&&str[0] != '-')
			{
				if (str[0]<'0' || str[0]>'9')
				{
					cout << "ERROR IN INFIX NOTATION" << endl;
					flag = 0;
				}
			}
		}
		//����Ƿ�����������������  ������� (-2)3
		if (flag != 0) {
			int flagdo = 0;
			for (int r = 0; r < length; r++)
			{
				if (str[r] == '*' || str[r] == '/' || str[r] == '%' || str[r] == '^')
				{
					flagdo = 1;//��������
					break;
				}
				else if (str[r] == '+' || str[r] == '-')
				{
					if (r != 0)
					{
						if (str[r - 1] == '(')//Ϊ�˱�֤r������0 ����	�ȼ��str[0]����Ϊ���ŵ����������һ���Ƿ�Ϊ���ֻ������ţ��Ƶ����������֮ǰ			
						{
							flagdo = 0;
						}
						else {
							flagdo = 1;//��������
							break;
						}
					}
					else
					{
						flagdo = 1;//��������
						break;
					}

				}
			}
			if (flagdo == 0)
			{
				cout << "ERROR IN INFIX NOTATION" << endl;
				flag = 0;
			}
		}

		//�������ĩβ�Ƿ�Ϊ����
		if (flag != 0)
		{
			if (str[length - 1]<'0' || str[length - 1]>'9')
			{
				if (str[length - 1] != ')')
				{
					cout << "ERROR IN INFIX NOTATION" << endl;
					flag = 0;
				}
			}
		}

		if (flag != 0)
		{
			//�ַ�����һλΪ+ or - ����ѹ��һ��0  ���� -2+4

			if (str[0] == '+' || str[0] == '-')
			{
				back.push('0');
				back.push('@');
			}
		
			//��׺���ʽת��׺���ʽ����back���д�ţ�ÿ��������֮����@�ָ����������
			for (i = 0; i < length; i++)
			{

				if (str[i] >= '0'&&str[i] <= '9')
				{
					back.push(str[i]);
					if (i == length - 1)
					{
						back.push('@');
					}
				}
				else if (str[i] == '.')
				{
					back.push('.');
				}
				else if (str[i] == '(')
				{
					if (i != 0)
					{
						if (str[i - 1] >= '0'&&str[i - 1] <= '9')
						{
							back.push('@');
						}
					}
					fuhao.push(str[i]);
					if (str[i + 1] == '-')
					{
						back.push('0');
						back.push('@');
					}
				}
				else if (str[i] == ')')
				{
					if (i != 0)
					{
						if (str[i - 1] >= '0'&&str[i - 1] <= '9')
						{
							back.push('@');
						}

					}
					while (fuhao.top() != '(')
					{
						char x = fuhao.top();
						back.push(x);
						fuhao.pop();
					}
					fuhao.pop();//�ѡ�(��ɾ��
				}
				else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '%' || str[i] == '^')
				{
					if (i != 0)
					{
						if (str[i - 1] >= '0'&&str[i - 1] <= '9')
						{
							back.push('@');
						}
					}
					if (fuhao.top() == '#' || judge(fuhao.top(), str[i]) == 1)
					{
						fuhao.push(str[i]);
					}
					else if (judge(fuhao.top(), str[i]) == -1)
					{

						do
						{
							char c = fuhao.top();
							fuhao.pop();
							back.push(c);
						}while (judge(fuhao.top(), str[i]) != 1);//һֱ����������
						fuhao.push(str[i]);
					}
				}
				else
				{
					cout << "ERROR IN INFIX NOTATION"<<endl;
					break;
				}
			}
			while (fuhao.top() != '#')
			{
				char c = fuhao.top();
				fuhao.pop();
				back.push(c);
			}

			//�����ŵĺ�׺���ʽ
				/*while (!back.empty())
				{
					cout << back.front()<<" ";
					back.pop();
				}
				cout << endl;*/

				//��������back������ĺ�׺���ʽ ������������ջ�������������������ջ�������֣���������󣬽���������ջ
			stack<double>num;
			double res = 0.0, xiaoshu = 0.0, ten = 1.0;
			double d;
			int count2 = 0;//С����λ�� ������0.1 ����0.01����
			while (!back.empty())
			{
				char k;
				if (back.front() >= '0'&&back.front() <= '9')
				{
					while (back.front() != '@')
					{
						char f = back.front();
						back.pop();
						res = res * 10.0 + (f - '0');
						if (back.front() == '.')
						{
							back.pop();//�ѡ�.��ɾ��
							while (back.front() != '@')
							{
								count2++;
								for (int e = 0; e < count2; e++)
								{
									ten = 0.1 * ten;
								}
								char q = back.front();
								back.pop();
								xiaoshu = xiaoshu + (q - '0')*ten;
								ten = 1.0;
							}
						}
					}
					if (back.front() == '@')
					{
						back.pop();
					}
					//cout << res << endl;
					//cout << res + xiaoshu << endl;
					num.push(res + xiaoshu);
					//cout << num.top() << endl;
					res = 0.0;
					count2 = 0;
					xiaoshu = 0.0;
				}
				else if (back.front() == '+' || back.front() == '-' || back.front() == '*' || back.front() == '/' || back.front() == '%' || back.front() == '^')
				{
					double a1 = num.top();
					num.pop();
					double a2 = num.top();
					num.pop();
					d = run(back.front(), a2, a1);
					//cout << d<<endl;
					back.pop();//������������ɾ��
					num.push(d);
				}
				else if (back.front() == '(')
				{
					back.pop();
				}
			}
			cout << fixed << setprecision(2) << num.top() << endl;
		}
	}
	system("pause");
	return 0;
}


//int main()
//{
//	string a="23";
//	cout << a + "5";
//	system("pause");
//	return 0;
//}







//int main()
//{
//	stack <double>num;//�������
//	stack<char>fuhao;//��ŷ���
//	char *op = "+-*/%^()#";
//	string str;
//	double result;
//	cin>>str;
//	str.append(1, '#');//string append()�÷���str.append(str2,11,7)�ӵ�11���ַ���ʼ�����7��/str.append(str2)/str.append(5,'.')���5��.
//	fuhao.push('#');//�Ƚ�#��ջ
//	int a = -1;
//	for (;;)
//	{
//		int b = a + 1;
//		a = str.find_first_of(op, a + 1);//��a+1��ʼ����str�еĵ�һ����op��ĳ���ַ����ϵ��ַ�������������λ�ã�û�ҵ��ͷ���string::npos
//		if (a == string::npos)break;
//		if (a != b)
//		{
//			string ss(str, b, a - b);
//			double d = atof(ss.c_str());//������������֮�������ת���ɸ�������֮ǰΪstring���ͣ�
//			num.push(d);//�������ֵ�ջ��
//		}
//
//		int f1= judge(fuhao.top(), str[a]);
//		if (f1 == 1)
//		{
//			double f2 = num.top();
//			num.pop();
//			double f3 = num.top();
//			num.pop();
//			double f4 = run(fuhao.top(), f2, f3);
//			num.push(f4);
//			a--;
//		}
//		if (f1 == -1)
//		{
//			fuhao.push(str[a]);
//		}
//		
//		str.erase(str.length() - 1, 1);
//		cout << str << "=" << num.top() << endl;
//	}
//	system("pause");
//	return 0;
//}





