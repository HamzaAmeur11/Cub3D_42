/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:51:08 by hameur            #+#    #+#             */
/*   Updated: 2022/11/29 17:22:33 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	ft_strchr_nl(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*read_fd(int fd, char *str)
{
	char	*s;
	int		i;

	if (str == NULL)
		str = ft_strdup("");
	s = (char *)malloc(BUFFER_SIZE + 1);
	while (ft_strchr_nl(str) == 0)
	{
		i = read(fd, s, BUFFER_SIZE);
		if (i < 0)
			return (free(str), free(s), NULL);
		s[i] = 0;
		if (i == 0)
			break ;
		str = ft_strjoin(str, s);
	}
	return (free(s), str);
}

char	*new_line(char *str)
{
	int		i;
	char	*s;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\n' && str[i] != 0)
		i++;
	s = (char *)malloc(i + 2);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		s[i++] = '\n';
	s[i] = 0;
	return (s);
}

char	*rst_ln(char *str)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\n' && str[i] != 0)
		i++;
	if (str[i] == 0)
		return (free(str), NULL);
	if (str[i] == '\n')
		i++;
	s = (char *)malloc(ft_strlen(str) - i + 2);
	while (str[i] != 0)
		s[j++] = str[i++];
	s[j] = 0;
	return (free(str), s);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*nl;
	int			chrch;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	chrch = ft_strchr_nl(rest);
	if (chrch == 0)
		rest = read_fd(fd, rest);
	nl = new_line(rest);
	rest = rst_ln(rest);
	if (nl[0] == 0)
		return (free(nl), free(rest), NULL);
	return (nl);
}
