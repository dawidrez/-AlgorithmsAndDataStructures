#include <iostream>
using namespace std;
#include <string>
#define SIZE 30*3*3*3*3*32
#define BASE 3
#define DIGITGROUP 5

struct Node {
	Node* next;
	int amount;
	string key;
};

int power(int base, int number) {
	int power=1;
	for (int i = 0;i < number;i++)
		power = power * base;
	return power;
}

int generateKey(string name) {
	int key=0;
	int digit;
	int pozycja=1;
	for (int i = 0;i < name.size();i++)
	{   if(digit = int(name[i]) - 94>=0)
		digit = int(name[i]) - 94;
	else
		digit = int(name[i]) - 64;
        key += digit * power(BASE,pozycja);
		pozycja = ((pozycja + 1) % DIGITGROUP);
	}
  return key;
}

int balance(Node** arr, int key,string name)
{
	int balance=0;
	if (arr[key] != NULL)
	{
		if (arr[key]->key == name)
			return arr[key]->amount;
		if (arr[key]->next != NULL) {
		Node* actual = arr[key]->next;
			while (actual != NULL) {
				if (actual->key == name)
					return actual->amount;
				actual = actual->next;
			}
		}
	}
	return balance;
}

void add(Node** arr, int key, int amount,string name) {
	Node* tmp = new Node;
	tmp->amount = amount;
	tmp->next = NULL;
	tmp->key = name;
	if (arr[key] == NULL)
	{
		arr[key] = tmp;
	}
	else
	{
		if (arr[key]->key == name)
		{
			arr[key]->amount += amount;
			delete tmp;
			return;
		}
		else if (arr[key]->next != NULL)
		{
			Node* actual = arr[key]->next;
			if (arr[key]->next->key == name)
			{
				actual->amount += amount;
				delete tmp;
				return;
			}
			while (actual->next != NULL) {
				if (actual->key == name)
				{
					actual->amount += amount;
					delete tmp;
					return;
				}
				actual = actual->next;
			}
			if (actual->key == name)
			{
				actual->amount += amount;
				delete tmp;
				return;
			}
			actual->next = tmp;
			return;
		}
		arr[key]->next = tmp;
	}
}


int main()
{
	char command;
	string owner;
	string recipent;
	string name;
	Node** hash=new Node*[SIZE];
	int amount;
	int key;
	for (int i = 0;i < SIZE;i++) {
		hash[i] = NULL;

	}
	while (cin >> command)
	{
		if (command == '+' || command == '?')
		{
		cin >> owner >> recipent;
		name = owner + recipent;
			key = generateKey(name);
			if (command == '?')
			{
				cout << balance(hash, key,name) << endl;
			}

			if (command == '+')
			{
				cin >> amount;
			
				add(hash, key, amount,name);
			}
		}
	}
	delete []hash;
	return 0;
}

