# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lleverge <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/21 17:32:58 by lleverge          #+#    #+#              #
#    Updated: 2016/04/14 16:54:21 by lleverge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = main.c	tools.c		ft_param.c		free.c\
	ft_setenv.c	ft_unsetenv.c	ft_cd.c		tools2.c\
	env.c	fork.c	tools3.c	ft_strsplit_ws.c\
	env2.c	tools4.c	prompt.c
OBJ = $(SRC:.c=.o)
LIB = ./libft/libft.a
FLAGS = -Wall -Wextra -Werror -g

$(NAME): $(OBJ)
	make -C ./libft
	gcc $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

all: $(NAME)

%.o: %.c
	gcc $(FLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean $(NAME)

.PHONY : all clean fclean re
