/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action_if_alive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:40:56 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:14 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_action_if_alive(t_philo *philo)
{
	if (philo->deadline <= ft_get_chrono(philo->start_time))
	{
		ft_print_last_msg(philo, "died");
		return (0);
	}
	return (1);
}
