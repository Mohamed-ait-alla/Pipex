/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:28:04 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/24 10:30:35 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cleanup(char **container)
{
	int	i;

	i = 0;
	while (container[i])
		free(container[i++]);
	free(container);
}

void	close_unused_pipes(int fd[2])
{
	close (fd[0]);
	close (fd[1]);
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	pids[2];
	int	status;
	int	i;

	status = 0;
	if (argc != 5)
		exit(1);
	if (pipe(fd) == -1)
		handle_syscall_errors('p');
	i = 0;
	while (i < 2)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			handle_syscall_errors('f');
		if (pids[i] == 0)
			execute_child(argv, env, fd, i);
		i++;
	}
	close_unused_pipes(fd);
	waitpid (pids[0], NULL, 0);
	waitpid (pids[1], &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		exit(WEXITSTATUS(status));
}
