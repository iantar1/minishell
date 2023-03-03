SRCS = ft_atoi.c ft_isprint.c ft_putchar_fd.c ft_striteri.c ft_strnstr.c ft_bzero.c ft_itoa.c ft_putendl_fd.c \
	ft_strjoin.c ft_strrchr.c ft_calloc.c ft_memchr.c ft_putnbr_fd.c ft_strlcat.c ft_strtrim.c ft_isalnum.c \
	ft_memcmp.c ft_putstr_fd.c ft_strlcpy.c ft_substr.c ft_isalpha.c ft_memcpy.c ft_split.c ft_strlen.c \
	ft_tolower.c ft_isascii.c ft_memmove.c ft_strchr.c ft_strmapi.c ft_toupper.c ft_isdigit.c ft_memset.c \
	ft_strdup.c ft_strncmp.c
SRCS_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

${NAME}: ${OBJS}
	ar -rsc ${NAME} ${OBJS}
all: ${NAME}
clean:
	rm -f  ${OBJS} ${OBJS_BONUS}
fclean:
	rm -f ${OBJS} ${OBJS_BONUS}
	rm -f ${NAME}
re: fclean all
bonus: ${OBJS_BONUS} ${OBJS}
	 ar -rsc ${NAME} ${OBJS_BONUS} ${OBJS}
