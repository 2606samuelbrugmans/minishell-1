NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Iinc

SRC = src/

INC = inc/

FCTS =  $(SRC)fcts/ft_split.c $(SRC)fcts/ft_strjoin.c $(SRC)fcts/ft_strlcat.c $(SRC)fcts/ft_strlcpy.c $(SRC)fcts/ft_strlen.c 

FT_PRINTF = $(SRC)printf/ft_printf.c $(SRC)printf/all_ft_1.c $(SRC)printf/all_ft_2.c

PIPEX = $(SRC)pipex/basic_functions.c $(SRC)pipex/basic_functions2.c $(SRC)pipex/family.c $(SRC)pipex/pipe_utils.c $(SRC)pipex/pipex.c

GET_NEXT_LINE = $(SRC)get_next_line/get_next_line.c $(SRC)get_next_line/get_next_line_utils.c \
				$(SRC)get_next_line/get_next_line_bonus.c $(SRC)get_next_line/get_next_line_bonus.c
					 
OBJS = $(SRCS:.c=.o)

SRCS = $(FCTS) $(FT_PRINTF) $(GET_NEXT_LINE)

ARRC = ar rc

RANLIB = ranlib

RM = rm -f

.c.o : $(SRCS)
	${CC} ${CFLAGS} -c -o $@ $^

$(NAME) : $(OBJS)
	$(ARRC) $(NAME) $(OBJS)
	$(RANLIB) $(NAME)

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all


.PHONY : all clean fclean re