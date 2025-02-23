/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:13:42 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/23 21:32:41 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_command(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	path = get_exec_path(env, args[0]);
	handle_errors(cmd, path, args);
	if (!path)
	{
		perror("./pipex: \n");
		exit(errno);
	}
	execve(path, args, NULL);
	perror("Failed to create new process.");
	exit(1);
}

static void	execute_child(t_pipex *px, int i)
{
	if (i == 0)
	{
		if (px->is_here_doc)
			redirect_input_from_file_here_doc(px->argv[2]);
		else
			redirect_input_from_file(px->argv[1]);
		redirect_output_to_pipe(px->pipes[i][1]);
	}
	else if (i == px->n_cmds - 1)
	{
		redirect_input_from_pipe(px->pipes[i - 1][0]);
		redirect_output_to_file(px->argv[px->argc - 1]);
	}
	else
	{
		redirect_input_from_pipe(px->pipes[i - 1][0]);
		redirect_output_to_pipe(px->pipes[i][1]);
	}
	close_unused_pipes(px->pipes, px->n_cmds - 1, -1);
	execute_command(px->argv[i + px->cmd_offset], px->env);
}

void	fork_and_execute_commands(t_pipex *px)
{
	int	i;

	i = 0;
	while (i < px->n_cmds)
	{
		px->pids[i] = fork();
		if (px->pids[i] == -1)
			handle_syscall_errors(-3);
		if (px->pids[i] == 0)
			execute_child(px, i);
		if (px->is_here_doc)
		{
			if (i == 0)
				wait(NULL);
		}
		i++;
	}
	close_unused_pipes(px->pipes, px->n_cmds - 1, -1);
}
