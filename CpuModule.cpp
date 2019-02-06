#include "CpuModule.hpp"

CpuModule::CpuModule( std::string name ) : _name(name), _info(0), _then(0) { }
CpuModule::CpuModule( void ) : _name("CpuModule"), _info(0), _then(0) { }
CpuModule::CpuModule( CpuModule const & cp) { *this = cp; }
CpuModule::~CpuModule( void ) { }
CpuModule& CpuModule::operator=( CpuModule const & rhs)
{
	_name = rhs._name;
	_info = rhs._info;
	return *this;
}

std::string CpuModule::getName( void ) const { return _name; }
std::vector<std::string> CpuModule::getInfo( void ) const { return _info; }

std::string CpuModule::getCpuModel()
{
	size_t bufferlen = 128;
    char buffer[bufferlen];
    sysctlbyname("machdep.cpu.brand_string",&buffer,&bufferlen,NULL,0);
	return buffer;
}

std::string CpuModule::getCpuCores()
{
	int count;
	size_t count_len = sizeof(count);
	sysctlbyname("hw.logicalcpu", &count, &count_len, NULL, 0);
	return std::to_string(count);
}

std::string CpuModule::getClockSpeed()
{
    uint64_t freq = 0;
    size_t size = sizeof(freq);
    sysctlbyname("hw.cpufrequency", &freq, &size, NULL, 0);
    return std::to_string(freq);
}

static unsigned long long _previousTotalTicks = 0;
static unsigned long long _previousIdleTicks = 0;

float 	CpuModule::getCpuLoad()
{
   host_cpu_load_info_data_t cpuinfo;
   mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
   if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, reinterpret_cast<host_info_t>(&cpuinfo), &count) == KERN_SUCCESS)
   {
		unsigned long long _totalTicks = 0;
		for(int i = 0; i < CPU_STATE_MAX; i++) 
			_totalTicks += cpuinfo.cpu_ticks[i];

		return setCpuLoad(cpuinfo.cpu_ticks[CPU_STATE_IDLE], _totalTicks);
   }
   else return -1.0f;
}

float 	CpuModule::setCpuLoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
	unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
	unsigned long long idleTicksSinceLastTime  = idleTicks - _previousIdleTicks;
	float ret = 1.0f-((totalTicksSinceLastTime > 0) ? (static_cast<float>(idleTicksSinceLastTime)/static_cast<float>(totalTicksSinceLastTime)) : 0);
	_previousTotalTicks = totalTicks;
	_previousIdleTicks  = idleTicks;
	return round(ret * 100);
}


void	CpuModule::setInfo( void )
{
	double curr = clock() / CLOCKS_PER_SEC;
	double span = curr - _then;
	if (span > CLOCKDELAY)
	{
		_info.clear();

		_info.push_back(getCpuModel());
		std::string cores = "Cores: " + getCpuCores(); 
		_info.push_back(cores);

		std::string load = "Current CPU Usage: " + std::to_string(static_cast<int>(getCpuLoad())) + "%";
		_info.push_back(load);
		_then = curr;
	}

}
