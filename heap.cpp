#include <cstdio>
#pragma warning(disable:4996)
#include <math.h> 
#define SIZE 65366

int left_child(int index) {
	return (index + 1) * 2-1;
}

int right_child(int index) {
	return (index + 1) * 2;
}

int parent(int index) {
	return (index + 1) / 2 - 1;
}

void swap(int* heap, int index1, int index2) {
	int tmp = heap[index1];
	heap[index1] = heap[index2];
	heap[index2] = tmp;
}

int  index_greater_son(int* heap, int  index, int  size)
{
	int index_L = left_child(index);
	if (index_L >= size)
		return -1;
	int index_R = right_child(index);
	int bigger= index_L;
	if (index_R < size)
		if(heap[index_L]<heap[index_R])
			 bigger = index_R;
	if (heap[index] < heap[bigger])
		return bigger;
	return -1;

}

bool heapify1(int* heap, int index, int size) {
	int greater_son = index_greater_son(heap, index, size);
	if (greater_son==-1)
	{
		return false;
	}
	swap(heap,index,greater_son);
	heapify1(heap,greater_son,size);
	return true;
}

int  index_smaller_son(int* heap, int  index, int  size)
{
	int index_L = left_child(index);
	if (index_L >= size)
		return -1;
	int index_R = right_child(index);
	int smaller = index_L;
	if (index_R < size)
		if (heap[index_L] > heap[index_R])
			 smaller = index_R;
	if (heap[index] > heap[smaller])
		return smaller;
	return -1;

}

bool heapify2(int* heap, int index, int size) {
	int smaller_son = index_smaller_son(heap, index, size);
	if (smaller_son == -1)
	{
		return false;
	}
	swap(heap, index, smaller_son);
	heapify2(heap, smaller_son, size);
	return true;
}

bool correct_heap(int * heap, int index,int min_max) {
	bool flag = false;
	if (index == 0)
		return flag;
	int parent_index=parent(index);
	if (heap[index] > heap[parent_index]&& min_max==1 || heap[index] < heap[parent_index] && min_max == -1)
	{
		flag = true;
		swap(heap,index,parent_index);
		correct_heap(heap,parent_index,min_max);
	}
	return flag;
}

void add_element(int* heap,int size,int min_max,int data) {
	heap[size] = data;
	correct_heap(heap,size,min_max);
}

void remove_root(int *heap,int size,int min_max) {
	printf("%d\n", heap[0]);
	heap[0] = heap[size-1];
	if(min_max==1)
	heapify1(heap, 0, size-1);
	else
	heapify2(heap, 0, size - 1);
}

int  build_new(int* heap, int min_max) {
	int n;
	scanf("%d", &n);
	int data;
	for (int i = 0;i < n;i++) {
		scanf("%d", &data);
		heap[i]=data;
	}
	for (int i = n - 1;i >= 0;i--)
		if (min_max == 1)
			heapify1(heap,i,n);
		else
			heapify2(heap, i, n);
	return n;
}

void print_array(int* heap, int size) {
	for (int i = 0;i < size;i++)
	{
		printf("%d ",heap[i]);
	}
	printf("\n");
}

//zmienna min_max  mowi,czy zmieniamy z rosnacego na malejacy,czy odwrotnie
void change_orientation(int* heap, int size, int min_max) {
	for (int i = size - 1;i >= 0;i--)
		if (min_max == 1)
			heapify1(heap, i, size);
		else
			heapify2(heap, i, size);
}

int main() {
	char command;
	int size = 0;
	int heap[SIZE];
	int exit = 0;
	int min_max=1;
	int data;
	while (scanf("%c", &command) && exit == 0)
	{
		switch (command) {
		case '+':
			scanf("%d",&data);
			add_element(heap, size,min_max,data);
			size++;
			break;
		case '-':
			remove_root(heap, size,min_max);
			size--;
			break;
		case 'p':
			print_array(heap, size);
			break;
		case 'r':
			size=build_new(heap, min_max);
			break;
		case 's':
			if (min_max == 1)
				min_max = -1;
			else
				min_max = 1;
			change_orientation(heap, size, min_max);
			break;
		case 'q':
			exit = 1;
			break;
		}
	}
	return 0;
}
