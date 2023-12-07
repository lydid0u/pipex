/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:15:22 by lboudjel          #+#    #+#             */
/*   Updated: 2023/12/07 16:02:42 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./ft_printf/ft_printf.h"
# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct pipex
{
	char	*path;
    char    **envp;
    char	*infile;
    char	*outfile;
    int		nbr_cmd;
    char	**arg_cmd;
    int     fd[2];
    int     pid[2];
    char    **args_path;
    char    **cmd;
}			t_pipex;

void	init_struct(t_pipex *pipex, int argc, char **argv, char **envp);
char	**get_path(char **envp);

#endif