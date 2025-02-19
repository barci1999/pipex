/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-03 16:30:16 by pablalva          #+#    #+#             */
/*   Updated: 2025-02-03 16:30:16 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	child(char *cmd, char **envp, t_data *pipex)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("Error en pipe");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
		perror("Error en fork");
	if (pid == 0)
	{
		close(pipefd[0]);
		if (pipex->i == pipex->argc - 2)
			dup2(pipex->outfile_fd, STDOUT_FILENO);
		else
			dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipex->outfile_fd);
		execute_cmd(cmd, envp);
	}
	else
	{
		if (pipex->i != pipex->argc - 2)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
		}
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	execute_cmd(char *cmds, char **envp)
{
	char	**cmd;
	char	*cmd_path;

	cmd = NULL;
	cmd_path = NULL;
	if(cmds == NULL)
		exit(1);
	cmd = ft_split(cmds, ' ');
	cmd_path = take_cmd_path(cmd, envp);
	if (!cmd_path)
	{
		ft_free_matrix(cmd);
		free(cmd_path);
		perror("Error in path");
		exit(1);
	}
	if (execve(cmd_path, cmd, envp) == -1)
	{
		perror("Error in execve");
		exit(1);
	}
}
