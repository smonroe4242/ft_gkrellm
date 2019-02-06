#include "OsInfoModule.hpp"
#include <sys/utsname.h>

OsInfoModule::OsInfoModule( std::string name ) : _name(name), _info(0) { }
OsInfoModule::OsInfoModule( void ) : _name("Operating System Info"), _info(0) { }
OsInfoModule::OsInfoModule( OsInfoModule const & cp) { *this = cp; }
OsInfoModule::~OsInfoModule( void ) { }
OsInfoModule& OsInfoModule::operator=( OsInfoModule const & rhs)
{
	_name = rhs._name;
	_info = rhs._info;
	return *this;
}

std::string OsInfoModule::getName( void ) const { return _name; }
std::vector<std::string> OsInfoModule::getInfo( void ) const { return _info; }

void	OsInfoModule::setInfo( void )
{
	_info.clear();

	struct utsname sysinfo;
	uname(&sysinfo);

	_info.push_back("System Name");
	_info.push_back(sysinfo.sysname);
	_info.push_back(" ");

	_info.push_back("Current Version");
	_info.push_back(sysinfo.release);
	_info.push_back(" ");


	_info.push_back("Hardware Identifier");
	_info.push_back(sysinfo.machine);
}


