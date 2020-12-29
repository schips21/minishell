SOURCES = SRCS/*.c SRCS/commands/*.c SRCS/env/*.c
NAME = minishell

HEADER = SRCS/shell_header.h SRCS/structures.h 

LIBFT = my_libft/libft.a

all: $(NAME)

$(LIBFT): my_libft/*.c my_libft/libft.h
	make -C my_libft

$(NAME): $(SOURCES) $(LIBFT) $(HEADER)
	gcc  $(SOURCES) $(LIBFT) -o $(NAME)

clean:
	make clean -C my_libft

fclean: clean
	rm -f $(NAME)
	make fclean -C my_libft

re: fclean all

.PHONY: all clean fclean re
