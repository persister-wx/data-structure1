#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<cassert>

//注意：一般触发断点可能是因为越界访问
template<class T>
class SymmetricMatrix
{
public :
	SymmetricMatrix(T* array, int N)//N代表方阵的行或列,将二维数组看作是一维数组
		:_pData(NULL)
		, _row(N)
		, _col(N)
	{
		int index = 0;
		_pData = new T[N * (N + 1) >> 1];//给下三角矩阵开辟空间
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j <= i; ++j)
			{
				_pData[index] = array[i * N + j];
				index++;
			}
		}
	}

	//访问矩阵中的元素
	T& Access(int row, int col)
	{
		if (row < col)//上三角的数据
		{
			std::swap(row, col);
		}
		return _pData[(row*(row + 1))/2 + col];
	}

	template<class T>//这里请注意：输出运算符重载函数不属于类，所以需要声明为模板函数
	friend ostream& operator<< (ostream& _cout, SymmetricMatrix<T>& m);

	~SymmetricMatrix()
	{
		if (_pData != NULL)
		{
			delete[] _pData;
			_pData = NULL;
		}
	}
private:
	T* _pData;
	size_t _row;
	size_t _col;
};

template<class T>
ostream& operator<<(ostream& _cout, SymmetricMatrix<T>& m)
{
	for (int i = 0; i < m._row; ++i)
	{
		for (int j = 0; j < m._col; ++j)
		{
			_cout << m.Access(i, j) << " ";
		}
		_cout << endl;
	}
	return _cout;
}

void Test()
{
	int a[5][5] = {
		{ 0, 1, 2, 3, 4 },
		{ 1, 0, 1, 2, 3 },
		{ 2, 1, 0, 1, 2 },
		{ 3, 2, 1, 0, 1 },
		{ 4, 3, 2, 1, 0 } };

	SymmetricMatrix<int> m((int*)a, 5);
	cout << m << endl;
	cout << m.Access(4,1);
}

int main()
{
	Test();
	return 0;
}
