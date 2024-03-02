/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:13:45 by lboudjel          #+#    #+#             */
/*   Updated: 2023/12/21 17:17:27 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// strace -o /dev/pts/11 -f

#include "../pipex.h"

void	redirection(t_pipex *pipex, int i)
{
	int	fd;

	fd = -1;
	if (i == 0)
	{
		fd = open_fd(pipex, i);
		dup2(fd, 0);
		close(fd);
	}
	if (i == pipex->nbr_cmd - 1)
	{
		fd = open_fd(pipex, i);
		dup2(fd, 1);
		close(fd);
	}
	if (i != 0)
		dup2(pipex->prev, 0);
	if (i != pipex->nbr_cmd - 1)
		dup2(pipex->fd[1], 1);
}

void	child(t_pipex *pipex, int i)
{
	char	*path;

	redirection(pipex, i);
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	pipex->tab_cmd = ft_split(pipex->arg_cmd[i], ' ');
	if (!pipex->tab_cmd)
		return (free_tab(pipex->tab_cmd));
	path = access_cmd(pipex, 0);
	if (path)
		execve(path, pipex->tab_cmd, NULL);
	return (free(path), free_tab(pipex->tab_cmd), exit(1));
}

void	piping_and_forking(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_cmd)
	{
		if (pipe(pipex->fd) == -1)
			return (ft_printf("Error: pipe function\n"), exit(EXIT_FAILURE));
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
			return (ft_printf("Error: fork function\n"), exit(EXIT_FAILURE));
		if (pipex->pid[i] == 0)
			child(pipex, i);
		else
		{
			close(pipex->fd[1]);
			if (i != 0)
				close(pipex->prev);
			pipex->prev = pipex->fd[0];
		}
		i++;
	}
	i = 0;
	while (i < pipex->nbr_cmd)
		waitpid(pipex->pid[i++], NULL, 0);
}

void	init_struct(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
	pipex->envp = envp;
	pipex->nbr_cmd = argc - 3;
	pipex->arg_cmd = argv + 2;
}

int	main(int argc, char **argv, char **envp)
{
	static t_pipex	pipex = {0};

	if (argc != 5)
		return (ft_printf("Error\nIncorrect number of arguments !\n"), 0);
	init_struct(&pipex, argc, argv, envp);
	piping_and_forking(&pipex);
	close(pipex.fd[0]);
}
