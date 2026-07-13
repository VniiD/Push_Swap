# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: v <v@student.42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/13 13:16:14 by v                 #+#    #+#              #
#    Updated: 2026/07/13 14:01:39 by v                ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = push_swap
BONUS_NAME  = checker

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

SRC         = utils_memory.c utils_parsing.c parser_main.c op_swap_push.c \
				op_rot_revrot.c disorder.c writer.c op_wrappers.c \
				op_wrappers_rot.c op_wrappers_double.c strat_simple.c \
				strat_medium.c strat_complex.c strat_adaptive.c main.c

BONUS_SRC   = utils_memory.c utils_parsing.c parser_main.c op_swap_push.c \
				op_rot_revrot.c disorder.c writer.c checker_bonus.c \
				checker_op_bonus.c main_bonus.c

OBJ         = $(SRC:.c=.o)
BONUS_OBJ   = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(BONUS_NAME)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus