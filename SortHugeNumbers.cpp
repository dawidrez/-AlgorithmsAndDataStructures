#include <stdio.h>
#include <cmath>
#define SIZE 40
#pragma warning(disable:4996)

int log2(int n) {
	return floor(log(n)/log(2));
}

void show(char** arr,int n) {
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < SIZE;j++)
		{
			if (int(arr[i][j]) >= 48 && int(arr[i][j]) <= 57)
			{
				printf("%c", arr[i][j]);
			}
			else 
				break;
			
		}
		printf("\n");
	}

}

int com(char* number1,char* number2) {
	int i = 0;
	int num1 = -1;
	int num2;
	int bigger = 0;
	int longer=0;
	while (i < SIZE&&longer==0) {

		if (number1[i]!=NULL)
		{
			num1 = int(number1[i])-48;
		}
		else
			num1 = -1;
		if (number2[i] != NULL)
		{
			num2 = int(number2[i])-48;
			if (num1 == -1)
			{
				longer = 2;
			}
			else
				if (bigger == 0)
				{
					if (num1 > num2)
						bigger = 1;
					else if (num2 > num1)
						bigger = 2;
				}
		}
		else if (num1 != -1)
			longer = 1;
		i++;
	}
	if (longer == 0)
		return bigger;
	else
		return longer;

}

void sort(char** numbers, int amount) {
	int n = log2(amount);
	int k = 1;
	char* number;
	for (int i = 0;i < n;i++)
		k *= 2;
	k--;
	int j;
	while (k >= 1)
	{
		for (int i = k;i < amount;i++)
		{
			number = numbers[i];
			j = i;
			while (j >= k && com(number, numbers[j - k]) == 2)
			{
				numbers[j] = numbers[j - k];
				j -= k;
			}numbers[j] = number;
		}
		k = (k+1) / 2 -1;
				
		
	}
}

int main() {
 int  n;
	scanf("%d",&n);
	char** numbers = new char* [n];
	char* number = new char [SIZE * n];
	for (int i = 0;i < n;i++)
	{
		numbers[i] = number + i * SIZE;
		scanf("%s", numbers[i]);
	}
	sort(numbers,n);
	show(numbers,n);
	delete number[];
	return 0;
}