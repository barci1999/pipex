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

static void	redirec_child(t_data *pipex, int *pipefd, char *cmd, char **envp)
{
	close(pipefd[0]);
	if (pipex->i == pipex->argc - 2)
		dup2(pipex->outfile_fd, STDOUT_FILENO);
	else
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	close(pipex->outfile_fd);
	close(pipex->infile_fd);
	execute_cmd(cmd, envp, pipex);
}

static void	redirec_father(t_data *pipex, int *pipefd)
{
	if (pipex->i != pipex->argc - 2)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
	}
	close(pipefd[0]);
	close(pipefd[1]);
}

pid_t	child(char *cmd, char **envp, t_data *pipex)
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
	{
		perror("Error en fork");
		exit(1);
	}
	if (pid == 0)
		redirec_child(pipex, pipefd, cmd, envp);
	else
		redirec_father(pipex, pipefd);

	return (pid);
}

void fun_clean(char *str, char *cmd_path, char **cmd, t_data *pipex)
{
	perror(str);
	if (cmd_path)
		free(cmd_path);
	if (cmd)
		ft_free_matrix(cmd);
	close(pipex->infile_fd);
	close(pipex->here_fd);
	exit(1);
}

void	execute_cmd(char *cmds, char **envp, t_data *pipex)
{
	char	**cmd;
	char	*cmd_path;
	char *temp;

	cmd = NULL;
	cmd_path = NULL;
	if (cmds == NULL)
		exit(1);
	cmd = ft_split(cmds, ' ');
	if (!cmd)
		fun_clean("Error Malloc :", NULL, NULL, pipex);
	if(cmd[0][0] == '/')
	{
		cmd_path = ft_strdup(cmd[0]);
		if (!cmd_path)
			fun_clean("Error Malloc :", NULL, cmd, pipex);
		if(ft_strrchr(cmd_path,'/') != NULL)
		{
			temp = ft_strdup(ft_strrchr(cmd_path,'/')+1);
			if(!temp)
				fun_clean("Error in maloc :",NULL,cmd,pipex);
			free(cmd[0]);
			cmd[0]= temp;
		}
 	}
	else
		cmd_path = take_cmd_path(cmd, envp);
	if (execve(cmd_path, cmd, envp) == -1)
		fun_clean("Error in execve :", cmd_path, cmd, pipex);
}
