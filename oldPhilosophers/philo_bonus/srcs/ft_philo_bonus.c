/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:27 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:30 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_philo(t_philo *philos, t_context *context)
{
	pid_t	full_checker;

	full_checker = -1;
	if (philos->context->meals_max)
	{
		ft_put_processes_on_routine(philos, context);
		if (philos->context->meals_max > 0)
		{
			full_checker = fork();
			if (!full_checker)
				ft_wait_last_plate(philos);
		}
		ft_soul_waiting(philos);
		if (full_checker > -1)
			kill(full_checker, SIGKILL);
		ft_kill_them_all(philos);
	}
	ft_unset_philos(philos);
}
