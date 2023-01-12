/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:56:10 by tlarraze          #+#    #+#             */
/*   Updated: 2022/11/11 18:16:44 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_prompt;

void	handler(int num)
{
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, g_prompt, ft_strlen(g_prompt));
	(void)num;
}

int	main(int argc, char **argv, char **env)
{
	char		***cmd_line;
	char		*str;
	struct stat	sb;

	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	g_prompt = ft_get_username(env);
	while (1)
	{
		stat("pipex", &sb);
		str = readline(g_prompt);
		cmd_line = ft_zied(env);
		add_history(str);
		if (ft_strncmp(str, "echo", 4) == 0)
			ft_echo(ft_split(str, ' '), env);
		if (ft_strncmp(str, "cd", 2) == 0)
			ft_cd(ft_split(str, ' '), env);
		if (ft_strncmp(str, "pwd", 3) == 0)
			ft_pwd(ft_split(str, ' '));
		if (ft_strncmp(str, "exit", 5) == 0)
			exit(0);
		free(str);
		if (str == NULL)
		{
			printf("exit");
			break ;
		}
	}
	(void)argc;
	(void)argv;
	(void)env;
	return (0);
}
