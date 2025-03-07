#include <exception>
#include <string>

// Inherits from exception to just throw an SdlError
class InitError : public std::exception
{
private:
	std::string msg;


public:
	InitError();
	InitError(const std::string&);

	virtual const char* what() const throw();

	virtual ~InitError() throw();
};
