/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:46:51 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/12 11:22:55 by mait-all         ###   ########.fr       */
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


char	*get_exec_path(char **env, char *cmd);
void	redirect_input_from_file(char *file);
void	redirect_input_from_pipe(int read_pipe_end);
void	redirect_output_to_file(char *file);
void	redirect_output_to_pipe(int write_pipe_end);
void	execute_command(char *cmd, char **env);
#endif