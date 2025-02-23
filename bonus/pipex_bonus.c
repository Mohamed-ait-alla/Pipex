/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:49:02 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/23 18:28:35 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	wait_for_childs(t_pipex *px)
{
	int	status;
	int	i;

	i = 0;
	while (i < px->n_cmds)
	{
		waitpid(px->pids[i], &status, 0);
		if (WIFEXITED(status) && i == px->n_cmds - 1)
		{
			free(px->pipes);
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

int	main(int argc, char **argv, char **env)
{
	t_pipex	px;

	px.n_cmds = argc - 3;
	px.argv = argv;
	px.env = env;
	px.argc = argc;
	if (argc <= 4)
		return (1);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		px.n_cmds = argc - 4;
		here_doc_execution(argc, argv, env, px.n_cmds);
		exit (0);
	}
	px.pipes = malloc((px.n_cmds - 1) * sizeof(int [2]));
	px.pids = malloc(px.n_cmds * sizeof(int));
	if (!px.pipes || !px.pids)
		handle_syscall_errors(-1);
	create_pipes(&px);
	fork_and_execute_commands(&px);
	close_unused_pipes(px.pipes, px.n_cmds - 1, -1);
	wait_for_childs(&px);
	return (0);
}
