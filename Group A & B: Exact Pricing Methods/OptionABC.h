//header file for Option Base Class
//This is to utilize polymorphism if needed
#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#ifndef Option_h
#define Option_h
namespace KhoaTran
{

		class Option
		{
		private:
			int idnum; //id number
		public:
			Option(); //default constructor
			Option(const Option& opt); //copy constructor
			virtual ~Option();//Destructor
			virtual std::string ToString() const; //Virtual ToString()
			//polymorphism functions
			virtual double IR()const =0;
			virtual void IR(double a) = 0;
			virtual double Vol()const = 0;
			virtual void Vol(double b) = 0;
			virtual double Strike()const = 0;
			virtual void Strike(double c) = 0;
			virtual double Cost() const = 0;
			virtual void Cost(double f) = 0;
			virtual char Type() const = 0;
			virtual void Type(char opttype) = 0;
			virtual double AssetPrice() const = 0;
			virtual void AssetPrice(double e) = 0;
			virtual double OptionPrice() const = 0;
			virtual std::vector<double> MeshPrice(std::vector<double> source) const = 0;
			int ID() const; //return ID of Option
			std::string Description() const; //Description() function
			Option& operator = (const Option& source); // assignment operator
		};
}
#endif