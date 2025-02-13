CC = cc
CFLAGS = #-Wall -Wextra -Werror 
RM = rm -f

NAME = pipex

SRCS = pipex.c \
	   parsing.c \
	   redirect_io.c \
	   run_commands.c \
	   ./ft_printf/ft_printf.c \
	   ./ft_printf/ft_printf_utils.c \
	   ./get_next_line/get_next_line.c \
	   ./get_next_line/get_next_line_utils.c

S_OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${S_OBJS} | LIB
		${CC} ${CFLAGS} ${S_OBJS} -Llibft -lft -o ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

LIB:
	make -C ./libft

clean: 
		${RM} ${S_OBJS}
		make clean -C ./libft

fclean: clean
		${RM} ${NAME}
		${RM} ./libft/libft.a

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: ${S_OBJS}