/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-04 15:29:16 by pablalva          #+#    #+#             */
/*   Updated: 2025-02-04 15:29:16 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void 	take_cmd_path(t_data *pipex, char *cmd, char **envp)
{
	char	*temp;
	int		i;
	char	*cmd_path;
	pipex->cmd_path = NULL;

	temp = NULL;
	i = 0;
	cmd_path = NULL;
	take_paths_env(pipex, envp);
	while (pipex->paths[i] != NULL)
	{
		temp = ft_strjoin(pipex->paths[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(cmd_path, X_OK) == 0)
		{
			pipex->cmd_path = ft_strdup(cmd_path);
			free(cmd_path);
			printf("%s",pipex->cmd_path);
			ft_free_matrix(pipex->paths);
			return;
		}
		free(cmd_path);
		i++;
	}
}

void	take_paths_env(t_data *pipex, char **envp)
{
	int	i;

	i = 0;
	pipex->path_env = NULL;
	while (*envp)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			pipex->path_env = envp[i] + 5;
			break ;
		}
		envp++;
	}
	pipex->paths = ft_split(pipex->path_env, ':');
	if (pipex->paths == NULL)
	{
		perror("Error");
		exit(1);
	}
}
