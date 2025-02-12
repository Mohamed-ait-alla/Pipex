/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:13:42 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/12 11:59:02 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	path = get_exec_path(env, args[0]);
	if (!path)
	{
		printf("path=%s\n", path);
		perror("Command Not Found\n");
		exit(1);
	}
	execve(path, args, NULL);
	perror("Error in creating new process\n");
}