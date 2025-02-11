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

void	first_cmd(t_data *pipex, char **cmds, char **envp)
{
	int		i;
	int		c;
	char	**cmd;
	int		pipefd[2];
	int		pipefd_prev[2];

	i = 0;
	c = 2;
	if (pipe(pipefd_prev) == -1)
	{
		perror("Error: no pipe_prev creation");
		exit(1);
	}
	while (i <= pipex->cmd_nbr)
	{
		printf("perro salchicha\n");
		if (c < pipex->cmd_nbr)
		{
			cmd = ft_split(cmds[c], ' ');
			take_cmd_path(pipex, cmd, envp);
		}
		//printf("hola %s\n",pipex->cmd_path);
		if (i < pipex->cmd_nbr && pipe(pipefd) == -1)
		{
			perror("Error in creation pipe");
			exit(1);
		}
		pipex->pid = fork();
		if (pipex->pid == 0)
		{
			if (i == 0)
			{
				dup2(pipex->infile_fd, STDIN_FILENO);
				dup2(pipefd[1], STDOUT_FILENO);
				if (execve(pipex->cmd_path, cmd, envp) == -1)
				{
					perror("Error in execve first");
					close(pipefd[0]);
					close(pipefd[1]);
					exit(1);
				}
			}
			else if (i == pipex->cmd_nbr)
			{
				dup2(pipefd_prev[0], STDIN_FILENO);
				dup2(pipex->outfile_fd, STDOUT_FILENO);
				if (execve(pipex->cmd_path, cmd, envp) == -1)
				{
					perror("Error in execve last");
					close(pipefd_prev[0]);
					close(pipefd_prev[1]);
					exit(1);
				}
			}
			else
			{
				dup2(pipefd_prev[0], STDIN_FILENO);
				dup2(pipefd[1], STDOUT_FILENO);
				if (execve(pipex->cmd_path, cmd, envp) == -1)
				{
					perror("Error in execve midium");
					close(pipefd[0]);
					close(pipefd[1]);
					close(pipefd_prev[0]);
					close(pipefd_prev[1]);
					exit(1);
				}
			}
		}
		if (i < pipex->cmd_nbr)
		{
			pipefd_prev[0] = pipefd[0];
			pipefd_prev[1] = pipefd[1];
			close(pipefd[0]);
			close(pipefd[1]);
		}
		c++;
		i++;
	}
	while (i--)
	{
		waitpid(-1, NULL, 0);
	}
		printf("perro\n");
	free(pipex->cmd_path);
}
// void	med_cmd(t_data *pipex,char **cmds,char **envp)
//{}
// void	last_cmd(t_data *pipex,char *last_cmd,char **envp)
//{}