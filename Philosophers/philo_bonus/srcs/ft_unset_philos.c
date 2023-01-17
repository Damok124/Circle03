/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_philos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:42:00 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:39 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_unset_philos(t_philo *tab)
{
	int	i;

	i = tab->context->members;
	while (--i >= 0)
		sem_close(tab[i].life);
	ft_true_free((void **)&tab);
}
