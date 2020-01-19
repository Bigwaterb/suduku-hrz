
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<iostream> 
#include<time.h>
#include<cstdlib>
typedef long long int ll;
const int Maxn = 1e6 + 10;	
const int Maxm = 10;	
const int INF = 0x3f3f3f3f; 
const int first_num = (9 + 3) % 9 + 1;  //学号1120171393
using namespace std;
typedef struct Point   //数独结构体
{
	int row;	//  所在行
	int col;	//  所在列
	int num;	//  该空格所在行、列、小九宫格中的由题已知的数字的总和
}Point;

int move_step[80][Maxm];
int permutation[Maxn][Maxm];
int CheckOrder(char order[], int & num, char name[], int & type)    //判断命令格式
{
	int len = strlen(order);
	int flag = 1;		
	int blank_num = 0;	
	int order_site = INF;	
	num = 0;
	type = 0;
	memset(name, 0, sizeof(char) * 100);
	int name_site = 0;
	if (len < 4) 
	{
		flag = 0;
	}
	else
	{
		if (order[0] != '-')  
		{
			flag = 0;
		}
		else if (order[2] == ' ')    
		{
			if (order[1] == 'c')
			{
				type = 1;
				order_site = 1;
			}
			else if (order[1] == 's')
			{
				type = 2;
				order_site = 1;
			}
			else  // 非法操作符
			{
				flag = 0;
			}
			blank_num = 1;
		}
	}
	for (int i = 3; i < len; i++)	
	{
		if (i > order_site + 1)  
		{
			if (type == 1)
			{
				if (order[i] < '0' || order[i] > '9')	
				{
					flag = 0;
					num = 0;	
					break;
				}
				else
				{
					num *= 10;
					num += order[i] - '0';
				}
			}
			else if (type == 2)	
			{
				if (order[i] == ' ')
				{
					flag = 0;
					memset(name, 0, sizeof(char) * strlen(name));
					break;
				}
				else
				{
					name[name_site] = order[i];
					name_site++;
				}
			}
		}
	}
	if (blank_num != 1 || order_site == INF || type == 0)  
	{
		flag = 0;
	}
	if (type == 1 && num == 0)	
	{
		flag = 0;
	}
	else if (type == 2 && strcmp(name, "") == 0)	
	{
		flag = 0;
	}
	return flag;
}

void Swap(int & a, int & b)  //交换a，b值
{
	int temp = a;
	a = b;
	b = temp;
}

void Permutate_for_temp(int source[], int start, int end, int target[6][3], int& line)
{
	if (start > end)  // 防止错误输入
	{
		start = end;
	}

	if (start == end)
	{
		for (int i = 0; i <= end; i++)
		{
			target[line][i] = source[i];
		}
		line++;
	}
	else
	{
		for (int i = start; i <= end; i++)
		{
			Swap(source[i], source[start]);
			Permutate_for_temp(source, start + 1, end, target, line);
			Swap(source[i], source[start]);
		}
	}
}

void Permutate_for_move_step(int temp1[2][2], int temp2[6][3], int temp3[6][3], int max_num, int move_step[80][Maxm])
{
	int cnt = 0;

	for (int i = 0; i < 2; i++)  //  二三行有两个排列，二选一
	{
		for (int j = 0; j < 6; j++)  //  四五六行有六个全排列，六选一
		{
			for (int k = 0; k < 6; k++)  //  七八九行有六个全排列，六选一
			{
				for (int r = 0; r < 8; r++)  //  每个排列有8个元素（首元素不动）
				{
					if (r < 2)
					{
						move_step[cnt][r] = temp1[i][r];
					}
					else if (r < 5)
					{
						move_step[cnt][r] = temp2[j][r - 2];
					}
					else
					{
						move_step[cnt][r] = temp3[k][r - 5];
					}
				}
				cnt++;
				if (cnt >= max_num)
				{
					return;
				}
			}
		}
	}
}

void Permutate_for_permutation(int source[], int start, int end, int target[Maxn][Maxm], int& line, int max_num)  //全排序
{
	if (start > end)  // 防止输入错误，导致越界
	{
		start = end;
	}

	if (start == end)	//  终止条件
	{
		for (int i = 0; i <= end; i++)
		{
			target[line][i] = source[i];
		}
		line++;
	}
	else
	{
		for (int i = start; i <= end; i++)
		{
			if (line >= max_num)	
			{
				return;
			}
			Swap(source[i], source[start]);		
			Permutate_for_permutation(source, start + 1, end, target, line, max_num);
			Swap(source[i], source[start]);
		}
	}
}

