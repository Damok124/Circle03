/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grab_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:13 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:22 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_grab_right(t_philo *philo, int *forks)
{
	sem_wait(philo->context->sem_forks);
	if (ft_action_if_alive(philo))
		ft_print_msg(philo, "has taken a fork");
	*forks += 1;
}
