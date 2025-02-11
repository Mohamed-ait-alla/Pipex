/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:30:40 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/10 21:34:17 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_exec_path(char **env, char *cmd)
{
	char	*path;
	char	*holder;
	char	*exec_path;
	char	**env_paths;
	int		i;

	if (cmd && (cmd[0] == '.' || cmd[0] == '/'))
	{
		exec_path = ft_memchr(cmd, '/', ft_strlen(cmd));
		if (access(exec_path, F_OK) == 0 && access(exec_path, X_OK) == 0)
			return (exec_path);
	}
	path = ft_memchr(env[19], '/', ft_strlen(env[19]));
	env_paths = ft_split(path, ':');
	i = 0;
	while (env_paths[i])
	{
		holder = ft_strjoin(env_paths[i], "/");
		exec_path = ft_strjoin(holder, cmd);
		free(holder);
		if (access(exec_path, F_OK) == 0 && access(exec_path, X_OK) == 0)
			return (exec_path);
		i++;
	}
	return (NULL);
}