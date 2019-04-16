/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbataini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 01:01:59 by bbataini          #+#    #+#             */
/*   Updated: 2018/11/28 01:13:28 by bbataini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		youshall(t_struct *p)
{
	if (p->sprite[0].k == 6 && p->sprite[1].k
			== 6 && p->sprite[2].k == 6 && p->sprite[3].k == 6)
	{
		system("killall afplay");
		system("afplay ./musics/matrix.mp3 &");
		p->c->p_x = 1.5;
		p->k = 5;
	}
	else if (p->c->youshall == 0)
		system("afplay ./musics/youshall.mp3 &");
	else if (p->c->youshall == 20)
		system("afplay ./musics/nop.mp3 &");
	else if (p->c->youshall == 40)
		system("afplay ./musics/isaid.mp3 &");
	else if (p->c->youshall == 70)
	{
		system("afplay ./musics/mmpf.mp3 &");
		p->c->youshall = -18;
	}
	p->c->youshall++;
}

void			rotation(t_struct *p, int key)
{
	float tmp_dir_x;
	float tmp_plane_x;

	if (key == LEFT)
		p->c->rotation_speed = 0.1;
	if (key == RIGHT)
		p->c->rotation_speed = -0.1;
	tmp_dir_x = p->c->dir_x;
	p->c->dir_x = tmp_dir_x * cos(-p->c->rotation_speed) -
		p->c->dir_y * sin(-p->c->rotation_speed);
	p->c->dir_y = tmp_dir_x * sin(-p->c->rotation_speed) +
		p->c->dir_y * cos(-p->c->rotation_speed);
	tmp_plane_x = p->c->plane_x;
	p->c->plane_x = tmp_plane_x * cos(-p->c->rotation_speed) -
		p->c->plane_y * sin(-p->c->rotation_speed);
	p->c->plane_y = tmp_plane_x * sin(-p->c->rotation_speed) +
		p->c->plane_y * cos(-p->c->rotation_speed);
}

static void		move_up3(t_struct *p, int move)
{
	if (move == 5 || move == 4)
	{
		if (p->k == 0 && move == 5)
		{
			p->c->p_x = 1.5;
			p->k = 3;
		}
		else if (p->k == 0 && move == 4)
		{
			p->c->p_x = 13.5;
			p->k = 4;
		}
		else
		{
			p->k = 0;
			p->c->p_x = ((int)p->c->p_x == 13) ? 1.5 : 13.5;
		}
	}
	if (move == 21)
		close_window(p);
	if (move == 22)
		youshall(p);
}

static void		move_up2(t_struct *p, int move)
{
	if (move == 13)
	{
		system("killall afplay");
		system("afplay ./musics/lego.mp3 &");
		if (p->k == 2)
		{
			system("killall afplay");
			system("afplay ./musics/amblobby.mp3 &");
		}
		p->c->p_y = (p->k == 0) ? 13.5 : 1.5;
		p->k = (p->k == 0) ? 2 : 0;
	}
	else if (move == 12)
	{
		system("killall afplay");
		system("afplay ./musics/ambbobo.mp3 &");
		if (p->k == 1)
		{
			system("killall afplay");
			system("afplay ./musics/amblobby.mp3 &");
		}
		p->c->p_y = (p->k == 0) ? 1.5 : 13.5;
		p->k = (p->k == 0) ? 1 : 0;
	}
	move_up3(p, move);
}

void			move_up(t_struct *p, int move, int i, float s)
{
	if (move == 0)
	{
		while (i < 5)
		{
			if (p->map[p->k][(int)((p->c->p_x + p->c->dir_x * i * s / 4))]
					[(int)((p->c->p_y + p->c->dir_y * i * s / 4))] == 1)
				break ;
			if (++i == 5)
			{
				p->c->p_x += p->c->dir_x * s;
				p->c->p_y += p->c->dir_y * s;
			}
		}
	}
	if (move == 12 || move == 13 || move == 5 || move == 4)
		system("afplay ./musics/tp.mp3 &");
	move_up2(p, move);
}
