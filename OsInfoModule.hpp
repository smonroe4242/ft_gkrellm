#ifndef OSINFOMODULE_H
# define OSINFOMODULE_H
# include "IMonitorModule.hpp"

class OsInfoModule : virtual public IMonitorModule {

public:
	OsInfoModule( std::string );
	OsInfoModule( void );
	OsInfoModule( OsInfoModule const & cp);
	virtual ~OsInfoModule( void );
	OsInfoModule& operator=( OsInfoModule const &);

	void	setInfo( void );
	std::string	getName( void ) const;
	std::vector<std::string> getInfo( void ) const;

private:
	std::string _name;
	std::vector<std::string> _info;
};

#endif
