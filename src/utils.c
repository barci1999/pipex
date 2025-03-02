/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-03 16:30:26 by pablalva          #+#    #+#             */
/*   Updated: 2025-02-03 16:30:26 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	open_fd_in(t_data *pipex, char *infile)
{
	if (access(infile, F_OK) == -1)
	{
		perror("Error");
		pipex->i++;
		return ;
	}
	pipex->infile_fd = open(infile, O_RDONLY);
	if (pipex->infile_fd == -1)
	{
		perror("Error");
		return ;
	}
}

void	open_fd_out(t_data *pipex, char *outfile, int flag)
{
	if (flag == 0)
		pipex->outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (flag == 1)
		pipex->outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (pipex->outfile_fd == -1)
	{
		perror("Error opening or creating output file");
		close(pipex->infile_fd);
		exit(1);
	}
}

void	fun_clean(char *str, char *cmd_path, char **cmd)
{
	perror(str);
	if (cmd_path)
		free(cmd_path);
	if (cmd)
	{
		printf("hola\n");
		ft_free_matrix(cmd);
	}
	exit(1);
}
