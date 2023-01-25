/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grab_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:12 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:21 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_grab_left(t_philo *philo, int *forks)
{
	sem_wait(philo->context->sem_forks);
	if (ft_action_if_alive(philo))
		ft_print_msg(philo, "has taken a fork");
	*forks += 2;
}
