#include "NetworkModule.hpp"

NetworkModule::NetworkModule( std::string name ) : _name(name), _info(0), _then(0), _curr(0), _ipack(0), _ibyte(0), _opack(0), _obyte(0) { }
NetworkModule::NetworkModule( void ) : _name("NetworkModule"), _info(0), _then(0), _curr(0), _ipack(0), _ibyte(0), _opack(0), _obyte(0) { }
NetworkModule::NetworkModule( NetworkModule const & cp) { *this = cp; }
NetworkModule::~NetworkModule( void ) { }
NetworkModule& NetworkModule::operator=( NetworkModule const & rhs)
{
	_name = rhs._name;
	_info = rhs._info;
	return *this;
}

std::string NetworkModule::getName( void ) const { return _name; }
std::vector<std::string> NetworkModule::getInfo( void ) const { return _info; }
# define MYMAX 2147483647
void	NetworkModule::setInfo( void )
{
	struct ifaddrs *ifp = 0;
	if (getifaddrs(&ifp))
	{
		_info.clear();
		_info.push_back("Internal Failure, My Apologies User.");
	}
	else
	{
		struct ifaddrs *ptr = ifp;
		while (ptr)
		{
			if (!strncmp(ptr->ifa_name, "en0", 3))
			{
				struct if_data *data = reinterpret_cast<struct if_data *>(ptr->ifa_data);
				if (data && (data->ifi_ibytes || data->ifi_obytes))
				{
					_curr = clock() / CLOCKS_PER_SEC;
					double span = _curr - _then;
					if (span > CLOCKDELAY)
					{
						_info.clear();
						_info.push_back(ptr->ifa_name);
						_info.push_back("Packet Speed : " + std::to_string(static_cast<int>((data->ifi_ipackets - _ipack) / span)) + " Packets/sec");
						_info.push_back("Byte Speed   : " + std::to_string(static_cast<int>(((data->ifi_ibytes - _ibyte + data->ifi_obytes - _obyte) / 1000) / span)) + " Kb/sec");
						_info.push_back("TX packets   : " + std::to_string(data->ifi_ipackets));
						_info.push_back("TX errors    : " + std::to_string(data->ifi_ierrors));
						_info.push_back("TX bytes     : " + std::to_string(data->ifi_ibytes));
						_info.push_back("RX packets   : " + std::to_string(data->ifi_opackets));
						_info.push_back("RX errors    : " + std::to_string(data->ifi_oerrors));
						_info.push_back("RX bytes     : " + std::to_string(data->ifi_obytes));
						_obyte = data->ifi_obytes;
						_opack = data->ifi_opackets;
						_ibyte = data->ifi_ibytes;
						_ipack = data->ifi_ipackets;
						_then = _curr;
					}
				}
				break;
			}
			ptr = ptr->ifa_next;
		}
		freeifaddrs(ifp);
	}
	if (_info.empty())
		_info.push_back("No Availble Network Data");
}
