/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoledan <mtoledan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:21:12 by mtoledan          #+#    #+#             */
/*   Updated: 2023/06/02 10:16:54 by mtoledan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	ssize_t		player;
	char		*buffer;
	static char	*stash;
	char		*line;

	player = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		free (stash);
		stash = NULL;
		return (NULL);
	}
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	stash = ft_well_read(fd, player, buffer, stash);
	if (!stash)
		return (NULL);
	line = line_return(stash);
	stash = new_stash(stash);
	return (line);
}

char	*ft_well_read(int fd, ssize_t player, char *buffer, char *stash)
{
	char	*temp;

	temp = "";
	while (player != 0)
	{
		player = read(fd, buffer, BUFFER_SIZE);
		temp = stash;
		if (player == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[player] = '\0';
		if (temp == NULL)
		{
			temp = ft_calloc(1, 1);
		}
		stash = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_where_backslash_n(stash) != -1)
			break ;
	}
	free(buffer);
	return (stash);
}

int	ft_where_backslash_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

char	*line_return(char *stash)
{
	int		loc;
	char	*res;

	if (!stash || stash[0] == '\0')
		return (NULL);
	loc = ft_where_backslash_n(stash);
	if (loc == -1)
	{
		res = ft_substr(stash, 0, ft_strlen(stash));
	}
	else
	{
		res = ft_substr(stash, 0, loc + 1);
	}
	return (res);
}

char	*new_stash(char *stash)
{
	char	*temp;
	int		loc;

	loc = ft_where_backslash_n(stash);
	if (!stash)
		return (NULL);
	if (loc == -1)
	{
		free(stash);
		return (NULL);
	}
	loc++;
	temp = ft_substr(stash, loc, ft_strlen(stash) - loc);
	if (!temp)
		return (NULL);
	free(stash);
	return (temp);
}
