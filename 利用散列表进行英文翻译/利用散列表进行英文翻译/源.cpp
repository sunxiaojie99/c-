/*
����:
������һ��İ����������У����������˵��һ�����˷ѽ��������ԣ��������˵��ǣ�
����һ���ʵ���԰������������Щ���ԡ�������ɢ�б�����������Է����Ӣ�ġ�
Ҫ��

��hash�����������ֵ䣬�����ַ��ͻ��
���룺
��������һ���ʵ䣬���а���������1000��������ÿ������ռ��һ�С�ÿһ����������һ��Ӣ�ĵ��ʺ�һ�����ﵥ�ʣ�
��������֮����һ���ո�����������ڴʵ��в�����ĳ�����ﵥ�ʳ����������ϵ������
֮����һ�����С���һ���������ѯ��һ�����ﵥ�ʡ������г��ֵĵ���ֻ����Сд��ĸ�����ҳ��Ȳ��ᳬ��10��
�����
����Ҫ������Ĵ���ѯ���ʷ����Ӣ�ĵ��ʡ����ĳ�����ﵥ�ʲ��ڴʵ��У��Ͱ�������ʷ���� ��eh����
���룺
dog ogday
cat atcay
pig igpay
froot ottfray
loops oopsla

atcay
�����
cat
*/

#include<iostream>
#include<string>

using namespace std;
class hashtable
{
public:
	int m,count1=0;
	string *eng;//�����ȷ��Ӣ��
	string *other;//�������
	bool *empty;
	hashtable(int n) {//���ֵ䳤�ȴ���
		eng = new string[100];
		other = new string[100];
		empty = new bool[100];
		m = n;
		for (int g = 0; g<100; g++)
		{
			empty[g] = true;
		}
	}
	void search(string check)
	{
		int i = 0, sum = 0, loc;
		for (i = 0; i<3; i++)//��ϣ��������������ַ���ǰ3λ��ASCII��-��a������� ���ֵ䳤��ȡ��  �����Ϊ�洢λ��
		{
			if (check[i] == '\0')
			{
				break;
			}
			sum = sum + (check[i] - 'a');
		}
		loc = sum%m;
		if (!empty[loc])//�����ϣ��λ�ò�Ϊ�գ��ڶ�Ӧ��other���Ƿ�ΪҪ���ҵ����ģ�������ǣ�������һ��λ��
		{
			while (1) {
				if (other[loc]==check)//string str1; string str2; str1.compare(str); str1>str2��������,��ȷ���0 С�ڷ��ظ���
				{
					int x = 0;
					while (eng[loc][x] != '\0')
					{
						cout << eng[loc][x];
						x++;
					}
					if (eng[loc][x] == '\0')
						break;
				}
				else
				{
					loc++;
					count1++;
				}
				if (count1 >= m)
				{
					cout << "eh";
					break;
				}
			}
		}
		else if (empty[loc])
		{
			cout << "eh";
		}
	}
};
int main()
{
	string a[100], b[100];
	string c;
	int i = 0, count;
	while (1)
	{
		getline(cin, c);
		if (c == "\0")
		{
			break;
		}
		for (int j = 0; j<c.length(); j++)
		{
			if (c[j] == ' ')
			{
				a[i] = c.substr(0, j);
				b[i] = c.substr(j + 1, c.length() - j);
				i++;
				break;
			}
		}
	}
	count = i;
	hashtable hh(count);
	int sum = 0, loc;
	for (int p = 0; p<count; p++)
	{
		sum = 0;
		for (int y = 0; y<3; y++)
		{
			if (b[p][y] == '\0')
			{
				break;
			}
			sum = sum + (b[p][y] - 'a');
			//cout << b[p][y] - 'a'<<" "<<sum<<endl;
		}
		loc = sum % count;
		//cout <<sum <<" "<<loc << endl;
		while (1)
		{
			if (hh.empty[loc])//�����ϣλ��Ϊ�� ��Ϊ���� ����Ӧ��other��eng�в�����Ӧ�ַ���
			{
				hh.empty[loc] = false;
				hh.other[loc] = b[p];
				hh.eng[loc] = a[p];
				break;
			}
			else//���λ�ò�Ϊ�գ��ж��Ƿ����Ҫ���������һ������һ����������һ��λ��Ѱ��
			{
				if (hh.other[loc] == b[p])
				{
					break;
				}
				else
				{
					loc++;
				}
			}

		}
	}
	//int r = 0;
	//while (r<=count)
	//{
	//	cout << hh.eng[r] <<" "<< hh.other[r] << endl;
	//	r++;
	//}

	string check;
	cin >> check;
	hh.search(check);
	system("pause");
	return 0;
}