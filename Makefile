NAME      = pipex
BONUS	  = pipex_bonus
CC        = clang
CFLAGS    = -Wall -Wextra -Werror -g3
RM        = rm -f
PRINTF    = ft_printf
FT_PRINTF = ft_printf/libftprintf.a
LIBFT     = libft
FT_LIBFT  = libft/libft.a
SRC       = mandatory/main.c mandatory/pipex.c
SRC_BONUS = bonus/main_bonus.c bonus/pipex_bonus.c bonus/here_doc.c gnl/get_next_line.c gnl/get_next_line_utils.c
OBJ       = ${SRC:.c=.o}
OBJ_BONUS = ${SRC_BONUS:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	${MAKE} -C ${PRINTF}
	${MAKE} -C ${LIBFT}
	${CC} ${OBJ} -o ${NAME} ${FT_PRINTF} ${FT_LIBFT}

bonus : ${BONUS}

${BONUS} : ${OBJ_BONUS}
	${MAKE} -C ${LIBFT}
	${MAKE} -C ${PRINTF}
	${CC} ${OBJ_BONUS} -o ${BONUS} ${FT_LIBFT} ${FT_PRINTF}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${OBJ} ${OBJ_BONUS}
	${MAKE} -C ${PRINTF} clean
	${MAKE} -C ${LIBFT} clean

fclean: clean
	${RM} ${NAME} ${BONUS}
	${MAKE} -C ${PRINTF} fclean
	${MAKE} -C ${LIBFT} fclean

re: fclean all

.PHONY: all clean fclean re
