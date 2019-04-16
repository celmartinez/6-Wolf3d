/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 22:42:14 by cmartine          #+#    #+#             */
/*   Updated: 2018/11/28 03:11:21 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

t_sprite	*init_sprite(void)
{
	static t_sprite sprite[NUMSPRITE] = {
		{2, 7, 7.5, 0},
		{4, 10, 10, 1},
		{1, 3, 3, 2},
		{3, 7.5, 7.5, 3},
		{2, 11, 6, 48},
		{2, 11, 9, 49},
		{2, 2, 3, 47},
		{2, 13, 3.5, 43},
		{2, 2, 11.5, 46},
		{2, 13, 11.5, 50},
		{2, 8, 2, 51},
		{2, 4.5, 6, 42},
		{2, 4.5, 9.5, 44},
		{2, 8, 13, 45},
		{1, 7.5, 7.5, 33},
	};

	return (sprite);
}

void		wall_dist(t_struct *p)
{
	if (p->c->side == 0)
		p->c->wall_dist = fabs((p->c->map_x - p->c->r_pos_x +
					(1.0 - p->c->step_x) / 2.0) / p->c->r_dir_x);
	else
		p->c->wall_dist = fabs((p->c->map_y - p->c->r_pos_y +
					(1.0 - p->c->step_y) / 2.0) / p->c->r_dir_y);
	if (p->c->side == 0)
	{
		p->c->wall_dist = fabs((p->c->map_x - p->c->r_pos_x +
					(1.0 - p->c->step_x) / 2.0) / p->c->r_dir_x);
		p->c->offset = p->c->r_pos_y + ((p->c->map_x
					- p->c->r_pos_x + (1 - p->c->step_x) / 2)
				/ p->c->r_dir_x) * p->c->r_dir_y;
	}
	else
	{
		p->c->wall_dist = fabs((p->c->map_y - p->c->r_pos_y +
					(1.0 - p->c->step_y) / 2.0) / p->c->r_dir_y);
		p->c->offset = p->c->r_pos_x + ((p->c->map_y - p->c->r_pos_y
					+ (1 - p->c->step_y) / 2)
				/ p->c->r_dir_y) * p->c->r_dir_x;
	}
	p->c->offset -= floor(p->c->offset);
}

void		hit_walls(t_struct *p)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (p->c->side_x < p->c->side_y)
		{
			p->c->side_x += p->c->delta_x;
			p->c->map_x += p->c->step_x;
			p->c->side = 0;
		}
		else
		{
			p->c->side_y += p->c->delta_y;
			p->c->map_y += p->c->step_y;
			p->c->side = 1;
		}
		if (p->map[p->k][p->c->map_x][p->c->map_y] > 0)
			hit = 1;
	}
	wall_dist(p);
}

void		walls_sides(t_struct *p)
{
	p->c->map_x = (int)p->c->p_x;
	p->c->map_y = (int)p->c->p_y;
	p->c->delta_x = fabs(1 / p->c->r_dir_x);
	p->c->delta_y = fabs(1 / p->c->r_dir_y);
	p->c->step_y = 1;
	p->c->side_y = (p->c->map_y + 1.0 - p->c->r_pos_y)
		* p->c->delta_y;
	if (p->c->r_dir_x < 0)
	{
		p->c->step_x = -1;
		p->c->side_x = (p->c->r_pos_x - p->c->map_x) * p->c->delta_x;
	}
	else
	{
		p->c->step_x = 1;
		p->c->side_x = (p->c->map_x + 1.0 - p->c->r_pos_x)
			* p->c->delta_x;
	}
	if (p->c->r_dir_y < 0)
	{
		p->c->step_y = -1;
		p->c->side_y = (p->c->r_pos_y - p->c->map_y) * p->c->delta_y;
	}
	hit_walls(p);
}

void		raycasting(t_struct *p, int x, int z)
{
	ft_bzero(p->img_str, (WIDTHMAP - 200) * (HEIGHTMAP * 2) * 4);
	ft_bzero(p->img_str2, WIDTH * HEIGHT * 4);
	z = WIDTH - 1;
	while (x++ < WIDTH)
	{
		p->c->camera_x = (2.0 * x / (float)WIDTH) - 1.0;
		p->c->r_pos_x = p->c->p_x;
		p->c->r_pos_y = p->c->p_y;
		p->c->r_dir_x = p->c->dir_x + p->c->plane_x * p->c->camera_x;
		p->c->r_dir_y = p->c->dir_y + p->c->plane_y * p->c->camera_x;
		walls_sides(p);
		draw_wall_3d(p, z - x, 0, 0);
		p->zbuff[z - x] = p->c->wall_dist;
	}
	p->sprite = init_sprite();
	order_sprite(p);
	raysprite(p, 0.0, -1, 0.0);
	if (p->sprite[0].k == 6 && p->sprite[1].k == 6 && p->sprite[2].k == 6 &&
			p->sprite[3].k == 6)
		p->tex[22].img_str = p->tex[6].img_str;
	minimap(p);
	mlx_put_image_to_window(p->mlx_ptr, p->w_ptr, p->img_ptr, 35, 35);
	mlx_put_image_to_window(p->mlx_ptr, p->w_ptr, p->img_ptr2, 340, 0);
	mlx_put_image_to_window(p->mlx_ptr, p->w_ptr, p->img_ptr3, 0, 653);
}
