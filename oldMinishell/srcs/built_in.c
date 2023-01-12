/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:58:13 by tlarraze          #+#    #+#             */
/*   Updated: 2022/11/11 17:57:07 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//reproduce echo
void    ft_echo(char **str, char **env)
{
	int i;

	i = 1;
	if (!str[1])
	{
		printf("\n");
		return ;
	}
	if (ft_strncmp(str[0], "echo", 5) == 0 && ft_strncmp(str[1], "-n", 3) == 0)
		ft_echo_n(str,env);
	else
	{
		while (str[i] != NULL)
		{
			if (str[i + 1] != NULL)
				printf("%s ", str[i]);
			if (str[i + 1] == NULL)
				printf("%s\n", str[i]);
			i++;
		}
	}
	(void)str;
	(void)env;
}

void	ft_echo_n(char **str, char **env)
{
	int	i;

	i = 2;
	while (str[i] != NULL)
	{
		if (str[i + 1] != NULL)
			printf("%s ", str[i]);
		if (str[i + 1] == NULL)
			printf("%s", str[i]);
		i++;
	}
	(void)str;
	(void)env;
}

void	ft_cd(char **str, char **env)
{
	if (chdir(str[1]) == -1)
		perror("chdir");
	(void)env;
}

void	ft_pwd(char **str)
{
	char	*path;

	if (str[1])
	{
		printf("pwd: too many arguments\n");
		return ;
	}
	path = getcwd(NULL, 6666);
	if (path != NULL)
		printf("%s\n", path);
	else
		perror("getcwd");
}