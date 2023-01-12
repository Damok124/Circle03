/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullphilo_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:34:45 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/08 23:34:30 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

// typedef struct s_context {
// 	int				members;
// 	int				life_time;
// 	int				meal_time;
// 	int				rest_time;
// 	int				meals_max;
// }					t_context;

// typedef struct s_philo {
// 	pthread_t		philo;
// 	int				id;
// 	pthread_mutex_t	life;
// 	int				alive;
// 	int				meals;
// 	long int		deadline;
// 	struct timeval	start_time;
// 	pthread_mutex_t	right;
// 	pthread_mutex_t	*left;
// 	pthread_mutex_t	*mut_printf;
// 	t_context		context;
// }					t_philo;

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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi_safe(const char *nptr, int *check)
{
	long int	i;
	int			k;

	i = 0;
	k = 0;
	if (nptr)
	{
		while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
			nptr++;
		if (*nptr == '-')
			k = -1;
		else if (*nptr == '+' || (*nptr >= '0' && *nptr <= '9'))
			k = 1;
		if (*nptr == '-' || *nptr == '+')
			nptr++;
		while (*nptr && *nptr >= '0' && *nptr <= '9')
		{
			i *= 10;
			i += *nptr - '0';
			if ((k * i) > INT_MAX || (k * i) < INT_MIN)
				*check = 0;
			nptr++;
		}
	}
	return (i * k);
}

void	ft_true_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static char	*ft_printitoa(char *a, int n, size_t i)
{
	int	j;

	j = 0;
	a[i] = '\0';
	i--;
	if (n == 0)
		a[i] = 0 + '0';
	else
	{
		while (i != 0)
		{
			j = n % 10;
			if (j < 0)
				j *= -1;
			a[i] = (j + '0');
			n /= 10;
			i--;
		}
		if (n <= 0)
			a[0] = '-';
		else
			a[i] = n + '0';
	}
	return (a);
}

static size_t	ft_intlen(int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
		i++;
	if (n == 0)
		return (1);
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*a;
	int		i;

	i = ft_intlen(n);
	a = malloc(sizeof(char) * i + 1);
	if (!a)
		return (NULL);
	a = ft_printitoa(a, n, i);
	return (a);
}

int	ft_check_arg_positive(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		return (0);
	while (ft_isdigit(arg[i]))
		i++;
	if (arg[i])
		return (0);
	return (1);
}

int	ft_check_arg_overflow(char *arg)
{
	int	check;

	check = 1;
	ft_atoi_safe(arg, &check);
	if (!check)
		return (0);
	return (1);
}

int	ft_check_args(int ac, char **argv)
{
	int	check;
	int	i;

	check = 1;
	i = 0;
	if (ac < 4 || ac > 5)
		return (0);
	while (argv && argv[i])
	{
		if (!ft_check_arg_positive(argv[i]) || !ft_check_arg_overflow(argv[i]))
			return (0);
		if (ft_atoi_safe(argv[0], &check) < 1)
			return (0);
		i++;
	}
	return (1);
}

t_context	*ft_init_context_sem(t_context *context)
{
	int	meals;

	meals = (context->members / 2);
	context->sem_forks = sem_open("sem_forks", O_CREAT, 0600, context->members);
	if (context->sem_forks == SEM_FAILED)
		return (NULL);
	sem_unlink("sem_forks");
	context->sem_printf = sem_open("sem_printf", O_CREAT, 0600, 1);
	if (context->sem_printf == SEM_FAILED)
		return (NULL);
	sem_unlink("sem_printf");
	context->sem_over = sem_open("sem_over", O_CREAT, 0600, 0);
	if (context->sem_over == SEM_FAILED)
		return (NULL);
	sem_unlink("sem_over");
	context->sem_full = sem_open("sem_full", O_CREAT, 0600, 0);
	if (context->sem_full == SEM_FAILED)
		return (NULL);
	sem_unlink("sem_full");
	context->sem_meal = sem_open("sem_meal", O_CREAT, 0600, meals);
	if (context->sem_full == SEM_FAILED)
		return (NULL);
	sem_unlink("sem_meal");
	return (context);
}

