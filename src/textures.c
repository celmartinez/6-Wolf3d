/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbataini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 05:39:10 by bbataini          #+#    #+#             */
/*   Updated: 2018/11/28 03:07:50 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void		init_textures(t_struct *p)
{
	int i;
	int bpp;
	int fd;

	i = 0;
	while (i < TEX)
	{
		if ((fd = open(p->tex[i].str, O_RDONLY)) != -1)
		{
			p->tex[i].img_ptr = mlx_xpm_file_to_image(p->mlx_ptr, p->tex[i].str,
					&p->tex[i].width, &p->tex[i].height);
			p->tex[i].img_str = mlx_get_data_addr(p->tex[i].img_ptr, &bpp,
					&p->tex[i].sizeline, &p->tex[i].endian);
			close(fd);
		}
		else
		{
			ft_putendl("error, textures are missing");
			system("killall afplay");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void		load_textures3(t_struct *p)
{
	p->tex[48].str = ft_strdup("textures/lego_sprite1.xpm");
	p->tex[49].str = ft_strdup("textures/lego_sprite2.xpm");
	p->tex[50].str = ft_strdup("textures/lego_starship.xpm");
	p->tex[51].str = ft_strdup("textures/lego_tree.xpm");
	p->tex[52].str = ft_strdup("textures/Van_Gogh_nuit2.xpm");
	p->tex[53].str = ft_strdup("textures/Van_Gogh_nuit1.xpm");
	p->tex[54].str = ft_strdup("textures/Claude_Monet_soleil.xpm");
	p->tex[55].str = ft_strdup("textures/Claude_Monet_soleil1.xpm");
	p->tex[56].str = ft_strdup("textures/babel1.xpm");
	p->tex[57].str = ft_strdup("textures/dali.xpm");
	p->tex[58].str = ft_strdup("textures/Mona_Lisa.xpm");
	p->tex[59].str = ft_strdup("textures/Monet1.xpm");
	p->tex[60].str = ft_strdup("textures/Monet2.xpm");
	p->tex[61].str = ft_strdup("textures/Monet3.xpm");
	p->tex[62].str = ft_strdup("textures/cat.xpm");
	p->tex[63].str = ft_strdup("textures/babel2.xpm");
	p->tex[64].str = ft_strdup("textures/murbobo.xpm");
	p->tex[65].str = ft_strdup("textures/rosace.xpm");
	init_textures(p);
}

void		load_textures2(t_struct *p)
{
	p->tex[24].str = ft_strdup("textures/lego_logo.xpm");
	p->tex[25].str = ft_strdup("textures/klimt.xpm");
	p->tex[26].str = ft_strdup("textures/la_liberte_guidant_le_peuple.xpm");
	p->tex[27].str = ft_strdup("textures/la_Meduse.xpm");
	p->tex[28].str = ft_strdup("textures/nympheas.xpm");
	p->tex[29].str = ft_strdup("textures/redon.xpm");
	p->tex[30].str = ft_strdup("textures/vinci-1.xpm");
	p->tex[31].str = ft_strdup("textures/vinci-2.xpm");
	p->tex[32].str = ft_strdup("textures/yport.xpm");
	p->tex[33].str = ft_strdup("textures/zeus.xpm");
	p->tex[34].str = ft_strdup("textures/klimt2.xpm");
	p->tex[35].str = ft_strdup("textures/klee.xpm");
	p->tex[36].str = ft_strdup("textures/jeunefille.xpm");
	p->tex[37].str = ft_strdup("textures/EdvardMunch.xpm");
	p->tex[38].str = ft_strdup("textures/chagall.xpm");
	p->tex[39].str = ft_strdup("textures/Basquiat.xpm");
	p->tex[40].str = ft_strdup("textures/aphrodite.xpm");
	p->tex[41].str = ft_strdup("textures/chagall.xpm");
	p->tex[42].str = ft_strdup("textures/lego_tresure.xpm");
	p->tex[43].str = ft_strdup("textures/lego_woman.xpm");
	p->tex[44].str = ft_strdup("textures/lego_baby.xpm");
	p->tex[45].str = ft_strdup("textures/lego_dog.xpm");
	p->tex[46].str = ft_strdup("textures/lego_guy.xpm");
	p->tex[47].str = ft_strdup("textures/lego_policeman.xpm");
	load_textures3(p);
}

void		load_textures(t_struct *p)
{
	p->tex[0].str = ft_strdup("textures/Potatoe.xpm");
	p->tex[1].str = ft_strdup("textures/Plane.xpm");
	p->tex[2].str = ft_strdup("textures/Dinosaur.xpm");
	p->tex[3].str = ft_strdup("textures/Tower.xpm");
	p->tex[4].str = ft_strdup("textures/Basic-5-Yellow.xpm");
	p->tex[5].str = ft_strdup("textures/Basic-6-Blue.xpm");
	p->tex[6].str = ft_strdup("textures/Matrix.xpm");
	p->tex[7].str = ft_strdup("textures/Basic-0-Floor.xpm");
	p->tex[8].str = ft_strdup("textures/Basic-1.xpm");
	p->tex[9].str = ft_strdup("textures/Basic-2.xpm");
	p->tex[10].str = ft_strdup("textures/Basic-3.xpm");
	p->tex[11].str = ft_strdup("textures/Basic-4.xpm");
	p->tex[12].str = ft_strdup("textures/bbataini.xpm");
	p->tex[13].str = ft_strdup("textures/cmartine.xpm");
	p->tex[14].str = ft_strdup("textures/Mobil1.xpm");
	p->tex[15].str = ft_strdup("textures/Mobil2.xpm");
	p->tex[16].str = ft_strdup("textures/Mobil3.xpm");
	p->tex[17].str = ft_strdup("textures/Plane_.xpm");
	p->tex[18].str = ft_strdup("textures/Potatoe_.xpm");
	p->tex[19].str = ft_strdup("textures/Dinosaur_.xpm");
	p->tex[20].str = ft_strdup("textures/Tower_.xpm");
	p->tex[21].str = ft_strdup("textures/Theend.xpm");
	p->tex[22].str = ft_strdup("textures/Gandalf.xpm");
	p->tex[23].str = ft_strdup("textures/lego_sol.xpm");
	load_textures2(p);
}
