/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zied.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:13:57 by zharzi            #+#    #+#             */
/*   Updated: 2022/11/11 17:34:30 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//cat<<EOF>file| wc -c | tr -d " " > file2 | echo "$USER" >> file2 | echo '$HOME' >> file2 | echo '"$USER"' >> file2 | "e"c'h'o"""""""" salut

char	**ft_sections_parsing(const char *section)
{
	char	**result;
	char	*save;
	char	*tmp;

	save = ft_strdup(section);
	tmp = ft_strtrim(save, " ");
	return (result);
}

char	***ft_minishell_parsing(char *src, char **env)
{
	char	***dest;
	char	**tmp;
	int		len;
	int		i;

	len = ft_count_strs(src, '|');
	dest = (char ***)malloc(sizeof(char **) * (len + 1));
	if (!dest)
		return (NULL);
	dest[len] = NULL;
	tmp = ft_split(src, '|');
	while (dest[i])
	{
		dest[i] = ft_sections_parsing(tmp[i]);
		i++;
	}
	return (dest);
}

char	***ft_zied(char **env)
{
	char	***cmd_line;
	char	*raw_cmd;
	int		fd;

	cmd_line = NULL;
	fd = open("cmdline", O_RDONLY);
	raw_cmd = get_next_line(fd);
	ft_printf("%s", raw_cmd);
	cmd_line = ft_minishell_parsing(raw_cmd, env);
	close(fd);
	return (cmd_line);
}
