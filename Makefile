NAME			= ft_container
STD				= std_container

OBJS_DIR		= objs/

OBJS			= $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))

OBJS_DIR_STD	= objs_STD/

OBJS_STD		= $(addprefix $(OBJS_DIR_STD), $(SRCS:.cpp=.o))

HEADER			= -I ./include/

SRCS_DIR		= ./src/

SRCS			= vector.cpp stack.cpp map.cpp main.cpp

FOLDER			= $(addprefix $(SRCS_DIR), $(SRCS))

CC				= clang++
CFLAGS 			= -Wall -Wextra -Werror -std=c++98
FSAN			= -g3 -fsanitize=address
RM				= rm -rf

all:			$(NAME) $(STD)

diff:			all
				mkdir -p diff/
				./$(NAME) > diff/ft.txt
				./$(STD) > diff/std.txt
				diff diff/ft.txt diff/std.txt > diff/diff.txt

$(NAME):		$(OBJS_DIR) $(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR):
				@mkdir $(OBJS_DIR)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.cpp
				$(CC) $(CFLAGS) -DFT=ft $(HEADER) -c $< -o $@

$(STD):			$(OBJS_DIR_STD) $(OBJS_STD)
				$(CC) $(CFLAGS) $(OBJS_STD) -o $(STD)

$(OBJS_DIR_STD):
				@mkdir $(OBJS_DIR_STD)

$(OBJS_DIR_STD)%.o:	$(SRCS_DIR)%.cpp
				$(CC) $(CFLAGS) -DFT=std $(HEADER) -c $< -o $@

fsan:			$(OBJS_DIR) $(OBJS)
				$(CC) $(CFLAGS) $(OBJS) $(FSAN) -o $(NAME)

leaks:			$(NAME)
				valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --show-leak-kinds=all --track-origins=yes ./$(NAME)

clean:
				$(RM) $(OBJS_DIR) $(OBJS_DIR_STD)

fclean:			clean
				$(RM) $(NAME) $(STD) diff

re:				fclean all

.PHONY: all clean fclean re