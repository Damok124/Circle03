/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:43 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:33 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
