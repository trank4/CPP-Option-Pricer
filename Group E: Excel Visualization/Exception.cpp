#include "Exception.h"
//OptionException
//Constructor
OptionException::OptionException()
{
	std::cout << "OptionException Object created" << std::endl;
}
//Destructor
OptionException::~OptionException()
{
	std::cout << "OptionException Object Terminated" << std::endl;
}

//NotPutnorCallException
//Constructor
NotPutnorCallException::NotPutnorCallException(char opt):OptionException(), Opt(opt)
{
	std::cout << "NotPutnorCallException Object Created." << std::endl;
}
//Destructor
NotPutnorCallException::~NotPutnorCallException()
{
	std::cout << "NotPutnorCallException Object Terminated." << std::endl;
}
//GetMessage()
std::string NotPutnorCallException::GetMessage() const
{
	std::string s_x;
	std::stringstream strs;
	strs << "Error: the given ["<<Opt<<"] type is neither Call or Put type.";
	return s_x = strs.str();
}

//NotEuropeanException
//Constructor
NotEuropeanException::NotEuropeanException(char opt) :OptionException(), Opt(opt)
{
	std::cout << "NotEuropeanException Object Created." << std::endl;
}
//Destructor
NotEuropeanException::~NotEuropeanException()
{
	std::cout << "NotEuropeanException Object Terminated." << std::endl;
}
//GetMessage()
std::string NotEuropeanException::GetMessage() const
{
	std::string s_x;
	std::stringstream strs;
	strs << "Error: the given [" << Opt << "] Option type has to be European Option ('E').";
	return s_x = strs.str();
}
//MeshException
//Constructor
MeshException::MeshException() :OptionException()
{
	std::cout << "MeshException Object Created." << std::endl;
}
//Destructor
MeshException::~MeshException()
{
	std::cout << "MeshException Object Terminated." << std::endl;
}
//GetMessage()
std::string MeshException::GetMessage() const
{
	std::string s_x;
	std::stringstream strs;
	strs << "Error: Inputs for MeshGenertor are invalid.";
	return s_x = strs.str();
}