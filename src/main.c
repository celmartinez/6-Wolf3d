/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbataini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 03:25:55 by bbataini          #+#    #+#             */
/*   Updated: 2018/11/28 22:15:33 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

int				close_window(t_struct *p)
{
	mlx_destroy_image(p->mlx_ptr, p->img_ptr);
	mlx_destroy_window(p->mlx_ptr, p->w_ptr);
	system("killall afplay");
	exit(EXIT_SUCCESS);
}

static void		*init(t_struct *param)
{
	t_camera	*camera;

	if (!(camera = (t_camera *)malloc(sizeof(t_camera))))
		return (NULL);
	param->c = camera;
	camera->p_x = 6.5;
	camera->p_y = 7.5;
	camera->dir_x = -1;
	camera->dir_y = 0;
	camera->plane_x = 0;
	camera->plane_y = 1;
	camera->move_speed = 0.2;
	camera->pas = 1;
	camera->youshall = 0;
	camera->tpobj = 0;
	system("afplay ./musics/amblobby.mp3 &");
	return (NULL);
}

static void		window(t_struct *p, int w, int h)
{
	int bpp;
	int size_l;
	int endian;

	p->mlx_ptr = mlx_init();
	p->w_ptr = mlx_new_window(p->mlx_ptr, 1620, 960, "wolf3D");
	p->img_ptr = mlx_new_image(p->mlx_ptr, WIDTHMAP * 2, HEIGHTMAP - 200);
	p->img_ptr2 = mlx_new_image(p->mlx_ptr, 1280, 960);
	p->img_ptr3 = mlx_xpm_file_to_image(p->mlx_ptr, "textures/W.xpm", &w, &h);
	p->img_str = mlx_get_data_addr(p->img_ptr, &bpp, &size_l, &endian);
	p->img_str2 = mlx_get_data_addr(p->img_ptr2, &bpp, &p->size_line, &endian);
	p->img_str3 = mlx_get_data_addr(p->img_ptr3, &bpp, &size_l, &endian);
	init(p);
	load_textures(p);
	raycasting(p, 0, 0);
	mlx_put_image_to_window(p->mlx_ptr, p->w_ptr, p->tex[17].img_ptr, -30, 210);
	mlx_put_image_to_window(p->mlx_ptr, p->w_ptr, p->tex[18].img_ptr, 140, 375);
	mlx_put_image_to_window(p->mlx_ptr, p->w_ptr, p->tex[19].img_ptr, -30, 375);
	mlx_put_image_to_window(p->mlx_ptr, p->w_ptr, p->tex[20].img_ptr, 140, 210);
	mlx_hook(p->w_ptr, KEYPRESS, KEYPRESSMASK, key_press_hook, p);
	mlx_hook(p->w_ptr, CLOSE, CLOSEMASK, close_window, p);
	mlx_loop(p->mlx_ptr);
}

int				main(int argc, const char **argv)
{
	t_struct	param;

	(void)argv;
	if (argc > 1)
	{
		perror("error, no argument needed");
		return (1);
	}
	if (WIDTH != 1280 || HEIGHT != 960)
	{
		ft_putendl("error, wrong size of window");
		exit(EXIT_FAILURE);
	}
	save_map(&param);
	window(&param, 0, 0);
	return (0);
}
