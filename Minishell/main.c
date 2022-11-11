/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 06:22:33 by zharzi            #+#    #+#             */
/*   Updated: 2022/11/11 11:51:23 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_zied(void)
{
	char	*cmdline;
	int		fd;

	fd = open("cmdline", O_RDONLY);
	cmdline = get_next_line(fd);
	ft_printf("%s", cmdline);
	ft_minishell_parsing(cmdline);
	close(fd);
}
