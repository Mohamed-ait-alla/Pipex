/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:08:42 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/27 21:03:17 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_tmp_file(void)
{
	char	*file;
	char	*tmpfile;
	int		i;

	file = ft_itoa((unsigned long long)&i);
	tmpfile = ft_strjoin("/tmp/", file);
	free(file);
	return (tmpfile);
}

void	here_doc_execution(t_pipex *px)
{
	allocate_pipes_and_pids(px);
	create_pipes(px);
	fork_and_execute_commands(px);
	wait_for_childs(px);
	exit (0);
}
