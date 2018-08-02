#include <iostream>
#include <math.h>
#include <tuple>
#include "Core"  // Eigen Library
#include "LU"    // Eigen Library


using namespace std;
using namespace Eigen;


float measurements[3] = {1, 2, 3 };

tuple<MatrixXf, MatrixXf> Kalman_filter(MatrixXf x, MatrixXf P, MatrixXf u, MatrixXf F, MatrixXf H, MatrixXf R, MatrixXf I )
{

	for(int n = 0; n < sizeof(measurements) / sizeof(measurements[0]); n++)
	{
		MatrixXf z( 1, 1);
		z << measurements[n];
	
		MatrixXf y( 1, 1);
		y << z - (H * x);

		MatrixXf S( 1, 1);
		S << H * P * H.transpose() * R;

		MatrixXf K( 2, 1);
		K << P * H.transpose() * S.transpose();

		x << x + (K * y);

		P << (I - (K * H )) * P;

		x << (F * x) + u;
		P << F * P * F.transpose();

	}
	return make_tuple(x, P);
}

int main()
{
	MatrixXf x(2, 1);
	x << 0,
		 0;

	MatrixXf P(2, 2);
	x << 10000, 0,
		 0, 10000;

	MatrixXf u(2, 1);
	x << 0,
		 0;

	MatrixXf F(2, 2);
	x << 1, 1,
		 0, 1;

	MatrixXf H(1, 2);
	x << 1,
		 0;

	MatrixXf R(1, 1);
	x << 1;
		 

	MatrixXf I(2, 2);
	x << 1, 0,
		 0, 1;
	
	tie(x, P) = Kalman_filter(x, P, u, F, H, R, I);
	cout << "x= " << x << endl;
	cout << "P= " << P << endl;

	return 0;
}

