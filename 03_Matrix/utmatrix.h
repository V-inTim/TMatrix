// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);          //                            (#О1)
  TVector(const TVector &v);                // конструктор копирования    (#Л1)
  ~TVector();                               //                            (#О2)
  int GetSize()      { return Size;       } // размер вектора              (#О)
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента     (#О)
  ValType& operator[](int pos);             // доступ                     (#П2)
  bool operator==(const TVector &v) const;  // сравнение                  (#П3)
  bool operator!=(const TVector &v) const;  // сравнение                  (#П3)
  TVector& operator=(const TVector &v);     // присваивание              (#О3)

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр           (#Л2)
  TVector  operator-(const ValType &val);   // вычесть скаляр             (#С1)
  TVector  operator*(const ValType &val);   // умножить на скаляр         (#С2)

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение                   (#С3)
  TVector  operator-(const TVector &v);     // вычитание                  (#С4)
  ValType  operator*(const TVector &v);     // скалярное произведение     (#С5)

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v) //                  (#П4)
  {
    return in;                                                      
  }
  friend ostream& operator<<(ostream &out, const TVector &v) //           (#С6)
  {
    return out;                                                     // SKIP_OFF
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
    
    if (s <= 0) {
        throw "wring size";
    }
    if (s > MAX_VECTOR_SIZE) {
        throw "wrong size";
    }
    if (si < 0) {
        throw "StartIndex can't be negative";
    }

    Size = s;
    StartIndex = si;
    pVector = new ValType[Size]();
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
    this->Size = v.Size;
    this->StartIndex = v.StartIndex;
    this->pVector = new ValType[v.Size];
    for (int i = 0; i < Size; i++) {
        pVector[i] = v.pVector[i];
    }
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
    delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
    if (pos - StartIndex < 0 || pos - StartIndex >= Size) {
        throw "wrong index";
    }
    return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
    if (this == &v)
        return true;
    else
        if (Size != v.Size)
            return false;
        else
        {
            if (StartIndex != v.StartIndex)
                return false;
            else
            {
                for (int i = 0; i < Size; i++)
                    if (pVector[i] != v.pVector[i])
                        return false;
                return true;
            }
        }
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
    return !((*this) == v);
} /*-------------------------------------------------------------------------*/


template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
    if (this == &v)
        return *this;

    if (Size != v.Size) {
        ValType* tmp = pVector;
        pVector = new ValType[v.Size];
        if (pVector == nullptr)
            pVector = tmp;
    }
    for (int i = 0; i < Size; i++) {
        this->pVector[i] = v.pVector[i];
    }
    Size = v.Size;
    StartIndex = v.StartIndex;
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
    TVector v(*this);
    for (int i = 0; i < Size; i++) {
        v[i] += val;
    }
    return v;                                                    // SKIP_OFF
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
    TVector v(*this);
    for (int i = 0; i < Size; i++) {
        v[i] -= val;
    }
    return v;                                                       // SKIP_OFF
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
    TVector v(*this);
    for (int i = 0; i < Size; i++) {
        v[i] *= val;
    }
    return v;                                                          // SKIP_OFF
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
    if (Size != v.Size) {
        throw "wrong size";
    }
    TVector ans(Size, StartIndex);
    for (int i = 0; i < Size; i++) {
        ans.pVector[i] = pVector[i] + pVector[i];
    }
    return ans;                                                      // SKIP_OFF
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
    if (Size != v.Size) {
        throw "wrong size";
    }
    TVector ans(Size, StartIndex);
    for (int i = 0; i < Size; i++) {
        ans.pVector[i] = pVector[i] - pVector[i];
    }
    return ans;                                                         // SKIP_OFF
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
    if (Size != v.Size) {
        throw "wrong size";
    }
    ValType f{};
    for (int i=0; i < Size; i++) {
        f += pVector[i] * v.pVector[i];
    }
    return f;                                                         // SKIP_OFF
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           //                       (#О1)
  TMatrix(const TMatrix &mt);                    // копирование           (#Л1)
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа   (#Л2)
  bool operator==(const TMatrix &mt) const;      // сравнение             (#П1)
  bool operator!=(const TMatrix &mt) const;      // сравнение             (#П1)
  TMatrix& operator= (const TMatrix &mt);        // присваивание          (#О2)
  TMatrix  operator+ (const TMatrix &mt);        // сложение              (#П2)
  TMatrix  operator- (const TMatrix &mt);        // вычитание             (#С1)

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)                //  (#П3)
  {
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt) //        (#С3)
  {                                
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(s) {
    if (s * s > MAX_MATRIX_SIZE) {
        throw "wrong size";
    }
    for (int i = 0; i < s; i++) {
        pVector[i] = TVector<ValType>(s - i, i);
    }
}
template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):TVector<TVector<ValType>>(mt){
    
    
}                 
template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>> &mt):TVector<TVector<ValType>>(mt) {
    
}                        
template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
    if (this == &mt)
        return true;
    if (Size != mt.Size)
        return false;
    else {
        for (int i = 0; i < Size; i++)
            if (pVector[i] != mt.pVector[i])
                return false;
        return true;
    }
} 
template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
    return !(*this == mt);
} 
template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
    if (this != &mt) {
        if (*this != mt.Size) {
            delete[]pVector;
            pVector = new TVector<ValType>[mt.Size];
            Size = mt.Size;
            for (int i = 0; i < Size; i++)
                pVector[i] = mt.pVector[i];
        }

    }
    return *this;
}
template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
    return TVector<TVector<ValType>>::operator+(mt);
}

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
    return TVector<TVector<ValType>>::operator-(mt);
} 

#endif
