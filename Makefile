CC = cc
CFLAGS =  -Wall -Wextra -Werror -g3
RM = rm -f

NAME = pipex
B_NAME = pipex_bonus

SRCS = srcs/pipex.c \
	   srcs/parse_args.c \
	   srcs/redirect_io.c \
	   srcs/run_commands.c \
	   srcs/error_handling.c \

BSRCS = bonus/pipex_bonus.c \
		bonus/parse_args_bonus.c \
		bonus/redirect_io_bonus.c \
		bonus/run_commands_bonus.c \
		bonus/error_handling_bonus.c \
		bonus/bns_utils.c \
		bonus/here_doc.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c

S_OBJS = ${SRCS:.c=.o}
B_OBJS = ${BSRCS:.c=.o}

all: ${NAME}

${NAME}: ${S_OBJS} | LIB
		${CC} ${CFLAGS} ${S_OBJS} -Llibft -lft -o ${NAME}

bonus: ${B_NAME}

${B_NAME}: ${B_OBJS} | LIB
		${CC} ${CFLAGS} ${B_OBJS} -Llibft -lft -o ${B_NAME}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

LIB:
	make -C ./libft

clean: 
		${RM} ${S_OBJS}
		${RM} ${B_OBJS}
		make clean -C ./libft

fclean: clean
		${RM} ${NAME}
		${RM} ${B_NAME}
		${RM} ./libft/libft.a

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: ${S_OBJS} ${B_OBJS}