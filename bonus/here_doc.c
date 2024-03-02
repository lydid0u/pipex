/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:01:13 by lboudjel          #+#    #+#             */
/*   Updated: 2023/12/21 17:13:52 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	here_doc(char *infile, char *stop_word)
{
	int		fd;
	char	*line;

	fd = open(infile, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
		return (perror("Error"), exit(1));
	stop_word = ft_strjoin(stop_word, "\n");
	while (1)
	{
		write(1, "heredoc> ", 10);
		line = get_next_line(0, 0);
		if (!line)
			break ;
		if (ft_strcmp(line, stop_word) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	get_next_line(0, 1);
	free(stop_word);
	close(fd);
}
