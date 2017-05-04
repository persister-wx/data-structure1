#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
//对称矩阵的压缩存储
template<class T>
class SymmetricMatrix
{
public:
    SymmetricMatrix(T* array, size_t N)
        :_N(N)
        ,_a(NULL)
    {
        _a = new T[(N * (N + 1))>> 1];
        for (size_t i = 0; i < N; ++i)
        {
            for (size_t j = 0; j < N; ++j)
            {
                if (i >= j)//表明是下三角数据时
                {
                    _a[(i * (i + 1))>>1 + j] = array[i * N + j];
                }
                else
                {
                    break;
                }
            }
        }
    }

    T& Access(size_t x, size_t y)
    {
        if (x < y)//如果访问上三角元素
        {
            swap(x, y);
        }
        return _a[(x * (x + 1)) >> 1 + y];
    }

    void DisPlay()
    {
        for (size_t i = 0; i < _N; ++i)
        {
            for (size_t j = 0; j < _N; ++j)
            {
                if (i >= j)//访问下三角元素
                {
                    cout<<Access(i, j)<<" ";
                }
                else
                {
                    cout << Access(j, i) << " ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    ~SymmetricMatrix()
    {
        if (_a)
        {
            delete[] _a;
            _a = NULL;
        }
    }

private:
    T* _a;
    size_t _N;
};

void Test()
{
    int a[5][5] =
    {
        { 0, 1, 2, 3, 4 },
        { 1, 0, 1, 2, 3 },
        { 2, 1, 0, 1, 2 },
        { 3, 2, 1, 0, 1 },
        { 4, 3, 2, 1, 0 },
    };
    SymmetricMatrix<int> sm((int*)a, 5);
    cout << sm.Access(0, 3) << endl;
    cout << sm.Access(3, 0) << endl;
    sm.DisPlay();
}

int main()
{
    Test();
    return 0;
}
