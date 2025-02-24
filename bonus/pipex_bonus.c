/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:49:02 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/24 17:30:18 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	px;

	if (argc <= 4)
		handle_syscall_errors(-4);
	px.n_cmds = argc - 3;
	px.argv = argv;
	px.env = env;
	px.argc = argc;
	px.is_here_doc = 0;
	px.cmd_offset = 2;
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc <= 5)
			handle_syscall_errors(-5);
		px.n_cmds = argc - 4;
		px.is_here_doc = 1;
		px.cmd_offset = 3;
		here_doc_execution(&px);
		exit (0);
	}
	allocate_pipes_and_pids(&px);
	create_pipes(&px);
	fork_and_execute_commands(&px);
	wait_for_childs(&px);
	return (0);
}
