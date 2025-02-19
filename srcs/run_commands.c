/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:47:31 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/18 10:41:00 by mait-all         ###   ########.fr       */
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
		ft_printf("./pipex: %s\n", strerror(errno));
		exit(errno);
	}
	execve(path, args, NULL);
	perror("Failed to create new process.");
}