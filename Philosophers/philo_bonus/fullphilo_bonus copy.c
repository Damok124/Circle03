/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullphilo_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:34:45 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/05 10:15:44 by zharzi           ###   ########.fr       */
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (!str1 && str2 && str2[0])
			return (-str2[0]);
		else if (str1 && !str2 && str1[0])
			return (str1[0]);
		else if ((!str1 && !str2) || (str1[i] == '\0' && str2[i] == '\0'))
			return (0);
		else if (str1[i] - str2[i] != 0)
			return (str1[i] - str2[i]);
		else
			i++;
	}
	return (0);
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

void	ft_usleep(t_philo *philo, int timer)
{
	long int	rest;

	rest = (long int)timer;
	sem_wait(philo->life);
	if ((long int)philo->deadline < (long int)ft_get_chrono(philo->start_time) + rest)
		rest = (long int)philo->deadline - (long int)ft_get_chrono(philo->start_time);
	sem_post(philo->life);
	if (rest < 0)
		rest = 0;
	usleep((rest + 1) * 1000);
	(void)philo;
}

/*
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
*/

void	ft_print_msg(t_philo *philo, char *msg)
{
	int	time;

	// if (!ft_is_full_or_dead(philo))
	// {
		// pthread_mutex_lock(philo->mut_printf);
		sem_wait(philo->context->sem_printf);
		time = ft_get_chrono(philo->start_time);
		printf("%i %i %s\n", time, philo->id, msg);
		if (ft_strncmp("died", msg, 5))
			sem_post(philo->context->sem_printf);
		else
		{
			sem_post(philo->context->sem_over);
			while (1)
				usleep(100000);
		}
		// pthread_mutex_unlock(philo->mut_printf);
	// }
}

void	ft_sleeping(t_philo *philo)
{
	// if (*forks > 2)
	// {
		// pthread_mutex_unlock(philo->left);
		// *forks -= 2;
	// }
	// if (*forks > 0)
	// {
		// pthread_mutex_unlock(&philo->right);
		// *forks -= 1;
	// }
	sem_post(philo->context->sem_forks);
	sem_post(philo->context->sem_forks);
	// if (!ft_is_full_or_dead(philo))
	// {
		ft_print_msg(philo, "is sleeping");
		ft_usleep(philo, philo->context->rest_time);
	// }
}

void	ft_eating(t_philo *philo)
{
	// ft_grab_right(philo, &forks);
	sem_wait(philo->context->sem_meal);////////////////////////
	sem_wait(philo->context->sem_forks);
	ft_print_msg(philo, "has taken a fork");
	sem_wait(philo->context->sem_forks);
	ft_print_msg(philo, "has taken a fork");
	sem_post(philo->context->sem_meal);/////////////////////////////
		// ft_grab_left(philo, &forks);
		// ft_usleep(philo, philo->context->life_time
		// 	- ft_get_chrono(philo->start_time));
	// if (!ft_is_full_or_dead(philo) && philo->context.members > 1)
	// if (philo->context->members > 1)
	// {
		// pthread_mutex_lock(&philo->life);
		sem_wait(philo->life);
		philo->deadline = (long int)ft_get_chrono(philo->start_time) \
			+ (long int)philo->context->life_time + 1;
		sem_post(philo->life);
		// pthread_mutex_unlock(&philo->life);
		ft_print_msg(philo, "is eating");
		ft_usleep(philo, philo->context->meal_time);
		// pthread_mutex_lock(&philo->life);
		philo->meals++;
		if (philo->meals == philo->context->meals_max)
			sem_post(philo->context->sem_full);
		// pthread_mutex_unlock(&philo->life);
	// }
	// return (forks);
}

void	ft_thinking(t_philo *philo)
{
	// if (!ft_is_full_or_dead(philo))
	// {
		ft_print_msg(philo, "is thinking");
		ft_usleep(philo, 2000);
	// }
}

/*

void	ft_join_them_all(t_philo *tab)
{
	int	i;

	i = -1;
	while (++i < tab->context.members)
		pthread_join(tab[i].philo, NULL);
}


void	ft_share_printf_mutex(t_philo *philos, pthread_mutex_t *mut_printf)
{
	int	i;

	i = -1;
	while (++i < philos->context.members)
		philos[i].mut_printf = mut_printf;
}
*/
/*
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
*/

void	ft_unset_philos(t_philo *tab)
{
	char	*sem_name;
	int		i;

	i = tab->context->members;
	sem_name = NULL;
	while (--i >= 0)
	{
		sem_close(tab[i].life);
		sem_name = ft_itoa(i);
		sem_unlink(sem_name);
		ft_true_free((void **)&sem_name);
	}
	ft_true_free((void **)&tab);
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

int	ft_is_alive(t_philo *philo)
{
	int	n;

	sem_wait(philo->life);
	n = philo->alive;
	sem_post(philo->life);
	return (n);
}

void	ft_routine(t_philo *philo, t_context *context)
{
	if (philo->id % 2 == 0 || (philo->id % 2 != 0 \
		&& philo->id == (context->members)))
	{
		ft_print_msg(philo, "is thinking");
		// ft_usleep(philo, philo->context->meal_time);
		ft_usleep(philo, philo->context->meal_time / 4);
	}
	while (ft_is_alive(philo))
	{
		if (ft_is_alive(philo))
			ft_eating(philo);
		// if (context->members == 1)
		// 	usleep(1000);
		if (ft_is_alive(philo))
			ft_sleeping(philo);
		// if (context->members == 1)
		// 	usleep(1000);
		if (ft_is_alive(philo))
			ft_thinking(philo);
	}
	while (1)
		usleep(100000);
}

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
			ft_routine(&tab[i], context);
	}
}

