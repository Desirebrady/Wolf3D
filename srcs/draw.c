/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshumba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 11:09:43 by dshumba           #+#    #+#             */
/*   Updated: 2018/08/14 11:21:14 by dshumba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	put_pxl_to_img(t_mlx *t, int x, int y)
{
	if (x < WINX && y < WINY)
	{
		t->skybox.tex_xy.y = abs((((y * 256 - WINY * 128 +
							t->draw.lineheight * 128) * 64)
							/ t->draw.lineheight) / 256);
		ft_memcpy(t->render_image.data + 4 * WINX * y + x * 4,
				&t->text_arr[t->ray.tex_id].data[(int)t->skybox.tex_xy.y % 64 *
				t->text_arr[t->ray.tex_id].sizeline +
				(int)t->skybox.tex_xy.x % 64 *
				t->text_arr[t->ray.tex_id].bpp / 8], sizeof(int));
	}
}

void	draw_wall(int x, int start, int end, t_mlx *t)
{
	t->ray.tex_id = t->map[(int)t->ray.ray_map.x][(int)t->ray.ray_map.y];
	if (t->ray.side == 0)
		t->draw.wallraypos = t->ray.raypos.y + t->ray.walldist *
												t->ray.raydir.y;
	else
		t->draw.wallraypos = t->ray.raypos.x + t->ray.walldist *
												t->ray.raydir.x;
	t->skybox.tex_xy.x = (int)(t->draw.wallraypos * (double)(64));
	if (t->ray.side == 0 && t->ray.raydir.x > 0)
		t->skybox.tex_xy.x = 64 - t->skybox.tex_xy.x - 1;
	if (t->ray.side == 1 && t->ray.raydir.y < 0)
		t->skybox.tex_xy.x = 64 - t->skybox.tex_xy.x - 1;
	t->skybox.tex_xy.x = fabs(t->skybox.tex_xy.x);
	while (++start <= end)
		put_pxl_to_img(t, x, start);
}

void	draw_sky(t_mlx *t)
{
	int texture_cood_x;
	int texture_cood_y;

	texture_cood_x = 0;
	while (texture_cood_x < WINX)
	{
		texture_cood_y = 0;
		while (texture_cood_y < WINY)
		{
			ft_memcpy(t->render_image.data + 4 * WINX * texture_cood_y +
									texture_cood_x * 4,
					&t->text_arr[6].data[texture_cood_y % SKYBOX_RES *
									t->text_arr[6].sizeline +
					texture_cood_x % (SKYBOX_RES / 10) *
									t->text_arr[6].bpp / 8], sizeof(int));
			texture_cood_y++;
		}
		texture_cood_x++;
	}
	t->skybox.tex_xy.x = texture_cood_x;
	t->skybox.tex_xy.y = texture_cood_y;
}

void	draw_ground(t_mlx *t, int x, int ground_colour)
{
	int y;

	if (t->ray.end > 0)
	{
		y = t->ray.end - 1;
		if (x < WINX && y < WINY)
			while (++y < WINY)
				ft_memcpy(t->render_image.data + 4 * WINX * y + x * 4,
						&ground_colour, sizeof(int));
	}
}
