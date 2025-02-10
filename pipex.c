/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:49:02 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/10 21:20:28 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	// create necesary variables

	int	fd[2];
	pid_t pid1, pid2;
	int	file1;
	int	file2;
	char	*path;
	char	**args;
	char	**args1;

	if (pipe(fd) == -1)
		return (1);
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
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
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
		file2 = open(argv[4], O_WRONLY);
		if (file2 == -1)
			perror("Error opening a file descriptor\n");
		dup2(file2, STDOUT_FILENO);
		close(file2);
		dup2(fd[0], STDIN_FILENO);
		close (fd[1]);
		close (fd[0]);
		args1 = ft_split(argv[3], ' ');
		path = get_exec_path(env, args1[0]);
		execve(path, args1, NULL);
		perror("Error in creating second new process\n");
	}
	close (fd[1]);
	close (fd[0]);
	// int i = 0;
	// while (args[i])
	// {
	// 	free(args[i]);
	// 	i++;
	// }
	// free(args);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}