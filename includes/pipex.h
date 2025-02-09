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
	int		cmd_nbr;
	int		here_fd;
	int		infile_fd;
	int		outfile_fd;
	char	*path_env;
	char	**paths;
	char	*cmd_path;
	int		num_pipes;
	int **pipes;
	pid_t pid;

}			t_data;

void		open_fd_out(t_data *pipex, char *outfile);
void		open_here(t_data *pipex, char *delim);
void		open_fd_in(t_data *pipex, char *infile);
void		first_cmd(t_data *pipex, char **cmd, char **envp);
void 	take_cmd_path(t_data *pipex, char *cmd, char **envp);
void		take_paths_env(t_data *pipex, char **envp);
int			**all_pipes(t_data *pipex);

#endif
