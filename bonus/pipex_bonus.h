/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:46:51 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/24 14:02:54 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# define ERR_NO_FILE "./pipex: no such file or directory: "
# define ERR_PERMISSION "./pipex: permission denied: "
# define ERR_CMD_NOT_FOUND "./pipex: command not found: "
# include <stdio.h> // why you're look at me
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

typedef struct s_pipex
{
	int		n_cmds;
	int		(*pipes)[2];
	int		*pids;
	int		argc;
	int		is_here_doc;
	int		cmd_offset;
	char	**argv;
	char	**env;
}	t_pipex;

void	ft_cleanup(t_pipex *px, char **container);
void	wait_for_childs(t_pipex *px);
void	create_pipes(t_pipex *px);
void	allocate_pipes_and_pids(t_pipex *px);
void	fork_and_execute_commands(t_pipex *px);
void	handle_syscall_errors(int err_flag);
void	handle_errors(t_pipex *px, char *arg, char *path, char **args);
char	*get_exec_path(t_pipex *px, char *cmd);
void	redirect_input_from_file(char *file);
void	redirect_input_from_pipe(int read_pipe_end);
void	redirect_output_to_file(char *file);
void	redirect_output_to_pipe(int write_pipe_end);
void	close_unused_pipes(int pipes[][2], int pipe_count, int except);
void	execute_command(t_pipex *px, char *cmd);
void	here_doc_execution(t_pipex *px);
void	redirect_input_from_file_here_doc(char *limiter);

#endif