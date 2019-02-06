#include "Ncurse.hpp"

Ncurse::Ncurse( std::vector<bool> arr )
: _arr(0), _winmaxY(0), _winmaxX(0), _curY(0)
{
	IMonitorModule *ref[MODULE_COUNT] = {
		new HostnameModule("Hostname/Username"),
		new OsInfoModule("OS Info"),
		new DateTimeModule("Date/Time"),
		new CpuModule("Cpu Stats"),
		new RamModule("Ram Stats"),
		new NetworkModule("Network Usage"),
		new AsciiCatModule("A Cat")};
	std::vector<bool>::iterator it = arr.begin();
	std::vector<bool>::iterator ite = arr.end();
	int i = 0;
	while (it != ite && i < MODULE_COUNT)
		_arr.push_back(std::make_pair(*it++, ref[i++]));
	this->init();
}

Ncurse::Ncurse( void ) : _arr(0), _winmaxY(0), _winmaxX(0), _curY(0) { }
Ncurse::Ncurse( Ncurse const & cp) { *this = cp; }
Ncurse::~Ncurse( void )
{
	endwin();
	if (!_arr.empty())
	{
		std::vector<std::pair<bool, IMonitorModule*> >::iterator it = _arr.begin();
		std::vector<std::pair<bool, IMonitorModule*> >::iterator ite = _arr.end();
		--it;
		while (++it != ite)
			delete it->second;
		_arr.clear();
	}
}

Ncurse& Ncurse::operator=( Ncurse const & rhs)
{
	_arr = rhs._arr;
	_winmaxY = rhs._winmaxY;
	_winmaxX = rhs._winmaxX;
	_curY = rhs._curY;
	return *this;
}

void	Ncurse::init( void )
{
	initscr();
	raw();
	noecho();
	timeout(0);
	curs_set(FALSE);
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	cbreak();
	start_color();
	init_pair(0, COLOR_BLACK, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	getmaxyx(stdscr, _winmaxY, _winmaxX);
}

void	Ncurse::drawWindow(IMonitorModule * module)
{
	module->setInfo();
	std::vector<std::string> info = module->getInfo();
	int x = 1;
	std::vector<std::string>::iterator it = info.begin();	
	std::vector<std::string>::iterator ite = info.end();	
	WINDOW* tmpwin = newwin(info.size() + 3, MODULE_WIDTH, _curY++, OFFSET);

	wattron(tmpwin, COLOR_PAIR(4));
	box(tmpwin, 0, 0);
	wattroff(tmpwin, COLOR_PAIR(4));

	wattron(tmpwin, COLOR_PAIR(6));
	mvwprintw(tmpwin, x, OFFSET, "[%c]", module->getName().c_str()[0]);
	wattroff(tmpwin, COLOR_PAIR(6));

	wattron(tmpwin, COLOR_PAIR(5));
	mvwprintw(tmpwin, x, OFFSET + 4, "%s", module->getName().c_str());
	wattroff(tmpwin, COLOR_PAIR(5));

	wattron(tmpwin, COLOR_PAIR(3));
	while (it != ite)
	{
		mvwprintw(tmpwin, ++x, OFFSET, "%s", it->c_str());
		it++;
		_curY++;
	}
	wattroff(tmpwin, COLOR_PAIR(3));

	wrefresh(tmpwin);
	delwin(tmpwin);
	_curY += 2;
}
	
void	Ncurse::loop( void )
{
	while (1)
	{
		std::vector<std::pair<bool, IMonitorModule *> >::iterator it = _arr.begin();
		std::vector<std::pair<bool, IMonitorModule *> >::iterator ite = _arr.end();
		_curY = 0;
		--it;
		while (++it != ite)
			if ((*it).first)
				this->drawWindow((*it).second);
		switch (getch()) {
		case 'h' : _arr[0].first ^= true; erase(); break;
		case 'o' : _arr[1].first ^= true; erase(); break;
		case 'd' : _arr[2].first ^= true; erase(); break;
		case 'c' : _arr[3].first ^= true; erase(); break;
		case 'r' : _arr[4].first ^= true; erase(); break;
		case 'n' : _arr[5].first ^= true; erase(); break;
		case 'a' : _arr[6].first ^= true; erase(); break;
		case 'q' : return; break;
		default : break;
		}
	}
}
