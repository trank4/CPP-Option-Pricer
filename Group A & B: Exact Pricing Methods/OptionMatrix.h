//Header file OptionMatrix class
/* in my opinion, the MatrixPricer requested by the prompt should be encapsulate as a class
because it will be easier to add extra functions such as XPO pricing and delta and gamma calculation, or like adding extra options in.
Basically it's a matrix with extra functions to calculate price, delta, gamma. I will call the class OptionMatrix instead of MatrixPricer.*/
#pragma once
#ifndef OptionMatrix_hpp
#define OptionMatrix_hpp
#include <vector>
#include "Exception.h"
namespace KhoaTran
{
	using namespace std;
	class OptionMatrix
	{
	private:
		vector<vector<double>> OptMatrix;
		//European Option Price functions
		double EPutPrice(double Sp, double rp, double sigp, double Kp, double Tp, double bp) const;
		double ECallPrice(double Sc, double rc, double sigc, double Kc, double Tc, double bc) const;
		//American Option Price functions
		double APutPrice(double aSp, double arp, double asigp, double aKp, double aTp, double abp) const;
		double ACallPrice(double aSc, double arc, double asigc, double aKc, double aTc, double abc) const;
		//European Delta functions
		double PutDelta(double Sp, double rp, double sigp, double Kp, double Tp, double bp) const;
		double CallDelta(double Sc, double rc, double sigc, double Kc, double Tc, double bc) const;
		//Eurpean Gamma functions
		double Gamma(double S, double r, double sig, double K, double T, double b) const;
		// Gaussian functions
		double n(double x) const;
		double N(double x) const;
	public:
		OptionMatrix();							// Default constructor
		OptionMatrix(vector<vector<double>> source);	//Parameter constructor
		OptionMatrix(const OptionMatrix& mat);	// Copy constructor
		virtual ~OptionMatrix(); //Destructor
		//Option calculations
		vector<double> PriceVector(); //Calculate the Price for each option and put all in a vector
		vector<double> DeltaVector();//Calculate the delta for each option and put all in a vector
		vector<double> GammaVector();//Calculate the gamma for each option and put all in a vector
		//operators
		OptionMatrix& operator = (const OptionMatrix& optmat);
	};
}
#endif