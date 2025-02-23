/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:47:31 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/23 15:05:57 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	path = get_exec_path(env, args[0]);
	handle_shell_errors(cmd, path, args);
	if (!path)
	{
		perror("./pipex: \n");
		exit(errno);
	}
	execve(path, args, NULL);
	perror("Failed to create new process.");
}

void	execute_child(char **argv, char **env, int fd[2], int i)
{
	if (i == 0)
	{
		close(fd[0]);
		redirect_input_from_file(argv[1]);
		redirect_output_to_pipe(fd[1]);
	}
	else
	{
		close(fd[1]);
		redirect_input_from_pipe(fd[0]);
		redirect_output_to_file(argv[4]);
	}
	close_unused_pipes(fd);
	execute_command(argv[i + 2], env);
}
