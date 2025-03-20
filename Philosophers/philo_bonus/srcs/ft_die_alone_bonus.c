/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_die_alone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:07 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:19 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_die_alone(t_philo *philo)
{
	ft_print_msg(philo, "has taken a fork");
	usleep(philo->context->life_time * 1000);
	ft_print_last_msg(philo, "died");
	sem_post(philo->context->sem_over);
	while (1)
		usleep(1000000);
}
