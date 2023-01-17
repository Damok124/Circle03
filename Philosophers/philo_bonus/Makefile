# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/31 13:40:41 by zharzi            #+#    #+#              #
#    Updated: 2023/01/17 23:45:11 by zharzi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libphilo_bonus.a

BINARY = philo_bonus

SRCSDIR = ./srcs/

SRCS = \
${SRCSDIR}ft_isdigit.c \
${SRCSDIR}ft_atoi_safe.c \
${SRCSDIR}ft_true_free.c \
${SRCSDIR}ft_itoa.c \
${SRCSDIR}ft_check_arg_positive.c \
${SRCSDIR}ft_check_arg_overflow.c \
${SRCSDIR}ft_check_args.c \
${SRCSDIR}ft_init_context_sem.c \
${SRCSDIR}ft_init_context.c \
${SRCSDIR}ft_get_chrono.c \
${SRCSDIR}ft_is_expired.c \
${SRCSDIR}ft_print_last_msg.c \
${SRCSDIR}ft_action_if_alive.c \
${SRCSDIR}ft_print_msg.c \
${SRCSDIR}ft_is_full_or_dead.c \
${SRCSDIR}ft_grab_right.c \
${SRCSDIR}ft_grab_left.c \
${SRCSDIR}ft_usleep.c \
${SRCSDIR}ft_sleeping.c \
${SRCSDIR}ft_die_alone.c \
${SRCSDIR}ft_eating.c \
${SRCSDIR}ft_thinking.c \
${SRCSDIR}ft_routine.c \
${SRCSDIR}ft_kill_them_all.c \
${SRCSDIR}ft_unset_philos.c \
${SRCSDIR}ft_put_processes_on_routine.c \
${SRCSDIR}ft_soul_waiting.c \
${SRCSDIR}ft_wait_last_plate.c \
${SRCSDIR}ft_philo.c \
${SRCSDIR}ft_init_tab_philo.c \
${SRCSDIR}ft_sem_close.c \
${SRCSDIR}ft_unset_context.c

HEADERDIR = includes/

HEADER = philo_bonus.h

OBJ = $(SRCS:.c=.o)

CC = clang

FLAGS = -Wall -Wextra -Werror -g3

IFLAG = -I$(HEADERDIR)

all : $(BINARY)

$(BINARY): libphilo.a
	-@$(CC) $(FLAGS) main_bonus.c -lpthread $(IFLAG) -L. -lphilo_bonus -o $(BINARY)

%.o : %.c
	-@$(CC) $(FLAGS) $(IFLAG) -o $@ -c $^

libphilo.a : $(OBJ) $(HEADERDIR)$(HEADER)
	-@ar -rcs $(NAME) $^

clean :
	-@rm -f $(OBJ)

fclean : clean
	-@rm -f $(NAME)
	-@rm -f $(BINARY)

re : fclean all

.PHONY : all clean fclean re
