/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 06:22:33 by zharzi            #+#    #+#             */
/*   Updated: 2022/11/01 20:15:01 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipex(t_data *data, char **validpaths)
{
	int			pfds[2];
	char		**cmd_args;
	static int	i;

	i++;
	cmd_args = ft_split(data->argv[i + 1], ' ');
	pipe(pfds);
	if (validpaths[i - 1] && validpaths[i - 1][0] != '\0' && !fork())
	{
		ft_clean_connect(STDOUT, pfds[WRITE_END], pfds[READ_END]);
		ft_infile_to_in(data->argv, cmd_args, validpaths, i);
		execve(validpaths[i - 1], cmd_args, data->env);
	}
	else
	{
		ft_clean_connect(STDIN, pfds[READ_END], pfds[WRITE_END]);
		ft_full_free((void **)cmd_args);
		if ((i + 1) < (data->ac - 3))
			ft_pipex(data, validpaths);
		else
		{
			cmd_args = ft_split(data->argv[i + 2], ' ');
			ft_outfile_to_out(validpaths, i, cmd_args, data);
		}
	}
}

int	main(int ac, char **argv, char **env)
{
	t_data	data;
	char	**paths;
	char	**validpaths;

	data = ft_init_data(ac, argv, env);
	if (ac == 5)
	{
		paths = ft_get_paths(env);
		validpaths = ft_get_validpaths(ac, argv, paths);
		ft_full_free((void **)paths);
		if (ft_test_files(argv, ac))
			ft_pipex(&data, validpaths);
		ft_print_cmderr(validpaths, argv);
		waitpid(-1, NULL, 0);
		ft_full_free((void **)validpaths);
	}
	else
		write(2, "ERROR : wrong number of arguments.\n", 35);
	ft_close_stdfds();
	return (0);
}
