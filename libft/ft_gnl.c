/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:29:37 by szilas            #+#    #+#             */
/*   Updated: 2024/07/19 19:05:12 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <fcntl.h>

char	*trim_line(char *line, char *stash)
{
	size_t	len;
	char	*ret;
	char	*leftovers;

	if (!line)
		return (NULL);
	leftovers = ft_strchr(line, '\n') + 1;
	len = leftovers - line;
	ret = malloc((len + 1) * sizeof (char));
	if (!ret)
		return (free(line), NULL);
	ft_strlcpy(ret, line, len + 1);
	ft_bzero(stash, BUFFER_SIZE + 1);
	ft_strlcpy(stash, leftovers, BUFFER_SIZE + 1);
	free(line);
	return (ret);
}

char	*file_to_line(char *line, char *stash, int fd)
{
	ssize_t	len;

	len = BUFFER_SIZE;
	ft_bzero(stash, BUFFER_SIZE + 1);
	while (len == BUFFER_SIZE && !ft_strchr(stash, '\n'))
	{
		len = read(fd, stash, BUFFER_SIZE);
		if (len == -1)
			return (free(line), NULL);
		stash[len] = 0;
		line = ft_strjoin(line, stash);
		if (!line)
			return (NULL);
	}
	if (ft_strchr(stash, '\n'))
		line = trim_line(line, stash);
	if (!ft_strlen(line))
	{
		free(line);
		line = NULL;
		ft_bzero(stash, BUFFER_SIZE + 1);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (ft_strchr(stash, '\n'))
	{
		line = ft_strjoin(line, stash);
		line = trim_line(line, stash);
		return (line);
	}
	else if (ft_strlen(stash))
	{
		line = ft_strjoin(line, stash);
		if (!line)
			return (NULL);
	}
	line = file_to_line(line, stash, fd);
	return (line);
}
/* int main()
{
	int fd = open("in", O_RDONLY);
	if (fd == -1)
		return (-1);
	char *buf3;
	while (	(buf3 = get_next_line(fd)) != NULL)
	{
		ft_printf("%s", buf3);
		free(buf3);
	}
	return 0;
} */
