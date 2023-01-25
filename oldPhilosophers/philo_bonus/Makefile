# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/31 13:40:41 by zharzi            #+#    #+#              #
#    Updated: 2023/01/18 13:38:34 by zharzi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libphilo_bonus.a

BINARYBONUS = philo_bonus

SRCSDIR = ./srcs/

SRCSBONUS = \
${SRCSDIR}ft_isdigit_bonus.c \
${SRCSDIR}ft_atoi_safe_bonus.c \
${SRCSDIR}ft_true_free_bonus.c \
${SRCSDIR}ft_itoa_bonus.c \
${SRCSDIR}ft_check_arg_positive_bonus.c \
${SRCSDIR}ft_check_arg_overflow_bonus.c \
${SRCSDIR}ft_check_args_bonus.c \
${SRCSDIR}ft_init_context_sem_bonus.c \
${SRCSDIR}ft_init_context_bonus.c \
${SRCSDIR}ft_get_chrono_bonus.c \
${SRCSDIR}ft_is_expired_bonus.c \
${SRCSDIR}ft_print_last_msg_bonus.c \
${SRCSDIR}ft_action_if_alive_bonus.c \
${SRCSDIR}ft_print_msg_bonus.c \
${SRCSDIR}ft_is_full_or_dead_bonus.c \
${SRCSDIR}ft_grab_right_bonus.c \
${SRCSDIR}ft_grab_left_bonus.c \
${SRCSDIR}ft_usleep_bonus.c \
${SRCSDIR}ft_sleeping_bonus.c \
${SRCSDIR}ft_die_alone_bonus.c \
${SRCSDIR}ft_eating_bonus.c \
${SRCSDIR}ft_thinking_bonus.c \
${SRCSDIR}ft_routine_bonus.c \
${SRCSDIR}ft_kill_them_all_bonus.c \
${SRCSDIR}ft_unset_philos_bonus.c \
${SRCSDIR}ft_put_processes_on_routine_bonus.c \
${SRCSDIR}ft_soul_waiting_bonus.c \
${SRCSDIR}ft_wait_last_plate_bonus.c \
${SRCSDIR}ft_philo_bonus.c \
${SRCSDIR}ft_init_tab_philo_bonus.c \
${SRCSDIR}ft_sem_close_bonus.c \
${SRCSDIR}ft_unset_context_bonus.c

HEADERDIR = includes/

HEADERBONUS = philo_bonus.h

OBJBONUS = $(SRCSBONUS:.c=.o)

CC = clang

FLAGS = -Wall -Wextra -Werror -g3

IFLAG = -I$(HEADERDIR)

all : $(BINARYBONUS)

$(BINARYBONUS): libphilo_bonus.a
	-@$(CC) $(FLAGS) main.c -lpthread $(IFLAG) -L. -lphilo_bonus -o $(BINARYBONUS)

%.o : %.c
	-@$(CC) $(FLAGS) $(IFLAG) -o $@ -c $^

libphilo_bonus.a : $(OBJBONUS) $(HEADERDIR)$(HEADERBONUS)
	-@ar -rcs $(NAME) $^

clean :
	-@rm -f $(OBJBONUS)

fclean : clean
	-@rm -f $(NAME)
	-@rm -f $(BINARYBONUS)

re : fclean all

.PHONY : all clean fclean re
