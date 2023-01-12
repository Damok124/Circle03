/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mutexes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:02:35 by zharzi            #+#    #+#             */
/*   Updated: 2022/12/24 00:13:59 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_init_mutexes(t_philo *tab)
{
	int	i;

	i = -1;
	while (tab && ++i < tab->context.members)
	{
		pthread_mutex_init(&tab[i].life, NULL);
		pthread_mutex_init(&tab[i].right, NULL);
		tab->left = NULL;
	}
}