void ft_init_context(t_context *context, char **argv, int ac)
{
	int			check;

	check = 1;
	context->members = ft_atoi_safe(argv[0], &check);
	context->life_time = ft_atoi_safe(argv[1], &check);
	context->meal_time = ft_atoi_safe(argv[2], &check);
	context->rest_time = ft_atoi_safe(argv[3], &check);
	if (ac == 5)
		context->meals_max = ft_atoi_safe(argv[4], &check);
	else
		context->meals_max = -1;
	context = ft_init_context_sem(context);
}

int	ft_get_chrono(struct timeval start)
{
	struct timeval	result;
	struct timeval	current;
	int				time;

	time = 0;
	gettimeofday(&current, NULL);
	result.tv_sec = current.tv_sec - start.tv_sec;
	result.tv_usec = current.tv_usec - start.tv_usec;
	time = (result.tv_sec * 1000) + (result.tv_usec / 1000);
	return (time);
}

int	ft_is_expired(t_philo *philo)
{
	sem_wait(philo->life);
	if (philo->deadline < ft_get_chrono(philo->start_time))
	{
		sem_post(philo->life);
		return (1);
	}
	sem_post(philo->life);
	return (0);
}

void	ft_print_last_msg(t_philo *philo, char *msg)////////////////////////
{
	int	time;

	time = ft_get_chrono(philo->start_time);
	sem_wait(philo->context->sem_printf);
	printf("%i %i %s\n", time, philo->id, msg);
	sem_post(philo->context->sem_over);
	while (1)
		usleep(1000000);
	//sem_post(philo->context->sem_printf);////////////////////////////////
}

int	ft_action_if_alive(t_philo *philo)
{
	if (philo->deadline < ft_get_chrono(philo->start_time))
	{
		ft_print_last_msg(philo, "died");
		return (0);
	}

	return (1);
}

void	ft_print_msg(t_philo *philo, char *msg)
{
	int	time;

	if (ft_action_if_alive(philo))
	{
		sem_wait(philo->context->sem_printf);
		time = ft_get_chrono(philo->start_time);
		printf("%i %i %s\n", time, philo->id, msg);
		sem_post(philo->context->sem_printf);
	}
}

int	ft_is_full_or_dead(t_philo *philo)
{
	sem_wait(philo->life);
	if (philo->alive && (philo->context->meals_max > 0 \
		&& philo->meals >= philo->context->meals_max))
	{
		sem_post(philo->life);
		return (2);
	}
	if (!philo->alive)
	{
		sem_post(philo->life);
		return (1);
	}
	if (philo->deadline < ft_get_chrono(philo->start_time))
	{
		sem_post(philo->life);
		return (1);
	}
	sem_post(philo->life);
	return (0);
}

void	ft_grab_right(t_philo *philo, int *forks)///////////////////////////
{
	sem_wait(philo->context->sem_forks);
	if (ft_action_if_alive(philo))
		ft_print_msg(philo, "has taken a fork");
	*forks += 1;
}

void	ft_grab_left(t_philo *philo, int *forks)////////////////////////////
{
	sem_wait(philo->context->sem_forks);
	if (ft_action_if_alive(philo))
		ft_print_msg(philo, "has taken a fork");
	*forks += 2;
}

void	ft_usleep(t_philo *philo, int timer)
{
	long int	rest;

	rest = (long int)timer;
	if ((long int)philo->deadline \
		< (long int)ft_get_chrono(philo->start_time) + rest)
		rest = (long int)philo->deadline \
			- (long int)ft_get_chrono(philo->start_time);
	if (rest < 0)
		rest = 0;
	usleep(rest * 1000);
	if (!ft_action_if_alive(philo))
		usleep(1000000);
}

void	ft_sleeping(t_philo *philo, int *forks)
{
	if (ft_action_if_alive(philo))
	{
		if (*forks > 2)
		{
			sem_post(philo->context->sem_forks);
			*forks -= 2;
		}
		if (*forks > 0)
		{
			sem_post(philo->context->sem_forks);
			*forks -= 1;
		}
			ft_print_msg(philo, "is sleeping");
			ft_usleep(philo, philo->context->rest_time);
	}
	else
		usleep(1000000);
}

