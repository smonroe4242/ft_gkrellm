#include "Sfml.hpp"

Sfml::Sfml( std::vector<bool> arr )
	: _arr(0), _winmaxY(2500), _winmaxX(1000), _curY(0), _window(sf::VideoMode(_winmaxX, _winmaxY), "ft_gkrellm")
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

Sfml::Sfml( void ) : _arr(0), _winmaxY(0), _winmaxX(0), _curY(0), _window(sf::VideoMode(_winmaxX, _winmaxY), "default") { }
Sfml::Sfml( Sfml const & cp) { *this = cp; }

Sfml::~Sfml( void )
{
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

Sfml& Sfml::operator=( Sfml const & rhs)
{
	_arr = rhs._arr;
	_winmaxY = rhs._winmaxY;
	_winmaxX = rhs._winmaxX;
	_curY = rhs._curY;
	_font = rhs._font;
	return *this;
}

void	Sfml::init( void )
{
	_font.loadFromFile("COURIER.TTF");
	_window.setKeyRepeatEnabled(false);
}

void	Sfml::drawWindow(IMonitorModule * module)
{
	module->setInfo();
	std::vector<std::string> info = module->getInfo();
	std::vector<std::string>::iterator it = info.begin();	
	std::vector<std::string>::iterator ite = info.end();	

	sf::RectangleShape bounds(sf::Vector2f(_winmaxX - (SFML_OFFSET << 2), (info.size() + 2) * SFML_OFFSET));
	bounds.setOutlineThickness(2);
	bounds.setOutlineColor(sf::Color(0, 0, 255));
	bounds.setPosition(SFML_OFFSET << 1, _curY++);
	bounds.setFillColor(sf::Color(0, 0, 0));
	_window.draw(bounds);

	std::string title = module->getName();
	sf::Text name(title, _font, SFML_FONT_SIZE);
	name.setPosition(SFML_OFFSET << 2, _curY);
	name.setOutlineThickness(1);
	name.setOutlineColor(sf::Color::Black);
	name.setFillColor(sf::Color::Cyan);
	_window.draw(name);

	char hotkey[4] = "[!]";
	hotkey[1] = title[0];
	sf::Text charopt(hotkey, _font, SFML_FONT_SIZE);
	charopt.setPosition(SFML_OFFSET << 1, _curY);
	charopt.setOutlineThickness(1);
	charopt.setOutlineColor(sf::Color::Black);
	charopt.setFillColor(sf::Color::Magenta);
	_window.draw(charopt);

	_curY += SFML_OFFSET;
	while (it != ite)
	{
		sf::Text line(it->c_str(), _font, SFML_FONT_SIZE);
		line.setPosition(SFML_OFFSET << 1, _curY);
		line.setOutlineThickness(1);
		line.setOutlineColor(sf::Color::Black);
		line.setFillColor(sf::Color::Green);
		_window.draw(line);
		it++;
		_curY += SFML_OFFSET;
	}
	_curY += SFML_OFFSET << 1;
}

void	Sfml::loop( void )
{
	sf::RectangleShape rect(sf::Vector2f(_winmaxX - (SFML_OFFSET << 1), _winmaxY - (SFML_OFFSET << 1)));
	rect.setOutlineThickness(SFML_OFFSET);
	rect.setOutlineColor(sf::Color(0, 0, 150));
	rect.setPosition(SFML_OFFSET, SFML_OFFSET);
	rect.setFillColor(sf::Color(0, 0, 0));
	std::vector<std::pair<bool, IMonitorModule *> >::iterator it;
	std::vector<std::pair<bool, IMonitorModule *> >::iterator ite;

	while (_window.isOpen())
	{
		sf::Event event;
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::H : _arr[0].first ^= true; break;
				case sf::Keyboard::O : _arr[1].first ^= true; break;
				case sf::Keyboard::D : _arr[2].first ^= true; break;
				case sf::Keyboard::C : _arr[3].first ^= true; break;
				case sf::Keyboard::R : _arr[4].first ^= true; break;
				case sf::Keyboard::N : _arr[5].first ^= true; break;
				case sf::Keyboard::A : _arr[6].first ^= true; break;
				case sf::Keyboard::Q : _window.close(); return; break;
				default : break;
				}
			}
		}
		_window.draw(rect);
		_curY = 50;
		it = _arr.begin();
		ite = _arr.end();
		--it;
		while (++it != ite)
			if ((*it).first)
				this->drawWindow((*it).second);
		_window.display();
	}
}
