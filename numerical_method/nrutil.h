#pragma once
#include <string>
#include <cmath>
#include <complex>
#include <iostream>
using namespace std;
typedef double DP;
template <class T>
inline const T SQR(const T& a) { return a * a; }
template <class T>
inline const T MAX(const T& a, const T& b) { return b > a ? (b) : (a); }
inline float MAX(const double& a, const float&b) { return b > a ? (b) : static_cast<float>(a); }
inline float MAX(const float& a, const double& b) { return b > a ? static_cast<float>(b) : (a); }
template<class T>
inline const T MIN(const T& a, const T& b) { return b > a ? (a) : (b); }
inline float MIN(const double& a, const float&b) { return b < a ? (b) : static_cast<float>(a); }
inline float MIN(const float& a, const double& b) { return b < a ? static_cast<float>(b) : (a); }
template<class T>
inline const T SIGN(const T &a, const T &b) {
	return (b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a));
}
template<class T>
inline const T SIGN(const T &a, const double &b) {
	return (b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a));
}
template<class T>
inline const T SIGN(const T &a, const float &b) {
	return (b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a));
}

template<class T>
inline void SWAP(T&a, T&b) {
	T dum = a; a = b; b = dum;
}

namespace NR {
	inline void	nrerror(const string error_text) {
		cerr << "Numerical recipes runtime error..." << endl;
		cerr << error_text << endl;
		cerr << "...now exiting..." << endl;
		exit(1);

	}
}

template<class T>
class NRVec {
private:
	int nn;
	T* v;
public:
	NRVec();
	explicit NRVec(int n);//防止类构造函数的隐式自动转换
	NRVec(const T&a, int n);
	NRVec(const T *a, int n);
	NRVec(const NRVec& rhs);
	NRVec& operator=(const NRVec&rhs);
	NRVec& operator=(const T&a);
	inline T& operator[](const int i);
	inline const T&operator[](const int i) const;
	inline int size() const;
	~NRVec();
};
template<class T>
NRVec<T>::NRVec() :nn(0), v(0) {};
template<class T>
NRVec<T>::NRVec(int n) :nn(n), v(new T[n]) {};
template<class T>
NRVec<T>::NRVec(const T&a, int n) :nn(n), v(new T[n]) {
	for (int i = 0; i < n; i++) {
		v[i] = a;
	}
}
template<class T>NRVec<T>::NRVec(const T*a, int n) : nn(n), v(new T[n]) {
	for (int i = 0; i < n; i++)
	{
		v[i] = *a++;
	}
}
template<class T>NRVec<T>::NRVec(const NRVec<T>&rhs) :nn(rhs.nn), v(new T[nn]) {
	for (int i = 0; i < nn; i++) {
		v[i] = rhs[i];
	}
}
template<class T>
NRVec<T> & NRVec<T>::operator=(const NRVec<T> & rhs)
{
	// TODO: insert return statement here
	if (this != rhs) {
		if (nn != rhs.nn) {
			if (v != 0) delete[](v);
			nn = rhs.nn;
			v = new T[nn];
		}
		for (int i = 0; i < nn; i++) {
			v[i] = rhs[i];
		}
	}
	return *this;
}
template<class T>NRVec<T>& NRVec<T>::operator=(const T& rhs) {
	for (int i = 0; i < nn; i++) {
		v[i] = rhs;

	}
	return *this;
}
template<class T>inline T& NRVec<T>::operator[](const int i) {
	return v[i];
}
template<class T>inline const T& NRVec<T>::operator[](const int i)const {
	return v[i];
}

template<class T>inline int NRVec<T>::size()const {
	return nn;
}

template<class T>
NRVec<T>::~NRVec() {
	if (v != 0) delete[](v);
}

