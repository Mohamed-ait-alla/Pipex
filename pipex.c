/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:49:02 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/10 11:22:30 by mait-all         ###   ########.fr       */
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
	int i;
	char	*path;
	char	*exec_path;
	char	**env_paths;
	char	*holder;
	char	*holder_helper;
	
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
		path = ft_memchr(env[19], '/', ft_strlen(env[19]));
		env_paths = ft_split(path, ':');
		i = 0;
		while (env_paths[i])
		{
			holder = env_paths[i];
			holder_helper = ft_strjoin(holder, "/");
			free(holder);
			exec_path = ft_strjoin(holder_helper, argv[2]);
			free(holder_helper);
			if (access(exec_path, F_OK) == 0)
			{
				printf("founded at %s\n", exec_path);
				break;
			}
			i++;
		}
		char* args[] = {exec_path, NULL};
		execve(exec_path, args, NULL);
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
		path = ft_memchr(env[19], '/', ft_strlen(env[19]));
		env_paths = ft_split(path, ':');
		i = 0;
		while (env_paths[i])
		{
			holder = env_paths[i];
			holder_helper = ft_strjoin(holder, "/");
			free(holder);
			exec_path = ft_strjoin(holder_helper, argv[2]);
			free(holder_helper);
			if (access(exec_path, F_OK) == 0)
			{
				printf("founded at %s\n", exec_path);
				break;
			}
			i++;
		}
		char* args1[] = {exec_path, NULL};
		execve(exec_path, args1, NULL);
		perror("Error in creating second new process\n");
	}
	close (fd[1]);
	close (fd[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}