void FillTheMoveStep(const int max_num, int move_step[80][Maxm])	
{
	int source2[] = { 1 , 4 , 7 }, source3[] = { 2 , 5 , 8 };	
	int temp1[2][2], temp2[6][3], temp3[6][3];
	int line2 = 0, line3 = 0;
	temp1[0][0] = 3, temp1[0][1] = 6;
	temp1[1][0] = 6, temp1[1][1] = 3;
	Permutate_for_temp(source2, 0, 2, temp2, line2);
	Permutate_for_temp(source3, 0, 2, temp3, line3);
	Permutate_for_move_step(temp1, temp2, temp3, max_num, move_step);	
}

void FillThePermutaion(const int max_num, int permutation[Maxn][Maxm])
{
	int source[] = { first_num , 1 , 2 ,  3 , 4 , 5 , 6 , 7 , 9 };
	int line = 0;
	Permutate_for_permutation(source, 1, 8, permutation, line, max_num);
}

void FillTheBlock(int cnt, int move_step[80][Maxm], int permutation[Maxn][Maxm])   //通过平移，生成数独终局
{
	int pl = cnt / 72;	
	int ml = cnt % 72;  
	char temp[200];	
	int temp_site = 0;
	memset(temp, 0, sizeof(char) * 200);
	for (int i = 0; i < 9; i++)	
	{
		temp[temp_site] = permutation[pl][i] + '0';
		temp_site++;

		if (i == 8)
		{
			temp[temp_site] = '\n';
			temp_site++;
		}
		else
		{
			temp[temp_site] = ' ';
			temp_site++;
		}
	}
	for (int i = 1; i < 9; i++)		//  输出 2 ~ 9 行
	{
		for (int j = 0; j < 9; j++)
		{
			int site = (j + move_step[ml][i - 1]) % 9;	
			temp[temp_site] = permutation[pl][site] + '0';
			temp_site++;
			if (j == 8)
			{
				if (i == 8)
				{
					temp[temp_site] = '\0';
					temp_site++;
				}
				else
				{
					temp[temp_site] = '\n';
					temp_site++;
				}
			}
			else
			{
				temp[temp_site] = ' ';
				temp_site++;
			}
		}
	}

	puts(temp);
}

void Generate(int num)
{
	FillTheMoveStep(min(num, 72), move_step);	
	FillThePermutaion(num / 72 + 1, permutation); 
	for (int cnt = 0; cnt < num; cnt++)
	{
		FillTheBlock(cnt, move_step, permutation);  
		if (cnt != num - 1)
		{
			printf("\n");
		}

	}
}
void SetMark(int str[Maxm][Maxm], const int& site, const int& num, const int flag)  
{
	str[site][num] = flag;
}
int GetBlockNum(const int& x, const int& y)  
{
	return x / 3 * 3 + y / 3;
}

int CheckNum(const int& rm, const int& cm, const int& bm)	
{
	return !(rm || cm || bm);
}
bool DFS(Point p[], const int& num, int rm[Maxm][Maxm], int cm[Maxm][Maxm], int bm[Maxm][Maxm], int step, int block[Maxm][Maxm])
//  通过递归，找到合适的解
{
	if (step == num)
	{
		return true;
	}
	else if (step < 0 || step > num)
	{
		return false;
	}
	for (int i = 1; i <= 9; i++)
	{
		int r = p[step].row, c = p[step].col;

		if (CheckNum(rm[r][i], cm[c][i], bm[GetBlockNum(r, c)][i]))	
		{
			SetMark(rm, r, i, 1);
			SetMark(cm, c, i, 1);
			SetMark(bm, GetBlockNum(r, c), i, 1);
			block[r][c] = i;
			if (DFS(p, num, rm, cm, bm, step + 1, block))	
			{
				return true;	
			}
			SetMark(rm, r, i, 0);
			SetMark(cm, c, i, 0);
			SetMark(bm, GetBlockNum(r, c), i, 0);
			block[r][c] = 0;
		}
	}

	return false;
}

