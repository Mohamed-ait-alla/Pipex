/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:37:54 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/24 15:41:15 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_shell_errors(char *arg, char *path, char **args)
{
	if (!args || !args[0])
	{
		ft_putstr_fd(ERR_PERMISSION, STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_cleanup(args);
		exit(126);
	}
	if (!path)
	{
		ft_putstr_fd(ERR_CMD_NOT_FOUND, STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_cleanup(args);
		exit(127);
	}
	if (ft_strncmp(path, "no file", ft_strlen(path)) == 0)
	{
		ft_putstr_fd(ERR_NO_FILE, STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_cleanup(args);
		exit(127);
	}
}

void	handle_syscall_errors(char c)
{
	if (c == 'p')
	{
		perror("pipe has been failed to generate pipes\n");
		exit(1);
	}
	else if (c == 'f')
	{
		perror("fork has been failed to create a child process\n");
		exit (1);
	}
	else if (c == 'a')
	{
		ft_putstr_fd("Error: Too few arguments!\n", STDERR_FILENO);
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		exit (EXIT_FAILURE);
	}
}
