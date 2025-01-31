/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-28 09:29:13 by pablalva          #+#    #+#             */
/*   Updated: 2025-01-28 09:29:13 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <wait.h>

typedef struct pipex
{
	char	*infile;
	char	**cmd1;
	char	**cmd2;
	char	*outfile;
	int		fd_in;
	int		fd_out;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

}			t_data;

void		open_fd(t_data *pipex);
void		parse_fd(char **argv);
void		parse_cmd(char **argv);
void		pipe_control(t_data *pipex);
void		execute_cmd1(t_data *pipex);
void		execute_cmd2(t_data *pipex);
#endif
