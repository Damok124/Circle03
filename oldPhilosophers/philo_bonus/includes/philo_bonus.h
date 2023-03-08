/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:33:15 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/18 12:09:22 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>

typedef struct s_context {
	sem_t			*sem_forks;
	sem_t			*sem_printf;
	sem_t			*sem_over;
	sem_t			*sem_full;
	sem_t			*sem_meal;
	int				members;
	int				life_time;
	int				meal_time;
	int				rest_time;
	int				meals_max;
}					t_context;

typedef struct s_philo {
	pid_t			pid;
	int				id;
	sem_t			*life;
	int				alive;
	int				meals;
	long int		deadline;
	struct timeval	start_time;
	t_context		*context;
}					t_philo;

/////////////////////////
//	UTILS
/////////////////////////
int			ft_isdigit(int c);
int			ft_atoi_safe(const char *nptr, int *check);
char		*ft_itoa(int n);
int			ft_get_chrono(struct timeval start);
void		ft_print_last_msg(t_philo *philo, char *msg);
void		ft_print_msg(t_philo *philo, char *msg);
void		ft_true_free(void **ptr);
void		ft_sem_close(sem_t *sem, char *sem_name);

/////////////////////////
//	PARSERS
/////////////////////////
int			ft_check_arg_positive(char *arg);
int			ft_check_arg_overflow(char *arg);
int			ft_check_args(int ac, char **argv);

/////////////////////////
//	CHECKERS
/////////////////////////
int			ft_is_expired(t_philo *philo);
int			ft_is_full_or_dead(t_philo *philo);

/////////////////////////
//	INITIALIZERS
/////////////////////////
t_context	*ft_init_context_sem(t_context *context);
void		ft_init_context(t_context *context, char **argv, int ac);
t_philo		*ft_init_tab_philo(t_context *context);

/////////////////////////
//	CORE
/////////////////////////
int			ft_action_if_alive(t_philo *philo);
void		ft_grab_right(t_philo *philo, int *forks);
void		ft_grab_left(t_philo *philo, int *forks);
void		ft_usleep(t_philo *philo, int timer);
void		ft_sleeping(t_philo *philo, int *forks);
void		ft_die_alone(t_philo *philo);
int			ft_eating(t_philo *philo);
void		ft_thinking(t_philo *philo);
void		ft_routine(void *arg);
void		ft_put_processes_on_routine(t_philo *tab, t_context *context);
void		ft_soul_waiting(t_philo *philo);
void		ft_wait_last_plate(t_philo *philo);
void		ft_philo(t_philo *philos, t_context *context);

/////////////////////////
//	EXIT
/////////////////////////
void		ft_kill_them_all(t_philo *tab);
void		ft_unset_philos(t_philo *tab);
void		ft_unset_context(t_context *context);

#endif
