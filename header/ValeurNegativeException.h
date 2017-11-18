#ifndef VALEURNEGATIVEEXCEPTION_H
#define VALEURNEGATIVEEXCEPTION_H

#include <exception>

using namespace std;

class ValeurNegativeException : public exception 
{
	
	public :
		ValeurNegativeException() throw() { }
		~ValeurNegativeException() throw() { }
	
		const char* what() const throw() {
			return "ValeurNegativeException";
		}
		
	private :
	
};

#endif

