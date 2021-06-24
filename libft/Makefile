NAME = libft.a

SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
	   ft_memchr.c ft_memcmp.c ft_strlen.c ft_strchr.c ft_strncmp.c \
	   ft_strrchr.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_atoi.c \
	   ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	   ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_strmapi.c \
	   ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_substr.c \
	   ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	   ft_putchar.c ft_putstr.c ft_putnbr.c \
	   ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
	   ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	   ft_lstclear.c ft_lstiter.c ft_lstmap.c \
	   get_next_line.c get_next_line_utils.c \
	   ft_putint_fd.c \
	   ft_max.c ft_min.c ft_abs.c \
	   ft_atol.c

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(OBJS): %.o: %.c
	gcc -c -Wall -Wextra -Werror $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all re clean fclean bonus
