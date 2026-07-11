NAME        = push_swap
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

SRCS        = main.c parser.c stack_utils.c op_swap_push.c op_rotate.c \
            	op_wrappers_a.c op_wrappers_b.c disorder_metric.c \
            	indexer.c math_utils.c simple_sort.c medium_sort.c \
            	complex_sort.c

OBJS        = $(SRCS:.c=.o)
HEADER      = push_swap.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re