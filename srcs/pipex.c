/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:28:04 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/20 11:08:35 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int pids[2];
	int	i;
	char **args;
	char *path;
	int status;

	// check arguments
	if (argc != 5)
		return (1);
	if (pipe(fd) == -1)
	{
		perror("Failed to create a pipe");
		exit (1);
	}
	i = 0;
	while (i < 2)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("Failed to create a child process\n");
			exit (1);
		}
		if (pids[i] == 0) // child processs
		{
			if (i == 0) // First command 
			{
				close(fd[0]);
				handle_errors(argv[2], env);
				redirect_input_from_file(argv[1]);
				redirect_output_to_pipe(fd[1]);
				close(fd[0]);
				close(fd[1]);
				execute_command(argv[2], env);
			}
			else
			{
    			close(fd[1]);
    			handle_errors(argv[3], env);
				redirect_input_from_pipe(fd[0]);
				redirect_output_to_file(argv[4]);
				close(fd[0]);
				close(fd[1]);
				execute_command(argv[3], env);
			}
		}
		i++;
	}
	close (fd[0]);
	close (fd[1]);
	waitpid(pids[0],NULL, 0);  
	waitpid (pids[1], &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
		// exit with last child's exit code
		exit(WEXITSTATUS(status));
	}
}