NAME      = pipex
CC        = clang
CFLAGS    = -Wall -Wextra -Werror -g3
RM        = rm -f
PRINTF    = ft_printf
FT_PRINTF = ft_printf/libftprintf.a
LIBFT     = libft
FT_LIBFT  = libft/libft.a
SRC       = main.c test.c
OBJ       = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	${MAKE} -C ${PRINTF}
	${MAKE} -C ${LIBFT}
	${CC} ${OBJ} -o ${NAME} ${FT_PRINTF} ${FT_LIBFT}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${OBJ}
	${MAKE} -C ${PRINTF} clean
	${MAKE} -C ${LIBFT} clean

fclean: clean
	${RM} ${NAME}
	${MAKE} -C ${PRINTF} fclean
	${MAKE} -C ${LIBFT} fclean

re: fclean all

.PHONY: all clean fclean re
