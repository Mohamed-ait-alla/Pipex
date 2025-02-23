/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:28:14 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/23 15:03:28 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define ERR_NO_FILE "./pipex: no such file or directory: "
# define ERR_PERMISSION "./pipex: permission denied: "
# define ERR_CMD_NOT_FOUND "./pipex: command not found: "
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include "../libft/libft.h"

void	execute_child(char **argv, char **env, int fd[2], int i);
void	handle_shell_errors(char *arg, char *path, char **args);
void	handle_syscall_errors(char c);
void	execute_command(char *cmd, char **env);
char	*get_exec_path(char **env, char *cmd);
void	redirect_input_from_file(char *file);
void	redirect_input_from_pipe(int read_pipe_end);
void	redirect_output_to_file(char *file);
void	redirect_output_to_pipe(int write_pipe_end);

#endif