// HardCoded.cpp
//
// C++ code to price an option, essential algorithms.
//
// We take CEV model with a choice of the elaticity parameter
// and the Euler method. We give option price and number of times
// S hits the origin.
//
// (C) Datasim Education BC 2008-2011
//

#include "OptionData.hpp" 
#include "NormalGenerator.hpp"
#include "Range.cpp"
#include <cmath>
#include <iostream>


namespace SDEDefinition
{ // Defines drift + diffusion + data

	OptionData* data;				// The data for the option MC

	double drift(double t, double X)
	{ // Drift term
	
		return (data->r)*X; // r - D
	}

	
	double diffusion(double t, double X)
	{ // Diffusion term
	
		double betaCEV = 1.0;
		return data->sig * pow(X, betaCEV);
		
	}

	double diffusionDerivative(double t, double X)
	{ // Diffusion term, needed for the Milstein method
	
		double betaCEV = 1.0;
		return 0.5 * (data->sig) * (betaCEV) * pow(X, 2.0 * betaCEV - 1.0);
	}
} // End of namespace
double SD(std::vector<double> prices, double r, double T)
{
	double M = prices.size();
	double sum_prices = 0;
	double squaredsum_prices = 0;
	//calculate sum of prices and square sum of prices
	for (int i = 0; i < M; i++)
	{
		sum_prices = sum_prices + prices[i];
		squaredsum_prices = squaredsum_prices + pow(prices[i], 2);
	}

	double tmp = sqrt(squaredsum_prices - (sum_prices * sum_prices) / M );
	double SD = tmp * exp(-r * T) /(M - 1.0);
	return SD;
}
double SE(std::vector<double> prices, double r, double T)
{
	double M = prices.size();
	double sum_prices = 0;
	double squaredsum_prices = 0;
	//calculate sum of prices and square sum of prices
	for (int i = 0; i < M; i++)
	{
		sum_prices = sum_prices + prices[i];
		squaredsum_prices = squaredsum_prices + pow(prices[i], 2);
	}

	double tmp = sqrt(squaredsum_prices - (sum_prices * sum_prices) / M);
	double SD = tmp * exp(-r * T) / (M - 1.0);
	double SE = SD / (sqrt(M));
	return SE;
}
int main()
{
	std::cout <<  "1 factor MC with explicit Euler\n";
	OptionData myOption;
	myOption.K = 100;
	myOption.T = 1;
	myOption.r = 0.0;
	myOption.sig = 0.2;
	myOption.type = 1;	// Put -1, Call +1
	double S_0 = 100;
	
	long N = 100;
	std::cout << "Number of subintervals in time: ";
	std::cin >> N;

	// Create the basic SDE (Context class)
	Range<double> range (0.0, myOption.T);
	double VOld = S_0;
	double VNew;

	std::vector<double> x = range.mesh(N);
	

	// V2 mediator stuff
	long NSim = 50000;
	std::cout << "Number of simulations: ";
	std::cin >> NSim;

	double k = myOption.T / double (N);
	double sqrk = sqrt(k);

	// Normal random number
	double dW;
	double price = 0.0;	// Option price

	// NormalGenerator is a base class
	NormalGenerator* myNormal = new BoostNormal();

	using namespace SDEDefinition;
	SDEDefinition::data = &myOption;

	std::vector<double> res;
	int coun = 0; // Number of times S hits origin
	std::vector<double> prices; //vector to get prices at t = T for SD SE functions
	// A.
	for (long i = 1; i <= NSim; ++i)
	{ // Calculate a path at each iteration
			
		if ((i/10000) * 10000 == i)
		{// Give status after each 1000th iteration

				std::cout << i << std::endl;
		}

		VOld = S_0;
		for (unsigned long index = 1; index < x.size(); ++index)
		{

			// Create a random number
			dW = myNormal->getNormal();
				
			// The FDM (in this case explicit Euler)
			VNew = VOld  + (k * drift(x[index-1], VOld))
						+ (sqrk * diffusion(x[index-1], VOld) * dW);

			VOld = VNew;

			// Spurious values
			if (VNew <= 0.0) coun++;
		}
			
		double tmp = myOption.myPayOffFunction(VNew);
		prices.push_back(tmp);
		price += (tmp)/double(NSim);
	}
	//Calculate SD, SE
	double SDresult = SD(prices,0.0,1);
	double SEresult = SE(prices, 0.0, 1);
	// D. Finally, discounting the average price
	price *= exp(-myOption.r * myOption.T);

	// Cleanup; V2 use scoped pointer
	delete myNormal;

	std::cout << "Price, after discounting: " << price << ", " << std::endl;
	std::cout << "Number of times origin is hit: " << coun << endl;
	std::cout << "SD: " << SDresult << endl;
	std::cout << "SE: " << SEresult << endl;
	return 0;
}