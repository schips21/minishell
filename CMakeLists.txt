cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(my_libft)
include_directories(SRCS)

add_executable(minishell
        my_libft/ft_atoi.c
        my_libft/ft_bzero.c
        my_libft/ft_calloc.c
        my_libft/ft_isalnum.c
        my_libft/ft_isalpha.c
        my_libft/ft_isascii.c
        my_libft/ft_isdigit.c
        my_libft/ft_isprint.c
        my_libft/ft_itoa.c
        my_libft/ft_lstadd_back.c
        my_libft/ft_lstadd_front.c
        my_libft/ft_lstclear.c
        my_libft/ft_lstdelone.c
        my_libft/ft_lstiter.c
        my_libft/ft_lstlast.c
        my_libft/ft_lstmap.c
        my_libft/ft_lstnew.c
        my_libft/ft_lstsize.c
        my_libft/ft_memccpy.c
        my_libft/ft_memchr.c
        my_libft/ft_memcmp.c
        my_libft/ft_memcpy.c
        my_libft/ft_memmove.c
        my_libft/ft_memset.c
        my_libft/ft_putchar_fd.c
        my_libft/ft_putendl_fd.c
        my_libft/ft_putnbr_fd.c
        my_libft/ft_putstr_fd.c
        my_libft/ft_split.c
        my_libft/ft_strchr.c
        my_libft/ft_strdup.c
        my_libft/ft_strjoin.c
        my_libft/ft_strlcat.c
        my_libft/ft_strlcpy.c
        my_libft/ft_strlen.c
        my_libft/ft_strmapi.c
        my_libft/ft_strncmp.c
        my_libft/ft_strnstr.c
        my_libft/ft_strrchr.c
        my_libft/ft_strtrim.c
        my_libft/ft_substr.c
        my_libft/ft_tolower.c
        my_libft/ft_toupper.c
        my_libft/get_next_line.c
        my_libft/get_next_line_utils.c
        my_libft/libft.h
        SRCS/parser.c
        SRCS/parser_mem_realloc.c
        SRCS/parser_mem_realloc_redir.c
        SRCS/shell_header.h
        SRCS/structures.h
        SRCS/parser_utils.c
        SRCS/parser_redirects.c
        SRCS/parser_dollar.c

        SRCS/check_work.c
        SRCS/info.c
        SRCS/process.c
        SRCS/redirects.c

        SRCS/commands/ft_echo.c
        SRCS/commands/ft_env.c
        SRCS/commands/ft_cd.c
        SRCS/commands/ft_pwd.c
        SRCS/commands/ft_export.c
        SRCS/commands/ft_unset.c
        SRCS/commands/ft_exit.c
        SRCS/commands/ft_export_2.c
        SRCS/commands/ft_other_commands.c
        SRCS/commands/ft_other_commands_2.c
        SRCS/env/env.c
        SRCS/env/env_2.c
        SRCS/env/env_change.c
        SRCS/main.c
        SRCS/parser_check_line.c
        )
