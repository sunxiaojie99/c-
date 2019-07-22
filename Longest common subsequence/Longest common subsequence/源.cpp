/*
Z=<a,b,f,c> is a subsequence of the sequence X=<a,b,c,f,b,c>, and the index of the subsequence in X is <1,2,4,6>. Z�����Ԫ����X��ȫ�����֣���˳�򲻱䣬
��ôZ��X��������
�ȸ��������ַ�������������Ĺ�ͬ��������
*/
/*
c[i][j]�����ַ���x�ĵ�i-1���ַ����ַ���y�е�j-1���ַ�����Ϊ�Ǵ�0��ʼ����������lcs
����һ����ά����c[][]����c[i][j]��¼X[i]��Y[j] ��LCS �ĳ��ȣ�b[i][j]��¼c[i][j]��ͨ����һ���������ֵ��õģ��Ծ��������ķ���
�������Ե����Ͻ��е��Ƽ��㣬��ô�ڼ���c[i,j]֮ǰ��c[i-1][j-1]��c[i-1][j]��c[i][j-1]���Ѽ��������
��ʱ���Ǹ���X[i] = Y[j]����X[i] != Y[j]���Ϳ��Լ����c[i][j]��
*/
/*��������ַ�����X=��x0��x1������xm-1��������Y=��y0��y1������yk-1����X�������У�����X��һ���ϸ�����±�����<i0��i1������ik-1>��ʹ�ö����е�j=0��1������k-1����xij=yj�����磬X=��ABCBDAB����Y=��BCDB����X��һ�������С�

���������������������ηֽ�������⣬��A=��a0��a1������am-1����B=��b0��b1������bm-1������Z=��z0��z1������zk-1��Ϊ���ǵ�����������С�����֤�����������ʣ�

��1�� ���am-1=bn-1����zk-1=am-1=bn-1���ҡ�z0��z1������zk-2���ǡ�a0��a1������am-2���͡�b0��b1������bn-2����һ������������У�

��2�� ���am-1!=bn-1������zk-1!=am-1���̺���z0��z1������zk-1���ǡ�a0��a1������am-2���͡�b0��b1������bn-1����һ������������У�

��3�� ���am-1!=bn-1������zk-1!=bn-1���̺���z0��z1������zk-1���ǡ�a0��a1������am-1���͡�b0��b1������bn-2����һ������������С�

����������A��B�Ĺ���������ʱ������am-1=bn-1�����һ�����һ�������⣬�ҡ�a0��a1������am-2���͡�b0��b1������bm-2����һ������������У�
���am-1!=bn-1����Ҫ������������⣬�ҳ���a0��a1������am-2���͡�b0��b1������bn-1����һ�������������
���ҳ���a0��a1������am-1���͡�b0��b1������bn-2����һ������������У���ȡ�����нϳ�����ΪA��B������������С�
*/
#include<iostream>
#include<string>
#include<stack>
using namespace std;
void printlac(string x, string y,int i,int j, int flag[200][200]) {
	stack<char>l;
	if (i == 0 || j == 0)
		return;
	if (flag[i][j] == 1) {
		l.push(x[i - 1]);
		printlac(x, y, i - 1, j - 1, flag);
	}
	else if (flag[i][j] == 2) {
		printlac(x, y, i - 1, j, flag);
	}
	else if (flag[i][j] == 3) {
		printlac(x, y, i, j - 1, flag);
	}
	while (!l.empty()) {
		cout << l.top()<<" ";
		l.pop();
	}
}
int max(int a, int b) {
	if (a > b)
		return a;
	else return b;
}
int LCS(int a[200][200], string x, string y, int flag[200][200]) {
	int xsize = x.length();
	int ysize = y.length();
	for (int i = 0; i <= xsize; i++) {
		a[i][0] = 0;
	}
	for (int j = 0; j <= ysize; j++) {
		a[0][j] = 0;
	}
	for (int i = 1; i <= xsize; i++) {
		for (int j = 1; j <= ysize; j++) {
			if (x[i-1] == y[j-1]) {
				a[i][j] = a[i - 1][j - 1] + 1;
				flag[i][j] = 1;
			}
			else {
				a[i][j] = max(a[i - 1][j], a[i][j - 1]);
				if (a[i][j] == a[i - 1][j])
					flag[i][j] = 2;
				else flag[i][j] = 3;
			}
		}
	}
	return a[xsize][ysize];
}
int main() {
	int a[200][200];
	int flag[200][200];
	string x;
	string y;
	cin >> x>>y;
	cout<<LCS(a, x, y, flag)<<endl;
	//printlac(x, y, x.size(), y.size(), flag);
	system("pause");
	return 0;
}