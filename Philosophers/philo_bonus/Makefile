# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/31 13:40:41 by zharzi            #+#    #+#              #
#    Updated: 2022/12/24 00:36:14 by zharzi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libphilo_bonus.a

BINARY = philo_bonus

SRCSDIR = ./srcs/

SRCS = \
${SRCSDIR}ft_isdigit_bonus.c \
${SRCSDIR}ft_atoi_safe_bonus.c \
${SRCSDIR}ft_true_free_bonus.c \
${SRCSDIR}ft_get_chrono_bonus.c \
${SRCSDIR}ft_print_msg_bonus.c \
${SRCSDIR}ft_print_last_msg_bonus.c \
${SRCSDIR}ft_usleep_bonus.c \
${SRCSDIR}ft_check_args_bonus.c \
${SRCSDIR}ft_check_arg_positive_bonus.c \
${SRCSDIR}ft_check_arg_overflow_bonus.c \
${SRCSDIR}ft_is_expired_bonus.c \
${SRCSDIR}ft_is_full_or_dead_bonus.c \
${SRCSDIR}ft_init_context_bonus.c \
${SRCSDIR}ft_init_tab_philo_bonus.c \
${SRCSDIR}ft_share_printf_mutex_bonus.c \
${SRCSDIR}ft_init_mutexes_bonus.c \
${SRCSDIR}ft_grab_right_bonus.c \
${SRCSDIR}ft_grab_left_bonus.c \
${SRCSDIR}ft_eating_bonus.c \
${SRCSDIR}ft_sleeping_bonus.c \
${SRCSDIR}ft_thinking_bonus.c \
${SRCSDIR}ft_routine_bonus.c \
${SRCSDIR}ft_put_thread_on_routine_bonus.c \
${SRCSDIR}ft_soul_taking_bonus.c \
${SRCSDIR}ft_philo_bonus.c \
${SRCSDIR}ft_join_them_all_bonus.c \
${SRCSDIR}ft_unset_philos_bonus.c


HEADERDIR = includes/

HEADER = philo_bonus.h

OBJ = $(SRCS:.c=.o)

CC = clang

FLAGS = -Wall -Wextra -Werror -g3

IFLAG = -I$(HEADERDIR)

all : $(BINARY)

$(BINARY): libphilo.a
	$(CC) $(FLAGS) main_bonus.c -lpthread $(IFLAG) -L. -lphilo_bonus -o $(BINARY)

%.o : %.c
	$(CC) $(FLAGS) $(IFLAG) -o $@ -c $^

libphilo.a : $(OBJ) $(HEADERDIR)$(HEADER)
	ar -rcs $(NAME) $^

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)
	rm -f $(BINARY)

re : fclean all

.PHONY : all clean fclean re
