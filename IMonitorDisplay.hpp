#ifndef IMONITORDISPLAY_H
# define IMONITORDISPLAY_H
# include <iostream>
# include <string>
# include <stdexcept>
# include <vector>
# include <curses.h>
# include <ncurses.h>
# include <utility>

# define MODULE_COUNT 7
# define OPT_STR "hodcrnatg"
# define MODULE_WIDTH 55
# define OFFSET 5

class IMonitorDisplay {

public:
	virtual	~IMonitorDisplay( void ) {}
	virtual void loop( void ) = 0;

};

#endif
