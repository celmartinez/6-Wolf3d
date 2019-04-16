/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 23:11:14 by cmartine          #+#    #+#             */
/*   Updated: 2018/12/05 22:15:56 by bbataini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void			free_line(char **line_split)
{
	int i;

	i = 0;
	while (line_split[i])
	{
		free(line_split[i]);
		i++;
	}
	free(line_split);
}

static void		create_map2(t_struct *p, int i, char **l_s, int k)
{
	int j;

	j = -1;
	while (++j < 15 && l_s[j] != '\0')
	{
		p->map[k][i][j] = ft_atoi(l_s[j]);
		if ((i == 0 || i == 14)
				&& (p->map[k][i][j] <= 0 || p->map[k][i][j] >= 66))
		{
			ft_putendl("error, invalid map");
			exit(EXIT_FAILURE);
		}
		if ((j == 0 || j == 14)
				&& (p->map[k][i][j] <= 0 || p->map[k][i][j] >= 66))
		{
			ft_putendl("error, invalid map");
			exit(EXIT_FAILURE);
		}
	}
	if (j != 15)
	{
		ft_putendl("error, invalid map");
		exit(EXIT_FAILURE);
	}
}

static void		create_map(t_struct *info, int fd, int k)
{
	int		i;
	char	**line_split;
	char	*line;

	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		line_split = ft_strsplit(line, ' ');
		free(line);
		if (!(info->map[k][i] = (int *)malloc(sizeof(int) * 16)))
			exit(EXIT_FAILURE);
		create_map2(info, i, line_split, k);
		free_line(line_split);
		i++;
	}
	free(line);
	if (i != 15)
	{
		ft_putendl("error, invalid map");
		exit(EXIT_FAILURE);
	}
}

void			save_map2(t_struct *param, const char *file, int k)
{
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_putendl("error, missing map");
		exit(EXIT_FAILURE);
	}
	if (!(param->map[k] = (int **)malloc(sizeof(int *) * 16)))
		exit(EXIT_FAILURE);
	create_map(param, fd, k);
	close(fd);
}

void			save_map(t_struct *param)
{
	if (!(param->map = (int ***)malloc(sizeof(int **) * 6)))
		exit(EXIT_FAILURE);
	save_map2(param, "maps/laby.tkt", 0);
	save_map2(param, "maps/boris.tkt", 1);
	save_map2(param, "maps/celeste.tkt", 2);
	save_map2(param, "maps/laby2.tkt", 4);
	save_map2(param, "maps/laby3.tkt", 3);
	save_map2(param, "maps/matrix.tkt", 5);
}
