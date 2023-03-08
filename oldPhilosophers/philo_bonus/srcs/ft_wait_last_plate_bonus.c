/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_last_plate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:38:40 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:42 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_wait_last_plate(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->context->members)
	{
		sem_wait(philo->context->sem_full);
		i++;
	}
	usleep(200);
	sem_post(philo->context->sem_over);
	while (1)
		usleep(100000);
}
