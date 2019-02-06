#include "AsciiCatModule.hpp"

AsciiCatModule::AsciiCatModule( std::string name ) : _name(name), _info(0), _then(0) { }
AsciiCatModule::AsciiCatModule( void ) : _name("AsciiCatModule"), _info(0), _then(0) { }
AsciiCatModule::AsciiCatModule( AsciiCatModule const & cp) { *this = cp; }
AsciiCatModule::~AsciiCatModule( void ) { }
AsciiCatModule& AsciiCatModule::operator=( AsciiCatModule const & rhs)
{
	_name = rhs._name;
	_info = rhs._info;
	_then = rhs._then;
	return *this;
}

std::string AsciiCatModule::getName( void ) const { return _name; }
std::vector<std::string> AsciiCatModule::getInfo( void ) const { return _info; }

void	AsciiCatModule::setInfo( void )
{
	double curr = clock() / CLOCKS_PER_SEC;
	double span = curr - _then;
	if (span > CLOCKDELAY)
	{
		_info.clear();
		static int i;
		i %= 3;
		if (i == 0) {
			_info.push_back("                      /|");
			_info.push_back("                     ///");
			_info.push_back("                    / /");
			_info.push_back("                   ||\\");
			_info.push_back("                   /   \\ ");
			_info.push_back("                   |   |");
			_info.push_back("             r     \\   \\     r^-");
			_info.push_back("             |\\---- |   |---/|");
			_info.push_back("             /      |   | |  \\ ");
			_info.push_back("- - - - -   (      /   /      ) - - - - - - -");
			_info.push_back("  - - - - - \\      |   |      / - - - - -");
			_info.push_back("       __-----^----|   |----^--#----+");
			_info.push_back("      H            |   |             #");
			_info.push_back("    /             /     \\             \\ ");
			_info.push_back("  {          /       *                 \\ ");
			_info.push_back("  -/       /                 9\\         \\-");
			_info.push_back("  {        |                   |        }");
			_info.push_back("  {        }                   {        }");
			_info.push_back("  #   ^    }                   {        }");
			_info.push_back("  {        }-\\__---\\____-----#-{        }");
			_info.push_back(" {^_^} v{-_-}                 {*_*} v(0_0}");
		}
	
		if (i == 1) {
			_info.push_back("                   |\\ ");
			_info.push_back("                   //\\ ");
			_info.push_back("                  /  |");
			_info.push_back("                  ||\\");
			_info.push_back("                  /   \\ ");
			_info.push_back("                  |   |");
			_info.push_back("             r    \\   \\     r^-");
			_info.push_back("             |\\----|   |---/|");
			_info.push_back("             /     |   | |   \\ ");
			_info.push_back("- - - - -   (      /   /      ) - - - - - - -");
			_info.push_back("  - - - - - \\      |   |      / - - - - -");
			_info.push_back("       __-----^----|   |----^--#----+");
			_info.push_back("      H            |   |             #");
			_info.push_back("    /             /     \\             \\ ");
			_info.push_back("  {          /       *                 \\ ");
			_info.push_back("  -/       /                 9\\         \\-");
			_info.push_back("  {        |                   |        }");
			_info.push_back("  {        }                   {        }");
			_info.push_back("  #   ^    }                   {        }");
			_info.push_back("  {        }-\\__---\\____-----#-{        }");
			_info.push_back(" {^_^} v{-_-}                 {*_*} v(0_0}");
		}
	
		if (i == 2) {
		_info.push_back("                   |\\  ");
		_info.push_back("                   \\\\ ");
		_info.push_back("                    \\ \\ ");
		_info.push_back("                    //|| ");
		_info.push_back("                   /   \\ ");
		_info.push_back("                   |   |");
		_info.push_back("             r     \\   \\     r^-");
		_info.push_back("             |\\---- |   |---/|");
		_info.push_back("             /      |   | |  \\ ");
		_info.push_back("- - - - -   (      /   /      ) - - - - - - -");
		_info.push_back("  - - - - - \\      |   |      / - - - - -");
		_info.push_back("       __-----^----|   |----^--#----+");
		_info.push_back("      H            |   |             #");
		_info.push_back("    /             /     \\             \\ ");
		_info.push_back("  {          /       *                 \\ ");
		_info.push_back("  -/       /                 9\\         \\-");
		_info.push_back("  {        |                   |        }");
		_info.push_back("  {        }                   {        }");
		_info.push_back("  #   ^    }                   {        }");
		_info.push_back("  {        }-\\__---\\____-----#-{        }");
		_info.push_back(" {^_^} v{-_-}                 {*_*} v(0_0}");
		}
		i++;
		_then = curr;
	}
}