template<class T>
class NRMat {
private:
	int nn;
	int mm;
	T **v;
public:
	NRMat();
	NRMat(int n, int m);
	NRMat(const T&a, int n, int m);
	NRMat(const T*a, int n, int m);
	NRMat(const NRMat &rhs);
	NRMat& operator=(const NRMat &rhs);
	NRMat& operator=(const T &a);
	inline T*operator[](const int i);
	inline const T* operator[] (const int i)const;
	inline int nrows() const;
	inline int ncols() const;
	~NRMat();
};
template<class T>
inline NRMat<T>::NRMat():nn(0),mm(0),v(0){}
template<class T>
inline NRMat<T>::NRMat(int n, int m):nn(n),mm(m),v(new T*[n])
{
	v[0] = new T[m*n];
	for (int i = 1; i < n; i++) {
		v[i] = v[i - 1] + m;
	}
}
template<class T>
NRMat<T>::NRMat(const T &a, int n, int m) :nn(n), mm(m), v(new T*[n]) {
	v[0] = new T[m*n];
	for (int i = 1; i < n; i++) {
		v[i] = v[i - 1] + m;

	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			v[i][j] = a;
		}
	}
}
template<class T>
NRMat<T>::NRMat(const T *a, int n, int m) :nn(n), mm(m), v(new T*[n]) {
	v[0] = new T[n*m];
	for (int i = 1; i < n; i++)
		v[i] = v[i - 1] + m;
	for(int i=0;i<n;i++)
		for (int j = 0; j < m; j++)
		{
			v[i][j] = *a++;
		}
}
template<class T>
NRMat<T>::NRMat(const NRMat<T> &rhs) :nn(rhs.nn), mm(rhs.mm), v(new T*[nn]) {
	v[0] = new T[nn*mm];
	for (int i = 1; i < nn; i++)
		v[i] = v[i - 1] + mm;
	for(int i=0;i<nn;i++)
		for (int j = 0; j < mm; j++) {
			v[i][j] = rhs[i][j];
		}
}

