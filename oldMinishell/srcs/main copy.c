/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 06:22:33 by zharzi            #+#    #+#             */
/*   Updated: 2022/11/11 11:49:13 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int argc, char **argv, char **env)
{
	char	*str;
	struct stat sb;

	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	Prompt = ft_strjoin(env[13] + 5, ":~$");
	while (1)
	{
		stat("pipex", &sb);
		
		str = readline(Prompt);
		add_history(str);
		if (str != NULL || ft_strncmp(str, "\0\0\0", 5) == 0)
			printf("%s\n", str);
		if (ft_strncmp(str, "exit", 5) == 0)
			exit(0);
		free(str);
		//rl_redisplay();
		//printf("%lu\n", sb.st_);
		//printf("%lu\n", sb.st_blksize);
		//printf("%lu\n", sb.st_nlink);
		//printf("%lu\n", sb.st_dev);
		//rl_clear_history();
		if (str == NULL)
			break;
	}
	(void)argc;
	(void)argv;
	return (0);
}

/* int	main(void)
{
	char	*str;
	int		fd;

	fd = open("cmdline", O_RDONLY);
	str = get_next_line(fd);
	ft_printf("%s", str);
	close(fd);
	return (0);
} */
