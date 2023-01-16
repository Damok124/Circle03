/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:02:59 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/15 23:41:34 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	int		forks;

	forks = 0;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0 || (philo->id % 2 != 0 \
		&& philo->id == (philo->context.members)))
	{
		if (!ft_is_expired(philo))
			ft_print_msg(philo, "is thinking");
		usleep(6000);
	}
	while (!ft_is_dead(philo))
	{
		if (!ft_is_expired(philo))
		{
			forks = ft_eating(philo);
			if (philo->context.members == 1)
				usleep(1000);
			ft_sleeping(philo, &forks);
			if (philo->context.members == 1)
				usleep(1000);
			ft_thinking(philo);
		}
	}
	return (NULL);
}
