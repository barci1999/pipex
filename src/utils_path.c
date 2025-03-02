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

char	*take_cmd_path(char **cmd, char **envp)
{
	char	*temp;
	int		i;
	char	*cmd_path;
	char	**paths;

	paths = NULL;
	temp = NULL;
	i = 0;
	cmd_path = NULL;
	if(cmd == NULL || cmd[0][0] == '\0')
		return(fun_clean("Error comand invalid\n",NULL,cmd),NULL);
	paths = take_paths_env(envp);
	while (paths[i] != NULL)
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			fun_clean("Error in malloc\n", NULL, paths);
		cmd_path = ft_strjoin(temp, cmd[0]);
		free(temp);
		if (!cmd_path)
			fun_clean("Error in malloc\n", NULL, paths);
		if (access(cmd_path, X_OK) == 0)
			return (ft_free_matrix(paths), cmd_path);
		free(cmd_path);
		i++;
	}
	ft_free_matrix(cmd);
	return (fun_clean("Error ", NULL, paths), NULL);
}

char	**take_paths_env(char **envp)
{
	int		i;
	char	*path_env;
	char	**paths;

	i = 0;
	paths = NULL;
	path_env = NULL;
	while (*envp)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		envp++;
	}
	paths = ft_split(path_env, ':');
	if (paths == NULL)
	{
		perror("Error");
		exit(1);
	}
	return (paths);
}
