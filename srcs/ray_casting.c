/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshumba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 11:21:20 by dshumba           #+#    #+#             */
/*   Updated: 2018/08/14 11:34:44 by dshumba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	dda_init(t_mlx *t)
{
	t->ray.dist.x = sqrt(1 + pow(t->ray.raydir.y / t->ray.raydir.x, 2));
	t->ray.dist.y = sqrt(1 + pow(t->ray.raydir.x / t->ray.raydir.y, 2));
	if (t->ray.raydir.x < 0)
	{
		t->ray.steps.x = -1;
		t->ray.s_dist.x = (t->ray.raypos.x - t->ray.ray_map.x) * t->ray.dist.x;
	}
	else
	{
		t->ray.steps.x = 1;
		t->ray.s_dist.x = (t->ray.ray_map.x + 1.0 - t->ray.raypos.x)
													* t->ray.dist.x;
	}
	if (t->ray.raydir.y < 0)
	{
		t->ray.steps.y = -1;
		t->ray.s_dist.y = (t->ray.raypos.y - t->ray.ray_map.y) * t->ray.dist.y;
	}
	else
	{
		t->ray.steps.y = 1;
		t->ray.s_dist.y = (t->ray.ray_map.y + 1.0 - t->ray.raypos.y)
													* t->ray.dist.y;
	}
}

void	dda(t_mlx *t)
{
	t->ray.hit = 0;
	while (t->ray.hit == 0)
	{
		if (t->ray.s_dist.x < t->ray.s_dist.y)
		{
			t->ray.s_dist.x += t->ray.dist.x;
			t->ray.ray_map.x += t->ray.steps.x;
			t->ray.side = 0;
		}
		else
		{
			t->ray.s_dist.y += t->ray.dist.y;
			t->ray.ray_map.y += t->ray.steps.y;
			t->ray.side = 1;
		}
		if (t->map[(int)t->ray.ray_map.x][(int)t->ray.ray_map.y] > 0)
			t->ray.hit = 1;
	}
}

void	ray_casting_init(t_mlx *t, int x)
{
	double current_rot_x;

	current_rot_x = 2 * x / (double)(WINX) - 1;
	t->ray.raypos.x = t->player.pos.x;
	t->ray.raypos.y = t->player.pos.y;
	t->ray.raydir.x = t->player.rot.x + t->camera.fov.x * current_rot_x;
	t->ray.raydir.y = t->player.rot.y + t->camera.fov.y * current_rot_x;
	t->ray.ray_map.x = (int)t->ray.raypos.x;
	t->ray.ray_map.y = (int)t->ray.raypos.y;
	dda_init(t);
	dda(t);
	if (t->ray.side == 0)
		t->ray.walldist = (t->ray.ray_map.x - t->ray.raypos.x +
				(1 - t->ray.steps.x) / 2) / t->ray.raydir.x;
	else
		t->ray.walldist = (t->ray.ray_map.y - t->ray.raypos.y +
				(1 - t->ray.steps.y) / 2) / t->ray.raydir.y;
}

void	ray_casting(t_mlx *t)
{
	int x;

	x = -1;
	t->render_image.img = mlx_new_image(t->mlx, WINX, WINY);
	t->render_image.data = mlx_get_data_addr(t->render_image.img,
											&t->render_image.bpp,
											&t->render_image.sizeline,
											&t->render_image.endian);
	draw_sky(t);
	while (++x < WINX)
	{
		ray_casting_init(t, x);
		t->draw.lineheight = (int)(WINY / t->ray.walldist);
		t->ray.start = -t->draw.lineheight / 2 + WINY / 2;
		if (t->ray.start < 0)
			t->ray.start = 0;
		t->ray.end = t->draw.lineheight / 2 + WINY / 2;
		if (t->ray.end >= WINY)
			t->ray.end = WINY - 1;
		draw_ground(t, x, 0x593E1A);
		draw_wall(x, t->ray.start - 1, t->ray.end, t);
	}
	mlx_put_image_to_window(t->mlx, t->win, t->render_image.img, 0, 0);
	mlx_destroy_image(t->mlx, t->render_image.img);
}
