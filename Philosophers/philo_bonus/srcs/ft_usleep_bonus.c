/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:03:12 by zharzi            #+#    #+#             */
/*   Updated: 2022/12/24 00:12:51 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_usleep(t_philo *philo, int timer)
{
	long int	rest;

	rest = (long int)timer;
	if ((long int)philo->deadline \
		< (long int)ft_get_chrono(philo->start_time) + rest)
		rest = (long int)philo->deadline \
			- (long int)ft_get_chrono(philo->start_time);
	if (rest < 0)
		rest = 0;
	usleep((rest + 1) * 1000);
}
