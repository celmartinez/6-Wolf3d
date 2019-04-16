/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 03:12:51 by cmartine          #+#    #+#             */
/*   Updated: 2018/11/28 22:11:06 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# define WIDTH 1280
# define HEIGHT 960
# define WIDTHMAP 640
# define HEIGHTMAP 480
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define SPACE 49
# define PAS 35
# define BPP 4
# define WHBPP 4915200
# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYPRESSMASK (1L<<0)
# define KEYRELEASEMASK (1L<<1)
# define CLOSE 17
# define CLOSEMASK (1L<<17)
# define NUMSPRITE 19
# define TEX 66
# define FOV 60
# define PI 3.14159256

typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}					t_color;

typedef struct		s_sprite
{
	int				k;
	float			y;
	float			x;
	int				id;
}					t_sprite;

typedef struct		s_mspr
{
	int				startx;
	int				starty;
	int				endx;
	int				endy;
	int				spritescreenx;
	double			transy;
}					t_mspr;

typedef struct		s_tex
{
	char			*str;
	int				height;
	int				width;
	void			*img_ptr;
	char			*img_str;
	int				sizeline;
	int				endian;
}					t_tex;

typedef struct		s_camera
{
	float			c_ang;
	float			c_speedmove;
	float			c_speedangle;
	float			p_x;
	float			p_y;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
	float			camera_x;
	float			r_pos_x;
	float			r_pos_y;
	float			r_dir_x;
	float			r_dir_y;
	float			floor_x;
	float			floor_y;
	int				map_x;
	int				map_y;
	int				side;
	int				step_x;
	int				step_y;
	float			shadow;
	int				what;
	float			side_x;
	float			side_y;
	float			delta_x;
	float			delta_y;
	float			wall_dist;
	int				y_end;
	float			offset;
	float			rotation_speed;
	float			move_speed;
	int				pas;
	float			inter_x;
	float			inter_y;
	int				i_sprite;
	float			len_sprite;
	int				youshall;
	int				tpobj;
	float			ra;
	int				colo;
	int				x1;
	int				calc;
}					t_camera;

typedef struct		s_struct
{
	t_tex			tex[TEX];
	float			zbuff[WIDTH];
	float			sprited[NUMSPRITE];
	int				ordersprite[NUMSPRITE];
	t_mspr			mspr;
	int				bpp;
	int				size_line;
	void			*mlx_ptr;
	void			*w_ptr;
	void			*img_ptr;
	void			*img_ptr2;
	void			*img_ptr3;
	char			*img_str;
	char			*img_str2;
	char			*img_str3;
	int				***map;
	int				k;
	int				tid;
	int				x;
	int				y;
	t_sprite		*sprite;
	t_color			color;
	t_camera		*c;
}					t_struct;

int					close_window(t_struct *p);
void				color_text(t_struct *p, int col, int line, float ratio);
void				draw_line(int y, int x2, int y2, t_struct *p);
void				draw_pixel(char *img_str, int x, int y, int color);
void				draw_pixel2(t_struct *p, char *img_str, int x, int y);
void				draw_wall_3d(t_struct *p, int x, int y, int wall_height);
int					hooks(t_struct *param);
void				load_textures(t_struct *p);
int					key_press_hook(int key, t_struct *p);
void				move_up(t_struct *p, int move, int i, float s);
void				minimap(t_struct *p);
void				order_sprite(t_struct *p);
void				raycasting(t_struct *param, int x, int z);
void				raysprite(t_struct *p, float d, int i, float ratio);
void				rotation(t_struct *p, int key);
void				save_map(t_struct *info);

#endif
