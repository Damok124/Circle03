/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_last_msg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:29 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:31 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print_last_msg(t_philo *philo, char *msg)
{
	int	time;

	time = ft_get_chrono(philo->start_time);
	sem_wait(philo->context->sem_printf);
	printf("%i %i %s\n", time, philo->id, msg);
	sem_post(philo->context->sem_over);
	while (1)
		usleep(1000000);
}
