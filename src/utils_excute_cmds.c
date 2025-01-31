/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_excute_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-31 18:57:03 by pablalva          #+#    #+#             */
/*   Updated: 2025-01-31 18:57:03 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	execute_cmd1(t_data *pipex)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
	{
		perror("Error");
		exit(1);
	}
	if (pipex->pid1 == 0)
	{
		close(pipex->pipefd[0]);
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		close(pipex->pipefd[1]);
		if (execve(pipex->cmd1[0], pipex->cmd1, NULL) == -1)
		{
			perror("Error");
			exit(1);
		}
	}
}

void	execute_cmd2(t_data *pipex)
{
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
	{
		perror("Error");
		exit(1);
	}
	if (pipex->pid2 == 0)
	{
		close(pipex->pipefd[0]);
		dup2(pipex->pipefd[1], STDIN_FILENO);
		close(pipex->pipefd[0]);
		if (execve(pipex->cmd2[0], pipex->cmd2, NULL) == -1)
		{
			perror("Error");
			exit(1);
		}
	}
}
