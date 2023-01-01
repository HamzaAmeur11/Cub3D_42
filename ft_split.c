/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:52:24 by hameur            #+#    #+#             */
/*   Updated: 2022/12/31 21:52:09 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	nbr_mots(char const *s, char c)
{
	int	i;
	int	nbr_mots;

	i = 0;
	nbr_mots = 0;
	if (s[0] != c && s[0])
		nbr_mots++;
	while (s[i] != 0)
	{
		if (s[i] == c)
		{
			if (s[i + 1] != c && s[i + 1] != 0)
			{
				nbr_mots++;
				i++;
			}
			else
				i++;
		}
		else
			i++;
	}
	return (nbr_mots);
}

char	*ft_copy(char *str, int start, int end)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = start;
	ret = (char *)malloc((end - start + 1) * sizeof(char));
	while (j < end)
		ret[i++] = str[j++];
	ret[i] = 0;
	return (ret);
}

int	find_char(char *str, int pos, char c, int id)
{
	while (str[pos] == c)
		pos++;
	while (str[pos] != c && str[pos] != 0)
		pos++;
	if (id == 2)
	{
		while (str[pos + 1] == c)
			pos++;
	}
	if (str[pos] == 0 && id == 0)
		return (0);
	return (pos);
}

static char	**ft_remplissage(char *s, char **copy, char c)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	while (s[start] == c)
		start++;
	end = 0;
	end = find_char(s, end, c, 0);
	while (end != 0)
	{
		copy[i++] = ft_copy(s, start, end);
		end = find_char(s, end + 1, c, 0);
		start = find_char(s, start, c, 2) + 1;
	}
	end = find_char(s, start + 1, c, 2);
	if (start != ft_strlen(s))
		copy[i++] = ft_copy(s, start, end);
	copy[i] = NULL;
	return (copy);
}

char	**ft_split(char *s, char c)
{
	char	**copy;

	if (!s)
		return (NULL);
	if (!*s)
	{
		copy = (char **)malloc (sizeof (char *) * 1);
		if (!copy)
			return (NULL);
		return (copy[0] = NULL, copy);
	}
	copy = (char **)malloc(sizeof(char *) * (nbr_mots(s, c) + 1));
	if (!copy)
		return (NULL);
	return (ft_remplissage(s, copy, c));
}
