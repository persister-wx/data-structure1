#include"vector1.h"

void Test()
{
	/*Vector<int> v1;
	cout << v1.Size() << endl;*/
	Vector<int > v2(10, 29);
	cout << v2.Size() << endl;
	Vector<int> v3(v2);
	v3.Print();
	cout << v3.Size() << endl;
	/*Vector<int>::Iterator pos = v3.Begin();
	v3.Insert(pos, 5);
	v3.Print();
	cout << v3.Size() << endl;*/
	Vector<int>::Iterator pos = v3.Begin();
	v3.Erase(pos);
	v3.Print();
	cout << v3.Size() << endl;
}

int main()
{
	Test();
	return 0;
}

