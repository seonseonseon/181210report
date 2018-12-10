#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void trivial(char* string, int rotate, int length);
void juggling(char* string, int rotate, int length);
void block_swap(char* string, int rotate, int length);
void swap(char* string, int fi, int si, int rotate);
void reverse(char* string, int rotate, int length);
void reverse_string(char* str, int start, int end);


//Trivial solution / juggling / block-swap / reverse Rotate 시간 비교

int main()
{
	clock_t start_time = clock(), end_time = clock(), elapsed_time;
	end_time = clock();
	elapsed_time = end_time - start_time;

	srand(time(NULL));

	int rotate = rand()%(10001) - 5000;
	int length = rand()%10000 + 1;

	rotate = 3;
	length = 10;

	printf("rotate=%d\nlength=%d\n", rotate, length);

	char* string = (char*)malloc(length);

	for (int i = 0; i < length; i++)
	{
		*(string + i) = rand() % 26 + 'a';
	}
	*(string + length) = NULL;

	printf("before : %s\n", string);
	trivial(string, rotate, length);
	juggling(string, rotate, length);
	block_swap(string, rotate, length);
	reverse(string, rotate, length);
	
	

}

void trivial(char* string, int rotate, int length)
{
	char tmp;
	
	if (rotate == 0 || abs(rotate) == length || abs(rotate) % length == 0)
	{
		printf("trivial : %s\n", string);
		return;
	}
		
	else if (rotate < 0)
	{
		rotate = abs(rotate) % length;

		for (int j = 0; j < rotate; j++)
		{
			tmp = *(string + 0);
			for (int i = 0; i < length - 1; i++)
			{
				*(string + i) = *(string + i + 1);
			}
			*(string + length - 1) = tmp;
			*(string + length) = NULL;
		}

		printf("trivial : %s\n", string);
		return;
	}

	else if (rotate > 0)
	{
		rotate = rotate % length;


		for (int j = 0; j < rotate; j++)
		{
			tmp = *(string + length - 1);
			for(int i = 0; i < length - 1; i++)
			{
				*(string + i + 1) = *(string + i);
			}
			*(string + 0) = tmp;
		}
		printf("trivial : %s\n", string);
		return;
	}
}

int find_gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return find_gcd(b, a%b);
}

void juggling(char* string, int rotate, int length)
{
	if (rotate == 0 || abs(rotate) == length || abs(rotate) % length == 0)
	{
		printf("juggling : %s\n", string);
		return;
	}
	else if (find_gcd(abs(rotate), length) < 0)
	{
		printf("최대공약수 구하기에 실패하였습니다.\n");
		return;
	}

	else if (find_gcd(abs(rotate), length) == 1)
	{
		char tmp;

		if (rotate == 0 || abs(rotate) == length || abs(rotate) % length == 0)
		{
			printf("juggling : %s\n", string);
			return;
		}

		else if (rotate < 0)
		{
			rotate = abs(rotate) % length;

			for (int j = 0; j < rotate; j++)
			{
				tmp = *(string + 0);
				for (int i = 0; i < length - 1; i++)
				{
					*(string + i) = *(string + i + 1);
				}
				*(string + length - 1) = tmp;
				*(string + length) = NULL;
			}

			printf("juggling : %s\n", string);
			return;
		}

		else if (rotate > 0)
		{
			rotate = rotate % length;


			for (int j = 0; j < rotate; j++)
			{
				tmp = *(string + length - 1);
				for (int i = 0; i < length - 1; i++)
				{
					*(string + i + 1) = *(string + i);
				}
				*(string + 0) = tmp;
			}
			printf("juggling : %s\n", string);
			return;
		}
		return;
	}

	else if (rotate > 0)
	{
		int gcd = find_gcd(rotate, length);
		rotate = abs(rotate) % length;
		char* tmp = (char*)malloc(gcd);

		for (int i = 0; i < gcd; i++)
		{
			*(tmp + i) =  'a';
		}
		*(tmp + gcd) = NULL;


		for (int j = 0; j < rotate; j++)
		{
			strncpy_s(tmp, sizeof(tmp), string + length - gcd, gcd);
			for (int i = length - 1; i > 0; i = i - gcd)
			{
				strncpy_s(string + i,sizeof(char), string + i - gcd, gcd);
			}
			strncpy_s(string, sizeof(char), tmp, gcd);
		}

		printf("juggling : %s\n", string);
		return;
	}

	else if (rotate < 0)
	{
		int gcd = find_gcd((-rotate), length);
		rotate = abs(rotate) % length;
		char* tmp = (char*)malloc(gcd);
		for (int i = 0; i < gcd; i++)
		{
			*(tmp + i) = 'a';
		}
		*(tmp + gcd) = NULL;

		for (int j = 0; j < abs(rotate); j++)
		{
			strncpy_s(tmp, sizeof(tmp), string, gcd);
			for (int i = 0; i < length - 1; i = i + gcd)
			{
				strncpy_s(string + i,sizeof(char), string + i + gcd, gcd);
			}
			strncpy_s(string + length - gcd,sizeof(char), tmp, gcd);
		}
		printf("juggling : %s\n", string);
		return;
	}
}


