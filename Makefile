NAME = minishell

LIBFT = libft.a

SRC = minishell.c upgrade_split.c utils1.c utils2.c get_env.c ft_expanding.c ft_parcing_operetor.c  GNL/get_next_line.c GNL/get_next_line_utils.c here_doc.c reform_rediraction.c parce_tree.c
		

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
COM="iantar"
git:
	git add .
	git commit -m "${COM}"
	git push