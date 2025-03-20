NAME        =   btc

SRC         =   main.cpp BitcoinExchange.cpp
OBJ         =   $(SRC:.cpp=.o)

CC          =   c++
RM          =   rm -f

CFLAGS      =   -Wall -Wextra -Werror

$(NAME):    $(OBJ)
	        $(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all:        $(NAME)

clean:
	        $(RM) $(OBJ)

fclean:     clean
	        $(RM) $(NAME)

re:         fclean all

.PHONY:     all clean fclean re