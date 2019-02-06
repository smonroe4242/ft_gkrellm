#include "RamModule.hpp"
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/mach.h>
#include <sys/utsname.h>

RamModule::RamModule( std::string name ) : _name(name), _info(0), _then(0){ }
RamModule::RamModule( void ) : _name("RamModule"), _info(0) { }
RamModule::RamModule( RamModule const & cp) { *this = cp; }
RamModule::~RamModule( void ) { }
RamModule& RamModule::operator=( RamModule const & rhs)
{
	_name = rhs._name;
	_info = rhs._info;
	return *this;
}

std::string RamModule::getName( void ) const { return _name; }
std::vector<std::string> RamModule::getInfo( void ) const { return _info; }

double RamModule::ParseMemValue(const char * b)
{
   while((*b)&&(isdigit(*b) == false)) b++;
   return isdigit(*b) ? atof(b) : -1.0;
}

float RamModule::getMemoryPercentage()
{
   FILE * fpIn = popen("/usr/bin/vm_stat", "r");
   if (fpIn)
   {
      double pagesUsed = 0.0, totalPages = 0.0;
      char buf[512];
      while(fgets(buf, sizeof(buf), fpIn) != NULL)
      {
         if (strncmp(buf, "Pages", 5) == 0)
         {
            double val = ParseMemValue(buf);
            if (val >= 0.0)
            {
               if ((strncmp(buf, "Pages wired", 11) == 0)||(strncmp(buf, "Pages active", 12) == 0)) pagesUsed += val;
               totalPages += val;
            }
         }
         else if (strncmp(buf, "Mach Virtual Memory Statistics", 30) != 0) break;  // Stop at "Translation Faults", we don't care about anything at or below that
      }
      pclose(fpIn);

      if (totalPages > 0.0) return static_cast<float>(pagesUsed/totalPages);
   }
   return -1.0f;  // indicate failure
}

std::string RamModule::getTotalSystemMemory()
{
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    return std::to_string(pages * page_size) + " Bytes";
}


void	RamModule::setInfo( void )
{
	double curr = clock() / CLOCKS_PER_SEC;
	double span = curr - _then;
	if (span > CLOCKDELAY)
	{
		_info.clear();

		_info.push_back("Total System Memory");
		_info.push_back(getTotalSystemMemory());

		std::string mem = "Memory Currently Being Used: " + std::to_string(static_cast<int>(getMemoryPercentage() * 100)) + "%";
		_info.push_back(mem);
		_then = curr;
	}

}
