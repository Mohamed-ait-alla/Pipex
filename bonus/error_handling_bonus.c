/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:05:03 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/24 18:12:43 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_errors(t_pipex *px, char *arg, char *path, char **args)
{
	if (!args || !args[0])
	{
		ft_putstr_fd(ERR_PERMISSION, STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_cleanup(px, args);
		exit(126);
	}
	if (!path)
	{
		ft_putstr_fd(ERR_CMD_NOT_FOUND, STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_cleanup(px, args);
		exit(127);
	}
	if (ft_strncmp(path, "no file", ft_strlen(path)) == 0)
	{
		ft_putstr_fd(ERR_NO_FILE, STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_cleanup(px, args);
		exit(127);
	}
}

void	handle_syscall_errors(int err_flag)
{
	if (err_flag == -1)
	{
		perror("malloc has been failed to allocate memory for pipes or pids\n");
		exit (EXIT_FAILURE);
	}
	else if (err_flag == -2)
	{
		perror("pipe has been failed to generate pipes\n");
		exit (EXIT_FAILURE);
	}
	else if (err_flag == -3)
	{
		perror("fork has been failed to create a child process\n");
		exit (EXIT_FAILURE);
	}
	else if (err_flag == -4)
	{
		ft_putstr_fd("Error: Too few arguments!\n", STDERR_FILENO);
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile\n", 2);
		exit (EXIT_FAILURE);
	}
	else if (err_flag == -5)
	{
		ft_putstr_fd("Error: Too few arguments!\n", STDERR_FILENO);
		ft_putstr_fd("Usage: ./pipex here_doc limitter cmd1 cmd2 outfile\n", 2);
		exit (EXIT_FAILURE);
	}
}
