/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:12:18 by tlarraze          #+#    #+#             */
/*   Updated: 2022/11/11 18:10:04 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//get the USERNAME in the environment and return it
char	*ft_get_username(char **env)
{
	char	*username;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "USER=", 5) != 0)
		i++;
	username = ft_strjoin(env[i] + 5, ":~$");
	return (username);
}