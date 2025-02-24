/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:48:47 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/24 11:29:57 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*search_exec_path(char **env_paths, char *cmd)
{
	char	*holder;
	char	*exec_path;
	int		i;

	i = 0;
	while (env_paths[i])
	{
		holder = ft_strjoin(env_paths[i], "/");
		exec_path = ft_strjoin(holder, cmd);
		free(holder);
		if (access(exec_path, F_OK) == 0 && access(exec_path, X_OK) == 0)
			return (exec_path);
		free(exec_path);
		i++;
	}
	return (NULL);
}

char	*get_env_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_exec_path(char **env, char *cmd)
{
	char	*path;
	char	*exec_path;
	char	**env_paths;

	if (!cmd || !cmd[0])
		return (NULL);
	if (cmd && (cmd[0] == '.' || cmd[0] == '/'))
	{
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
			return (cmd);
		return ("no file");
	}
	path = get_env_path(env);
	env_paths = ft_split(path, ':');
	exec_path = search_exec_path(env_paths, cmd);
	ft_cleanup(env_paths);
	return (exec_path);
}
