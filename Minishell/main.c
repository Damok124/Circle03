/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:56:10 by tlarraze          #+#    #+#             */
/*   Updated: 2022/11/11 16:12:34 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
char	*Prompt;

void	handler(int	num)
{
	if (num == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		write(STDOUT_FILENO, Prompt, ft_strlen(Prompt));
	}
	if (num == SIGQUIT)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		exit(0);
	}
	(void)num;
}
*/
int	main(int argc, char **argv, char **env)
{
	char	***cmd_line;
	// char	*str;
	// struct stat sb;

	// signal(SIGINT, handler);
	// signal(SIGQUIT, handler);
	// Prompt = ft_strjoin(env[13] + 5, ":~$");
	// while (1)
	// {
	// 	stat("pipex", &sb);

	// 	str = readline(Prompt);
	// 	add_history(str);
	// 	if (str != NULL || ft_strncmp(str, "\0\0\0", 5) == 0)
	// 		printf("%s\n", str);
	// 	if (ft_strncmp(str, "exit", 5) == 0)
	// 		exit(0);
	// 	free(str);
	// 	//rl_redisplay();
	// 	//printf("%lu\n", sb.st_);
	// 	//printf("%lu\n", sb.st_blksize);
	// 	//printf("%lu\n", sb.st_nlink);
	// 	//printf("%lu\n", sb.st_dev);
	// 	//rl_clear_history();
	// 	if (str == NULL)
	// 		break;
	// }
	cmd_line = ft_zied(env);
	(void)argc;
	(void)argv;
	(void)env;
	return (0);
}