template<class T>
NRMat<T>& NRMat<T>::operator=(const NRMat<T>&rhs) {
	if (this != &rhs)
	{
		int i, j;
		if ((nn != rhs.nn) || (mm != rhs.mm))
		{
			if (v != 0) {
				delete[] (v[0]);
				delete[] (v);
			
			}
			nn = rhs.nn;
			mm = rhs.mm;
			v = new T*[nn];
			v[0] = new T[nn*mm];
			
		}
		for (i = 1; i < nn; i++)
			v[i] = v[i - 1] + mm;
		for(i=0;i<nn;i++)
			for (j = 0; j < mm; j++) {
				v[i][j] = rhs[i][j];
			}
	}
	return *this;
}
template<class T>
NRMat<T>& NRMat<T>::operator=(const T& a) {
	for (int i = 0; i < nn; i++)
	{
		for (int j = 0; j < mm; j++) {
			v[i][j] = a;
		}
	}
	return *this;
}
template<class T>
inline T * NRMat<T>::operator[](const int i)
{
	return v[i];
}
template<class T>
inline const T * NRMat<T>::operator[](const int i) const 
{
	return v[i];
}
template<class T>
NRMat<T>::~NRMat() {
	if (v != 0) {
		delete[](v[0]);
		delete[](v);
	}
}
template<class T>
inline int NRMat<T>::nrows() const
{
	return nn;
}
template<class T>
inline int NRMat<T>::ncols() const
{
	return mm;
}
template<class T>
class NRMat3d {
private:
	int nn;
	int mm;
	int kk;
	T ***v;
public:
	NRMat3d();
	NRMat3d(int n, int m, int k);
	NRMat3d(const T&a, int n, int m,int k);
	NRMat3d(const T*a, int n, int m, int k);
	NRMat3d(const NRMat3d &rhs);
	NRMat3d& operator=(const NRMat3d &rhs);
	NRMat3d& operator=(const T &a);
	inline T** operator[](const int i);
	inline const T* const * operator[] (const int i)const;
	inline int dim1() const ;
	inline int dim2() const ;
	inline int dim3() const ;
	~NRMat3d();
};
template<class T>
inline NRMat3d<T>::NRMat3d() :nn(0), mm(0),kk(0), v(0) {}
template<class T>
inline NRMat3d<T>::NRMat3d(int n, int m, int k) : nn(n), mm(m), kk(k),v(new T**[n])
{
	v[0] = new T*[m*n];
	v[0][0] = new T[m*n*k];
	for (int j = 1; j < m; j++)
		v[0][j] = v[0][j - 1] + k;
	for (int i = 1; i < n; i++) {
		v[i] = v[i - 1] + m;
		v[i][0] = v[i - 1][0] + m*k;
		for (int j = 1; j < m; j++) {
			v[i][j] = v[i][j - 1] + k;
		}
	}

}
template<class T>
NRMat3d<T>::NRMat3d(const T &a, int n, int m, int k) :nn(n), mm(m),kk(k), v(new T**[n]) {
	v[0] = new T*[m*n];
	v[0][0] = new T[m*n*k];
	for (int j = 1; j < m; j++)
		v[0][j] = v[0][j - 1] + k;
	for (int i = 1; i < n; i++) {
		v[i] = v[i - 1] + m;
		v[i][0] = v[i - 1][0] + m * k;
		for (int j = 1; j < m; j++) {
			v[i][j] = v[i][j - 1] + k;
		}
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			for (int l = 0; l < k; l++)
			{
				v[i][j][l] = a;
			}
}
template<class T>
NRMat3d<T>::NRMat3d(const T *a, int n, int m,int k) :nn(n), mm(m),kk(k), v(new T**[n]) {
	v[0] = new T*[m*n];
	v[0][0] = new T[m*n*k];
	for (int j = 1; j < m; j++)
		v[0][j] = v[0][j - 1] + k;
	for (int i = 1; i < n; i++) {
		v[i] = v[i - 1] + m;
		v[i][0] = v[i - 1][0] + m * k;
		for (int j = 1; j < m; j++) {
			v[i][j] = v[i][j - 1] + k;
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			for(int l=0;l<k;l++)
		{
			v[i][j][l] = *a++;
		}
}
template<class T>
NRMat3d<T>::NRMat3d(const NRMat3d<T> &rhs) :nn(rhs.nn), mm(rhs.mm),kk(rhs.kk),v(new T**[nn]) {
	v[0] = new T*[mm*nn];
	v[0][0] = new T[mm*nn*kk];
	for (int j = 1; j < mm; j++)
		v[0][j] = v[0][j - 1] + kk;
	for (int i = 1; i < nn; i++) {
		v[i] = v[i - 1] + mm;
		v[i][0] = v[i - 1][0] + mm * kk;
		for (int j = 1; j < mm; j++) {
			v[i][j] = v[i][j - 1] + kk;
		}
	}
	for (int i = 0; i < nn; i++)
		for (int j = 0; j < mm; j++) 
			for(int l=0;l<kk;l++)
		{
			v[i][j][l]= rhs[i][j][l];
		}
}

template<class T>
NRMat3d<T>& NRMat3d<T>::operator=(const NRMat3d<T>&rhs) {
	if (this != &rhs)
	{
		if ((nn != rhs.nn) || (mm != rhs.mm))
		{
			if (v != 0) {
				delete[](v[0][0]);
				delete[](v[0]);
				delete[](v);

			}
			nn = rhs.nn;
			mm = rhs.mm;
			kk = rhs.kk;
			v = new T**[nn];
			v[0] = new T*[nn*mm];
			v[0][0] = new T[nn*mm*kk];
		}
		
		for (int j = 1; j < mm; j++)
			v[0][j] = v[0][j - 1] + kk;
		for (int i = 1; i < nn; i++) {
			v[i] = v[i - 1] + mm;
			v[i][0] = v[i - 1][0] + mm * kk;
			for (int j = 1; j < mm; j++) {
				v[i][j] = v[i][j - 1] + kk;
			}
		}
		for (int i = 0; i < nn; i++)
			for (int j = 0; j < mm; j++)
				for (int l = 0; l < kk; l++)
				{
					v[i][j][l] = rhs[i][j][l];
				}
	}
	return *this;
}
template<class T>
NRMat3d<T>& NRMat3d<T>::operator=(const T& a) {
	for (int i = 0; i < nn; i++)
		for (int j = 0; j < mm; j++)
			for (int l = 0; l < kk; l++)
			{
				v[i][j][l] = a;
			}
	return *this;
}
template<class T>
inline T ** NRMat3d<T>::operator[](const int i)
{
	return v[i];
}
template<class T>
inline const T * const * NRMat3d<T>::operator[](const int i) const
{
	return v[i];
}
template<class T>
NRMat3d<T>::~NRMat3d() {
	if (v != 0) {
		delete[](v[0][0]);
		delete[](v[0]);
		delete[](v);
	}
}
template<class T>
inline int NRMat3d<T>::dim1() const
{
	return nn;
}
template<class T>
inline int NRMat3d<T>::dim2() const
{
	return mm;
}
template<class T>
inline int NRMat3d<T>::dim3() const
{
	return kk;
}