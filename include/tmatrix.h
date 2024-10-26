// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE) throw out_of_range("Too much importance");
    pMem = new T[sz]();// {}; // У типа T д.б. конструктор по умолчанию
    if (pMem == nullptr) throw domain_error("domain_error");
  }

  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    if (pMem == nullptr) throw domain_error("domain_error");
    std::copy(arr, arr + sz, pMem);
  }

  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz];
      if (pMem == nullptr) 
          throw domain_error("domain error");
      for (int i = 0; i < sz; i++)
          pMem[i] = v.pMem[i];
  }

  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = 0;
      pMem = nullptr;
      swap(*this, v);
  }

  ~TDynamicVector()
  {
      delete[] pMem;
      pMem = nullptr;
  }

  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v)
          return *this;
      if (sz != v.sz)
      {
          T* p = new T[v.sz];
          delete[] pMem;
          sz = v.sz;
          pMem = p;
      }

      std::copy(v.pMem, v.pMem + sz, pMem);
      return *this;
  }

  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      sz = 0;
      delete[] pMem;
      pMem = nullptr;
      swap(*this, v);
      return (*this);
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }

  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < 0 || ind >= sz)
      {
          throw range_error("range error");
      }
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0 || ind >= sz)
      {
          throw range_error("range error");
      }
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz)
          return false;
      for (int i = 0; i < sz; i++)
          if (pMem[i] != v.pMem[i])
              return false;
      return true;
  }

  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(*this);
      for (int i = 0; i < sz; i++)
          res.pMem[i] += val;
      return res;
  }

  TDynamicVector operator-(T val)
  {
      TDynamicVector res(*this);
      for (int i = 0; i < sz; i++)
          res.pMem[i] -= val;
      return res;
  }

  TDynamicVector operator*(T val)
  {
      TDynamicVector res(*this);
      for (int i = 0; i < sz; i++)
          res.pMem[i] *= val;
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw length_error("length error");

      TDynamicVector res(*this);
      for (int i = 0; i < sz; i++)
          res.pMem[i] += v.pMem[i];

      return res;
  }

  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw length_error("length error");

      TDynamicVector res(*this);
      for (int i = 0; i < sz; i++)
          res.pMem[i] -= v.pMem[i];

      return res;
  }

  T operator*(const TDynamicVector& v) 
  {
      if (sz != v.sz) throw length_error("length error");
      T sum = T(); 
      for (size_t i = 0; i < sz; ++i) 
          sum += (pMem[i] * v.pMem[i]);
      return sum;

  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (sz > MAX_MATRIX_SIZE) 
          throw out_of_range("out_of_range");
      if (sz == 0) 
          throw out_of_range("out_of_range");
      for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T> >::at;
  size_t size() const noexcept { return sz; }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz)
          return false;
      for (int i = 0; i < sz; i++)
          if (pMem[i] != m.pMem[i])
              return false;
      return true;
  }

  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      return !(*this == m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] * val;
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (size() != v.size()) 
          throw range_error;

      TDynamicVector<T> res(sz);
      for (i = 0; i < sz; i++) 
          for (j = 0; j < sz; j++) 
              res[i] += pMem[i][j] * v[j];

      return res;

  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw length_error("length error");
      TDynamicMatrix<T> res(sz);
      for (int i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] + m.pMem[i];
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw length_error("length error");
      TDynamicMatrix<T> res(sz);
      for (int i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] - m.pMem[i];
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw length_error("length error");
      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++)
          for (int k = 0; k < sz; k++)
              for (int j = 0; j < sz; j++)
                  res.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++) {
          istr >> v.pMem[i];
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++) 
          ostr << v.pMem[i] << endl;
      return ostr;
  }
};

#endif
