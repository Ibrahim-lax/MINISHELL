SRCS			=	ft_ft.c ft_ft1.c ft_split.c gnl.c
OBJS			= $(SRCS:.c=.o)

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

NAME			= libft.a

all:			$(NAME)


$(NAME):		$(OBJS)
				ar rc $(NAME) $(OBJS)

%.o : %.c  libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all
