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
	int		here_fd;
	int		infile_fd;
	int		outfile_fd;
	int		argc;
	int		i;
	int		temp;
	pid_t	pid;
	pid_t	pid2;

}			t_data;

void		open_fd_out(t_data *pipex, char *outfile, int flag);
void		create_here(t_data *pipex, char *delim);
void		open_fd_in(t_data *pipex, char *infile);
char		*take_cmd_path(char **cmd, char **envp);
char		**take_paths_env(char **envp);
pid_t		child(char *cmd, char **envp, t_data *pipex);
void		execute_cmd(char *cmds, char **envp);
void		fun_clean(char *str, char *cmd_path, char **cmd);

#endif
