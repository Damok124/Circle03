/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:09 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:20 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
