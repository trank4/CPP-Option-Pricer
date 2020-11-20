#pragma once
//header file for exception objects (hierarchy)
#pragma once
#include <iostream>
#include <sstream>

#ifndef OptionException_h
#define OptionException_h
class OptionException
{
private:
public:
	OptionException(); //Constructor
	virtual std::string GetMessage() const = 0; //GetMessage() interface
	virtual ~OptionException(); //Destructor
};
class NotPutnorCallException : public OptionException
{
private: char Opt;
public:
	NotPutnorCallException(char opt); //Constructor
	std::string GetMessage() const; //GetMessage()
	virtual ~NotPutnorCallException();
};
class NotEuropeanException : public OptionException
{
private: char Opt;
public:
	NotEuropeanException(char opt); //Constructor
	std::string GetMessage() const; //GetMessage()
	virtual ~NotEuropeanException();
};
class MeshException : public OptionException
{
public:
	MeshException(); //Constructor
	std::string GetMessage() const; //GetMessage()
	virtual ~MeshException();
};
#endif
