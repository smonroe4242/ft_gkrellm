#ifndef CPUMODULE_H
# define CPUMODULE_H
# include "IMonitorModule.hpp"
# include <sys/types.h>
# include <sys/sysctl.h>
# include <mach/mach_init.h>
# include <mach/mach_error.h>
# include <mach/mach_host.h>
# include <mach/vm_map.h>
# include <cmath>
class CpuModule : virtual public IMonitorModule {

public:
	CpuModule( std::string );
	CpuModule( void );
	CpuModule( CpuModule const & cp);
	virtual ~CpuModule( void );
	CpuModule& operator=( CpuModule const &);

	std::string 				getCpuModel( void );
	std::string 				getCpuCores( void );
	std::string 				getClockSpeed( void );
	float 						getCpuLoad( void );
	float 						setCpuLoad(unsigned long long idleTicks, unsigned long long totalTicks);
	void						setInfo( void );
	std::string					getName( void ) const;
	std::vector<std::string> 	getInfo( void ) const;

private:
	std::string 				_name;
	std::vector<std::string> 	_info;
	double		 				_then;	
};

#endif
