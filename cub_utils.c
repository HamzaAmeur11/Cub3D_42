/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:24:59 by hameur            #+#    #+#             */
/*   Updated: 2022/12/24 21:59:29 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

double rad_to_deg(double rad)
{
	return (rad * 180 / M_PI);
}

double deg_to_rad(double deg)
{
	return (deg * M_PI / 180);
}


int	ft_strlen(char *str)
{
	int i;

	i = -1;
	while (str[++i] != 0)
		;
	return (i);
}

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
	return (p);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	x;

	x = 0;
	while ((s1[x] || s2[x]) && x < n)
	{
		if (s1[x] != s2[x])
			return (s1[x] - s2[x]);
		x++;
	}
	return (EXIT_SUCCESS);
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

void ft_bzero(char *str, int size)
{
	int i;

	i = 0;
	while (i < size)
		str[i++] = 0;
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd((char *)"-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n < 10)
		ft_putchar_fd(n + '0', fd);
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s == 0)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
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