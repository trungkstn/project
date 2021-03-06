/*************************************************************************
	> File Name: func.c
	> Author: Soul
	> Mail:souldong1591@gmail.com 
	> Created Time: 2014年07月19日 星期六 23时20分17秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

//暴力移位
void leftShift1(char *arr, int n)
{
	size_t tmpLen = strlen(arr);
	char tmpChar;
	int i, j;
	if(n >= 0)
	{
		for(i = 0; i < n; i++)
		{
			tmpChar = *arr;
			for (j = 0; j < tmpLen - 1; j++) 
			{
				*(arr + j) = *(arr + j + 1);
				
			}
			*(arr + tmpLen - 1) = tmpChar;
		}
	}
	else
	{
		for(i = 0; i < -n; i++)
		{
			tmpChar = *(arr + tmpLen -1);
			for(j = tmpLen - 1; j > 0; j--)
			{
				*(arr + j) = *(arr + j - 1);
			}
			*arr = tmpChar;
		}
	}
}

//指针移位
void leftShift2(char *arr, int n)
{
	int i;
	size_t tmpLen = strlen(arr);
	int p0 = 0;
	int p1 = n;
	char tmpChar;
	while(p1 + n -1 < tmpLen)
	{
		tmpChar = *(arr + p0);
		*(arr + p0) = *(arr + p1);
		*(arr + p1) = tmpChar;
		p0++;
		p1++;
	}

	while(p1 < tmpLen)
	{
		tmpChar = *(arr + p1);
		for (i = p1; i > p0; i--) 
		{
			*(arr + i) = *(arr + i -1); 
		}
		*(arr + p0) = tmpChar;
		p0++;
		p1++;
	}
}








int main(int argc, const char *argv[])
{
	char buf[128] = "";
	int n;
	while(memset(buf, 0, 128), printf("Please enter string: "), scanf("%s", buf) != EOF)
	{
		printf("please enter n: ");
		scanf("%d", &n);
		leftShift(buf, n);
		printf("after leftShift: %s\n", buf);
	}
	return 0;
}
