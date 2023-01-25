/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tab_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:18 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:25 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*ft_init_tab_philo(t_context *context)
{
	t_philo	*tab;
	char	*sem_name;
	int		i;

	i = -1;
	if (!context)
		return (NULL);
	tab = (t_philo *)malloc(sizeof(t_philo) * context->members);
	if (!tab)
		return (NULL);
	sem_name = NULL;
	while (context && ++i < context->members)
	{
		tab[i].pid = 0;
		tab[i].id = i + 1;
		sem_name = ft_itoa(i);
		tab[i].life = sem_open(sem_name, O_CREAT, 0600, 1);
		sem_unlink(sem_name);
		ft_true_free((void **)&sem_name);
		tab[i].alive = 1;
		tab[i].context = context;
		tab[i].deadline = (long int)context->life_time;
		tab[i].meals = 0;
	}
	return (tab);
}
