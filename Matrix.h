#pragma once

#include <vector>

template <class T>
class SymmetricMatrix
{
public:
	SymmetricMatrix(T *a, size_t size)
		:_array(new T[size * (size+1)/2])
		, _size(size * (size + 1)/2)
	{
		assert(a);

		size_t index = 0;
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				if (i >= j)
				{
					_array[index++] = a[i * size + j];
				}
				else
				{
					break;
				}
			}
		}
	}

	T & Access(size_t i, size_t j)
	{
		if (i < j)
		{
			swap(i, j);
		}

		return _array[i * (i+1)/2 + j];
	}
private:
	T *_array;
	size_t _size;
};


template<class T>
struct Triple
{
	Triple(int row = 0, int col = 0, const T& value = T())
		:_row(row)
		, _col(col)
		, _value(value)
	{}

	int _row;
	int _col;
	T _value;
};

template<class T>
class SparseMatrix
{
public:
	SparseMatrix()
		:_row(0)
		, _col(0)
	{}
	SparseMatrix(T* a, int m, int n, const T& invalid)
		:_row(m)
		, _col(n)
		, _invalid(invalid)
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (a[i * n + j] != invalid)
				{
					_a.push_back(Triple<T>(i, j, a[i*n + j]));
				}
			}
		}
	}

	void Display()
	{
		size_t index = 0;
		for (size_t i = 0; i < _row; i++)
		{
			for (size_t j = 0; j < _col; j++)
			{
				if (index < _a.size()
					&& i == _a[index]._row
					&& j == _a[index]._col)
				{
					cout << _a[index++]._value << " ";
				}
				else
				{
					cout << _invalid << " ";
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	// O(col*有效数据的个数)
	SparseMatrix<T> Transport()
	{
		SparseMatrix<T> tmp;
		tmp._col = _row;
		tmp._row = _col;
		tmp._invalid = _invalid;

		tmp._a.reserve(_a.size());

		for (size_t i = 0; i < _col; i++)
		{
			size_t index = 0;
			while (index < _a.size())
			{
				if (_a[index]._col == i)
				{
					Triple<T> tp;
					tp._col = _a[index]._row;
					tp._row = _a[index]._col;
					tp._value = _a[index]._value;

					tmp._a.push_back(tp);
				}
				++index;
			}
		}

		return tmp;
	}

	// O(有效数据的个数+col)
	// O (col)
	SparseMatrix<T> FastTransport()
	{
		SparseMatrix<T> tmp;
		tmp._col = _row;
		tmp._row = _col;
		tmp._invalid = _invalid;
		tmp._a.resize(_a.size());

		int *rowCount = new int[_col];
		int *rowStart = new int[_col];
		memset(rowCount, 0, sizeof(int)*_col);
		memset(rowStart, 0, sizeof(int)*_col);

		size_t index = 0;
		while (index < _a.size())
		{
			rowCount[_a[index]._col]++;
			index++;
		}

		rowStart[0] = 0;
		for (size_t i = 1; i < _col; i++)
		{
			rowStart[i] = rowStart[i - 1] + rowCount[i - 1];	
		}

		index = 0;
		while (index < _a.size())
		{
			int &r = rowStart[_a[index]._col];

			Triple<T> tp;
			tp._col = _a[index]._row;
			tp._row = _a[index]._col;
			tp._value = _a[index]._value;

			tmp._a[r++] = tp;
			index++;
		}

		delete[] rowCount;
		delete[] rowStart;

		return tmp;
	}
private:
	vector<Triple<T>> _a;
	size_t _row;
	size_t _col;
	T _invalid;
};
