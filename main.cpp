// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2019/02/01 15:37:30 by smonroe           #+#    #+#             //
//   Updated: 2019/02/05 17:15:32 by smonroe          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Ncurse.hpp"
#include "Sfml.hpp"
//#include <unistd.h> //FOR GETOPT

int usage( void )
{
	std::cout << "Usage: ./ft_gkrellm -(t|g)[hodcrn]" << std::endl;
	std::cout << "Only one of these" << std::endl;
	std::cout << "\t-t : Text UI" << std::endl;
	std::cout << "\t-g : Graphic UI" << std::endl;
	std::cout << "Zero or many of these:" << std::endl;
	std::cout << "\t-h : Hostname/Username" << std::endl;
	std::cout << "\t-o : OS Info" << std::endl;
	std::cout << "\t-d : Date/Time" << std::endl;
	std::cout << "\t-c : CPU" << std::endl;
	std::cout << "\t-r : RAM" << std::endl;
	std::cout << "\t-n : Network" << std::endl;
	std::cout << "\t-a : Ascii Cat" << std::endl;
	return 1;
}

int	main(int ac, char **av)
{
	IMonitorDisplay* display = NULL;
	std::vector<bool> flags(MODULE_COUNT, false);
	int mode = 2;
	char ch = 0;
	while ((ch = getopt(ac, av, OPT_STR)) != -1)
	{
		switch (ch) {
		case 'h' : flags[0] = true; break;
		case 'o' : flags[1] = true; break;
		case 'd' : flags[2] = true; break;
		case 'c' : flags[3] = true; break;
		case 'r' : flags[4] = true; break;
		case 'n' : flags[5] = true; break;
		case 'a' : flags[6] = true; break;
		case 't' : mode = mode == 2 ? 0 : 2; break;
		case 'g' : mode = mode == 2 ? 1 : 2; break;
		default : return usage(); break;
		}
	}
	if (mode == 2)
		return usage();
	else if (mode == 1)
		display = new Sfml(flags);
	else
		display = new Ncurse(flags);
	display->loop();
	delete display;
	return 0;
}
