/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 06:22:33 by zharzi            #+#    #+#             */
/*   Updated: 2022/11/10 16:17:22 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <dirent.h>

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("Minishell:>");
		add_history(str);
		//rl_redisplay();
		printf("%s\n", getenv("YOLO"));
		//rl_clear_history();
		if (str == NULL)
			break;
	}
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
