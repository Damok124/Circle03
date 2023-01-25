/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_context.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:57 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:38 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_unset_context(t_context *context)
{
	ft_sem_close(context->sem_meal, "sem_meal");
	ft_sem_close(context->sem_over, "sem_over");
	ft_sem_close(context->sem_full, "sem_full");
	ft_sem_close(context->sem_forks, "sem_forks");
	ft_sem_close(context->sem_printf, "sem_printf");
	ft_true_free((void **)&context);
}
