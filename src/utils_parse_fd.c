/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-31 16:48:48 by pablalva          #+#    #+#             */
/*   Updated: 2025-01-31 16:48:48 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	open_fd(t_data *pipex)
{
	pipex->fd_in = open(pipex->infile, O_RDONLY);
	if (pipex->fd_in == -1)
	{
		perror("Error opening infile");
		exit(1);
	}
	pipex->fd_out = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_out == -1)
	{
		perror("Error opening or creating outfile");
		exit(1);
	}
}

void	parse_fd(char **argv)
{
	t_data	pipex;

	pipex.infile = argv[1];
	pipex.outfile = argv[4];
	if (access(pipex.infile, F_OK) == -1)
	{
		perror("Error");
		exit(1);
	}
	open_fd(&pipex);
}
