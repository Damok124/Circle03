/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:26:16 by zharzi            #+#    #+#             */
/*   Updated: 2023/01/05 12:11:54 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_nod
{
    char            *key;
    char            *value;
    struct s_nod    *next;
}                    t_nod;

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
	strs = (char **)malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	strs[i] = NULL;
	i = 0;
	while (first)
	{
		tmp = ft_strjoin("=", first->value);
		strs[i] = ft_strjoin(first->key, tmp);
		ft_true_free((void **)&tmp);
		first = first->next;
		i++;
	}
	return (strs);
}

typedef struct s_nod
{
    char            *key;
    char            *value;
    struct s_nod    *next;
}                    t_nod;

void	ft_show_nod(t_nod *nod)
{
	while (nod)
	{
		printf("%s=%s\n", nod->key, nod->value);
		nod = nod->next;
	}
}
