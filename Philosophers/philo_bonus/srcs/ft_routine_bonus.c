/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:02:59 by zharzi            #+#    #+#             */
/*   Updated: 2022/12/24 00:12:42 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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