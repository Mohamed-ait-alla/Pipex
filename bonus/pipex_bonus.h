/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:46:51 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/23 18:30:56 by mait-all         ###   ########.fr       */
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
	char	**argv;
	char	**env;
}	t_pipex;

void	fork_and_execute_commands(t_pipex *px);
void	handle_syscall_errors(int err_flag);
void	handle_errors(char *arg, char *path, char **args);
char	*get_exec_path(char **env, char *cmd);
void	redirect_input_from_file(char *file);
void	redirect_input_from_pipe(int read_pipe_end);
void	redirect_output_to_file(char *file);
void	redirect_output_to_pipe(int write_pipe_end);
void	close_unused_pipes(int pipes[][2], int pipe_count, int except);
void	execute_command(char *cmd, char **env);
void	here_doc_execution(int argc, char **argv, char **env, int n_of_cmds);
void	redirect_input_from_file_here_doc(char *limiter);

#endif