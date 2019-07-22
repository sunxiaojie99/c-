#include<stdio.h>
#include<iostream>
#define  RANGE 8
#define  TRUE 1
#define  FALSE 0
void showEightQueens(int(*eq)[RANGE]);
int isPositionSafe(int(*eq)[RANGE], int row, int col);
void eightQueens(int(*eq)[RANGE], int i);
void eightQueens(int(*eq)[RANGE], int i)
{
	int j;
	if (i >= RANGE)//�ݹ麯������Ҫ��һ�����ڣ��������޵ݹ�
		showEightQueens(eq);
	else
	{
		for (j = 0; j < RANGE; j++)
		{
			if (isPositionSafe(eq, i, j))//�жϴ�λ���Ƿ�ȫ
			{
				eq[i][j] = 1;//����ȫ����λ�÷Żʺ�
				eightQueens(eq, i + 1);//������һ�������һ������λ�ö�����ȫ���򷵻ص��õݹ��λ�ã�������������Ĳ�����
				eq[i][j] = 0;//��ɴ�λ�õĲ����󣬽��ʺ�ȥ������ΪҪ�г����еĿ��ܽ������Ӧ��ÿ��λ�ö��жϡ�
			}
		}
	}
}
int isPositionSafe(int(*eq)[RANGE], int row, int col)//�ж�λ���Ƿ�ȫ
{
	int OK = TRUE;//����һ�����ɣ���Ӧ��ѧ�ᣬ�൱�ڼ�����õ��ܶ�ı�־λ
	int i;
	int j;
	for (i = row - 1, j = col - 1; OK && i >= 0 && j >= 0; i--, j--)//�Խ���
		if (eq[i][j] == 1)
			OK = FALSE;
	for (i = row - 1, j = col; OK && i >= 0; i--)//��
		if (eq[i][j] == 1)
			OK = FALSE;
	for (i = row - 1, j = col + 1; OK && i >= 0 && j < RANGE; i--, j++)//��б�Խ���
		if (eq[i][j] == 1)
			OK = FALSE;
	return OK;
}
void showEightQueens(int(*eq)[RANGE])
{
	int i;
	int j;
	static int count = 0;//�õ��˾�̬����
	printf("��%d�ְڷ�\n", ++count);
	for (i = 0; i < RANGE; i++)
	{
		for (j = 0; j < RANGE; j++)
			printf("%3d", eq[i][j]);
		printf("\n");
	}
}
void main(void)
{
	int eightQueen[RANGE][RANGE] = { 0 };
	eightQueens(eightQueen, 0);
	system("pause");
}