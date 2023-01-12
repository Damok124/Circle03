/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_share_printf_mutex.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:03:01 by zharzi            #+#    #+#             */
/*   Updated: 2022/12/24 00:12:43 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_share_printf_mutex(t_philo *philos, pthread_mutex_t *mut_printf)
{
	int	i;

	i = -1;
	while (++i < philos->context.members)
		philos[i].mut_printf = mut_printf;
}
