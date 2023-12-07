/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:13:45 by lboudjel          #+#    #+#             */
/*   Updated: 2023/12/07 16:07:20 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	access_cmd(t_pipex *pipex)
{
	int i;
	char	**split_cmd;
	//char	**tab2;
	i = 0;
	pipex->args_path = get_path(pipex->envp);
	split_cmd = ft_split(pipex->arg_cmd[ind], ' ');
	// tab2 = ft_split(pipex->arg_cmd[ind], ' ');
	// while (tab2[i])
	// {
	// 	printf("tab2: %s\n", tab2[i]);
	// 	i++;
	// }
	while (pipex->args_path[i])
	{
		split_cmd = ft_split(pipex->arg_cmd[ind], ' ');
		if (access(args[i], X_OK) == 0)
		{
			printf("path: %s\n", args[i]);
			break ;
		}
		i++;
	}
	//checker comment recuperer les args et les stocker pour les joins 
}

char	**get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}
// void	child(t_pipex *pipex)
// {
	
// }

void	piping_and_forking(t_pipex *pipex)
{
	if (pipe(pipex->fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pipex->pid[0] = fork();
	if (pipex->pid[0] == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	// if (pipex->pid[0] == 0)
	// {	
	// 	dup2();
	// 	execve();
	// }
	// else	
		// close();
	
		
}
void	init_struct(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->infile = argv[2];
	pipex->outfile = argv[argc - 1];
	pipex->envp = envp;
	pipex->nbr_cmd = argc - 3;
	//pipex->arg_cmd = argv + 2; //demander a matheo pq il fait ca de cette facon
}
int	main(int argc, char **argv, char **envp)
{
	static t_pipex	pipex = {0};
	
	init_struct(&pipex, argc, argv, envp);
	access_cmd(&pipex);
	//check_args;
	//parse_cmd;
	//parse_args
	// while(pipex.arg_cmd)
		// piping_and_forking(&pipex);
	// get_path(&pipex, envp);	
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