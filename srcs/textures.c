/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshumba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 10:16:53 by dshumba           #+#    #+#             */
/*   Updated: 2018/08/14 10:58:02 by dshumba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		load_texture(t_mlx *t, char *path, int size)
{
	static int	i = 0;

	t->text_arr[i].img = mlx_xpm_file_to_image(t->mlx, path, &size, &size);
	t->text_arr[i].data = mlx_get_data_addr(t->text_arr[i].img,
												&t->text_arr[i].bpp,
												&t->text_arr[i].sizeline,
												&t->text_arr[i].endian);
	i++;
}

void			load_textures(t_mlx *t)
{
	int			texture_size;
	int			skybox_texture_size;

	texture_size = 64;
	skybox_texture_size = SKYBOX_RES;
	load_texture(t, "textures/wood.xpm", texture_size);
	load_texture(t, "textures/stone.xpm", texture_size);
	load_texture(t, "textures/mossy.xpm", texture_size);
	load_texture(t, "textures/redbrick.xpm", texture_size);
	load_texture(t, "textures/wood.xpm", texture_size);
	load_texture(t, "textures/sand.xpm", texture_size);
	load_texture(t, "textures/sky.xpm", skybox_texture_size);
}
