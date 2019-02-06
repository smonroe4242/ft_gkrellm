#ifndef NCURSE_H
# define NCURSE_H

# include "IMonitorDisplay.hpp"
# include "HostnameModule.hpp"
# include "OsInfoModule.hpp"
# include "DateTimeModule.hpp"
# include "CpuModule.hpp"
# include "RamModule.hpp"
# include "NetworkModule.hpp"
# include "AsciiCatModule.hpp"

class Ncurse : public IMonitorDisplay {

public:
	Ncurse( std::vector<bool> );
	Ncurse( void );
	Ncurse( Ncurse const & cp);
	virtual ~Ncurse( void );
	Ncurse& operator=( Ncurse const &);

	void	init( void );
	void	drawWindow( IMonitorModule* );
	void	loop( void );

private:
	std::vector< std::pair < bool, IMonitorModule* > >	_arr;
	int _winmaxY;
	int _winmaxX;
	int _curY;
};

#endif
