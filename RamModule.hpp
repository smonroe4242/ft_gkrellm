#ifndef RAMMODULE_H
# define RAMMODULE_H
# include "IMonitorModule.hpp"
# include <unistd.h>
# include <iostream>

class RamModule : virtual public IMonitorModule {

public:
	RamModule( std::string );
	RamModule( void );
	RamModule( RamModule const & cp);
	virtual ~RamModule( void );
	RamModule& operator=( RamModule const &);

	void						setInfo( void );
	std::string					getName( void ) const;
	std::vector<std::string> 	getInfo( void ) const;
	double 						ParseMemValue(const char * b);
	float 						getMemoryPercentage( void );
	std::string		 			getTotalSystemMemory( void );

private:
	std::string 				_name;
	std::vector<std::string> 	_info;
	double		 				_then;
};

#endif
