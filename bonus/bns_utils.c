/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:58:17 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/27 20:22:35 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_cleanup(t_pipex *px, char **container)
{
	int	i;

	i = 0;
	while (container[i])
		free(container[i++]);
	free(container);
	if (px && px->pids)
		free(px->pids);
	if (px && px->pipes)
		free(px->pipes);
}

void	wait_for_childs(t_pipex *px)
{
	int	status;
	int	i;

	i = 0;
	if (px->is_here_doc)
		i = 1;
	while (i < px->n_cmds)
	{
		waitpid(px->pids[i], &status, 0);
		if (WIFEXITED(status) && (i == px->n_cmds - 1))
		{
			if (px->is_here_doc)
			{
				if (unlink(px->tmpfile) == -1)
					perror("failed to remove tmpfile\n");
				free(px->tmpfile);
			}
			if (px->pipes)
				free(px->pipes);
			if (px->pids)
				free(px->pids);
			exit(WEXITSTATUS(status));
		}
		i++;
	}
}

void	create_pipes(t_pipex *px)
{
	int	i;

	i = 0;
	while (i < px->n_cmds - 1)
	{
		if (pipe(px->pipes[i]) == -1)
			handle_syscall_errors(-2);
		i++;
	}
}

void	close_unused_pipes(int pipes[][2], int pipe_count, int except)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (i != except)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}

void	allocate_pipes_and_pids(t_pipex *px)
{
	px->pipes = malloc((px->n_cmds - 1) * sizeof(int [2]));
	px->pids = malloc(px->n_cmds * sizeof(int));
	if (!px->pipes || !px->pids)
		handle_syscall_errors(-1);
}
