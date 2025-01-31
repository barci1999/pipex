NAME	= pipex

CC	= cc
CFLAGS = -Wall -Werror -Wextra -I./includes -I libft -I printf
LIBFT_DIR = ./libft
PRINT_DIR = ./printf 
LIBS = -L$(LIBFT_DIR) -lft -L$(PRINT_DIR) -lftprintf
SRCS = src/main.c src/utils_parse_cmd.c src/utils_parse_fd.c src/utils_pipe.c src/utils_excute_cmds.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -s -C $(PRINT_DIR)
	make -s -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c includes/pipex.h 
	$(CC) $(CFLAGS) -I./includes -c $< -o $@

clean:
	rm -f $(OBJS)
	make -s -C $(LIBFT_DIR) clean
	make -s -C $(PRINT_DIR) clean

fclean: clean
	make -s -C $(LIBFT_DIR) fclean
	make -s -C $(PRINT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re  