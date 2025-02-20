/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:08:42 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/20 15:31:59 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc_execution(int argc, char **argv, char **env, int n_of_cmds)
{
	int pipes[n_of_cmds - 1][2];
	int	pids[n_of_cmds];
	int	i;
	
	// creating pipes
	i = 0;
	while (i < n_of_cmds - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("Failed to create the pipes");
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < n_of_cmds)
	{
		// create child process that will execute the commands
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("Failed to create a child process here-doc\n");
			exit(1);
		}
		if (pids[i] == 0)
		{
			// if i is 0 => reads from the here_doc (tmp_data)
			if (i == 0)
				redirect_input_from_file_here_doc(argv[2]);
			// else reads from a pipe
			else
				redirect_input_from_pipe(pipes[i - 1][0]);
			// if i is equal to the pre-last command => output to outfile.txt
			if (i == n_of_cmds - 1)
				redirect_output_to_file(argv[argc - 1]);
			// else output to a pipe
			else
				redirect_output_to_pipe(pipes[i][1]);
			close_unused_pipes(pipes, n_of_cmds - 1, -1);
			execute_command(argv[i + 3], env);
		}
		i++;
	}
	close_unused_pipes(pipes, n_of_cmds - 1, -1);
	i = 0;
	while (i < n_of_cmds)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	// remove the tmp file after the execution
	if (unlink("/tmp/tmp_data") == -1)
		perror("Failed to remove temporary file\n");
}