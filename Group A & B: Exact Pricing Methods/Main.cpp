#include "EuropeanOption.h"
#include "XPO.h"
#include "OptionABC.h"
#include "OptionMatrix.h"
#include <vector>
#include <iostream>
using namespace KhoaTran;
//Global function MeshGenerator()
vector<double> MeshGenerator(double start, double end, double step)
{
	if (((end - start) * (step)) < 0) // checking if the inputs are valid
	{
		throw MeshException();
	}
	int vecsize = 1 + abs(floor((end - start) / (step)));
	vector<double> vec(vecsize);
	for (int i = 0; i < vec.size(); i++)
	{
		vec[i]=(start + (step * i));
	}
	return vec;
}

int main()
{
	try
	{
		//Test batch 1
		cout << ".................Testing Batches................." << endl;
		EuropeanOption Option1('c', 60, 0.08, 0.08, 0.3, 65, 0.25);
		std::cout << "Option Price: " << Option1.OptionPrice() << std::endl;
		Option1.Type('P');
		std::cout << "Option Price: " << Option1.OptionPrice() << std::endl;
		//Test batch 2
		EuropeanOption Option2('c', 100, 0.0, 0.0, 0.2, 100, 1);
		std::cout << "Option Price: " << Option2.OptionPrice() << std::endl;
		Option2.Type('P');
		std::cout << "Option Price: " << Option2.OptionPrice() << std::endl;
		//Test batch 3
		EuropeanOption Option3('c', 5, 0.12, 0.12, 0.5, 10, 1);
		std::cout << "Option Price: " << Option3.OptionPrice() << std::endl;
		Option3.Type('P');
		std::cout << "Option Price: " << Option3.OptionPrice() << std::endl;
		//Test batch 4
		EuropeanOption Option4('c', 100, 0.08, 0.08, 0.3, 100, 30);
		std::cout << "Option Price: " << Option4.OptionPrice() << std::endl;
		Option4.Type('P');
		std::cout << "Option Price: " << Option4.OptionPrice() << std::endl;
		//Parity Test
		cout << "..............Testing Parity.............." << endl;
		cout << Option4.Parity('P', 1.2475) << endl;
		cout << Option4.Parity('C', 92.1757) << endl;
		Option4.Parity(92.17570, 1.24750);
		//Increment Mesh S Test
		cout << ".............Testing MeshPrice................" << endl;
		vector<double> PriceMesh = MeshGenerator(100, 150, 10);
		vector<double> PriceTest = Option4.MeshPrice(PriceMesh);
		for (int i = 0; i < PriceTest.size(); i++) cout << PriceTest[i] << endl;
		Option4.Type('C');
		PriceTest = Option4.MeshPrice(PriceMesh);
		for (int i = 0; i < PriceTest.size(); i++) cout << PriceTest[i] << endl;
		//Testing Greeks
		cout << "............Testing Greeks............" << endl;
		EuropeanOption Option5('c', 105, 0.1, 0.0, 0.36, 100, 0.5);
		cout << Option5.Delta() << endl;
		Option5.Type('P');
		cout << Option5.Delta() << endl;
		cout << Option5.Gamma() << endl;
		//Testing Delta Mesh
		cout << ".........Testing Delta Mesh............." << endl;
		vector<double> DeltaMesh = MeshGenerator(105, 120, 5);
		vector<double> DeltaTest = Option5.MeshDelta(DeltaMesh);
		for (int i = 0; i < DeltaTest.size(); i++) cout << DeltaTest[i] << endl;
		Option5.Type('C');
		DeltaTest = Option5.MeshDelta(DeltaMesh);
		for (int i = 0; i < DeltaTest.size(); i++) cout << DeltaTest[i] << endl;
		//Testing Approximated Delta and Gamma
		cout << ".........Testing Approximated Delta and Gamma............." << endl;
		cout << "Estimated Call Delta of Option5 (h=0.01, 10 steps trial):" << endl;
		for (int i = 0; i < 10; i++)
		{
			double h = 0.01 + 0.01 * i;
			cout << Option5.ApproxDelta(h);
		}
		cout << endl;
		Option5.Type('P');
		cout << "Estimated Put Delta of Option5 (h=0.01, 10 steps trial):" << endl;
		for (int i = 0; i < 10; i++)
		{
			double h = 0.01 + 0.01 * i;
			cout << Option5.ApproxDelta(h);
		}
		cout << endl;
		cout << "Estimated Gamma of Option5 (h=0.01, 10 steps trial):" << endl;
		for (int i = 0; i < 10; i++)
		{
			double h = 0.01 + 0.01 * i;
			cout << Option5.ApproxGamma(h);
		}
		cout << endl;
		///////////////////////////////////////////////////////////////////////////////
		//PART B
		//Testing Perpetual American Option	
		cout << ".............Testing Perpetual American Option..........." << endl;
		XPO Option6('C', 110, 0.1, 0.02, 0.1, 100);
		std::cout << "Option Price: " << Option6.OptionPrice() << std::endl;
		Option6.Type('P');
		std::cout << "Option Price: " << Option6.OptionPrice() << std::endl;
		//Test batch 1 data
		XPO AOption1('C', 60, 0.08, 0.08, 0.3, 65);
		std::cout << "Option Price: " << AOption1.OptionPrice() << std::endl;
		//Test American Price Mesh
		cout << "............Testing American MeshPrice.............." << endl;
		vector<double> AmericanMesh = MeshGenerator(110, 150, 10);
		vector<double> AmericanTest = Option6.MeshPrice(AmericanMesh);
		for (int i = 0; i < AmericanTest.size(); i++) cout << AmericanTest[i] << endl;
		Option6.Type('C');
		AmericanTest = Option6.MeshPrice(AmericanMesh);
		for (int i = 0; i < AmericanTest.size(); i++) cout << AmericanTest[i] << endl;
		//Testing Polymorphism
		cout << "......................Testing Polymorphism.................." << endl;
		Option* option[2];
		option[0] = new EuropeanOption('c', 60, 0.08, 0.08, 0.3, 65, 0.25);
		option[1] = new XPO('C', 110, 0.1, 0.02, 0.1, 100);
		for (int i = 0; i < 2; i++)
		{
			cout << option[i]->ToString();
			cout << "Option Price: " << option[i]->OptionPrice() << endl;
		}
		for (int i = 0; i < 2; i++)
			delete option[i];
		cout << ".........Testing MatrixPricer............." << endl;
		/*Instead of calculating the monotonically increase parameters matrix, I choose to write the
		MatrixPricer() capable of calculating prices based on matrix on option data getting from a templated
		way specified in VectorExport(). I believe this is more robust and allow more practical uses*/
		//Test VectorExport()
		vector<double> Exp7 = AOption1.VectorExport();
		vector<double> Exp6 = Option6.VectorExport();
		vector<double> Exp5 = Option5.VectorExport();
		vector<double> Exp4 = Option4.VectorExport();
		vector<double> Exp3 = Option3.VectorExport();
		vector<double> Exp2 = Option2.VectorExport();
		vector<double> Exp1 = Option1.VectorExport();
		//Populate an Option Matrix
		vector<vector<double>> OptMatrix(0);
		OptMatrix.push_back(Exp1);
		OptMatrix.push_back(Exp2);
		OptMatrix.push_back(Exp3);
		OptMatrix.push_back(Exp4);
		OptMatrix.push_back(Exp5);
		OptMatrix.push_back(Exp6);
		OptMatrix.push_back(Exp7);
		//MatrixPricer()
		OptionMatrix Matrix(OptMatrix);
		cout << "Prices of Options in the matrix:" << endl;
		for (int i = 0; i < Matrix.PriceVector().size(); i++) cout << Matrix.PriceVector()[i] << endl;
		//Eliminate American options Exp6 and Exp7 in OptMatrix to test DeltaVector() and GammaVector()
		OptMatrix.pop_back();
		OptMatrix.pop_back();
		OptionMatrix Matrix2(OptMatrix);
		cout << "Deltas of Options in the matrix:" << endl;
		for (int i = 0; i < Matrix2.PriceVector().size(); i++) cout << Matrix2.DeltaVector()[i] << endl;
		cout << "Gammas of Options in the matrix:" << endl;
		for (int i = 0; i < Matrix2.PriceVector().size(); i++) cout << Matrix2.GammaVector()[i] << endl;
		//EuropeanOption ErrorOption('m', 60, 0.08, 0.08, 0.3, 65, 0.25); //This should trigger the catch
		return 1;
	}
	catch (OptionException & Err)
	{
		std::cout << Err.GetMessage() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unexpected Error Occurred" << std::endl;
	}
}