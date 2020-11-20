//header file for Perpetual American option class
#pragma once
#ifndef XPO_hpp
#define XPO_hpp
#include <string>
#include <vector>
#include "OptionABC.h"
#include "Exception.h"
namespace KhoaTran
{
	using namespace std;
	class XPO: public Option
	{
	private:
		double r;		// Interest rate
		double sig;		// Volatility
		double K;		// Strike price
		double b;		// Cost of carry
		double S; //Current Asset Price
		char OptType;	// Option name (call, put)
		//Price functions take price input(same idea as for European Option)
		double PutPrice(double U) const;
		double CallPrice(double U) const;
	public:
		XPO();							// Default constructor
		XPO(char type, double asprice,
			double inter, double cost, double vol, double strike);	//Parameter constructor
		XPO(const XPO& option2);	// Copy constructor
		virtual ~XPO();
		//getters and setters
		double IR()const; //interest rate getter
		void IR(double a); //interest rate setter
		double Vol()const; //volitality getter
		void Vol(double b); //volitality setter
		double Strike()const; //strike price getter
		void Strike(double c); //strike price setter
		double Cost() const;//Cost of carry getter
		void Cost(double f);//Cost of carry setter
		char Type() const; //Option Type getter
		void Type(char opttype); // Option Type setter, valid inputs: "C", "P"
		double AssetPrice() const;//Asset price getter
		void AssetPrice(double e);//Asset price setter
		std::string ToString() const;//Print out option description
		//Option calculations
		double OptionPrice() const; //Calculate Option price
		vector<double> MeshPrice(vector<double> source) const;//Calculate price from the mesh
		//Option Parameters Export function: Export Parameters of an option to a vector
		vector<double> VectorExport() const;
		//operators
		XPO& operator = (const XPO& option2);
		friend std::ostream& operator << (std::ostream& os, const XPO& option); // Send to ostream.
	};
}
#endif