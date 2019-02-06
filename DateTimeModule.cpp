#include "DateTimeModule.hpp"

DateTimeModule::DateTimeModule( std::string name ) : _name(name), _info(0) { }
DateTimeModule::DateTimeModule( void ) : _name("DateTimeModule"), _info(0) { }
DateTimeModule::DateTimeModule( DateTimeModule const & cp) { *this = cp; }
DateTimeModule::~DateTimeModule( void ) { }
DateTimeModule& DateTimeModule::operator=( DateTimeModule const & rhs)
{
	_name = rhs._name;
	_info = rhs._info;
	return *this;
}

std::string DateTimeModule::getName( void ) const { return _name; }
std::vector<std::string> DateTimeModule::getInfo( void ) const { return _info; }

void	DateTimeModule::setInfo( void )
{
	_info.clear();

	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (buffer,80,"%r     %D",timeinfo);
	_info.push_back(buffer);
}


