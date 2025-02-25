/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:37:54 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/25 15:31:33 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	display_error(char *error_msg, char *arg, char **args)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_cleanup(args);
}

void	handle_shell_errors(char *arg, char *path, char **args)
{
	if (!args || !args[0])
	{
		display_error(ERR_PERMISSION, arg, args);
		exit(126);
	}
	if (!path)
	{
		display_error(ERR_CMD_NOT_FOUND, arg, args);
		exit(127);
	}
	if (ft_strncmp(path, "no file", ft_strlen(path)) == 0)
	{
		display_error(ERR_NO_FILE, arg, args);
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
