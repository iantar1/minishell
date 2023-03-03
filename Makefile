NAME = minishell

LIBFT = libft.a

SRC = minishell.c upgrade_split.c utils1.c utils2.c get_env.c ft_expanding.c

OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Wextra -Werror

${NAME}: ${LIBFT} ${OBJ}
	cc ${CFLAGS} ${OBJ} ${LIBFT} -lreadline -o ${NAME}

all:${NAME} ${LIBFT}

${LIBFT}:
	make bonus -C ./LIBFT
	make clean -C  ./LIBFT
	mv ./LIBFT/libft.a .

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME} ${LIBFT}

re:fclean all

git:
	git add .
	git commit -m "iantar"
	git push