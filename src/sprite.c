/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 02:30:42 by cmartine          #+#    #+#             */
/*   Updated: 2018/11/28 02:45:39 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int			sprited(t_struct *p, int i)
{
	int a;

	a = ((p->c->p_x - p->sprite[i].x) * (p->c->p_x - p->sprite[i].x)
			+ (p->c->p_y - p->sprite[i].y) * (p->c->p_y - p->sprite[i].y));
	return (a);
}

void				order_sprite(t_struct *p)
{
	int i;
	int tmp;

	i = -1;
	while (++i < NUMSPRITE)
	{
		p->ordersprite[i] = i;
		p->sprited[i] = sprited(p, i);
	}
	i = 0;
	while (i < NUMSPRITE - 1)
	{
		if (p->sprited[i] < p->sprited[i + 1])
		{
			tmp = p->sprited[i];
			p->sprited[i] = p->sprited[i + 1];
			p->sprited[i + 1] = tmp;
			tmp = p->ordersprite[i];
			p->ordersprite[i] = p->ordersprite[i + 1];
			p->ordersprite[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

static void			draw_sprite(t_struct *p, float d, float ratio, int col)
{
	int line;

	p->x = p->mspr.startx - 1;
	p->c->what = 2;
	while (++p->x < p->mspr.endx)
	{
		col = (p->x - p->mspr.startx) / d;
		col = col * BPP;
		if (p->mspr.transy > 0 && p->x > 0 && p->x < WIDTH &&
				p->mspr.transy < p->zbuff[p->x])
		{
			p->y = p->mspr.starty - 1;
			while (++p->y < p->mspr.endy)
			{
				line = (p->y - p->mspr.starty) / d;
				line = (line * p->tex[p->tid].sizeline);
				p->color.a = p->tex[p->tid].img_str[col + line + 3];
				if (p->color.a == 0)
				{
					color_text(p, col, line, ratio);
					draw_pixel2(p, p->img_str2, p->x, p->y);
				}
			}
		}
	}
}

static void			matrice_sprite(t_struct *p, int i)
{
	double		invdet;
	double		spritex;
	double		spritey;
	double		transformx;
	int			spriteheight;

	spritex = (p->sprite[p->ordersprite[i]].x - p->c->p_x);
	spritey = (p->sprite[p->ordersprite[i]].y - p->c->p_y);
	invdet = 1.0 / (p->c->plane_x
			* p->c->dir_y - p->c->dir_x * p->c->plane_y);
	transformx = invdet * (p->c->dir_y * spritex - p->c->dir_x * spritey);
	p->mspr.transy = invdet
		* (-p->c->plane_y * spritex + p->c->plane_x * spritey);
	p->mspr.spritescreenx = ((WIDTH / 2) * (1 + transformx / p->mspr.transy));
	spriteheight = abs((int)(HEIGHT / (p->mspr.transy)));
	p->mspr.starty = -spriteheight / 2 + HEIGHT / 2;
	p->mspr.endy = spriteheight / 2 + HEIGHT / 2;
	if (p->mspr.starty < 0)
		p->mspr.starty = 0;
	if (p->mspr.endy >= HEIGHT)
		p->mspr.endy = HEIGHT - 1;
}

void				raysprite(t_struct *p, float d, int i, float ratio)
{
	float		spritewidth;
	int			drawtmp;

	while (++i < NUMSPRITE)
	{
		if (p->sprite[p->ordersprite[i]].k == p->k)
		{
			p->sprited[p->ordersprite[i]] = sprited(p, p->ordersprite[i]);
			p->tid = p->sprite[p->ordersprite[i]].id;
			matrice_sprite(p, i);
			spritewidth = abs((int)(HEIGHT / (p->mspr.transy)));
			p->mspr.startx = -spritewidth / 2 + p->mspr.spritescreenx;
			if (p->mspr.startx < 0)
				p->mspr.startx = 0;
			p->mspr.endx = spritewidth / 2 + p->mspr.spritescreenx;
			d = spritewidth / 256;
			drawtmp = p->mspr.startx;
			p->mspr.startx = (1280 - p->mspr.endx);
			p->mspr.endx = (1280 - drawtmp);
			ratio = p->sprited[p->ordersprite[i]] * 0.1;
			if (ratio > 1)
				ratio = 1;
			draw_sprite(p, d, ratio, 0);
		}
	}
}
