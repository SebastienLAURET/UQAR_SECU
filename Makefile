NAME			= BruteForce

FILES			= C++/main.cpp \
					C++/Dependence/MD5.cpp

OBJS			= $(FILES:.cpp=.o)

GCC 			= g++

CPPFLAGS	= -std=c++11 -I ./C++/Dependence/ -I ./C++/ -pthread

RM				= rm -f

all: $(NAME)

$(NAME): $(OBJS)
		$(GCC) $(OBJS) -o $(NAME) $(CPPFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
