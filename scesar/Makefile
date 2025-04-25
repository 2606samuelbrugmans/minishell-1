NAME = minishell

CC = cc

CFLAGS = -Werror -Wextra -Wall

LIBFT = ./Libft/libft.a

INC = inc/minishell.h

SRCS = $(wildcard src/*.c)

OBJS = $(SRCS:.c=.o)

RM = rm -rf

all : $(NAME)

%.o : %.c
	${CC} -I${INC} -c -o $@ $<

$(LIBFT):
	@make -C ./Libft

$(NAME) : $(OBJS) $(LIBFT)
	${CC} $(OBJS) ${LIBFT} -o ${NAME} ${CFLAGS} -lreadline

clean :
	$(RM) $(OBJS)
	@make clean -C ./Libft
fclean : clean
	$(RM) $(NAME)
	@make fclean -C ./Libft
re : fclean all


.PHONY : all clean fclean re
