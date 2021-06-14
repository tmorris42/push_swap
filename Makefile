CHECKER = checker
PUSH_SWAP = push_swap

FLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a

STACK_SRCS = stack.c stack_utils.c stack_operations.c read_args.c commands.c \
			 errors.c
STACK_OBJS = ${STACK_SRCS:.c=.o}
CHECKER_SRCS = checker.c 
CHECKER_OBJS = ${CHECKER_SRCS:.c=.o}
PUSH_SWAP_SRCS = push_swap.c
PUSH_SWAP_OBJS = ${PUSH_SWAP_SRCS:.c=.o}

all: $(CHECKER) $(PUSH_SWAP)

$(LIBFT):
	$(MAKE) -C libft

$(STACK_OBJS): %.o : %.c
	gcc $(FLAGS) -c $< -o $@

$(CHECKER_OBJS): %.o : %.c
	gcc $(FLAGS) -c $< -o $@

$(CHECKER): $(LIBFT) $(STACK_OBJS) $(CHECKER_OBJS)
	gcc $(FLAGS) $(CHECKER_OBJS) $(STACK_OBJS) $(LIBFT) -o $(CHECKER)

$(PUSH_SWAP_OBJS): %.o : %.c
	gcc $(FLAGS) -c $< -o $@

$(PUSH_SWAP): $(LIBFT) $(STACK_OBJS) $(PUSH_SWAP_OBJS)
	gcc $(FLAGS) $(PUSH_SWAP_OBJS) $(STACK_OBJS) $(LIBFT) -o $(PUSH_SWAP)

clean:
	rm -f $(CHECKER_OBJS) $(PUSH_SWAP_OBJS) $(STACK_OBJS)

fclean: clean
	rm -f $(CHECKER) $(PUSH_SWAP)

re: fclean all

.PHONY: all clean fclean re test
