/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 23:49:54 by cmartine          #+#    #+#             */
/*   Updated: 2018/12/05 22:13:35 by bbataini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void		draw_pixel(char *img_str, int x, int y, int color)
{
	int *str;

	str = (int *)img_str;
	if (x + y * WIDTH < HEIGHT * WIDTH && x > 0 && y > 0)
		str[x + y * (int)WIDTH] = color;
}

void		draw_pixel2(t_struct *p, char *img_str, int x, int y)
{
	x = x * BPP;
	y = y * p->size_line;
	if (x + y + 4 < WHBPP)
	{
		img_str[x + y] = p->color.r;
		img_str[x + y + 1] = p->color.g;
		img_str[x + y + 2] = p->color.b;
	}
}

static void	draw_case_one(int y1, int x2, int y2, t_struct *p)
{
	int x;

	if (x2 - p->c->x1 != 0)
	{
		if (x2 < p->c->x1)
		{
			x = x2 - 1;
			while (++x <= p->c->x1 && (p->c->calc = x + (WIDTH * (y1 + (y2 - y1)
			* (x - p->c->x1) / (x2 - p->c->x1)))) < WIDTH * HEIGHT)
			{
				if (p->c->calc >= 0 && x >= 0 && x < WIDTH)
					((int *)p->img_str)[p->c->calc] = p->c->colo;
			}
		}
		else
		{
			x = p->c->x1 - 1;
			while (++x <= x2 && (p->c->calc = (x + (WIDTH * (y1 + (y2 - y1) *
				(x - p->c->x1) / (x2 - p->c->x1))))) < WIDTH * HEIGHT)
			{
				if (p->c->calc >= 0 && x >= 0 && x < WIDTH)
					((int *)p->img_str)[p->c->calc] = p->c->colo;
			}
		}
	}
}

static void	draw_case_two(int y1, int x2, int y2, t_struct *p)
{
	int y;
	int calc;

	if (y2 < y1)
	{
		y = y2 - 1;
		while (++y <= y1 && (calc = (p->c->x1 + (x2 - p->c->x1) * (y - y1) /
						(y2 - y1)) + (WIDTH * y)) < WIDTH * HEIGHT)
		{
			if (calc >= 0 && (p->c->x1 + (x2 - p->c->x1) * (y - y1) / (y2 - y1))
		>= 0 && (p->c->x1 + (x2 - p->c->x1) * (y - y1) / (y2 - y1)) < WIDTH)
				((int *)p->img_str)[calc] = p->c->colo;
		}
	}
	else
	{
		y = y1 - 1;
		while (++y <= y2 && (calc = (p->c->x1 + (x2 - p->c->x1) * (y - y1) /
					(y2 - y1)) + (WIDTH * y)) < WIDTH * HEIGHT)
		{
			if (calc >= 0 && (p->c->x1 + (x2 - p->c->x1) * (y - y1) / (y2 - y1))
		>= 0 && (p->c->x1 + (x2 - p->c->x1) * (y - y1) / (y2 - y1)) < WIDTH)
				((int *)p->img_str)[calc] = p->c->colo;
		}
	}
}

void		draw_line(int y, int x2, int y2, t_struct *p)
{
	int dx;
	int dy;

	dx = abs(p->c->x1 - x2);
	dy = abs(y - y2);
	if (dx >= dy)
		draw_case_one(y, x2, y2, p);
	if (dy >= dx)
		draw_case_two(y, x2, y2, p);
}
