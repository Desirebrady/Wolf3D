/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshumba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 10:26:45 by dshumba           #+#    #+#             */
/*   Updated: 2018/08/14 11:06:10 by dshumba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		key_press(int keycode, t_mlx *t)
{
	if (keycode == 13)
		t->player.move[0] = 1;
	else if (keycode == 1)
		t->player.move[1] = 1;
	else if (keycode == 124)
		t->player.move[2] = 1;
	else if (keycode == 123)
		t->player.move[3] = 1;
	else if (keycode == 257)
		t->player.player_speed = 0.15f;
	else if (keycode == 53)
		exit(1);
	else if (keycode == 117)
		wolf3d_init(t);
	return (0);
}

int		key_release(int keycode, t_mlx *t)
{
	if (keycode == 13)
		t->player.move[0] = 0;
	else if (keycode == 1)
		t->player.move[1] = 0;
	else if (keycode == 124)
		t->player.move[2] = 0;
	else if (keycode == 123)
		t->player.move[3] = 0;
	else if (keycode == 257)
		t->player.player_speed = 0.05;
	return (0);
}

void	move_side(t_mlx *t)
{
	if (t->player.move[2] == 1)
	{
		t->player.rot.x = t->player.rot.x * cos(-t->player.rot_speed) -
							t->player.rot.y * sin(-t->player.rot_speed);
		t->player.rot.y = t->player.old_rot.x * sin(-t->player.rot_speed) +
							t->player.rot.y * cos(-t->player.rot_speed);
		t->camera.old_fov.x = t->camera.fov.x;
		t->camera.fov.x = t->camera.fov.x * cos(-t->player.rot_speed) -
							t->camera.fov.y * sin(-t->player.rot_speed);
		t->camera.fov.y = t->camera.old_fov.x * sin(-t->player.rot_speed) +
							t->camera.fov.y * cos(-t->player.rot_speed);
	}
	if (t->player.move[3] == 1)
	{
		t->player.rot.x = t->player.rot.x * cos(t->player.rot_speed) -
							t->player.rot.y * sin(t->player.rot_speed);
		t->player.rot.y = t->player.old_rot.x * sin(t->player.rot_speed) +
							t->player.rot.y * cos(t->player.rot_speed);
		t->camera.old_fov.x = t->camera.fov.x;
		t->camera.fov.x = t->camera.fov.x * cos(t->player.rot_speed) -
							t->camera.fov.y * sin(t->player.rot_speed);
		t->camera.fov.y = t->camera.old_fov.x * sin(t->player.rot_speed) +
							t->camera.fov.y * cos(t->player.rot_speed);
	}
	t->player.old_rot.x = t->player.rot.x;
}

int		move(t_mlx *t)
{
	if (t->player.move[0] == 1)
	{
		if (t->map[(int)(t->player.pos.x + t->player.rot.x *
					t->player.player_speed)][(int)(t->player.pos.y)] == 0)
			t->player.pos.x += t->player.rot.x * t->player.player_speed;
		if (t->map[(int)(t->player.pos.x)][(int)(t->player.pos.y +
					t->player.rot.y * t->player.player_speed)] == 0)
			t->player.pos.y += t->player.rot.y * t->player.player_speed;
	}
	if (t->player.move[1] == 1)
	{
		if (t->map[(int)(t->player.pos.x - t->player.rot.x *
					t->player.player_speed)][(int)(t->player.pos.y)] == 0)
			t->player.pos.x -= t->player.rot.x * t->player.player_speed;
		if (t->map[(int)(t->player.pos.x)][(int)(t->player.pos.y -
					t->player.rot.y * t->player.player_speed)] == 0)
			t->player.pos.y -= t->player.rot.y * t->player.player_speed;
	}
	move_side(t);
	ray_casting(t);
	return (0);
}
