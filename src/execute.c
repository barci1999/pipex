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
	int i;
	i = 0;
	int j;
	j = 0;
	char **cmd;
	pid_t child;

	while(i <= pipex->num_pipes)
	{
		child = fork();
		if(child == 0)
		{
			cmd = ft_split(cmds[i+1],' ');
			take_cmd_path(pipex, cmds[i], envp);
			if(i == 0)
			{
				if(pipex->infile_fd != -1)
				{
					dup2(pipex->infile_fd,STDIN_FILENO);
					close(pipex->infile_fd);
				}
				close(pipex->pipes[i][0]);
				dup2(pipex->pipes[i][1],STDOUT_FILENO);
				close(pipex->pipes[i][1]);
			}
			else if (i == pipex->num_pipes)
			{
				close(pipex->pipes[i - 1][1]);
				dup2(pipex->pipes[i -1][0],STDIN_FILENO);
				close(pipex->pipes[i -1][0]);
				if(pipex->outfile_fd != -1)
				{
					dup2(pipex->outfile_fd,STDOUT_FILENO);
					close(pipex->outfile_fd);
				}
			}
			else
			{
				close(pipex->pipes[i -1][1]);
				dup2(pipex->pipes[i -1][0],STDIN_FILENO);
				close(pipex->pipes[i -1][0]);

				close(pipex->pipes[i][0]);
				dup2(pipex->pipes[i][1],STDOUT_FILENO);
				close(pipex->pipes[i][1]);
			}
			execve(pipex->cmd_path,cmds,envp);
		}
		i++;
	}
	while (j <= pipex->num_pipes + 1)
	{
		waitpid(-1,NULL,0);
		j++;
	}	
	free(pipex->cmd_path);
	
}
// void	med_cmd(t_data *pipex,char **cmds,char **envp)
//{}
// void	last_cmd(t_data *pipex,char *last_cmd,char **envp)
//{}