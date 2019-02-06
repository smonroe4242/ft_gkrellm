#ifndef HOSTNAMEMODULE_H
# define HOSTNAMEMODULE_H
# include "IMonitorModule.hpp"
#include <limits.h>
#include <unistd.h>

class HostnameModule : virtual public IMonitorModule {

public:
	HostnameModule( std::string );
	HostnameModule( void );
	HostnameModule( HostnameModule const & cp);
	virtual ~HostnameModule( void );
	HostnameModule& operator=( HostnameModule const &);

	void	setInfo( void );
	std::string	getName( void ) const;
	std::vector<std::string> getInfo( void ) const;

private:
	std::string _name;
	std::vector<std::string> _info;
};

#endif
