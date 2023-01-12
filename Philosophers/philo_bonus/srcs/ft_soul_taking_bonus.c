/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_soul_taking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:03:05 by zharzi            #+#    #+#             */
/*   Updated: 2022/12/24 00:12:46 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
