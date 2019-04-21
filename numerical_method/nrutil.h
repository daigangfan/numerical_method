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
};
