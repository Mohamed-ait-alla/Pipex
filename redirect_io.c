/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:20:44 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/12 10:44:59 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect_input_from_file(char *file)
{
	int	fd;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Failed to open fd\n");
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close (fd);
}

void	redirect_input_from_pipe(int read_pipe_end)
{
	dup2(read_pipe_end, STDIN_FILENO);
	close (read_pipe_end);
}

void	redirect_output_to_file(char *file)
{
	int	fd;
	
	fd = open(file, O_WRONLY | O_CREAT);
	if (fd < 0)
	{
		perror("Failed to open fd\n");
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close (fd);
}

void	redirect_output_to_pipe(int write_pipe_end)
{
	dup2(write_pipe_end, STDOUT_FILENO);
	close (write_pipe_end);
}