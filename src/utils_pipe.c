/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-31 18:10:31 by pablalva          #+#    #+#             */
/*   Updated: 2025-01-31 18:10:31 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	pipe_control(t_data *pipex)
{
	if (pipe(pipex->pipefd) == -1)
	{
		perror("Error");
		exit(1);
	}
}
