#include"Heap1.h"
#include"PriorityQueue1.h"

void TestHeap()
{
	int array[] = {53,17,78,9,45,65,87,23};
	Heap<int,Greater<int> > h(array,sizeof(array)/sizeof(int));
	cout << h.IsMaxHeap() << endl;
   	//h.Push(80);
	h.Pop();
	cout << h.IsMaxHeap() << endl;
}

void TestQueue()
{
	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23 };
	size_t len = sizeof(array) / sizeof(int);
	PriorityQueue<int> p;
	for (size_t index = 0; index < len; ++index)
	{
		p.Push(array[index]);
	}

	cout << p.Top() << endl;
	p.Pop();
	cout << p.Top() << endl;
}

void TestSort()
{
	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23 };
	Heap<int, Greater<int> > h(array, sizeof(array) / sizeof(int));
	h.Sort();
}


void TestTopk()
{
	Topk();
}


int main()
{
	//TestHeap();
	//TestQueue();
	//TestSort();
	Topk();
	return 0;
}
