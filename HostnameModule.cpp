#include "HostnameModule.hpp"

HostnameModule::HostnameModule( std::string name ) : _name(name), _info(0) { }
HostnameModule::HostnameModule( void ) : _name("Hostname"), _info(0) { }
HostnameModule::HostnameModule( HostnameModule const & cp) { *this = cp; }
HostnameModule::~HostnameModule( void ) { }
HostnameModule& HostnameModule::operator=( HostnameModule const & rhs)
{
	_name = rhs._name;
	_info = rhs._info;
	return *this;
}

std::string HostnameModule::getName( void ) const { return _name; }
std::vector<std::string> HostnameModule::getInfo( void ) const { return _info; }

void	HostnameModule::setInfo( void )
{
	_info.clear();

	char hostname[_POSIX_HOST_NAME_MAX];
	char username[_POSIX_LOGIN_NAME_MAX];
	
	gethostname(hostname, _POSIX_HOST_NAME_MAX);
	getlogin_r(username, _POSIX_LOGIN_NAME_MAX);
	
	_info.push_back("Hostname");
	_info.push_back(hostname);
	_info.push_back(" ");
	_info.push_back("Username");
	_info.push_back(username);
}
