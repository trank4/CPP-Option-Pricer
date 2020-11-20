//source code for American Option class
#include "XPO.h"
#include <cmath>
#include <iostream>
namespace KhoaTran
{
	using namespace std;
	//Put and Call private functions
	double XPO::PutPrice(double U) const
	{
		double tmp = (b/(sig*sig)-0.5)* (b / (sig * sig) - 0.5) + (2*r)/(sig*sig);
		double y2 = 0.5 - (b /(sig * sig)) - sqrt(tmp);
		double tolerance = 0.001;
		if (abs(y2- 1.0)< tolerance) return U;
		double tmp2 = pow(((y2 - 1)*U)/(y2* K), y2);
		return ((K/(1-y2))*tmp2);
	}
	double XPO::CallPrice(double U) const
	{
		double tmp = (b / (sig * sig) - 0.5) * (b / (sig * sig) - 0.5) + (2 * r) / (sig * sig);
		double y1 = 0.5 - (b / (sig * sig)) + sqrt(tmp);
		double tolerance = 0.001;
		if (abs(y1 - 1.0) < tolerance) return U;
		double tmp2 = pow(((y1 - 1) * U) / (y1 * K), y1);
		return ((K / (y1-1)) * tmp2);
	}
	//default constructor
	XPO::XPO() : r(0.05), sig(0.2), K(110.0), S(100), OptType('C'), b(0.05), Option()
	{
		cout << "A Default Perpetual American Option was created" << endl;
	}
	//ParaConstructor
	XPO::XPO(char type, double asprice,
		double inter, double cost, double vol, double strike) : S(asprice), r(inter), sig(vol), K(strike), b(cost), OptType(type), Option()
	{
		//Check capitalized OptType
		if (OptType == 'c') OptType = 'C';
		if (OptType == 'p') OptType = 'P';
		if (((OptType != 'P') && (OptType != 'C')) == 1) throw NotPutnorCallException(OptType);
		cout << "A specified Perpetual American Option was created" << endl;
	}
	//Copy Constructor
	XPO::XPO(const XPO& option2) : r(option2.r), sig(option2.sig), K(option2.K),
		S(option2.S), OptType(option2.OptType), b(option2.b), Option(option2)
	{
		cout << "An Perpetual American Option was created by copy constructor" << endl;
	}
	//Destrutor
	XPO::~XPO()
	{
		cout << "An Perpetual American Option terminated" << endl;
	}
	//interest rate getter
	double XPO::IR() const
	{
		return r;
	}
	//interest rate setter
	void XPO::IR(double a)
	{
		r = a;
	}
	//Volitality getter
	double XPO::Vol()const
	{
		return sig;
	}
	//Volitality setter
	void XPO::Vol(double v)
	{
		sig = v;
	}
	//SPrice getter
	double XPO::Strike()const
	{
		return K;
	}
	//SPrice setter
	void XPO::Strike(double c)
	{
		K = c;
	}
	//Type getter
	char XPO::Type() const
	{
		return OptType;
	}
	//Type setter
	void XPO::Type(char opttype)
	{
		OptType = opttype;
		//Check capitalized OptType
		if (OptType == 'c') OptType = 'C';
		if (OptType == 'p') OptType = 'P';
		if (((OptType != 'P') && (OptType != 'C')) == 1) throw NotPutnorCallException(OptType);
	}
	//AssetPrice getter
	double XPO::AssetPrice() const
	{
		return S;
	}
	//AssetPrice setter
	void XPO::AssetPrice(double e)
	{
		S = e;
	}
	//Cost getter
	double XPO::Cost()const
	{
		return b;
	}
	//Cost setter
	void XPO::Cost(double f)
	{
		b = f;
	}
	//Calculate option price
	double XPO::OptionPrice() const
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
	vector<double> XPO::MeshPrice(vector<double> source) const
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
	//= operator
	XPO& XPO::operator = (const XPO& option2)
	{
		if (this == &option2) return *this;

		else
		{
			r = option2.r;
			sig = option2.sig;
			K = option2.K;
			b = option2.b;
			S = option2.S;
			OptType = option2.OptType;
			Option::operator=(option2);
			return *this;
		}
	}
	//<< operator
	std::ostream& operator << (std::ostream& os, const XPO& option)
	{
		os << "The European Option has the following properties:" << std::endl;
		os << "Asset Price: " << option.S << std::endl;
		os << "Interest Rate: " << option.r << std::endl;
		os << "Voltality: " << option.sig << std::endl;
		os << "Strike Price: " << option.K << std::endl;
		os << "Cost of Carry: " << option.b << std::endl;
		os << "Option Type (C = Call, P = Put): " << option.OptType << std::endl;
		return os;
	}
	//Option Parameters Export function
	vector<double> XPO::VectorExport() const
	{
		vector<double> Exp(8);
		Exp[0] = 'A';
		Exp[1] = OptType;
		Exp[2] = S;
		Exp[3] = r;
		Exp[4] = sig;
		Exp[5] = K;
		Exp[6] = 0;
		Exp[7] = b;
		return Exp;
	}
	//ToString()
	std::string XPO::ToString() const
	{
		std::string s_x;
		std::stringstream strs;
		std::string s = Option::ToString();
		strs << "American Option ID: " << s << std::endl;
		strs << "The American Option has the following properties:" << std::endl;
		strs << "Asset Price: " << S << std::endl;
		strs << "Interest Rate: " << r << std::endl;
		strs << "Voltality: " << sig << std::endl;
		strs << "Strike Price: " << K << std::endl;
		strs << "Cost of Carry: " << b << std::endl;
		strs << "Option Type (C = Call, P = Put): " << OptType << std::endl;
		return s_x = strs.str();
	}
}


