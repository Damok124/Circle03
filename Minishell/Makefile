# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 17:12:24 by zharzi            #+#    #+#              #
#    Updated: 2022/11/09 20:40:18 by zharzi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libminishell.a

BINARY = minishell

SRCSDIR = ./srcs/

SRCS = \
${SRCSDIR}test.c

HEADERDIR = includes/

HEADER = minishell.h

OBJ = $(SRCS:.c=.o)

CC = clang

FLAGS = -Wall -Wextra -Werror -g3

IFLAG = -I$(HEADERDIR) -Ift_printf/includes/ -Ilibft/includes/

all : libft.a libft_printf.a libpipex.a $(BINARY)

$(BINARY):
	$(CC) $(FLAGS) main.c $(IFLAG) -L. -lminishell -L./pipex -lpipex \
		-L./libft -lft -L./ft_printf -lft_printf -o $(BINARY)

%.o : %.c
	$(CC) $(FLAGS) $(IFLAG) -o $@ -c $^

libminishell.a : $(OBJ) $(HEADERDIR)$(HEADER)
	ar -rcs $(NAME) $^

libft.a :
	@${MAKE} -sC libft/

libft_printf.a :
	@${MAKE} -sC ft_printf/

libpipex.a :
	@${MAKE} -sC pipex/

clean :
	rm -f $(OBJ)
	@${MAKE} clean -sC libft/
	@${MAKE} clean -sC ft_printf/
	@${MAKE} clean -sC pipex/

fclean : clean
	rm -f $(NAME)
	rm -f $(BINARY)
	@${MAKE} fclean -sC libft/
	@${MAKE} fclean -sC ft_printf/
	@${MAKE} fclean -sC pipex/

re : fclean all

bre : fclean bonus

.PHONY : all bonus clean fclean re bre