void block_swap(char* string, int rotate, int length)
{
	

	if (rotate == 0 || abs(rotate) == length || abs(rotate) % length == 0)
	{
		printf("blockswap : %s\n", string);
		return;
	}
	

	else if (length == abs(rotate) * 2)
	{
		swap(string, 0, length - rotate, rotate);
		printf("blockswap : %s\n", string);
		return;
	}

	else if (rotate < 0)	//왼쪽, 앞으로 rotate
	{
		rotate = abs(rotate) % length;
		int i = rotate;
		int j = length - rotate;
		while (i != j)
		{
			if (i < j) // A is shorter
			{
				swap(string, rotate - i, rotate + j - i, i);
				j = j - i;
			}
			else // B is shorter
			{
				swap(string, rotate - i, rotate, j);
				i = i - j;
			}
			
		}
		swap(string, rotate - i, rotate, i);
		printf("blockswap : %s\n", string);
		return;
	}

	else if (rotate > 0)	// 오른쪽, 뒤로 rotate
	{
		rotate = rotate % length;
		int i = length - rotate;
		int j = rotate;

		while (i != j)
		{
			if (i < j) // A is shorter
			{
				swap(string, rotate - i, rotate + j - i, i);
				j = j - i;
			}
			else // B is shorter
			{
				swap(string, rotate - i, rotate, j);
				i = i - j;
			}

		}
		swap(string, rotate - i, rotate, i);
		printf("blockswap : %s\n", string);
		return;
	}
}

void swap(char* string, int fi, int si, int rotate)
{
	char tmp;
	for (int i = 0; i < rotate; i++)
	{
		tmp = *(string + fi + i);
		*(string + fi + i) = *(string + si + i);
		*(string + si + i) = tmp;
	}
	return;
}


void reverse(char* string, int rotate, int length)
{
	if (rotate == 0 || abs(rotate) == length || abs(rotate) % length == 0)
	{	
		printf("reverse : %s\n", string);
		return;
	}
	else if (rotate < 0)
	{
		reverse_string(string, 0, abs(rotate) - 1);
		reverse_string(string, abs(rotate), length - 1);
		reverse_string(string, 0, length - 1);

		printf("reverse : %s\n", string);
		return;
	}
	else if (rotate > 0)
	{
		reverse_string(string, 0, length - 1);
		reverse_string(string, rotate, length - 1);
		reverse_string(string, 0, rotate - 1);

		printf("reverse : %s\n", string);
		return;
	}
}

void reverse_string(char* str, int start, int end)
{
	char tmp;
	int len = end - start ;

	for (int i = 0; i < len / 2; i++)
	{
		tmp = *(str + start + i);
		*(str + start + i) = *(str + end - i);
		*(str + end - i) = tmp;
	}

	return;
}