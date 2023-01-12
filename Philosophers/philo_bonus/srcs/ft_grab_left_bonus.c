/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grab_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:02:27 by zharzi            #+#    #+#             */
/*   Updated: 2022/12/24 00:13:51 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_grab_left(t_philo *philo, int *forks)
{
	pthread_mutex_lock(philo->left);
	ft_print_msg(philo, "has taken a fork");
	*forks += 2;
}