void	ft_die_alone(t_philo *philo)
{
	while (ft_action_if_alive(philo))
		usleep(100);
}

int	ft_eating(t_philo *philo)
{
	int	forks;

	forks = 0;
	sem_wait(philo->context->sem_meal);
	ft_grab_right(philo, &forks);
	if (philo->context->members > 1)
		ft_grab_left(philo, &forks);
	else
		ft_die_alone(philo);
	if (ft_action_if_alive(philo))
		sem_post(philo->context->sem_meal);
	if (ft_action_if_alive(philo) && philo->context->members > 1)
	{
		sem_wait(philo->life);
		philo->deadline = (long int)ft_get_chrono(philo->start_time) \
			+ (long int)philo->context->life_time + 1;
		sem_post(philo->life);
		ft_print_msg(philo, "is eating");
		ft_usleep(philo, philo->context->meal_time);
		sem_wait(philo->life);
		philo->meals++;
		if (philo->meals == philo->context->meals_max)
			sem_post(philo->context->sem_full);
		sem_post(philo->life);
	}
	return (forks);
}

void	ft_thinking(t_philo *philo)
{
	int	timer;

	timer = philo->context->meal_time - philo->context->rest_time;
	if (ft_action_if_alive(philo))
	{
		ft_print_msg(philo, "is thinking");
		if (philo->context->rest_time <= philo->context->meal_time)
		{
			ft_usleep(philo, timer + 1);
		}
	}
}

void	ft_routine(void *arg)
{
	t_philo	*philo;
	int		forks;

	forks = 0;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0 || (philo->id % 2 != 0 \
		&& philo->id == (philo->context->members)))
	{
		ft_print_msg(philo, "is thinking");
		ft_usleep(philo, philo->context->meal_time);
	}
	while (ft_action_if_alive(philo))
	{
		forks = ft_eating(philo);
		if (philo->context->members == 1)
			usleep(1000);
		ft_sleeping(philo, &forks);
		if (philo->context->members == 1)
			usleep(1000);
		ft_thinking(philo);
	}
	while (1)
		usleep(1000000);
}

void	ft_kill_them_all(t_philo *tab)
{
	int	i;

	i = -1;
	while (++i < tab->context->members)
		kill(tab[i].pid, SIGKILL);
}

void	ft_unset_philos(t_philo *tab)
{
	int	i;

	i = tab->context->members;
	while (--i >= 0)
		sem_close(tab[i].life);
	ft_true_free((void **)&tab);
}

// void	ft_put_thread_on_routine(t_philo *tab)
// {
// 	struct timeval	beginning;
// 	int				i;

// 	i = -1;
// 	gettimeofday(&beginning, NULL);
// 	while (++i < tab->context->members)
// 	{
// 		tab[i].start_time = beginning;
// 		pthread_create(&tab[i].philo, NULL, ft_routine, (void *)&tab[i]);
// 	}
// }

void	ft_put_processes_on_routine(t_philo *tab, t_context *context)
{
	struct timeval	beginning;
	int				i;

	i = -1;
	gettimeofday(&beginning, NULL);
	while (++i < context->members)
	{
		tab[i].id = i + 1;
		tab[i].start_time = beginning;
		tab[i].pid = fork();
		if (!tab[i].pid)
			ft_routine(&tab[i]);
	}
}

// void	ft_share_printf_mutex(t_philo *philos, pthread_mutex_t *mut_printf)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < philos->context.members)
// 		philos[i].mut_printf = mut_printf;
// }

void	ft_soul_taking(t_philo *philo)
{
	// int		i;

	// i = 0;
	// while (!ft_is_full_or_dead(&philo[i]))
	// {
	// 	i = (i + 1) % philo->context->members;
	// 	usleep(10);
	// }
	sem_wait(philo->context->sem_over);
	// if (ft_is_expired(&philo[i]))
	// 	ft_print_last_msg(&philo[i], "died");
	// i = 0;
	// while (i < philo->context->members)
	// {
	// 	sem_wait(philo[i].life);
	// 	philo[i].alive = 0;
	// 	sem_post(philo[i].life);
	// 	i++;
	// }
}

