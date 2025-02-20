/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:49:02 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/20 21:38:13 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_errors(char *arg, char **env)
{
	char **args;
	char *path;

	args = ft_split(arg, ' ');
	if (!args || !args[0])  // Check for empty or invalid command
	{
		ft_printf("./pipex: permission denied: %s\n", arg);
		exit(126);
	}
	path = get_exec_path(env, args[0]);
	if (!path)
	{
		ft_printf("./pipex: command not found: %s\n", arg);
		exit(127);
	}
	if (ft_strncmp(path, "no file", ft_strlen(path)) == 0)
	{
		ft_printf("./pipex: no such file or directory: %s\n", arg);
		exit(127);
	}
}

void close_unused_pipes(int pipes[][2], int pipe_count, int except)
{
    for (int i = 0; i < pipe_count; i++) {
		if (i != except)
		{
        	close(pipes[i][0]);
        	close(pipes[i][1]);	
		}
    }
}


int	main(int argc, char **argv, char **env)
{
	int	n_of_cmds;
	n_of_cmds = argc - 3;
	int	pipes[n_of_cmds - 1][2];
	int pids[n_of_cmds];
	int	status;
	int	i;
	
	// check the arguments
	if (argc < 4)
		return (1);
	// check for here-doc arg, if is exist swicht to here-docoment
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		// here-doc execution 
		n_of_cmds = argc - 4;
		here_doc_execution(argc, argv, env, n_of_cmds);
		exit (0);
	}
	// create pipes
	i = 0;
	while (i < n_of_cmds - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("Error in creating pipes\n");
			return (1);
		}
		i++;
	}
	// fork child processes that will exectutes the commands
	i = 0;
	while (i < n_of_cmds)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("Failed to create a child process\n");
			return (2);
		}
		if (pids[i] == 0)
		{
			// child processes
			if (i == 0) // redirection input to file1
			{
				handle_errors(argv[i + 2], env);
				redirect_input_from_file(argv[1]);
			}
			else
			{
				handle_errors(argv[i + 2], env);
				redirect_input_from_pipe(pipes[i - 1][0]);
			}
			if (i == n_of_cmds - 1)
			{
				handle_errors(argv[i + 2], env);
				redirect_output_to_file(argv[argc - 1]);
			}
			else
			{
				handle_errors(argv[i + 2], env);
				redirect_output_to_pipe(pipes[i][1]);
			}
			close_unused_pipes(pipes, n_of_cmds - 1, -1);
			execute_command(argv[i + 2], env);
		}
		i++;		
	}
	close_unused_pipes(pipes, n_of_cmds - 1, -1);
	i = 0;
	while (i < n_of_cmds - 1)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	waitpid(pids[n_of_cmds], &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
		// exit with last child's exit code
		exit(WEXITSTATUS(status));
	}
	return (0);
}
