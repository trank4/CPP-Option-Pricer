//source code for European Option class
#include "EuropeanOption.h"
#include <cmath>
#include <iostream>
#include <boost/math/distributions.hpp> 
namespace KhoaTran
{
	using namespace std;
	//Gaussian functions
	double EuropeanOption::n(double x) const
	{
		boost::math::normal_distribution<> myNormal(0.0, 1.0);
		return pdf(myNormal, x);
	}

	double EuropeanOption::N(double x) const
	{ 
		boost::math::normal_distribution<> myNormal(0.0, 1.0);
		return cdf(myNormal, x);
	}
	//Put and Call private functions
	double EuropeanOption::PutPrice(double U) const
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (K * exp(-r * T) * N(-d2)) - (U * exp((b - r) * T) * N(-d1));
	}
	double EuropeanOption::CallPrice(double U) const
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (U * exp((b - r) * T) * N(d1)) - (K * exp(-r * T) * N(d2));
	}
	//Delta private functions
	double EuropeanOption::PutDelta(double U) const
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / tmp;
		return exp((b - r) * T) * (N(d1) - 1);
	}
	double EuropeanOption::CallDelta(double U) const
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / tmp;
		return exp((b - r) * T) * N(d1);
	}
	
	//default constructor
	EuropeanOption::EuropeanOption() : r(0.05), sig(0.2), K(110.0), T(0.5), S(100), OptType('C'), b(0.05), Option()
	{
		cout << "A Default European Option was created" << endl;
	}
	//ParaConstructor
	EuropeanOption::EuropeanOption(char type, double asprice,
		double inter, double cost, double vol, double strike, double exp) : S(asprice), r(inter), sig(vol), K(strike), T(exp), b(cost), OptType(type), Option()
	{
		//Check capitalized OptType
		if (OptType == 'c') OptType = 'C';
		if (OptType == 'p') OptType = 'P';
		if (((OptType != 'P') && (OptType != 'C')) == 1) throw NotPutnorCallException(OptType);
		cout << "A specified European Option was created" << endl;
	}
	//Copy Constructor
	EuropeanOption::EuropeanOption(const EuropeanOption& option2) : r(option2.r), sig(option2.sig), K(option2.K), T(option2.T),
		 S(option2.S), OptType(option2.OptType), b(option2.b), Option(option2)
	{
		cout << "An European Option was created by copy constructor" << endl;
	}
	//Destrutor
	EuropeanOption::~EuropeanOption()
	{
		cout << "An European Option terminated" << endl;
	}
	//interest rate getter
	double EuropeanOption::IR()const
	{
		return r;
	}
	//interest rate setter
	void EuropeanOption::IR(double a)
	{
		r=a;
	}
	//Volitality getter
	double EuropeanOption::Vol()const
	{
		return sig;
	}
	//Volitality setter
	void EuropeanOption::Vol(double v)
	{
		sig=v;
	}
	//SPrice getter
	double EuropeanOption::Strike()const
	{
		return K;
	}
	//SPrice setter
	void EuropeanOption::Strike(double c)
	{
		K=c;
	}
	//Exp getter
	double EuropeanOption::Exp()const
	{
		return T;
	}
	//Exp setter
	void EuropeanOption::Exp(double d)
	{
		T=d;
	}
	//Type getter
	char EuropeanOption::Type()const
	{
		return OptType;
	}
	//Type setter
	void EuropeanOption::Type(char opttype)
	{
		OptType= opttype;
		//Check capitalized OptType
		if (OptType == 'c') OptType = 'C';
		if (OptType == 'p') OptType = 'P';
		if (((OptType != 'P') && (OptType != 'C')) == 1) throw NotPutnorCallException(OptType);
	}
	//AssetPrice getter
	double EuropeanOption::AssetPrice() const
	{
		return S;
	}
	//AssetPrice setter
	void EuropeanOption::AssetPrice(double e)
	{
		S=e;
	}
	//Cost getter
	double EuropeanOption::Cost()const
	{
		return b;
	}
	//Cost setter
	void EuropeanOption::Cost(double f)
	{
		b = f;
	}
	//Calculate option price
	double EuropeanOption::OptionPrice() const
	{
		if (OptType == 'C')
		{
			return CallPrice(S);
		}
		else
		{
			return PutPrice(S);
		}
	}
	//Calculate price from the mesh
	vector<double> EuropeanOption::MeshPrice(vector<double> source) const
	{
		vector<double> vec;
		if (OptType == 'C')
		{
			for (int i = 0; i < source.size(); i++)
			{
				vec.push_back(CallPrice(source[i]));
			}
		}
		else
		{
			for (int i = 0; i < source.size(); i++)
			{
				vec.push_back(PutPrice(source[i]));
			}
		}
		return vec;
	}
	//Calculate Option Delta
	double EuropeanOption::Delta() const
	{
		if (OptType == 'C')
		{
			return CallDelta(S);
		}
		else
		{
			return PutDelta(S);
		}
	}
	//Calculate delta from the mesh
	vector<double> EuropeanOption::MeshDelta(vector<double> source1) const
	{
		vector<double> vec;
		if (OptType == 'C')
		{
			for (int i = 0; i < source1.size(); i++)
			{
				vec.push_back(CallDelta(source1[i]));
			}
		}
		else
		{
			for (int i = 0; i < source1.size(); i++)
			{
				vec.push_back(PutDelta(source1[i]));
			}
		}
		return vec;
	}
	//= operator
	EuropeanOption& EuropeanOption::operator = (const EuropeanOption& option2)
	{
		if (this == &option2) return *this;

		else
		{
			r = option2.r;
			sig = option2.sig;
			K = option2.K;
			T = option2.T;
			b = option2.b;
			S = option2.S;
			OptType = option2.OptType;
			Option::operator=(option2);
			return *this;
		}
	}
	//<< operator
	std::ostream& operator << (std::ostream& os, const EuropeanOption& option)
	{
		os << "The European Option has the following properties:"<< std::endl;
		os << "Asset Price: " << option.S << std::endl;
		os << "Interest Rate: " <<option.r<< std::endl;
		os << "Voltality: " << option.sig << std::endl;
		os << "Strike Price: " << option.K << std::endl;
		os << "Maturity (Years): " << option.T << std::endl;
		os << "Cost of Carry: " << option.b << std::endl;
		os << "Option Type (C = Call, P = Put): " << option.OptType << std::endl;
		return os;
	}
	//ParityCall
	double EuropeanOption::Parity(char name, const double p)const
	{
		if ((name == 'P') || (name=='p'))
		{
			return (p + S - K * exp(-r * T));
		}
		else
		{
			return (-(-p + S - K * exp(-r * T)));
		}
	}
	//parity check
	void EuropeanOption::Parity(double p1, double p2)const
	{
		double tolerance = 0.001;
		if (abs(p1 - (p2 + S - K * exp(-r * T))) < tolerance)
		{
			cout << "Call Put Parity Sastisfied" << endl;
		}
		else
		{
			cout << "Call Put Parity Not Sastisfied" << endl;
		}
	}
	
	//Option Parameters Export function
	vector<double> EuropeanOption::VectorExport() const
	{
		vector<double> Exp(8);
		Exp[0] = 'E';
		Exp[1] = OptType;
		Exp[2] = S;
		Exp[3] = r;
		Exp[4] = sig;
		Exp[5] = K;
		Exp[6] = T;
		Exp[7] = b;
		return Exp;
	}
	//Option Gamma
	double EuropeanOption::Gamma() const
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;
		return ((n(d1) * exp((b - r) * T)) / (S * tmp));
	}
	//ToString()
	std::string EuropeanOption::ToString() const
	{
		std::string s_x;
		std::stringstream strs;
		std::string s = Option::ToString();
		strs << "European Option ID: " << s << std::endl;
		strs << "The European Option has the following properties:" << std::endl;
		strs << "Asset Price: " << S << std::endl;
		strs << "Interest Rate: " << r << std::endl;
		strs << "Voltality: " << sig << std::endl;
		strs << "Strike Price: " << K << std::endl;
		strs << "Maturity (Years): " << T << std::endl;
		strs << "Cost of Carry: " << b << std::endl;
		strs << "Option Type (C = Call, P = Put): " << OptType << std::endl;
		return s_x = strs.str();
	}
	//Approximate Delta
	double EuropeanOption::ApproxDelta(double h) const
	{
		if (OptType == 'C')
		{
			double tmp1 = CallPrice(S + h);
			double tmp2 = CallPrice(S - h);
			return (tmp1-tmp2)/(2*h);
		}
		else
		{
			double tmp1 = PutPrice(S + h);
			double tmp2 = PutPrice(S - h);
			return (tmp1 - tmp2) / (2 * h);
		}
	}
	//Approximate Gamma
	double EuropeanOption::ApproxGamma(double h) const
	{
		double tmp1 = CallPrice(S + h);
		double tmp2 = CallPrice(S - h);
		double tmp3 = CallPrice(S);
		return (tmp1 - 2*tmp3 + tmp2) / (2 * h*h);
	}
}


