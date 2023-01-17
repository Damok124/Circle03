/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_processes_on_routine.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:33 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:32 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_put_processes_on_routine(t_philo *tab, t_context *context)
{
	struct timeval	beginning;
	int				i;

	i = -1;
	gettimeofday(&beginning, NULL);
	while (++i < context->members)
	{
		tab[i].id = i + 1;
		tab[i].start_time = beginning;
		tab[i].pid = fork();
		if (!tab[i].pid)
			ft_routine(&tab[i]);
	}
}
