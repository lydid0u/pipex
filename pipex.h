/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:15:22 by lboudjel          #+#    #+#             */
/*   Updated: 2023/12/21 15:18:11 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./ft_printf/ft_printf.h"
# include "./libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct pipex
{
	char	**envp;
	char	*infile;
	char	*outfile;
	int		nbr_cmd;
	char	**arg_cmd;
	int		infile_fd;
	int		outfile_fd;
	int		fd[2];
	int		pid[1024];
	char	**tab_cmd;
	char	**args_path;
	int		prev;
}			t_pipex;

//				main			//

void		child(t_pipex *pipex, int i);
void		piping_and_forking(t_pipex *pipex);
void		init_struct(t_pipex *pipex, int argc, char **argv, char **envp);
void		redirection(t_pipex *pipex, int i);

//				pipex				//

char		*access_cmd(t_pipex *pipex, int i);
int			open_fd(t_pipex *pipex, int i);
char		**get_path(char **envp);
void		free_tab(char **tab);

#endif