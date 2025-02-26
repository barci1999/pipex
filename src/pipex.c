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

static void	cmd_heredoc(t_data *pipex, char **argv)
{
	pipex->i = 3;
	pipex->temp = pipex->i;
	create_here(pipex, argv[2]);
	open_fd_out(pipex, argv[pipex->argc - 1], 1);
	pipex->here_fd = open("temp_heredoc", O_RDONLY, 0644);
	if (pipex->here_fd == -1)
	{
		perror("Error");
		exit(1);
	}
	dup2(pipex->here_fd, STDIN_FILENO);
}

static void	cmd_org(t_data *pipex, char **argv)
{
	pipex->i = 2;
	pipex->temp = pipex->i;
	open_fd_in(pipex, argv[1]);
	open_fd_out(pipex, argv[pipex->argc - 1], 0);
	dup2(pipex->infile_fd, STDIN_FILENO);
}

static void	finish(t_data *pipex)
{
	close(pipex->outfile_fd);
	close(pipex->infile_fd);
	close(pipex->here_fd);
	if (access("temp_heredoc", F_OK) != -1)
		unlink("temp_heredoc");
}

int	main(int argc, char **argv, char **envp)
{
	t_data	pipex;
	int		status;
	int		salida;

	ft_memset(&pipex, 0, sizeof(pipex));
	pipex.argc = argc;
	if (argc < 5)
		return (0);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		cmd_heredoc(&pipex, argv);
	else
		cmd_org(&pipex, argv);
	while (pipex.i <= pipex.argc - 2)
	{
		pipex.pid = child(argv[pipex.i], envp, &pipex);
		pipex.i++;
	}
	while (pipex.temp++ <= argc - 2)
	{
		pipex.pid2 = wait(&status);
		if (pipex.pid2 == pipex.pid)
			salida = WEXITSTATUS(status);
	}
	finish(&pipex);
	return (salida);
}
