/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-03 16:30:19 by pablalva          #+#    #+#             */
/*   Updated: 2025-02-03 16:30:19 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	create_here(t_data *pipex, char *delim)
{
	char	*temp_line;
	pid_t here;
	char *temp_delim;
	temp_delim = NULL;
	temp_delim = ft_strjoin(delim,"\n");
	temp_line = NULL;
	pipex->here_fd = open("temp_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->here_fd == -1)
	{
		perror("Error");
		exit(1);
	}
	here = fork();
	if(here == 0)
	{
		while (1)
		{
			ft_printf("here_doc> ");
			temp_line = get_next_line(0);
			if (temp_line == NULL)
			{
				break ;
			}
			if (ft_strcmp(temp_line, temp_delim) == 0)
			{
				free(temp_delim);
				free(temp_line);
				break ;
			}
			write(pipex->here_fd, temp_line, ft_strlen(temp_line));
			free(temp_line);
		}
		exit(0);
	}
	free(temp_delim);
	waitpid(here,NULL,0);
	close(pipex->here_fd);
}
