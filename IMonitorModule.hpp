#ifndef IMONITORMODULE_H
# define IMONITORMODULE_H
# define CLOCKDELAY 0.001
# include <iostream>
# include <string>
# include <stdexcept>
# include <vector>
class IMonitorModule {

public:
	virtual ~IMonitorModule( void ) {};
	virtual void setInfo( void ) = 0;
	virtual std::string getName( void ) const = 0;
	virtual std::vector<std::string> getInfo( void ) const = 0;
};

#endif
