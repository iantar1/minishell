NAME = minishell

LIBFT = libft.a

SRC = ./parcing/upgrade_split.c ./parcing/utils1.c ./parcing/utils2.c ./parcing/get_env.c ./parcing/ft_expanding.c ./parcing/ft_parcing_operetor.c \
	./parcing/GNL/get_next_line.c ./parcing/GNL/get_next_line_utils.c ./parcing/here_doc.c ./parcing/reform_rediraction.c ./parcing/parce_tree.c \
	./parcing/parenthisis.c ./parcing/ambiguous_redirect.c ./parcing/syntax_error.c ./parcing/wildcard.c ./parcing/rediraction_handle.c ./parcing/upgrade_malloc.c ./parcing/upgrade_libft1.c ./parcing/upgrade_libft2.c \
	./execution/utils.c ./execution/utils2.c ./execution/minishell_utiles.c ./execution/minishell_utiles2.c ./execution/ft_split.c\
	./execution/export_var.c ./execution/export_var2.c ./execution/export_parse.c ./execution/ft_substr.c ./execution/utils1.c\
	./execution/handle_export_unset.c ./execution/export_var3.c ./execution/unset_exit.c ./execution/update_env.c ./execution/cd_pwd_echo.c ./execution/execute.c\
	./execution/ft_printf/ft_print_hex.c ./execution/ft_printf/ft_print_ptr.c ./execution/ft_printf/ft_printf.c ./execution/ft_printf/ft_putchar_fd.c\
	./execution/ft_printf/ft_putnbr_fd.c ./execution/ft_printf/ft_putstr_fd.c ./execution/ft_itoa.c ./execution/tree_execute.c ./execution/execute_utiles.c\
	./execution/tree_execute_utils.c ./execution/attr_utils.c \
	main.c 

OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

#${NAME}: ${LIBFT} ${OBJ}
#	@cc ${CFLAGS} ${OBJ} ${LIBFT} -lreadline -o ${NAME} -L /Users/oidboufk/homebrew/Cellar/readline/8.2.1/lib -I /Users/oidboufk/homebrew/Cellar/readline/8.2.1/include

#${NAME}: ${LIBFT} ${OBJ}
#	@cc ${CFLAGS} ${OBJ} ${LIBFT} -lreadline -o ${NAME} -L /Users/oidboufk/homebrew/Cellar/readline/8.2.1/lib -I /Users/oidboufk/homebrew/Cellar/readline/8.2.1/include

${NAME}: ${LIBFT} ${OBJ}
	@cc ${CFLAGS} ${OBJ} ${LIBFT} -lreadline -o ${NAME} -L ../lib -I ../include

all:${NAME} ${LIBFT}

${LIBFT}:
	make bonus -C ./parcing/LIBFT
	make clean -C  ./parcing/LIBFT
	mv ./parcing/LIBFT/libft.a .

clean:
	@rm -f ${OBJ}
	@echo "clean object files ..."

fclean: clean
	@rm -f ${NAME} ${LIBFT}
	@echo "clean Executable ..."

re:fclean all

COM="iantar"
git:
	git add .
	git commit -m "${COM}"
	git push