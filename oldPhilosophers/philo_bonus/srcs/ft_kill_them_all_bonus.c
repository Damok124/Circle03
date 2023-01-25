/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill_them_all.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:26 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:29 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_kill_them_all(t_philo *tab)
{
	int	i;

	i = -1;
	while (++i < tab->context->members)
		kill(tab[i].pid, SIGKILL);
}
