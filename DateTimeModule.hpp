#ifndef DATETIMEMODULE_H
# define DATETIMEMODULE_H
# include "IMonitorModule.hpp"

class DateTimeModule : virtual public IMonitorModule {

public:
	DateTimeModule( std::string );
	DateTimeModule( void );
	DateTimeModule( DateTimeModule const & cp);
	virtual ~DateTimeModule( void );
	DateTimeModule& operator=( DateTimeModule const &);

	void	setInfo( void );
	std::string	getName( void ) const;
	std::vector<std::string> getInfo( void ) const;

private:
	std::string _name;
	std::vector<std::string> _info;
};

#endif
