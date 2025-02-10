/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-03 16:30:21 by pablalva          #+#    #+#             */
/*   Updated: 2025-02-03 16:30:21 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	pipex;
	ft_memset(&pipex,0,sizeof(pipex));

	if (argc < 5)
	{
		return (0);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		pipex.cmd_nbr = argc - 4;
		pipex.num_pipes = pipex.cmd_nbr - 1;
		open_here(&pipex, argv[2]);
		open_fd_out(&pipex, argv[argc - 1]);
		first_cmd(&pipex, argv, envp);
		// mid_cmd(&pipex,argv,envp);
		// last_cmd(&pipex,argv[argc - 2],envp);
		close(pipex.outfile_fd);
	}
	else
	{
		pipex.cmd_nbr = argc - 3;
		pipex.num_pipes = pipex.cmd_nbr - 1;
		open_fd_in(&pipex, argv[1]);
		open_fd_out(&pipex, argv[argc - 1]);
		first_cmd(&pipex, argv, envp);	
		// mid_cmd(&pipex,argv,envp);
		// last_cmd(&pipex,argv[argc - 2],envp);
	}
	return (0);
}
