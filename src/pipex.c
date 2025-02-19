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
	int		i;
	int		temp;

	i = 0;
	ft_memset(&pipex, 0, sizeof(pipex));
	pipex.argc = argc;
	if (argc < 5)
		return (0);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		pipex.i = 3;
		temp = pipex.i;
		create_here(&pipex, argv[2]);
		open_fd_out(&pipex, argv[argc - 1]);
		pipex.here_fd = open("temp_heredoc", O_RDONLY, 0644);
		if (pipex.here_fd == -1)
		{
			perror("Error");
			exit(1);
		}
		dup2(pipex.here_fd, STDIN_FILENO);
	}
	else
	{
		pipex.i = 2;
		temp = pipex.i;
		open_fd_in(&pipex, argv[1]);
		open_fd_out(&pipex, argv[argc - 1]);
		dup2(pipex.infile_fd, STDIN_FILENO);
	}
	while (pipex.i <= pipex.argc - 2)
	{
		child(argv[pipex.i], envp, &pipex);
		pipex.i++;
	}
	while (temp++ <= argc - 2)
		wait(NULL);
	close(pipex.outfile_fd);
	close(pipex.infile_fd);
	close(pipex.here_fd);
	return (0);

}
