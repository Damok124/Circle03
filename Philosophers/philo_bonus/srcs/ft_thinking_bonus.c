/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thinking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:03:07 by zharzi            #+#    #+#             */
/*   Updated: 2022/12/24 00:12:47 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_thinking(t_philo *philo)
{
	if (!ft_is_full_or_dead(philo))
	{
		ft_print_msg(philo, "is thinking");
	}
}
