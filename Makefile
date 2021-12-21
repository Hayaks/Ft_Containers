NAME			= container
STL				= stl_container

OBJS_DIR		= objs/

OBJS			= $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))

OBJS_DIR_STL	= objs_stl/

OBJS_STL		= $(addprefix $(OBJS_DIR_STL), $(SRCS:.cpp=.o))

HEADER			= -I ./include/

SRCS			= main.cpp

FOLDER			= $(addprefix ./, $(SRCS))

CC				= clang++
CFLAGS 			= -Wall -Wextra -Werror -std=c++98
FSAN			= -g3 -fsanitize=address
RM				= rm -rf

all:			$(NAME) $(STL)

$(NAME):		$(OBJS_DIR) $(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR):
				@mkdir $(OBJS_DIR)

$(OBJS_DIR)%.o:	./%.cpp
				$(CC) $(CFLAGS) -DFT=ft $(HEADER) -c $< -o $@

$(STL):			$(OBJS_DIR_STL) $(OBJS_STL)
				$(CC) $(CFLAGS) $(OBJS_STL) -o $(STL)

$(OBJS_DIR_STL):
				@mkdir $(OBJS_DIR_STL)

$(OBJS_DIR_STL)%.o:	./%.cpp
				$(CC) $(CFLAGS) -DFT=stl $(HEADER) -c $< -o $@

fsan:			$(OBJS_DIR) $(OBJS)
				$(CC) $(CFLAGS) $(OBJS) $(FSAN) -o $(NAME)

leaks:			$(NAME)
				valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --show-leak-kinds=all --track-origins=yes ./$(NAME)

clean:
				$(RM) $(OBJS_DIR) $(OBJS_DIR_STL)

fclean:			clean
				$(RM) $(NAME) $(STL)

re:				fclean all

.PHONY: all clean fclean re