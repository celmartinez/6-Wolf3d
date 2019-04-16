/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbataini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 03:42:36 by bbataini          #+#    #+#             */
/*   Updated: 2018/11/28 03:12:15 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				*fill_color(int *str, int x, int y, int c)
{
	int w;
	int h;

	w = WIDTHMAP * 2;
	h = HEIGHTMAP - 200;
	if (str[x + w * y] != c && x + w * y < w * h)
	{
		str[x + w * y] = c;
		if (str[x + 1 + w * y] != c && x + 1 + w * y < w * h)
			str = fill_color(str, x + 1, y, c);
		if (str[x - 1 + w * y] != c)
			str = fill_color(str, x - 1, y, c);
		if (str[x + w * (y + 1)] != c && x + w * (y + 1) < w * h)
			str = fill_color(str, x, y + 1, c);
		if (str[x + w * (y - 1)] != c && x + w * (y - 1) < w * h)
			str = fill_color(str, x, y - 1, c);
	}
	return (str);
}

static int		laby_bonus(t_struct *p, int i, int j)
{
	int c;

	c = 0xFFFFFF;
	if (p->map[p->k][j][i] == 5)
		c = 0x33FFF6;
	if (p->map[p->k][j][i] == 4)
		c = 0xFFFF33;
	if (p->map[p->k][j][i] == 12)
		c = 0x33FF49;
	if (p->map[p->k][j][i] == 13)
		c = 0xFF33DD;
	return (c);
}

static void		labyrinthe(t_struct *p, int x, int y, int cb)
{
	int i;
	int j;

	j = -1;
	while (++j < 15)
	{
		i = -1;
		while (++i < 15)
		{
			if (p->map[p->k][j][i] >= 1)
			{
				p->c->colo = laby_bonus(p, i, j);
				x = j * 18;
				y = i * 18;
				p->c->x1 = x + cb;
				draw_line(y, x + cb, y + cb, p);
				p->c->x1 = x;
				draw_line(y, x + cb, y, p);
				draw_line(y + cb, x + cb, y + cb, p);
				draw_line(y, x, y + cb, p);
				if (p->map[p->k][j][i] == 22)
					fill_color((int *)p->img_str, x + 2, y + 2, p->c->colo);
			}
		}
	}
}

static void		sprite(t_struct *p, int c, int alpha, int r)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (p->sprite[i].k < 5 && p->sprite[i].k == p->k)
		{
			if (p->sprite[i].k == 2)
				c = 0xFF33DD;
			else if (p->sprite[i].k == 4)
				c = 0xFFFF33;
			else if (p->sprite[i].k == 1)
				c = 0x33FF49;
			else if (p->sprite[i].k == 3)
				c = 0x33FFF6;
			alpha = 0;
			while (alpha <= 360)
			{
				draw_pixel(p->img_str, p->sprite[i].x * 18 + r * cos(alpha),
						p->sprite[i].y * 18 + r * sin(alpha), c);
				alpha++;
			}
		}
		i++;
	}
}

void			minimap(t_struct *p)
{
	int alpha;
	int r;

	r = 5;
	alpha = 0;
	while (alpha <= 360)
	{
		draw_pixel(p->img_str, p->c->p_x * 18 + r * cos(alpha),
				p->c->p_y * 18 + r * sin(alpha), 0xFFFF);
		alpha++;
	}
	labyrinthe(p, 0, 0, 17);
	sprite(p, 0xFFFF, 0, 5);
	p->c->x1 = p->c->p_x * 18;
	draw_line(p->c->p_y * 18, p->c->p_x * 18
			+ p->c->dir_x * 18, p->c->p_y * 18 + p->c->dir_y * 18, p);
}
