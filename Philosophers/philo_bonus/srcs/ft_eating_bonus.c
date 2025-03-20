/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eating_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:09 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/18 13:22:34 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void ft_handle_single_philo(t_philo *philo, int *forks)
{
	ft_die_alone(philo);
	*forks = 0;
}

void ft_update_deadline(t_philo *philo)
{
	sem_wait(philo->life);
	philo->deadline = (long int)ft_get_chrono(philo->start_time)
		+ (long int)philo->context->life_time + 1;
	sem_post(philo->life);
}

void ft_eat(t_philo *philo)
{
	ft_print_msg(philo, "is eating");
	ft_usleep(philo, philo->context->meal_time);
	sem_wait(philo->life);
	if (++philo->meals == philo->context->meals_max)
		sem_post(philo->context->sem_full);
	sem_post(philo->life);
}

int ft_eating(t_philo *philo)
{
	int forks = 0;

	sem_wait(philo->context->sem_meal);
	ft_grab_right(philo, &forks);
	if (philo->context->members > 1)
		ft_grab_left(philo, &forks);
	else
	{
		ft_handle_single_philo(philo, &forks);
		return forks;
	}
	if (ft_action_if_alive(philo))
		sem_post(philo->context->sem_meal);
	if (ft_action_if_alive(philo) && philo->context->members > 1)
	{
		ft_update_deadline(philo);
		ft_eat(philo);
	}
	return forks;
}