void Output(int block[Maxm][Maxm])
{
	char temp[200]; // temp 最大数量为9 * 9 * 2 = 162
	int temp_site = 0;
	memset(temp, 0, sizeof(char) * 200);
	for (int i = 0; i < 9; i++)	
	{
		for (int j = 0; j < 9; j++)
		{
			temp[temp_site] = block[i][j] + '0';
			temp_site++;
			if (j == 8)
			{
				if (i == 8)
				{
					temp[temp_site] = '\0';
				}
				else
				{
					temp[temp_site] = '\n';
				}
				temp_site++;
			}
			else
			{
				temp[temp_site] = ' ';
				temp_site++;
			}
		}
	}

	puts(temp);
}
bool Cmp(Point& x, Point& y) //比较
{
	return x.num > y.num;
}
void Init(int rowmark[Maxm][Maxm], int colmark[Maxm][Maxm], int blockmark[Maxm][Maxm],
	int row_num[Maxm], int col_num[Maxm], int block_num[Maxm],
	int& input_row, int& right, int& ans_num)    //初始化
{
	memset(row_num, 0, sizeof(int) * Maxm);
	memset(col_num, 0, sizeof(int) * Maxm);
	memset(block_num, 0, sizeof(int) * Maxm);
	memset(rowmark, 0, sizeof(int) * Maxm * Maxm);
	memset(colmark, 0, sizeof(int) * Maxm * Maxm);
	memset(blockmark, 0, sizeof(int) * Maxm * Maxm);
	input_row = 0;
	right = 1;
	ans_num = 0;
}
void  Solve()   //生成终局函数
{
	int rowmark[Maxm][Maxm];	
	int colmark[Maxm][Maxm];		
	int blockmark[Maxm][Maxm];		
	int row_num[Maxm], col_num[Maxm], block_num[Maxm];  
	int block[Maxm][Maxm];		
	Point ans_point[Maxm * Maxm];  
	int ans_num;  
	int right;	
	char temp_input[2 * Maxm];
	int input_row;
	int mark = 0;  
	Init(rowmark, colmark, blockmark, row_num, col_num, block_num, input_row, right, ans_num);
	while (gets(temp_input))
	{
		temp_input[strlen(temp_input)] = '\0';
		if (strcmp(temp_input, "") == 0)
		{
			if (input_row != 9)
			{
				if (mark != 0)
				{
					printf("\n");
				}
				printf("Imcompleted input!\n");
				mark++;
			}
			Init(rowmark, colmark, blockmark, row_num, col_num, block_num, input_row, right, ans_num);
			continue;
		}
		if (right) 
		{
			int input_col = 0; 
			int len = strlen(temp_input);
			if (len != 17)
			{
				right = 0;
				len = 0; 
			}

			for (int i = 0; i < len; i++)
			{
				if (temp_input[i] <'0' || temp_input[i] > '9')
				{
					if (temp_input[i] != ' ')
					{
						right = 0;
						break;
					}
					continue;
				}
				int temp_num = temp_input[i] - '0';
				block[input_row][input_col] = temp_num;
				if (temp_num == 0) 
				{
					ans_point[ans_num].row = input_row;
					ans_point[ans_num].col = input_col;
					ans_num++;
				}
				else 
				{
					if (rowmark[input_row][temp_num] == 1 ||
						colmark[input_col][temp_num] == 1 ||
						blockmark[GetBlockNum(input_row, input_col)][temp_num] == 1)
					{
						right = 0;
						break;
					}
					else  
					{
						SetMark(rowmark, input_row, temp_num, 1);
						SetMark(colmark, input_col, temp_num, 1);
						SetMark(blockmark, GetBlockNum(input_row, input_col), temp_num, 1);

						row_num[input_row] ++;
						col_num[input_col] ++;
						block_num[GetBlockNum(input_row, input_col)] ++;
					}
				}
				input_col++; 
			}
			input_row++;  
			if (input_row == 9) // 如果已经输入了9行
			{
				if (right)	// 输入的9行都信息正确
				{
					for (int i = 0; i < ans_num; i++)
					{
						int r = ans_point[i].row, c = ans_point[i].col;
						ans_point[i].num = row_num[r] + col_num[c] + block_num[GetBlockNum(r, c)];
					}
					sort(ans_point, ans_point + ans_num, Cmp);	
					if (DFS(ans_point, ans_num, rowmark, colmark, blockmark, 0, block))	
					{
						if (mark != 0)	
						{
							printf("\n");
						}
						Output(block);
						mark++;
					}
				}
				else  // 如果输入的九行中检测到错误
				{
					printf("Some errors?\n");
				}
			}
		}

	}

	if (input_row != 9)
	{
		if (mark != 0)
		{
			printf("\n");
		}

		printf("Imcompleted input!");
		mark++;
	}
}
int main()
{
	char order[100];	
	int num, type;		
	char name[100];		
	if (freopen("sudoku.txt", "w", stdout))
	{
		gets(order);		
		while (!CheckOrder(order, num, name, type))   
		{
			cout << "Please check the command!" << endl;
			gets(order);
		}

		if (type == 1)	//操作符为 -c
		{
			Generate(num);
		}
		else if (type == 2)  // 操作符为 -s
		{
			fclose(stdin);

			if (freopen(name, "r", stdin))
			{
				Solve();
			}
		}

		fclose(stdout);
	}
	return 0;
}