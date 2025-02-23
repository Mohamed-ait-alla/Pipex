/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:08:42 by mait-all          #+#    #+#             */
/*   Updated: 2025/02/23 21:40:30 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc_execution(t_pipex *px)
{
	allocate_pipes_and_pids(px);
	create_pipes(px);
	fork_and_execute_commands(px);
	wait_for_childs(px);
}
