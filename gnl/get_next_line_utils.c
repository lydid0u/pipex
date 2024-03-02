/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:58:58 by lboudjel          #+#    #+#             */
/*   Updated: 2023/12/26 16:33:37 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_malloc(char *buffer)
{
	if (!buffer)
		return (0);
	return (1);
}

int	ft__strlen(const char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		i++;
		return (i);
	}
	return (0);
}
