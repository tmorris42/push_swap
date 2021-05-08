CHECKER = checker
PUSH_SWAP = push_swap

FLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a

CHECKER_SRCS = checker.c 
CHECKER_OBJS = ${CHECKER_SRCS:.c=.o}
PUSH_SWAP_SRCS = push_swap.c 
PUSH_SWAP_OBJS = ${PUSH_SWAP_SRCS:.c=.o}

all: $(CHECKER) $(PUSH_SWAP)

$(LIBFT):
	$(MAKE) bonus -C libft

$(CHECKER_OBJS): %.o : %.c
	gcc $(FLAGS) -c $< -o $@

$(CHECKER): $(LIBFT) $(CHECKER_OBJS)
	gcc $(FLAGS) $(CHECKER_OBJS) $(LIBFT) -o $(CHECKER)

$(PUSH_SWAP_OBJS): %.o : %.c
	gcc $(FLAGS) -c $< -o $@

$(PUSH_SWAP): $(LIBFT) $(PUSH_SWAP_OBJS)
	gcc $(FLAGS) $(PUSH_SWAP_OBJS) $(LIBFT) -o $(PUSH_SWAP)

clean:
	rm -f $(CHECKER_OBJS) $(PUSH_SWAP_OBS)

fclean: clean
	rm -f $(CHECKER) $(PUSH_SWAP)

re: fclean all

.PHONY: all clean fclean re test
