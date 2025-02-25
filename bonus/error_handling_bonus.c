/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:05:03 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/25 15:40:16 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	display_error(t_pipex *px, char *error_msg, char *arg, char **args)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_cleanup(px, args);
}

void	handle_shell_errors(t_pipex *px, char *arg, char *path, char **args)
{
	if (!args || !args[0])
	{
		display_error(px, ERR_PERMISSION, arg, args);
		exit(126);
	}
	if (!path)
	{
		display_error(px, ERR_CMD_NOT_FOUND, arg, args);
		exit(127);
	}
	if (ft_strncmp(path, "no file", ft_strlen(path)) == 0)
	{
		display_error(px, ERR_NO_FILE, arg, args);
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
	else
	{
		ft_putstr_fd("Error: Too few arguments!\n", STDERR_FILENO);
		if (err_flag == -4)
			ft_putstr_fd(ERR_USAGE, STDERR_FILENO);
		else if (err_flag == -5)
			ft_putstr_fd(ERR_USAGE_HD, STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
}
