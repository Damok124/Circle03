/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_expired.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:20 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:25 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
