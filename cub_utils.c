/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:24:59 by hameur            #+#    #+#             */
/*   Updated: 2023/01/01 00:01:29 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	p = (char *)malloc(ft_strlen(s2) + ft_strlen(s1) + 1);
	if (!p)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != 0)
		p[i] = s1[i];
	while (s2[j] != 0)
		p[i++] = s2[j++];
	p[i] = 0;
	free(s1);
	return (p);
}

char	*ft_strdup(char *s1)
{
	char	*p;
	int		i;

	i = ft_strlen(s1);
	p = (char *)malloc(i + 1);
	if (!p)
		return (NULL);
	i = -1;
	while (s1[++i] != 0)
		p[i] = s1[i];
	p[i] = 0;
	return (p);
}

int	ft_atoi(char *str)
{
	int	resultat;
	int	i;

	resultat = 0;
	i = 0;
	while (((str[i] >= 9) && (str[i] <= 13)) || (str[i] == ' '))
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
		resultat = (resultat * 10) + (str[i++] - '0');
	return (resultat);
}

void	init_angle(t_plr *plr, char c)
{
	if (c == 'N')
	{
		plr->alpha = 270;
		plr->beta = (3 * M_PI) / 2;
	}
	else if (c == 'W')
	{
		plr->alpha = 180;
		plr->beta = M_PI;
	}
	else if (c == 'E')
	{
		plr->alpha = 0;
		plr->beta = 0;
	}
	else if (c == 'S')
	{
		plr->alpha = 90;
		plr->beta = M_PI / 2;
	}
}
