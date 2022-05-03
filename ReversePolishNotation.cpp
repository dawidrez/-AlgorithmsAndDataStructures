#include <iostream>
using namespace std;
#pragma warning(disable:4996)
#define START 20
typedef struct {
	int size;
	int amountElements;
	char* arr;

}stack;

void  push(char a,stack* st) {
	st->amountElements++;
	if (st->amountElements == st->size)
	{
		st->arr=(char*)realloc(st->arr,st->size*2);
		if (st->arr == NULL)
		{
			cout << "Blad";
		}
		st->size = 2 * st->size;
	}
	st->arr[st->amountElements - 1] = a;


}

char pop(stack* st) {
	if (st->amountElements > 0)
	{
		return st->arr[--st->amountElements];
	}
	cout << "stos jest pusty";
	return 'Z';
}

void  Negation(stack* st) {
	char a = pop(st);
	if (a == 'f')
		push('t', st);
	else if (a == 't')
		push('f', st);
}

void conjuction(stack* st) {
	char a = pop(st);
	if (a == 'Z')
		return;
	char b = pop(st);
	if (b == 'Z')
		return;
	else if (a == 't' && b == 't')
		push('t', st);
	else
		push('f', st);
}

void alternative(stack* st) {
	char a = pop(st);
	if (a == 'Z')
		return;
	char b = pop(st);
	if (b == 'Z')
		return;
	else if (a == 't' || b == 't')
		push('t', st);
	else
		push('f', st);
}


int main()
{
	int n;
	cin >> n;
	char a='0';
	scanf("%c", &a);
	for (int i = 0;i < n;i++)
	{
		stack st;
		st.arr = (char*)malloc(START*sizeof(char));
		st.size = START;
		st.amountElements = 0;
		while (a!=1)
		{
			scanf("%c", &a);
			if (a == 't' || a == 'f')
				push(a, &st);
			else if (a == 10)
				a = 1;
			else if (a == 'C')
				conjuction(&st);
			else if (a == 'N')
				Negation(&st);
			else if (a=='A')
				alternative(&st);
		}
		cout<<pop(&st);
		free(st.arr);
		a = 0;

	}


	return 0 ;
}

