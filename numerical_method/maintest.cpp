#include<iostream>

#include "nrutil.h"
int main() {
// test for mats
	NRMat<int>x;
	NRMat<int>y(10,5,6);
	x = y;
	NRMat3d<int>z;
	NRMat3d<int>w(10, 5, 6, 4);
	z = w;
	
	NRVec<int>r;
	NRVec<int>s(10,4);
	int z1[5] = { 1,2,3,4,5 };
	NRVec<int>p(z1,5);
	int z2[4] =
	{ 1,2,3,4 };

	NRMat<int>p2(z2, 2, 2);
	NRMat3d<int>p3(z2, 1, 2, 2);
	std::cout << "зјБъ2,2,1:" << z[2][2][1] << endl;
	system("pause");


}