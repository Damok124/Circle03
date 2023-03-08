/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleeping_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:47 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/18 13:14:46 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