void	ft_decimation(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->context->members)
	{
		// sem_wait(philos[i].life);
		// philos[i].alive = 0;
		// sem_post(philos[i].life);
		kill(philos[i].pid, SIGKILL);
	}
}

void	ft_waiting_sated_philos(t_context *context)
{
	int	i;

	i = context->members;
	while (i)
	{
		sem_wait(context->sem_full);
		i--;
	}
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

void	ft_death_parade(t_philo *philo, pid_t *death)
{
	int	i;

	i = 0;
	*death = fork();
	if (!death)
	{
		while (!ft_is_expired(&philo[i]))
		{
			i = (i + 1) % philo->context->members;
			usleep(10);
		}
		if (ft_is_expired(&philo[i]))
			ft_print_msg(&philo[i], "died");
		i = 0;
		while (i < philo->context->members)
		{
			sem_wait(philo[i].life);
			philo[i].alive = 0;
			sem_post(philo[i].life);
			i++;
		}
		while (1)
			usleep(100000);
	}
}

void	ft_philo(t_philo *philos, t_context *context, pid_t filled, pid_t death)
{
	// pid_t	filled;

	// filled = -1;
	if (context->meals_max)
	{
		ft_put_processes_on_routine(philos, context);
		if (context->meals_max > 0)
		{
			ft_death_parade(philos, &death);
			usleep(50000);
			filled = fork();
			if (!filled)
			{
				ft_waiting_sated_philos(context);
				sem_post(context->sem_over);
				while (1)
					usleep(100000);
			}
		}
		sem_wait(context->sem_over);
		kill(death, SIGKILL);
		kill(filled, SIGKILL);
		ft_decimation(philos);
	}
	ft_unset_philos(philos);
	ft_unset_context(context);
}

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
		sem_unlink(sem_name);
		tab[i].life = sem_open(sem_name, O_CREAT, 0600, 1);
		ft_true_free((void **)&sem_name);
		tab[i].alive = 1;
		tab[i].context = context;
		tab[i].deadline = (long int)context->life_time;
		tab[i].meals = 0;
	}
	return (tab);
}

t_context	*ft_init_context_sem(t_context *context)
{
	int	meals;

	meals = (context->members / 2);
	context->sem_forks = sem_open("sem_forks", O_CREAT, 0600, context->members);
	if (context->sem_forks == SEM_FAILED)
		return (NULL);
	context->sem_printf = sem_open("sem_printf", O_CREAT, 0600, 1);
	if (context->sem_printf == SEM_FAILED)
	{
		ft_sem_close(context->sem_forks, "sem_forks");
		return (NULL);
	}
	context->sem_over = sem_open("sem_over", O_CREAT, 0600, 0);
	if (context->sem_over == SEM_FAILED)
	{
		ft_sem_close(context->sem_forks, "sem_forks");
		ft_sem_close(context->sem_printf, "sem_printf");
		return (NULL);
	}
	context->sem_full = sem_open("sem_full", O_CREAT, 0600, 0);
	if (context->sem_full == SEM_FAILED)
	{
		ft_sem_close(context->sem_forks, "sem_forks");
		ft_sem_close(context->sem_printf, "sem_printf");
		ft_sem_close(context->sem_over, "sem_over");
		return (NULL);
	}
	context->sem_meal = sem_open("sem_meal", O_CREAT, 0600, meals);
	if (context->sem_full == SEM_FAILED)
	{
		ft_sem_close(context->sem_forks, "sem_forks");
		ft_sem_close(context->sem_printf, "sem_printf");
		ft_sem_close(context->sem_over, "sem_over");
		ft_sem_close(context->sem_full, "sem_full");
		return (NULL);
	}
	return (context);
}

void	ft_remove_artifacts(void)
{
	sem_unlink("sem_meal");
	sem_unlink("sem_over");
	sem_unlink("sem_full");
	sem_unlink("sem_forks");
	sem_unlink("sem_printf");
}

t_context	*ft_init_context(char **argv, int ac)
{
	t_context	*context;
	int			check;

	check = 1;
	ft_remove_artifacts();
	context = (t_context *)malloc(sizeof(t_context));
	if (!context)
		return (NULL);
	context->members = ft_atoi_safe(argv[0], &check);
	context->life_time = ft_atoi_safe(argv[1], &check);
	context->meal_time = ft_atoi_safe(argv[2], &check);
	context->rest_time = ft_atoi_safe(argv[3], &check);
	if (ac == 5)
		context->meals_max = ft_atoi_safe(argv[4], &check);
	else
		context->meals_max = -1;
	context = ft_init_context_sem(context);///////////////////////a tester
	return (context);
}

int	main(int ac, char **argv)
{
	t_context	*context;
	t_philo		*philos;

	philos = NULL;
	context = NULL;
	if (ft_check_args(ac - 1, argv + 1))
	{
		context = ft_init_context(argv + 1, ac -1);
		philos = ft_init_tab_philo(context);
		if (philos)
			ft_philo(philos, context, -1, -1);
		else
			printf("FAILURE\n");
	}
	else
	{
		ft_true_free((void **)&context);
		printf("Wrong arguments.\n");
	}
	return (EXIT_SUCCESS);
}
