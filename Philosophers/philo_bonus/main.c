/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:34:45 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 22:57:17 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **argv)
{
	t_context	*context;
	t_philo		*philos;

	philos = NULL;
	context = (t_context *)malloc(sizeof(t_context));
	if (!context)
		return (0);
	if (ft_check_args(ac - 1, argv + 1))
	{
		ft_init_context(context, argv + 1, ac -1);
		philos = ft_init_tab_philo(context);
		if (philos)
			ft_philo(philos, context);
		else
			printf("FAILURE\n");
	}
	else
		printf("Wrong arguments.\n");
	ft_unset_context(context);
	return (EXIT_SUCCESS);
}
