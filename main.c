/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:13:45 by lboudjel          #+#    #+#             */
/*   Updated: 2023/12/12 15:15:00 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*access_cmd(t_pipex *pipex, char **envp, int i)
{
	int j;
	char *access_cmd;
	
	j = 0;
	(void)i;
	pipex->args_path = get_path(envp);
	while (pipex->args_path[j])
	{
		access_cmd = ft_strjoin(pipex->args_path[j], pipex->cmd[0]);
		// printf("cmd found : %s\n", access_cmd);
		if (access(access_cmd, F_OK | X_OK) == 0)
			return(access_cmd);
		// printf("cmd no found : %s\n", access_cmd);
		free(access_cmd);
		j++;
	}
	return (NULL);
	// + ya ca a rajouter qlq part 
	// 
	// if (ft_strchr(tab2[0], '/'))
	// {
	// 	if (access(tab2[0], F_OK | X_OK) != -1)
	// 		return (ft_strdup(tab2[0]));
	// 	return (NULL);
	// }
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

char **create_cmd(t_pipex *pipex)
{
	char **temp;
	int i;

	i = 0;
	temp = ft_split(pipex->arg_cmd[i], ' ');
	while (temp[i])
	{
		printf("%s\n", temp[i]);
		i++;	
	}
	temp[i] = NULL;
	//fair eun str len de temp et ajouter 1 pour malloc et ajouter Null a la fin pour execve
	return temp;
}

void	child(t_pipex *pipex, char **envp, int i)
{
	char *path;

	pipex->cmd = create_cmd(pipex);
	path = access_cmd(pipex, envp, i);
	if (path)
		execve(path, pipex->cmd, NULL);
	//ajouter perror "bonne pratique" a mettre partout
}

void	*redirection(t_pipex *pipex, int i)
{
	if (i == 0)
	{
		if(dup2(pipex->infile_fd, STDIN_FILENO) == -1)
			return (perror("dup"), NULL);
		close (pipex->fd[0]);
		dup2(pipex->fd[1], STDOUT_FILENO);
		close (pipex->fd[1]);
	}
	if (i == 1)
	{
		if(dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
			return (perror("dup"), NULL);
		close (pipex->fd[1]);
		dup2(pipex->fd[0], STDOUT_FILENO);
		close (pipex->fd[0]);
	}
	return NULL;
}
void	*piping_and_forking(t_pipex *pipex, char **envp)
{
	int		i;
	
	i = 0;
	while(i < pipex->nbr_cmd)
	{
		pipe(pipex->fd);
		pipex->pid = fork();
		redirection(pipex, i);
		printf("current pid = %d\n", pipex->pid);
		if (pipex->pid == 0)
			child(pipex, envp, i);
		i++;
	}
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	wait(NULL);
	//a revoir avec waitpid
	return (NULL);
}
void	init_struct(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int i;

	i = 0;
	pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
	pipex->envp = envp;
	pipex->nbr_cmd = argc - 3;
	pipex->arg_cmd = argv + 2;
}
int	main(int argc, char **argv, char **envp)
{
	(void)envp;
	(void)argc;
	static t_pipex	pipex = {0};

	pipex.infile_fd = open(argv[1], O_RDONLY);
	if (pipex.infile_fd == -1)
		return (perror("open infile"), 0);
	pipex.outfile_fd = open(argv[4], O_WRONLY, O_CREAT | O_TRUNC, 0644);
	if (pipex.outfile_fd == -1)
		return (perror("open outfile"), 0);
	init_struct(&pipex, argc, argv, envp);
	piping_and_forking(&pipex, envp);
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