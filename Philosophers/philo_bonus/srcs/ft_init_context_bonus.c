/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_context_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:17 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/18 13:15:19 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_init_context(t_context *context, char **argv, int ac)
{
	int	check;

	check = 1;
	context->members = ft_atoi_safe(argv[0], &check);
	context->life_time = ft_atoi_safe(argv[1], &check);
	context->meal_time = ft_atoi_safe(argv[2], &check);
	context->rest_time = ft_atoi_safe(argv[3], &check);
	if (ac == 5)
		context->meals_max = ft_atoi_safe(argv[4], &check);
	else
		context->meals_max = -1;
	context = ft_init_context_sem(context);
}
