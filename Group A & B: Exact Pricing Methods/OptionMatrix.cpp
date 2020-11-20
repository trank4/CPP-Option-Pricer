//source code for OptionMatrix class
#include "OptionMatrix.h"
#include <cmath>
#include <iostream>
#include <boost/math/distributions.hpp> 
namespace KhoaTran
{
	using namespace std;
	//private functions
	double OptionMatrix::n(double x) const
	{
		boost::math::normal_distribution<> myNormal(0.0, 1.0);
		return pdf(myNormal, x);
	}

	double OptionMatrix::N(double x) const
	{
		boost::math::normal_distribution<> myNormal(0.0, 1.0);
		return cdf(myNormal, x);
	}
	double OptionMatrix::EPutPrice(double Sp, double rp, double sigp, double Kp, double Tp, double bp) const
	{
		double tmp = sigp * sqrt(Tp);
		double d1 = (log(Sp / Kp) + (bp + (sigp * sigp) * 0.5) * Tp) / tmp;
		double d2 = d1 - tmp;
		return (Kp * exp(-rp * Tp) * N(-d2)) - (Sp * exp((bp - rp) * Tp) * N(-d1));
	}
	double OptionMatrix::ECallPrice(double Sc, double rc, double sigc, double Kc, double Tc, double bc) const
	{
		double tmp = sigc * sqrt(Tc);
		double d1 = (log(Sc / Kc) + (bc + (sigc * sigc) * 0.5) * Tc) / tmp;
		double d2 = d1 - tmp;
		return (Sc * exp((bc - rc) * Tc) * N(d1)) - (Kc * exp(-rc * Tc) * N(d2));
	}
	double OptionMatrix::APutPrice(double aSp, double arp, double asigp, double aKp, double aTp, double abp) const
	{
		double tmp = (abp / (asigp * asigp) - 0.5) * (abp / (asigp * asigp) - 0.5) + (2 * arp) / (asigp * asigp);
		double y2 = 0.5 - (abp / (asigp * asigp)) - sqrt(tmp);
		double tolerance = 0.001;
		if (abs(y2 - 1.0) < tolerance) return aSp;
		double tmp2 = pow(((y2 - 1) * aSp) / (y2 * aKp), y2);
		return ((aKp/ (1 - y2)) * tmp2);
	}
	double OptionMatrix::ACallPrice(double aSc, double arc, double asigc, double aKc, double aTc, double abc) const
	{
		double tmp = (abc / (asigc * asigc) - 0.5) * (abc / (asigc * asigc) - 0.5) + (2 * arc) / (asigc * asigc);
		double y1 = 0.5 - (abc / (asigc * asigc)) + sqrt(tmp);
		double tolerance = 0.001;
		if (abs(y1 - 1.0) < tolerance) return aSc;
		double tmp2 = pow(((y1 - 1) * aSc) / (y1 * aKc), y1);
		return ((aKc / (y1 - 1)) * tmp2);
	}
	double OptionMatrix::PutDelta(double Sp, double rp, double sigp, double Kp, double Tp, double bp) const
	{
		double tmp = sigp * sqrt(Tp);
		double d1 = (log(Sp / Kp) + (bp + (sigp * sigp) * 0.5) * Tp) / tmp;
		return exp((bp - rp) * Tp) * (N(d1) - 1);
	}
	double OptionMatrix::CallDelta(double Sc, double rc, double sigc, double Kc, double Tc, double bc) const
	{
		double tmp = sigc * sqrt(Tc);
		double d1 = (log(Sc / Kc) + (bc + (sigc * sigc) * 0.5) * Tc) / tmp;
		return exp((bc - rc) * Tc) * N(d1);
	}
	double OptionMatrix::Gamma(double S, double r, double sig, double K, double T, double b) const
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;
		return ((n(d1) * exp((b - r) * T)) / (S * tmp));
	}
	//Default Constructor
	OptionMatrix::OptionMatrix()
	{
		OptMatrix.resize(1);
		OptMatrix[1].resize(0);
		OptMatrix[1].push_back('E');
		OptMatrix[1].push_back('C');
		OptMatrix[1].push_back(100);
		OptMatrix[1].push_back(0.05);
		OptMatrix[1].push_back(0.2);
		OptMatrix[1].push_back(110.0);
		OptMatrix[1].push_back(0.5);
		OptMatrix[1].push_back(0.05);
		cout << "A Default Option Matrix was created" << endl;
	}
	//Parameter constructor
	OptionMatrix::OptionMatrix(vector<vector<double>> source): OptMatrix(source)
	{
		cout << "A specified Option Matrix was created" << endl;
	}
	// Copy constructor
	OptionMatrix::OptionMatrix(const OptionMatrix& mat): OptMatrix(mat.OptMatrix)
	{
		cout << "An Option Matrix was created by copy constructor" << endl;
	}
	//Destructor
	OptionMatrix::~OptionMatrix()
	{
		cout << "An Option Matrix terminated" << endl;
	}
	//Operator=
	OptionMatrix& OptionMatrix::operator = (const OptionMatrix& optmat)
	{
		if (this == &optmat) return *this;

		else
		{
			OptMatrix = optmat.OptMatrix;
			return *this;
		}
	}
	//PriceVector()
	vector<double> OptionMatrix::PriceVector()
	{
		vector<double> price(0);
		for (int i = 0; i < OptMatrix.size(); i++)
		{
			if (OptMatrix[i][0] == 'E')
			{
					if (OptMatrix[i][1] == 'C')
					{
						double tmp = ECallPrice(OptMatrix[i][2], OptMatrix[i][3], OptMatrix[i][4], OptMatrix[i][5], OptMatrix[i][6], OptMatrix[i][7]);
						price.push_back(tmp);
					}
					else
					{
						double tmp = EPutPrice(OptMatrix[i][2], OptMatrix[i][3], OptMatrix[i][4], OptMatrix[i][5], OptMatrix[i][6], OptMatrix[i][7]);
						price.push_back(tmp);
					}
				
			}
			else
			{
					if (OptMatrix[i][1] == 'C')
					{
						double tmp = ACallPrice(OptMatrix[i][2], OptMatrix[i][3], OptMatrix[i][4], OptMatrix[i][5], OptMatrix[i][6], OptMatrix[i][7]);
						price.push_back(tmp);
					}
					else
					{
						double tmp = APutPrice(OptMatrix[i][2], OptMatrix[i][3], OptMatrix[i][4], OptMatrix[i][5], OptMatrix[i][6], OptMatrix[i][7]);
						price.push_back(tmp);
					}
			}
		}
		return price;
	}
	//DeltaVector()
	vector<double> OptionMatrix::DeltaVector()
	{
		vector<double> delta(0);
		for (int i = 0; i < OptMatrix.size(); i++)
		{
			if (OptMatrix[i][0] == 'A') throw NotEuropeanException(OptMatrix[i][0]); //check to make sure it's not American Option
			if (OptMatrix[i][1] == 'C')
			{
				double tmp = CallDelta(OptMatrix[i][2], OptMatrix[i][3], OptMatrix[i][4], OptMatrix[i][5], OptMatrix[i][6], OptMatrix[i][7]);
				delta.push_back(tmp);
			}
			else
			{
				double tmp = PutDelta(OptMatrix[i][2], OptMatrix[i][3], OptMatrix[i][4], OptMatrix[i][5], OptMatrix[i][6], OptMatrix[i][7]);
				delta.push_back(tmp);
			}
		}
		return delta;
	}
	//GammaVector()
	vector<double> OptionMatrix::GammaVector()
	{
		vector<double> gamma(0);
		for (int i = 0; i < OptMatrix.size(); i++)
		{
			if (OptMatrix[i][0] == 'A') throw NotEuropeanException(OptMatrix[i][0]); //check to make sure it's not American Option
			double tmp = Gamma(OptMatrix[i][2], OptMatrix[i][3], OptMatrix[i][4], OptMatrix[i][5], OptMatrix[i][6], OptMatrix[i][7]);
			gamma.push_back(tmp);
		}
		return gamma;
	}

}