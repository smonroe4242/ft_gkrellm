#ifndef NETWORKMODULE_H
# define NETWORKMODULE_H
# include "IMonitorModule.hpp"
# include <ifaddrs.h>
# include <net/if.h>
# include <ctime>
#include <unistd.h>
class NetworkModule : virtual public IMonitorModule {

public:
	NetworkModule( std::string );
	NetworkModule( void );
	NetworkModule( NetworkModule const & cp);
	virtual ~NetworkModule( void );
	NetworkModule& operator=( NetworkModule const &);

	void	setInfo( void );
	std::string	getName( void ) const;
	std::vector<std::string> getInfo( void ) const;

private:
	std::string _name;
	std::vector<std::string> _info;
	double	_then;
	double	_curr;
	int		_ipack;
	int		_ibyte;
	int		_opack;
	int		_obyte;
};

#endif
