/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullphilo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:34:45 by zharzi            #+#    #+#             */
/*   Updated: 2022/12/24 11:18:35 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_context {
	int				members;
	int				life_time;
	int				meal_time;
	int				rest_time;
	int				meals_max;
}					t_context;

typedef struct s_philo {
	pthread_t		philo;
	int				id;
	pthread_mutex_t	life;
	int				alive;
	int				meals;
	long int		deadline;
	struct timeval	start_time;
	pthread_mutex_t	right;
	pthread_mutex_t	*left;
	pthread_mutex_t	*mut_printf;
	t_context		context;
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

t_context	ft_init_context(char **argv, int ac)
{
	t_context	context;
	int			check;

	check = 1;
	context.members = ft_atoi_safe(argv[0], &check);
	context.life_time = ft_atoi_safe(argv[1], &check);
	context.meal_time = ft_atoi_safe(argv[2], &check);
	context.rest_time = ft_atoi_safe(argv[3], &check);
	if (ac == 5)
		context.meals_max = ft_atoi_safe(argv[4], &check);
	else
		context.meals_max = -1;
	return (context);
}

int	ft_get_chrono(struct timeval start)
{
	struct timeval	result;
	struct timeval	actual;
	int				time;

	time = 0;
	gettimeofday(&actual, NULL);
	result.tv_sec = actual.tv_sec - start.tv_sec;
	result.tv_usec = actual.tv_usec - start.tv_usec;
	time = (result.tv_sec * 1000) + (result.tv_usec / 1000);
	return (time);
}

int	ft_is_expired(t_philo *philo)
{
	pthread_mutex_lock(&philo->life);
	if (philo->deadline < ft_get_chrono(philo->start_time))
	{
		pthread_mutex_unlock(&philo->life);
		return (1);
	}
	pthread_mutex_unlock(&philo->life);
	return (0);
}

int	ft_is_full_or_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->life);
	if (philo->alive && (philo->context.meals_max > 0 \
		&& philo->meals >= philo->context.meals_max))
	{
		pthread_mutex_unlock(&philo->life);
		return (2);
	}
	if (!philo->alive)
	{
		pthread_mutex_unlock(&philo->life);
		return (1);
	}
	if (philo->deadline < ft_get_chrono(philo->start_time))
	{
		pthread_mutex_unlock(&philo->life);
		return (1);
	}
	pthread_mutex_unlock(&philo->life);
	return (0);
}

void	ft_print_msg(t_philo *philo, char *msg)
{
	int	time;

	if (!ft_is_full_or_dead(philo))
	{
		pthread_mutex_lock(philo->mut_printf);
		time = ft_get_chrono(philo->start_time);
		printf("%i %i %s\n", time, philo->id, msg);
		pthread_mutex_unlock(philo->mut_printf);
	}
}

void	ft_print_last_msg(t_philo *philo, char *msg)
{
	int	time;

	time = ft_get_chrono(philo->start_time);
	pthread_mutex_lock(philo->mut_printf);
	printf("%i %i %s\n", time, philo->id, msg);
	pthread_mutex_unlock(philo->mut_printf);
}

void	ft_grab_right(t_philo *philo, int *forks)
{
	pthread_mutex_lock(&philo->right);
	ft_print_msg(philo, "has taken a fork");
	*forks += 1;
}

void	ft_grab_left(t_philo *philo, int *forks)
{
	pthread_mutex_lock(philo->left);
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
	usleep((rest + 1) * 1000);
}

void	ft_sleeping(t_philo *philo, int *forks)
{
	if (*forks > 2)
	{
		pthread_mutex_unlock(philo->left);
		*forks -= 2;
	}
	if (*forks > 0)
	{
		pthread_mutex_unlock(&philo->right);
		*forks -= 1;
	}
	if (!ft_is_full_or_dead(philo))
	{
		ft_print_msg(philo, "is sleeping");
		ft_usleep(philo, philo->context.rest_time);
	}
}

int	ft_eating(t_philo *philo)
{
	int	forks;

	forks = 0;
	ft_grab_right(philo, &forks);
	if (philo->context.members > 1)
		ft_grab_left(philo, &forks);
	else
		ft_usleep(philo, philo->context.life_time \
			- ft_get_chrono(philo->start_time));
	if (!ft_is_full_or_dead(philo) && philo->context.members > 1)
	{
		pthread_mutex_lock(&philo->life);
		philo->deadline = (long int)ft_get_chrono(philo->start_time) \
			+ (long int)philo->context.life_time + 1;
		pthread_mutex_unlock(&philo->life);
		ft_print_msg(philo, "is eating");
		ft_usleep(philo, philo->context.meal_time);
		pthread_mutex_lock(&philo->life);
		philo->meals++;
		pthread_mutex_unlock(&philo->life);
	}
	return (forks);
}

void	ft_thinking(t_philo *philo)
{
	if (!ft_is_full_or_dead(philo))
	{
		ft_print_msg(philo, "is thinking");
	}
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	int		forks;

	forks = 0;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0 || (philo->id % 2 != 0 \
		&& philo->id == (philo->context.members)))
	{
		ft_print_msg(philo, "is thinking");
		usleep(6000);
	}
	while (!ft_is_full_or_dead(philo))
	{
		forks = ft_eating(philo);
		if (philo->context.members == 1)
			usleep(1000);
		ft_sleeping(philo, &forks);
		if (philo->context.members == 1)
			usleep(1000);
		ft_thinking(philo);
	}
	return (NULL);
}

void	ft_join_them_all(t_philo *tab)
{
	int	i;

	i = -1;
	while (++i < tab->context.members)
		pthread_join(tab[i].philo, NULL);
}

void	ft_unset_philos(t_philo *tab)
{
	int	i;

	i = tab->context.members;
	while (--i >= 0)
	{
		pthread_mutex_destroy(&tab[i].right);
		pthread_mutex_destroy(&tab[i].life);
		tab[i].left = NULL;
	}
	ft_true_free((void **)&tab);
}

void	ft_put_thread_on_routine(t_philo *tab)
{
	struct timeval	beginning;
	int				i;

	i = -1;
	gettimeofday(&beginning, NULL);
	while (++i < tab->context.members)
	{
		tab[i].start_time = beginning;
		pthread_create(&tab[i].philo, NULL, ft_routine, (void *)&tab[i]);
	}
}

void	ft_share_printf_mutex(t_philo *philos, pthread_mutex_t *mut_printf)
{
	int	i;

	i = -1;
	while (++i < philos->context.members)
		philos[i].mut_printf = mut_printf;
}

void	*ft_soul_taking(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	while (!ft_is_full_or_dead(&philo[i]))
	{
		i = (i + 1) % philo->context.members;
		usleep(10);
	}
	if (ft_is_expired(&philo[i]))
		ft_print_last_msg(&philo[i], "died");
	i = 0;
	while (i < philo->context.members)
	{
		pthread_mutex_lock(&philo[i].life);
			philo[i].alive = 0;
		pthread_mutex_unlock(&philo[i].life);
		i++;
	}
	return (NULL);
}

void	ft_philo(t_philo *philos)
{
	pthread_mutex_t	mut_printf;

	pthread_mutex_init(&mut_printf, NULL);
	ft_share_printf_mutex(philos, &mut_printf);
	if (philos->context.meals_max)
	{
		ft_put_thread_on_routine(philos);
		ft_soul_taking(philos);
		ft_join_them_all(philos);
	}
	pthread_mutex_destroy(&mut_printf);
	ft_unset_philos(philos);
}

void	ft_init_mutexes(t_philo *tab)
{
	int	i;

	i = -1;
	while (tab && ++i < tab->context.members)
	{
		pthread_mutex_init(&tab[i].life, NULL);
		pthread_mutex_init(&tab[i].right, NULL);
		tab->left = NULL;
	}
}

t_philo	*ft_init_tab_philo(t_context context)
{
	t_philo	*tab;
	int		i;

	i = -1;
	tab = (t_philo *)malloc(sizeof(t_philo) * context.members);
	if (!tab)
		return (NULL);
	while (++i < context.members)
	{
		tab[i].id = i + 1;
		tab[i].alive = 1;
		tab[i].context = context;
		tab[i].deadline = (long int)context.life_time;
		tab[i].meals = 0;
		tab[i].left = NULL;
	}
	ft_init_mutexes(tab);
	if (context.members > 1)
	{
		tab[--i].left = &tab[0].right;
		while (--i >= 0)
			tab[i].left = &tab[i + 1].right;
	}
	return (tab);
}

int	main(int ac, char **argv)
{
	t_context	context;
	t_philo		*philos;

	philos = NULL;
	if (ft_check_args(ac - 1, argv + 1))
	{
		context = ft_init_context(argv + 1, ac -1);
		philos = ft_init_tab_philo(context);
		if (philos)
			ft_philo(philos);
		else
			printf("FAILURE\n");
	}
	else
		printf("Wrong arguments.\n");
	return (EXIT_SUCCESS);
}
