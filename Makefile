CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -f

NAME = pipex

SRCS = srcs/pipex.c \
	   srcs/parse_args.c \
	   srcs/redirect_io.c \
	   srcs/run_commands.c \
	   srcs/error_handling.c

BSRCS = bonus/pipex_bonus.c \
		bonus/parse_args_bonus.c \
		bonus/redirect_io_bonus.c \
		bonus/run_commands_bonus.c \
		bonus/error_handling_bonus.c \
		bonus/bns_utils.c \
		bonus/here_doc.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c

S_OBJS = $(SRCS:.c=.o)
B_OBJS = $(BSRCS:.c=.o)

IS_BONUS = 0

ifeq ($(MAKECMDGOALS),bonus)
IS_BONUS = 1
endif

ifeq ($(IS_BONUS),1)
OBJS = $(B_OBJS)
else
OBJS = $(S_OBJS)
endif

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS) | LIB
	$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -o ${NAME}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

LIB:
	make -C ./libft

clean:
	$(RM) $(S_OBJS) $(B_OBJS)
	make clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	$(RM) ./libft/libft.a

re: fclean all

.PHONY: all bonus clean fclean re
.SECONDARY: ${S_OBJS} ${B_OBJS}