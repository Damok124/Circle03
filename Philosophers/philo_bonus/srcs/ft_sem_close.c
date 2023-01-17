/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sem_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:45 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:34 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sem_close(sem_t* sem, char *sem_name)
{
	if (sem)
	{
		sem_close(sem);
		sem_unlink(sem_name);
	}
}
