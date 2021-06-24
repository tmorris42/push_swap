CHECKER = checker
PUSH_SWAP = push_swap

GCC = gcc
FLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a

INCLUDES = -Iincludes/ -Ilibft/
STACK_SRCS = stack.c stack_utils.c stack_operations.c \
			 read_args.c commands.c errors.c
STACK_OBJS = ${STACK_SRCS:.c=.o}
CHECKER_SRCS = checker.c 
CHECKER_OBJS = ${CHECKER_SRCS:.c=.o}
PUSH_SWAP_SRCS = push_swap.c \
				 lowhigh.c \
				 pivot.c \
				 push_lowest.c \
				 quicksort.c \
				 rotate_and_insert.c \
				 sort_3.c \
				 take_highest.c \
				 take_top_3.c 
PUSH_SWAP_OBJS = ${PUSH_SWAP_SRCS:.c=.o}

all: $(CHECKER) $(PUSH_SWAP)

$(LIBFT):
	$(MAKE) -C libft

$(STACK_OBJS): %.o : srcs/%.c
	$(GCC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(CHECKER_OBJS): %.o : srcs/%.c
	$(GCC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(CHECKER): $(LIBFT) $(STACK_OBJS) $(CHECKER_OBJS)
	$(GCC) $(FLAGS) $(INCLUDES) $(CHECKER_OBJS) $(STACK_OBJS) $(LIBFT) -o $(CHECKER)

$(PUSH_SWAP_OBJS): %.o : srcs/%.c
	$(GCC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(PUSH_SWAP): $(LIBFT) $(STACK_OBJS) $(PUSH_SWAP_OBJS)
	$(GCC) $(FLAGS) $(INCLUDES) $(PUSH_SWAP_OBJS) $(STACK_OBJS) $(LIBFT) -o $(PUSH_SWAP)

clean:
	rm -f $(CHECKER_OBJS) $(PUSH_SWAP_OBJS) $(STACK_OBJS)

fclean: clean
	rm -f $(CHECKER) $(PUSH_SWAP)

re: fclean all

visARG: $(PUSH_SWAP)
	python3.7 ../push_swap_visualizer/pyviz.py `ruby -e "puts '${ARGS}'"`

vis500: $(PUSH_SWAP)
	python3.7 ../push_swap_visualizer/pyviz.py `ruby -e "puts (-250..250).to_a.shuffle.join(' ')"`

vis100: $(PUSH_SWAP)
	python3.7 ../push_swap_visualizer/pyviz.py `ruby -e "puts (-50..50).to_a.shuffle.join(' ')"`

vis50: $(PUSH_SWAP)
	python3.7 ../push_swap_visualizer/pyviz.py `ruby -e "puts (-25..25).to_a.shuffle.join(' ')"`

vis10: $(PUSH_SWAP)
	python3.7 ../push_swap_visualizer/pyviz.py `ruby -e "puts (-5..5).to_a.shuffle.join(' ')"`

vis5: $(PUSH_SWAP)
	python3.7 ../push_swap_visualizer/pyviz.py `ruby -e "puts (-2..2).to_a.shuffle.join(' ')"`

vis3: $(PUSH_SWAP)
	python3.7 ../push_swap_visualizer/pyviz.py `ruby -e "puts (-1..1).to_a.shuffle.join(' ')"`

test: all
	@echo "Copying push_swap and checker into tests directory"
	@cp ./push_swap ./tests/
	@cp ./checker ./tests/
	@python3.7 ./tests/test.py
	@echo "Cleaning up..."
	@rm ./tests/push_swap ./tests/checker
	@echo "Done."

clearlogs:
	rm -rf logs
	mkdir logs


.PHONY: all clean fclean re test clearlogs
