//header file for european option class
#pragma once
#ifndef EuropeanOption_hpp
#define EuropeanOption_hpp
#include <string>
#include <vector>
#include "OptionABC.h"
#include "Exception.h"
namespace KhoaTran
{
	using namespace std;
	class EuropeanOption : public Option
	{
	private:
		double r;		// Interest rate
		double sig;		// Volatility
		double K;		// Strike price
		double T;		// Expiry date
		double b;		// Cost of carry
		double S; //Current Asset Price
		char OptType;	// Option name (call, put)
		// Gaussian functions
		double n(double x) const;
		double N(double x) const;
		//Price functions take price input(so that I can use in MeshPrice() without the need for temporary object, plus I dont have to repeat the code )
		double PutPrice(double U) const;
		double CallPrice(double U) const;
		//Delta functions take price input(same idea)
		double PutDelta(double U) const;
		double CallDelta(double U) const;
	public:
		EuropeanOption();							// Default constructor
		EuropeanOption(char type, double asprice,
			double inter, double cost, double vol, double strike, double exp);	//Parameter constructor
		EuropeanOption(const EuropeanOption& option2);	// Copy constructor
		virtual ~EuropeanOption();
		//getters and setters
		double IR()const; //interest rate getter
		void IR(double a); //interest rate setter
		double Vol()const; //volitality getter
		void Vol(double b); //volitality setter
		double Strike()const; //strike price getter
		void Strike(double c); //strike price setter
		double Exp() const; //expiry date getter
		void Exp(double d); //expiry date setter
		double Cost() const;//Cost of carry getter
		void Cost(double f);//Cost of carry setter
		char Type() const; //Option Type getter
		void Type(char opttype); // Option Type setter, valid inputs: "C", "P"
		double AssetPrice() const;//Asset price getter
		void AssetPrice(double e);//Asset price setter
		std::string ToString() const; //Print out option description
		//Option calculations
		double OptionPrice() const; //Calculate Option price
		vector<double> MeshPrice(vector<double> source) const;//Calculate price from the mesh
		double Delta() const; //Calculate Option Delta
		vector<double> MeshDelta(vector<double> source1) const;//Calculate delta from the mesh
		double Gamma() const;////Calculate Option Gamma
		double ApproxDelta(double h) const;//Approximate Delta
		double ApproxGamma(double k) const;//Approximate Gamma
		//Put-Call Parity
		double Parity(char name, const double p)const;//Alternative way to compute Call & Put based on parity formular, input P or C, and the associated price to compute the other
		void Parity(double p1, double p2)const;//check if the 2 price satisfy the parity condition
		//I decided to make this a member function to have access to private members
		//Option Parameters Export function: Export Parameters of an option to a vector
		vector<double> VectorExport() const;
		//operators
		EuropeanOption& operator = (const EuropeanOption& option2);
		friend std::ostream& operator << (std::ostream& os, const EuropeanOption& option); // Send to ostream.
	};
}
#endif