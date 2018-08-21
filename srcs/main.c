/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshumba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 10:23:51 by dshumba           #+#    #+#             */
/*   Updated: 2018/08/14 10:23:53 by dshumba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		expose_hook(t_mlx *mlx)
{
	ray_casting(mlx);
	return (0);
}

int		ft_close(void)
{
	exit(1);
	return (0);
}

void	mlx_win_init(t_mlx *t)
{
	char	*title;

	title = ft_strjoin("Wolf3d : ", t->map_name);
	t->mlx = mlx_init();
	t->win = mlx_new_window(t->mlx, WINX, WINY, "wolf3d");
	ft_strdel(&title);
}

void	wolf3d_init(t_mlx *t)
{
	t->player.pos.x = 3;
	t->player.pos.y = 3;
	t->player.player_speed = 0.05;
	t->player.move[0] = 0;
	t->player.move[1] = 0;
	t->player.move[2] = 0;
	t->player.move[3] = 0;
	t->player.rot.x = -1;
	t->player.rot.y = 0;
	t->player.rot_speed = 0.05;
	t->camera.fov.x = 0;
	t->camera.fov.y = 0.66f;
	t->skybox.tex_xy.x = 0;
	t->skybox.tex_xy.y = 0;
	load_textures(t);
}

int		main(int ac, char **av)
{
	t_mlx *t;

	if (ac != 2)
	{
		ft_putstr(USAGE);
		return (0);
	}
	if (!(t = (t_mlx *)malloc(sizeof(t_mlx))))
		return (0);
	if (!(read_map(t, av)))
		return (0);
	mlx_win_init(t);
	mlx_hook(t->win, 17, 0, ft_close, t);
	mlx_hook(t->win, 2, 0, key_press, t);
	mlx_hook(t->win, 3, 0, key_release, t);
	wolf3d_init(t);
	ray_casting(t);
	mlx_loop_hook(t->mlx, move, t);
	mlx_loop(t->mlx);
}
