#ifndef INDICEPLATEAUEXCEPTION_H
#define INDICEPLATEAUEXCEPTION_H

#include <exception>

using namespace std;

class IndicePlateauException : public exception 
{
	
	public :
		IndicePlateauException() throw() { }
		~IndicePlateauException() throw() { }
	
		const char* what() const throw() {
			return "IndicePlateauException";
		}
		
	private :
	
};

#endif
