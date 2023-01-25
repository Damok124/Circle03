/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thinking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:51 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:36 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_thinking(t_philo *philo)
{
	int	timer;

	timer = philo->context->meal_time - philo->context->rest_time;
	if (ft_action_if_alive(philo))
	{
		ft_print_msg(philo, "is thinking");
		if (philo->context->rest_time <= philo->context->meal_time)
		{
			ft_usleep(philo, timer + 1);
		}
	}
}
