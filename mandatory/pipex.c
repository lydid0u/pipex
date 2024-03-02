/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:01:16 by lboudjel          #+#    #+#             */
/*   Updated: 2023/12/26 14:42:31 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*access_cmd(t_pipex *pipex, int i)
{
	int		j;
	char	*check_access;

	j = 0;
	pipex->args_path = get_path(pipex->envp);
	if (!pipex->args_path)
		return (free_tab(pipex->args_path), NULL);
	if (ft_strchr(pipex->tab_cmd[i], '/'))
	{
		if (access(pipex->tab_cmd[i], F_OK | X_OK) != -1)
			return (ft_strdup(pipex->tab_cmd[i]));
		return (NULL);
	}
	while (pipex->args_path[j])
	{
		check_access = ft_strjoin_slash(pipex->args_path[j], pipex->tab_cmd[i]);
		if (access(check_access, F_OK | X_OK) == 0)
			return (check_access);
		free(check_access);
		j++;
	}
	ft_printf("command not found : %s \n", pipex->tab_cmd[i]);
	return (free_tab(pipex->args_path), NULL);
}

int	open_fd(t_pipex *pipex, int i)
{
	int	fd;

	fd = -1;
	if (i == 0)
	{
		fd = open(pipex->infile, O_RDONLY);
		if (fd < 0)
			return (close(pipex->fd[0]), close(pipex->fd[1]),
				perror("Infile"), exit(1), fd);
	}
	if (i == pipex->nbr_cmd - 1)
	{
		fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			close(pipex->fd[0]);
			return (close(pipex->prev), close(pipex->fd[1]),
				perror("Outfile"), exit(1), fd);
		}
	}
	return (fd);
}

char	**get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
