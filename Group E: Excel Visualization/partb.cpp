#include "UtilitiesDJD/ExcelDriver/ExcelDriverLite.hpp"
#include "UtilitiesDJD/ExcelDriver/Utilities.hpp"
#include "EuropeanOption.h"
using namespace std;
vector<double> MeshGenerator(double start, int numstep, double h)
{
	vector<double> vec(numstep+1);
	for (int i = 0; i < vec.size(); i++)
	{
		vec[i] = (start + (h * i));
	}
	return vec;
}
int main()
{
	//Create an European Option from batch 1
	KhoaTran::EuropeanOption Option1('c', 60, 0.08, 0.08, 0.3, 65, 0.25);
	//Create a mesh of prices staring at 60 with 100 step and mesh size of 5
	vector<double> price = MeshGenerator(60, 100, 5.0);
	//Calculate Call Price for these prices
	vector<double> CallPrice;
	for (int i = 0; i < price.size(); i++)
	{
		Option1.AssetPrice(price[i]);
		CallPrice.push_back(Option1.OptionPrice());
	}
	//Calculate Put Price for these prices
	Option1.Type('P');
	vector<double> PutPrice;
	for (int i = 0; i < price.size(); i++)
	{
		Option1.AssetPrice(price[i]);
		PutPrice.push_back(Option1.OptionPrice());
	}
	//Pump it out to excel
	ExcelDriver xl; 
	xl.MakeVisible(true);
	//Create labels
	std::list<std::string> labels;
	labels.push_back("Call Price");
	labels.push_back("Put Price");
	//Create functions
	std::list<std::vector<double> > curves;
	curves.push_back(CallPrice);
	curves.push_back(PutPrice);
	std::cout << "Thanks God the code worked\n";
	xl.CreateChart(price, labels, curves, "Call and Put Prices", "Asset Price", "Option Price");
	return 1;
}
