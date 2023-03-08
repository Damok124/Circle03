/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_context_sem.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:15 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:23 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_context	*ft_init_context_sem(t_context *context)
{
	int	meals;

	meals = (context->members / 2);
	context->sem_forks = sem_open("sem_forks", O_CREAT, 0600, context->members);
	if (context->sem_forks == SEM_FAILED)
		return (NULL);
	sem_unlink("sem_forks");
	context->sem_printf = sem_open("sem_printf", O_CREAT, 0600, 1);
	if (context->sem_printf == SEM_FAILED)
		return (NULL);
	sem_unlink("sem_printf");
	context->sem_over = sem_open("sem_over", O_CREAT, 0600, 0);
	if (context->sem_over == SEM_FAILED)
		return (NULL);
	sem_unlink("sem_over");
	context->sem_full = sem_open("sem_full", O_CREAT, 0600, 0);
	if (context->sem_full == SEM_FAILED)
		return (NULL);
	sem_unlink("sem_full");
	context->sem_meal = sem_open("sem_meal", O_CREAT, 0600, meals);
	if (context->sem_full == SEM_FAILED)
		return (NULL);
	sem_unlink("sem_meal");
	return (context);
}
