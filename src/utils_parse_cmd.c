/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-31 16:50:10 by pablalva          #+#    #+#             */
/*   Updated: 2025-01-31 16:50:10 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	parse_cmd(char **argv)
{
	t_data	pipex;

	pipex.cmd1 = ft_split(argv[2], ' ');
	pipex.cmd2 = ft_split(argv[3], ' ');
	if (pipex.cmd1 == NULL || pipex.cmd2 == NULL)
	{
		ft_free_matrix(pipex.cmd1);
		ft_free_matrix(pipex.cmd2);
		ft_putstr_fd("Error: no commands or invalid commands.\n", 2);
		exit(1);
	}
}
