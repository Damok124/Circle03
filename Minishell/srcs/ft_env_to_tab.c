/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:26:16 by zharzi            #+#    #+#             */
/*   Updated: 2022/12/21 17:39:36 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char **ft_env_to_tab(t_nod *nod)
{
	char	**strs;
	char	*tmp;
	t_nod	*first;
	int		i;

	i = 0;
	first = nod;
	tmp = NULL;
	while (nod)
	{
		i++;
		nod = nod->next;
	}
	strs = (char **)malloc(sizeof(char *) * (i + 1))
	if (!strs)
		return (NULL);
	i = 0;
	while (first)
	{
		tmp = ft_strjoin("=", first->value);
		strs[i] = ft_strjoin(first->key, tmp);
		ft_true_free((void **)&tmp);
		first = first->next;
	}
	return (strs);
}
