/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 02:06:49 by cmartine          #+#    #+#             */
/*   Updated: 2018/11/28 03:10:14 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		take_object(t_struct *p)
{
	int i;
	int x;
	int y;

	i = 0;
	while (i < 4)
	{
		if ((int)p->sprited[i] == 0)
		{
			p->sprite[i].k = 6;
			if (i == 1 || i == 2)
				x = -30;
			if (i == 0 || i == 3)
				x = 140;
			if (i == 1 || i == 3)
				y = 210;
			if (i == 2 || i == 0)
				y = 375;
			mlx_put_image_to_window(p->mlx_ptr, p->w_ptr,
					p->tex[i].img_ptr, x, y);
			system("afplay ./musics/zip.mp3 &");
		}
		i++;
	}
}

void			soundstep(t_struct *p)
{
	if (p->c->pas == PAS && (p->c->pas = 1) == 1)
		system("afplay ./musics/pas1.mp3 &");
	else if (p->c->pas == PAS + 1 && (p->c->pas = 2) == 2)
		system("afplay ./musics/pas2.mp3 &");
	else if (p->c->pas == PAS + 2 && (p->c->pas = 3) == 3)
		system("afplay ./musics/pas3.mp3 &");
	else if (p->c->pas == PAS + 3 && (p->c->pas = 4) == 4)
		system("afplay ./musics/pas4.mp3 &");
	else if (p->c->pas == PAS + 4 && (p->c->pas = 5) == 5)
		system("afplay ./musics/pas5.mp3 &");
	else if (p->c->pas == PAS + 5 && (p->c->pas = 6) == 6)
		system("afplay ./musics/pas6.mp3 &");
	else if (p->c->pas == PAS + 6 && (p->c->pas = 0) == 0)
		system("afplay ./musics/pas7.mp3 &");
}

void			flee(t_struct *p)
{
	if ((int)p->sprited[2] == 0 && p->c->tpobj == 0)
	{
		p->sprite[2].x = 12;
		p->c->tpobj++;
		system("afplay ./musics/flee.mp3 &");
	}
	else if ((int)p->sprited[2] == 0 && p->c->tpobj == 1)
	{
		p->sprite[2].y = 12;
		p->c->tpobj++;
		system("afplay ./musics/flee.mp3 &");
	}
	else if ((int)p->sprited[2] == 0 && p->c->tpobj++ == 2)
	{
		p->sprite[2].x = 3;
		system("afplay ./musics/flee.mp3 &");
	}
}

int				key_press_hook(int key, t_struct *p)
{
	float s;

	if (key == 53)
		close_window(p);
	else if (key == SPACE)
		take_object(p);
	else if (key == RIGHT || key == LEFT)
		rotation(p, key);
	else if (key == UP || key == DOWN)
	{
		if (key == UP)
			s = 0.2;
		else
			s = -0.2;
		key = p->map[p->k][(int)((p->c->p_x + p->c->dir_x * s))]
			[(int)((p->c->p_y + p->c->dir_y * s))];
		soundstep(p);
		if (key == 0)
			p->c->pas += 7;
		move_up(p, key, 0, s);
	}
	if (p->k == 1)
		flee(p);
	raycasting(p, 0, 0);
	return (0);
}
