/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:08:42 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/14 11:20:45 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc_execution(char **argv, char **env)
{
	char	**args;
	char	**args1;
	char	*line;
	char	*exec_path;
	char	*limiter;
	int		tmp_fd;
	int		outfile;
	int		p_chanel[2];
	int		pid1, pid2;

	if (pipe(p_chanel) == -1)
	{
		perror("Failed to create here-doc pipe\n");
		exit(1);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork has been failed to create first child\n");
		exit(1);
	}
	// first child that will execute the first command 
	if (pid1 == 0)
	{
		tmp_fd = open("/tmp/tmp_data", O_WRONLY | O_CREAT | O_APPEND , 0644);
		if (tmp_fd < 0)
		{
			perror("Failed to open here-doc fds\n");
			exit(1);
		}
		line = get_next_line(0);
		limiter = ft_strjoin(argv[2], "\n");
		while (line && (ft_strncmp(line, limiter, ft_strlen(line)) != 0))
		{
			write(tmp_fd, line, ft_strlen(line));
			free(line);
			line = get_next_line(0);
		}
		close (tmp_fd);
		tmp_fd = open("/tmp/tmp_data", O_RDONLY);
		free(limiter);
		dup2(tmp_fd, STDIN_FILENO);
		dup2(p_chanel[1], STDOUT_FILENO);
		close (p_chanel[1]);
		close (p_chanel[0]);
		close(tmp_fd);
		args = ft_split(argv[3], ' ');
		exec_path = get_exec_path(env, args[0]);
		if (!exec_path)
		{
			perror("Command Not found\n");
			exit(1);
		}
		execve(exec_path, args, NULL);
		perror("execve has been failed in here-doc\n");
	}
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork has been failed to create second child\n");
		exit(1);
	}
	// second child process that will execute the second command 
	if (pid2 == 0)
	{
		outfile = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfile < 0)
		{
			perror("Failed to open here-doc fds\n");
			exit(1);
		}
		dup2(outfile, STDOUT_FILENO);
		close (outfile);
		dup2(p_chanel[0], STDIN_FILENO);
		close (p_chanel[0]);
		close (p_chanel[1]);
		args1 = ft_split(argv[4], ' ');
		exec_path = get_exec_path(env, args1[0]);
		if (!exec_path)
		{
			perror("Command Not found\n");
			exit(1);
		}
		execve(exec_path, args1, NULL);
		perror("execve has been failed in here-doc\n");
	}
	close (p_chanel[0]);
	close (p_chanel[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	// remove the tmp file after the execution
	if (unlink("/tmp/tmp_data") == -1)
		perror("Failed to remove temporary file\n");
}