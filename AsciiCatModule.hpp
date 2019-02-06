#ifndef ASCIICATMODULE_H
# define ASCIICATMODULE_H
# include "IMonitorModule.hpp"

class AsciiCatModule : virtual public IMonitorModule {

public:
	AsciiCatModule( std::string );
	AsciiCatModule( void );
	AsciiCatModule( AsciiCatModule const & cp);
	virtual ~AsciiCatModule( void );
	AsciiCatModule& operator=( AsciiCatModule const &);

	void	setInfo( void );
	std::string	getName( void ) const;
	std::vector<std::string> getInfo( void ) const;

private:
	std::string _name;
	std::vector<std::string> _info;
	double _then;
};

#endif
