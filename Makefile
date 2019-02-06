NAME = ft_gkrellm

SRC = CpuModule.cpp DateTimeModule.cpp HostnameModule.cpp Ncurse.cpp NetworkModule.cpp OsInfoModule.cpp RamModule.cpp Sfml.cpp AsciiCatModule.cpp main.cpp

CC = clang++ -Wall -Werror -Wextra --std=c++98 -lncurses -I./SFML/include  -L./SFML/lib  -lsfml-graphics -lsfml-window -lsfml-system

ifeq ($(LD_LIBRARY_PATH),./SFML/lib)
	COMPILE = $(CC) $(SRC) -o $(NAME)
else
	COMPILE = @echo 'Please run source sfml.sh'
endif

all: $(NAME)

$(NAME):
	$(COMPILE)

clean:
	/bin/rm -rf *~ a.out *.swp *.gch \#*\#

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all

fsan:
	$(COMPILE) -g -fsanitize=address

