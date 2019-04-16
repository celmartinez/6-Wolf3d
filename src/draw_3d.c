/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 03:10:31 by cmartine          #+#    #+#             */
/*   Updated: 2018/11/28 22:12:22 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		which_text(t_struct *p)
{
	if (p->map[p->k][p->c->map_x % 18][p->c->map_y % 18] == 1)
	{
		if (p->c->side == 0 && p->c->r_dir_x > 0)
			p->tid = 9;
		else if (p->c->side == 0 && p->c->r_dir_x < 0)
			p->tid = 10;
		else if (p->c->side == 1 && p->c->r_dir_y > 0)
			p->tid = 11;
		else
			p->tid = 8;
	}
	else if (p->map[p->k][p->c->map_x % 18][p->c->map_y % 18] > 1)
		p->tid = p->map[p->k][p->c->map_x % 18][p->c->map_y % 18];
	if (p->c->what == 1)
	{
		p->tid = 7;
		if (p->k == 5)
			p->tid = 6;
	}
	if (p->k == 2 && p->tid != 24 && p->tid != 13)
		p->tid = 23;
	if (p->k == 1 && p->c->what == 1)
		p->tid = 65;
}

void			color_text(t_struct *p, int col, int line, float ratio)
{
	if (p->c->what != 2)
	{
		which_text(p);
		col = col * BPP;
		line = line * p->tex[p->tid].sizeline;
	}
	if (col + line + 3 < p->tex[p->tid].width * 4 * p->tex[p->tid].height)
	{
		p->color.r = p->tex[p->tid].img_str[col + line];
		p->color.r = (1 - ratio * 0.8) * p->color.r;
		p->color.g = p->tex[p->tid].img_str[col + line + 1];
		p->color.g = (1 - ratio * 0.8) * p->color.g;
		p->color.b = p->tex[p->tid].img_str[col + line + 2];
		p->color.b = (1 - ratio * 0.8) * p->color.b;
		p->color.a = p->tex[p->tid].img_str[col + line + 3];
	}
}

static void		floor_casting(t_struct *p, int x, int y, int z)
{
	float	distance;
	float	tmp_fl_x;
	float	tmp_fl_y;
	int		tex_x;
	int		tex_y;

	y = p->c->y_end;
	z = HEIGHT / 2 - (y - HEIGHT / 2);
	p->c->what = 1;
	while (y++ < HEIGHT - 1 && z-- > 0)
	{
		distance = (float)HEIGHT / (2.0 * (float)y - (float)HEIGHT);
		p->c->ra = distance / p->c->wall_dist;
		p->c->shadow = distance * 0.25;
		if (p->c->shadow > 1)
			p->c->shadow = 1;
		tmp_fl_x = p->c->ra * p->c->floor_x + (1.0 - p->c->ra) * p->c->p_x;
		tmp_fl_y = p->c->ra * p->c->floor_y + (1.0 - p->c->ra) * p->c->p_y;
		tex_x = (int)(tmp_fl_x * p->tex[p->tid].width) % p->tex[p->tid].width;
		tex_y = (int)(tmp_fl_y * p->tex[p->tid].height) % p->tex[p->tid].height;
		color_text(p, tex_x, tex_y, p->c->shadow);
		draw_pixel2(p, p->img_str2, x, y);
		draw_pixel2(p, p->img_str2, x, z);
	}
	p->c->what = 0;
}

static void		draw_floor_3d(t_struct *p, float wall_x)
{
	wall_x = (p->c->side == 0) ? p->c->r_pos_y + ((p->c->map_x - p->c->r_pos_x
		+ (1 - p->c->step_x) / 2) / p->c->r_dir_x) * p->c->r_dir_y
		: p->c->r_pos_x + ((p->c->map_y - p->c->r_pos_y
		+ (1 - p->c->step_y) / 2) / p->c->r_dir_y) * p->c->r_dir_x;
	wall_x -= floor(wall_x);
	if (p->c->side == 0 && p->c->r_dir_x > 0)
	{
		p->c->floor_x = p->c->map_x;
		p->c->floor_y = p->c->map_y + p->c->offset;
	}
	else if (p->c->side == 0 && p->c->r_dir_x < 0)
	{
		p->c->floor_x = p->c->map_x + 1.0;
		p->c->floor_y = p->c->map_y + p->c->offset;
	}
	else if (p->c->side == 1 && p->c->r_dir_y > 0)
	{
		p->c->floor_x = p->c->map_x + p->c->offset;
		p->c->floor_y = p->c->map_y;
	}
	else
	{
		p->c->floor_x = p->c->map_x + p->c->offset;
		p->c->floor_y = p->c->map_y + 1.0;
	}
}

void			draw_wall_3d(t_struct *p, int x, int y, int wall_height)
{
	int		tex_x;
	int		tex_y;
	float	distance;

	wall_height = abs((int)(HEIGHT / p->c->wall_dist));
	y = (int)(-wall_height / 2 + HEIGHT / 2);
	p->c->y_end = (int)(wall_height / 2 + HEIGHT / 2);
	if (y < 0)
		y = 0;
	if (p->c->y_end > HEIGHT)
		p->c->y_end = HEIGHT - 1;
	tex_x = p->c->offset * 256;
	draw_floor_3d(p, 0.0);
	floor_casting(p, x, 0, 0);
	distance = (float)HEIGHT / (2.0 * (float)p->c->y_end - (float)HEIGHT);
	p->c->shadow = distance * 0.25;
	if (p->c->shadow > 1)
		p->c->shadow = 1;
	while (y++ < p->c->y_end)
	{
		tex_y = (y * 2 - HEIGHT + wall_height)
			* (p->tex[p->tid].height / 2) / wall_height;
		color_text(p, tex_x, tex_y, p->c->shadow);
		draw_pixel2(p, p->img_str2, x, y);
	}
}
