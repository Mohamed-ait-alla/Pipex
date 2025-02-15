/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:46:51 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/14 16:29:52 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H
#include <stdio.h> // why you're look at me
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "./libft/libft.h"
#include "./ft_printf/ft_printf.h"
#include "./get_next_line/get_next_line.h"


char	*get_exec_path(char **env, char *cmd);
void	redirect_input_from_file(char *file);
void	redirect_input_from_pipe(int read_pipe_end);
void	redirect_output_to_file(char *file);
void	redirect_output_to_pipe(int write_pipe_end);
void	close_unused_pipes(int pipes[][2], int pipe_count);
void	execute_command(char *cmd, char **env);
void	here_doc_execution(int argc, char **argv, char **env, int n_of_cmds);
void	redirect_input_from_file_here_doc(char *limiter);
#endif