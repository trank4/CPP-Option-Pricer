//source file for OptionABC class
#include "OptionABC.h"
namespace KhoaTran
{

		//default constructor
		Option::Option() : idnum(rand())
		{
			std::cout << "An Option base class created by default constructor" << std::endl;
		}
		//Copy constructor
		Option::Option(const Option& opt) : idnum(opt.idnum)
		{
			std::cout << "An Option base class created by copy constructor" << std::endl;
		}
		//Assignment Operator =
		Option& Option::operator= (const Option& source)
		{
			if (this == &source)
			{
				return (*this);
			}
			else
			{
				idnum = source.idnum;
				return (*this);
			}
		}
		//ToString()
		std::string Option::ToString() const
		{
			std::string s_x;
			std::stringstream strs;
			strs << "ID: " << idnum;
			return s_x = strs.str();
		}
		//ID()
		int Option::ID() const
		{
			return idnum;
		}
		//Destructor
		Option::~Option()
		{
			std::cout << "An Option base class terminated" << std::endl;
		}
		
		//Print() function
		std::string Option::Description() const
		{
			return ToString();
		}
}
