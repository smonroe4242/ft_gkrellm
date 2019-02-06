#ifndef SFML_H
# define SFML_H

# include "IMonitorDisplay.hpp"
# include "HostnameModule.hpp"
# include "OsInfoModule.hpp"
# include "DateTimeModule.hpp"
# include "CpuModule.hpp"
# include "RamModule.hpp"
# include "NetworkModule.hpp"
# include "AsciiCatModule.hpp"
# include <SFML/Graphics.hpp>

# define SFML_OFFSET 30
# define SFML_FONT_SIZE 25

class Sfml : public IMonitorDisplay {

public:
	Sfml( std::vector<bool> );
	Sfml( void );
	Sfml( Sfml const & cp);
	virtual ~Sfml( void );
	Sfml& operator=( Sfml const &);

	void	init( void );
	void	drawWindow( IMonitorModule* );
	void	loop( void );

private:
	std::vector< std::pair < bool, IMonitorModule* > >	_arr;
	int _winmaxY;
	int _winmaxX;
	int _curY;
	sf::RenderWindow _window;
	sf::Font _font;
};

#endif
