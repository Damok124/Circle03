/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grab_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:02:30 by zharzi            #+#    #+#             */
/*   Updated: 2022/12/24 00:13:53 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_grab_right(t_philo *philo, int *forks)
{
	pthread_mutex_lock(&philo->right);
	ft_print_msg(philo, "has taken a fork");
	*forks += 1;
}