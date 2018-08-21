/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshumba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 10:37:10 by dshumba           #+#    #+#             */
/*   Updated: 2018/08/17 09:55:04 by dshumba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

# define WINX 1024
# define WINY 768
# define SKYBOX_RES 596
# define USAGE "usage: wolf3d \"map\"\n"

typedef struct	s_readinfo
{
	int			columns;
	int			rows;
}				t_readinfo;

typedef struct	s_image
{
	void		*img;
	char		*data;
	int			bpp;
	int			sizeline;
	int			endian;
}				t_image;

typedef struct	s_vector3
{
	double		x;
	double		y;
	double		z;
}				t_vector3;

typedef struct	s_player
{
	int			move[4];
	double		player_speed;
	double		rot_speed;
	t_vector3	pos;
	t_vector3	rot;
	t_vector3	old_rot;
}				t_player;

typedef struct	s_draw
{
	int			lineheight;
	double		wallraypos;
}				t_draw;

typedef struct	s_skybox
{
	t_vector3	tex_xy;
}				t_skybox;

typedef struct	s_ray
{
	t_vector3	ray_map;
	int			start;
	int			end;
	int			tex_id;
	t_vector3	dist;
	t_vector3	raydir;
	t_vector3	steps;
	t_vector3	s_dist;
	t_vector3	raypos;
	int			side;
	int			hit;
	double		walldist;
}				t_ray;

typedef struct	s_camera
{
	t_vector3	fov;
	t_vector3	old_fov;
}				t_camera;

typedef struct	s_mlx
{
	t_readinfo	read;
	t_camera	camera;
	t_image		text_arr[9];
	t_image		render_image;
	t_draw		draw;
	char		*map_name;
	void		*mlx;
	void		*win;
	int			**map;
	t_player	player;
	t_ray		ray;
	t_skybox	skybox;
}				t_mlx;

void			draw_sky(t_mlx *t);
void			draw_ground(t_mlx *t, int x, int ground_colour);
void			draw_wall(int x, int start, int end, t_mlx *t);
void			put_pxl_to_img(t_mlx *t, int x, int y);

int				key_press2(int keycode, t_mlx *t);
int				key_press(int keycode, t_mlx *t);
int				key_release(int keycode, t_mlx *t);
void			move_side(t_mlx *t);
int				move(t_mlx *t);

void			load_textures(t_mlx *t);
void			load_textures2(t_mlx *t, int a, int b);

int				ft_close(void);
void			mlx_win_init(t_mlx *t);
void			wolf3d_init(t_mlx *t);

int				check_the_map(char *buff, t_mlx *t);
int				read_map(t_mlx *t, char **av);
int				read_pos(t_mlx *t, char **av);

void			ray_casting(t_mlx *t);
void			ray_casting_init(t_mlx *t, int x);
void			floor_and_ceiling(t_mlx *t, int x);
void			dda(t_mlx *t);
void			dda_init(t_mlx *t);

#endif
