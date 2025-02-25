/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:20:44 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/25 09:44:11 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	redirect_input_from_file(t_pipex *px)
{
	int	fd;

	fd = open(px->argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(ERR_PERMISSION, STDERR_FILENO);
		ft_putstr_fd(px->argv[1], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free(px->pipes);
		free(px->pids);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close (fd);
}

void	redirect_input_from_file_here_doc(char *limiter)
{
	char	*line;
	char	*h_limiter;
	int		fd;

	fd = open("/tmp/tmp_data", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("Failed to open temprary file\n");
		exit(1);
	}
	line = get_next_line(0);
	h_limiter = ft_strjoin(limiter, "\n");
	while (line && (ft_strncmp(line, h_limiter, ft_strlen(line)) != 0))
	{
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(line);
	get_next_line(-2);
	close (fd);
	free(h_limiter);
	fd = open("/tmp/tmp_data", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close (fd);
}

void	redirect_input_from_pipe(int read_pipe_end)
{
	dup2(read_pipe_end, STDIN_FILENO);
	close (read_pipe_end);
}

void	redirect_output_to_file(t_pipex *px)
{
	int	fd;

	if (px->is_here_doc)
		fd = open(px->argv[px->argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(px->argv[px->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd(ERR_PERMISSION, STDERR_FILENO);
		ft_putstr_fd(px->argv[px->argc - 1], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free(px->pids);
		free(px->pipes);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close (fd);
}

void	redirect_output_to_pipe(int write_pipe_end)
{
	dup2(write_pipe_end, STDOUT_FILENO);
	close (write_pipe_end);
}
