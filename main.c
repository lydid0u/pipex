/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:13:45 by lboudjel          #+#    #+#             */
/*   Updated: 2023/12/05 15:16:23 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	access_cmd(t_pipex *pipex)
// {
// 	int i;
// 	char	**args;

// 	i = 0;
// 	args = ft_split(pipex->path, ':');
// 	while (args[i])
// 	{
// 		if()
// 		i++;
// 	}
// }

void	get_path(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			pipex->path = ft_strdup(envp[i] + 5);
			break ;
		}
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	static t_pipex	pipex = {0};

	get_path(&pipex, envp);
	// access_cmd(&pipex);
}

// int main()
// {
// int fd;

// fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
// dup2(fd, STDOUT_FILENO);
// close(fd);
// printf("prout\n");
//---------------------------------------------
// char *args[3];

// args[0] = "cat";
// args[1] = "salut.txt";
// args[2] = NULL;
// execve("/bin/cat", args, NULL);
//---------------------------------------------
// int fd[2];
// int pid;
// char buffer[12];

// if (pipe(fd) == -1)
// {
// 	perror("pipe");
// 	exit(EXIT_FAILURE);
// }
// pid = fork();
// if (pid == -1)
// {
// 	perror("fork");
// 	exit(EXIT_FAILURE);
// }

// if (pid == 0)
// {
// 	close(fd[0]); // close the read end of the pipe
// 	write(fd[1], "Hello parent!", 13);
// 	close(fd[1]); // close the write end of the pipe
// 	exit(EXIT_SUCCESS);
// }
// else
// {
// 	close(fd[1]); // close the write end of the pipe
// 	read(fd[0], buffer, 13);
// 	close(fd[0]); // close the read end of the pipe
// 	printf("Message from child: '%s'\n", buffer);
// 	exit(EXIT_SUCCESS);
// }
// return (0);
// }