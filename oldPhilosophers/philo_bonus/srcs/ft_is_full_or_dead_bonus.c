/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_full_or_dead.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:22 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:26 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
