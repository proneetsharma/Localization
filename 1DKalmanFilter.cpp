#include <iostream>
#include <math.h>
#include <tuple>

using namespace std;
double new_mean, new_var;
tuple<double, double> measurement_update(double mean1, double var1, double mean2, double var2)

{
	new_mean = (mean1 * var2 + mean2 * var1) / (var1 + var2);
	new_var = 1 / (1 / var1 + 1 / var2);
	return make_tuple(new_mean, new_var);
}

tuple<double, double> state_prediction(double mean1, double var1, double mean2, double var2)

{
	new_mean = mean1 + mean2;
	new_var = var1 + var2;
	return make_tuple(new_mean, new_var);
}

int main()
{
	// measurements and measurement variance
	double measurements[5] = {5, 6, 7, 9, 10};      // these are the positions (coordinates)
	double measurement_sig = 4;

	// Motions and motion variance
	double motions[5] = {1, 1, 2, 1, 1};            // these are the change in positions
	double motion_sig = 2;

	// Initial state
	double mu = 0;                     				// initial coordinate 
	double sig = 1000;

	for(int i = 0; i < sizeof(measurements) / sizeof(measurements[0]); i++)
	{
		tie(mu, sig) = measurement_update(mu, sig, measurements[i], measurement_sig);
		printf("[%f, %f]", mu, sig);
		tie(mu, sig) = state_prediction(mu, sig, motions[i], motion_sig);
		printf("[%f, %f]\n", mu, sig);

	}
	
	return 0;
}

