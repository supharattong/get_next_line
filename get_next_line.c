/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthanikp <jthanikp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:54:42 by jthanikp          #+#    #+#             */
/*   Updated: 2023/03/30 18:14:50 by jthanikp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *buff, char *stash)
{
	char	*temp;
	int		read_status;

	read_status = 1;
	while (read_status != 0)
	{
		read_status = read(fd, buff, BUFFER_SIZE);
		if (read_status == -1)
			return (NULL);
		if (read_status == 0)
			break ;
		buff[read_status] = '\0';
		if (!stash)
			stash = ft_strdup("");
		temp = stash;
		stash = ft_strjoin(temp, buff);
		free(temp);
		temp = NULL;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (stash);
}

char	*ft_clean(char *line)
{
	char	*temp;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (NULL);
	temp = ft_substr(line, i + 1, ft_strlen(line) - (i + 1));
	if (*temp == '\0')
	{
		free(temp);
		temp = NULL;
	}
	line[i + 1] = '\0';
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*line;
	static char	*stash[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!buff)
		return (NULL);
	line = read_file(fd, buff, stash[fd]);
	free(buff);
	buff = NULL;
	if (line)
		stash[fd] = ft_clean(line);
	return (line);
}
