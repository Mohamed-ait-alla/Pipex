/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:46:51 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/10 17:49:41 by mait-all         ###   ########.fr       */
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
#endif