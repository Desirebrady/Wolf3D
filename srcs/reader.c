/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshumba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 11:34:55 by dshumba           #+#    #+#             */
/*   Updated: 2018/08/17 09:38:50 by dshumba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			check_the_map(char *buff, t_mlx *t)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	t->read.columns = ft_columns(buff);
	t->read.rows = ft_rows(buff);
	while (buff[i] && buff[i] != '\0')
	{
		if ((buff[i] < 48 || buff[i] > 57) && buff[i] != ' ' && buff[i] != '\n')
			return (0);
		len++;
		if (buff[i] == '\n')
		{
			if (len - 1 != t->read.columns)
				return (0);
			len = 0;
		}
		i++;
	}
	return (1);
}

int			read_pos(t_mlx *t, char **av)
{
	int		i;
	int		j;
	int		k;
	int		fd;
	char	*str;

	i = 0;
	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &str) > 0)
	{
		j = -1;
		k = 0;
		if (!(t->map[i] = (int *)malloc(sizeof(int) * t->read.columns)))
			return (0);
		while (++j < t->read.columns)
		{
			if (str[k] == ' ')
				k++;
			t->map[i][j] = ft_atoi(&str[k]);
			k++;
		}
		i++;
		free(str);
	}
	return (1);
}

int			read_map(t_mlx *t, char **av)
{
	int		fd;
	char	*buff;
	int		i;

	i = 0;
	buff = ft_strnew(10000);
	fd = open(av[1], O_RDONLY);
	if (fd < 0 || (read(fd, buff, 10000)) < 1)
		return (0);
	if (!(check_the_map(buff, t)))
		return (0);
	while (buff[i] != '\0' && buff[i] != '\n')
	{
		if (buff[i] == ' ')
			t->read.columns--;
		i++;
	}
	ft_strdel(&buff);
	t->map_name = av[1];
	close(fd);
	if (!(t->map = (int **)malloc(sizeof(int *) * t->read.rows))
			|| !(read_pos(t, av)))
		return (0);
	return (1);
}