void	ft_wait_last_plate(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->context->members)
	{
		sem_wait(philo->context->sem_full);
		i++;
	}
	usleep(200);
	sem_post(philo->context->sem_over);
	while (1)
		usleep(100000);
}

void	ft_philo(t_philo *philos, t_context *context)
{
	pid_t	full_checker;
	//pthread_mutex_t	mut_printf;

	//pthread_mutex_init(&mut_printf, NULL);
	//ft_share_printf_mutex(philos, &mut_printf);
	full_checker = -1;
	if (philos->context->meals_max)
	{
		// ft_put_thread_on_routine(philos);
		ft_put_processes_on_routine(philos, context);
		if (philos->context->meals_max > 0)
		{
			full_checker = fork();
			if (!full_checker)
				ft_wait_last_plate(philos);
		}
		ft_soul_taking(philos);////////////////////////////
		if (full_checker > -1)
			kill(full_checker, SIGKILL);
		ft_kill_them_all(philos);
	}
	// pthread_mutex_destroy(&mut_printf);
	ft_unset_philos(philos);
}

// void	ft_init_mutexes(t_philo *tab)
// {
// 	int	i;

// 	i = -1;
// 	while (tab && ++i < tab->context.members)
// 	{
// 		pthread_mutex_init(&tab[i].life, NULL);
// 		pthread_mutex_init(&tab[i].right, NULL);
// 		tab->left = NULL;
// 	}
// }

// t_philo	*ft_init_tab_philo(t_context context)
// {
// 	t_philo	*tab;
// 	int		i;

// 	i = -1;
// 	tab = (t_philo *)malloc(sizeof(t_philo) * context.members);
// 	if (!tab)
// 		return (NULL);
// 	while (++i < context.members)
// 	{
// 		tab[i].id = i + 1;
// 		tab[i].alive = 1;
// 		tab[i].context = context;
// 		tab[i].deadline = (long int)context.life_time;
// 		tab[i].meals = 0;
// 		tab[i].left = NULL;
// 	}
// 	ft_init_mutexes(tab);
// 	if (context.members > 1)
// 	{
// 		tab[--i].left = &tab[0].right;
// 		while (--i >= 0)
// 			tab[i].left = &tab[i + 1].right;
// 	}
// 	return (tab);
// }

t_philo	*ft_init_tab_philo(t_context *context)
{
	t_philo	*tab;
	char	*sem_name;
	int		i;

	i = -1;
	if (!context)
		return (NULL);
	tab = (t_philo *)malloc(sizeof(t_philo) * context->members);
	if (!tab)
		return (NULL);
	sem_name = NULL;
	while (context && ++i < context->members)
	{
		tab[i].pid = 0;
		tab[i].id = i + 1;
		sem_name = ft_itoa(i);
		tab[i].life = sem_open(sem_name, O_CREAT, 0600, 1);
		sem_unlink(sem_name);
		ft_true_free((void **)&sem_name);
		tab[i].alive = 1;
		tab[i].context = context;
		tab[i].deadline = (long int)context->life_time;
		tab[i].meals = 0;
	}
	return (tab);
}

void	ft_sem_close(sem_t* sem, char *sem_name)
{
	if (sem)
	{
		sem_close(sem);
		sem_unlink(sem_name);
	}
}

void	ft_unset_context(t_context *context)
{
	ft_sem_close(context->sem_meal, "sem_meal");
	ft_sem_close(context->sem_over, "sem_over");
	ft_sem_close(context->sem_full, "sem_full");
	ft_sem_close(context->sem_forks, "sem_forks");
	ft_sem_close(context->sem_printf, "sem_printf");
	ft_true_free((void **)&context);
}

int	main(int ac, char **argv)
{
	t_context	*context;
	t_philo		*philos;

	philos = NULL;
	context = (t_context *)malloc(sizeof(t_context));
	if (!context)
		return (0);
	if (ft_check_args(ac - 1, argv + 1))
	{
		ft_init_context(context, argv + 1, ac -1);
		philos = ft_init_tab_philo(context);
		if (philos)
			ft_philo(philos, context);
		else
			printf("FAILURE\n");
	}
	else
		printf("Wrong arguments.\n");
	ft_unset_context(context);
	return (EXIT_SUCCESS);
}
