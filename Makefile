SRCS	=	$(addprefix srcs/, errors.c ft_list.c ft_split.c parsing_pipex.c\
			pipex.c utils.c parsing_utils.c)

OBJS	=	${SRCS:.c=.o}

NAME	=	pipex

CC	=		gcc

CFLAGS	=	-Wall -Wextra -Werror

RM	=		rm -f

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o pipex

all:		${NAME}

clean:
			${RM} ${OBJS} ${OBJS_BONUS}

fclean:		clean
			${RM} ${NAME}

exe_clean:	all clean

re:			fclean all

.PHONY:		all clean fclean exe_clean re
