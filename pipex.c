/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:49:02 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/11 12:10:43 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	// create necesary variables

	int	fd[2][2];
	pid_t pid1, pid2, pid3;
	int	file1;
	int	file2;
	int i;
	char	*path;
	char	**args;
	char	**args1;
	char	**args2;

	// creates two pipes
	i = 0;
	while (i < 2)
	{
		if (pipe(fd[i]) == -1)
			{
				perror("Error in creating pipes\n");
				return (1);
			}
		i++;
	}
	// create first child to execute the first command 
	pid1 = fork();
	if (pid1 == -1)
		return (2);
	
	// open infile and redirect it to sding
	if (pid1 == 0)
	{
		// child process
		file1 = open(argv[1], O_RDONLY);
		if (file1 == -1)
			return (3);
		dup2(file1, STDIN_FILENO);
		dup2(fd[0][1], STDOUT_FILENO);
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[1][0]);
		close(file1);
		args = ft_split(argv[2], ' ');
		path = get_exec_path(env, args[0]);
		if (!path)
			perror("Command Not found!\n");
		execve(path, args, NULL);
		perror("error in creating new process\n");
	}
	pid2 = fork();
	if (pid2 == -1)
		perror("Error in creating a child process\n");
	if (pid2 == 0)
	{
		// child process that we want it to execute the cmd2
		dup2(fd[1][1], STDOUT_FILENO);
		dup2(fd[0][0], STDIN_FILENO);
		close (fd[0][0]);
		close (fd[0][1]);
		close (fd[1][1]);
		close (fd[1][0]);
		args1 = ft_split(argv[3], ' ');
		path = get_exec_path(env, args1[0]);
		execve(path, args1, NULL);
		perror("Error in creating second new process\n");
	}
	// create third process that will run command 3
	pid3 = fork();
	if (pid3 == -1)
		perror("Error in creating third child process\n");
	if (pid3 == 0)
	{
		// third child process
		file2 = open(argv[5], O_WRONLY);
		if (file2 == -1)
			perror("Error opening a file descriptor\n");
		dup2(file2, STDOUT_FILENO);
		close(file2);
		dup2(fd[1][0], STDIN_FILENO);
		close (fd[1][0]);
		close (fd[0][0]);
		close (fd[0][1]);
		close (fd[1][1]);
		args2 = ft_split(argv[4], ' ');
		path = get_exec_path(env, args2[0]);
		execve(path, args2, NULL);
		perror("Error in creating third new process\n");
	}
	close (fd[0][0]);
	close (fd[0][1]);
	close (fd[1][1]);
	close (fd[1][0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	waitpid(pid3, NULL, 0);
}