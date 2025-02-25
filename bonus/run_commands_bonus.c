/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:13:42 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/25 15:45:06 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_command(t_pipex *px, char *cmd)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	path = get_exec_path(px, args[0]);
	handle_shell_errors(px, cmd, path, args);
	if (!path || ft_strncmp(path, "no permission", ft_strlen(path)) == 0)
	{
		display_error(px, ERR_PERMISSION, cmd, args);
		exit(126);
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
			redirect_input_from_file(px);
		redirect_output_to_pipe(px->pipes[i][1]);
	}
	else if (i == px->n_cmds - 1)
	{
		redirect_input_from_pipe(px->pipes[i - 1][0]);
		redirect_output_to_file(px);
	}
	else
	{
		redirect_input_from_pipe(px->pipes[i - 1][0]);
		redirect_output_to_pipe(px->pipes[i][1]);
	}
	close_unused_pipes(px->pipes, px->n_cmds - 1, -1);
	execute_command(px, px->argv[i + px->cmd_offset]);
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
