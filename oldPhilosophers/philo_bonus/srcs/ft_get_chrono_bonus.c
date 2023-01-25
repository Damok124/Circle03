/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_chrono.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:41:10 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/17 23:42:21 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_get_chrono(struct timeval start)
{
	struct timeval	result;
	struct timeval	current;
	int				time;

	time = 0;
	gettimeofday(&current, NULL);
	result.tv_sec = current.tv_sec - start.tv_sec;
	result.tv_usec = current.tv_usec - start.tv_usec;
	time = (result.tv_sec * 1000) + (result.tv_usec / 1000);
	return (time);
}
