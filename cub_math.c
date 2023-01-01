/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 23:36:22 by hameur            #+#    #+#             */
/*   Updated: 2023/01/01 00:05:16 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

double	rad_to_deg(double rad)
{
	return (rad * 180 / M_PI);
}

double	deg_to_rad(double deg)
{
	return (deg * M_PI / 180);
}

double	normalize_rad(double angle)
{
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	if (angle >= 2 * M_PI)
		angle = angle - (2 * M_PI);
	return (angle);
}

double	normalize_deg(double angle)
{
	if (angle < 0)
		angle = 360 + angle;
	if (angle >= 360)
		angle = angle - 360;
	return (angle);
}

double	distence(t_point p, t_point q)
{
	return (sqrt(((p.x - q.x) * (p.x - q.x)) + (p.y - q.y) * (p.y - q.y)));
}
