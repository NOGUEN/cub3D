/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:53:03 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/22 16:57:07 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		name_check(char *arg, char *ext){
	int	i;

	i = 0;
	while (arg[i] != '\0')
		i++;
	if ((i > 4 && arg[i - 1] == ext[2] && arg[i - 2] == ext[1])
		&& (arg[i - 3] == ext[0] && arg[i - 4] == '.'))
		return (1);
	return (0);
}

int		map_check(t_all *s){
	int		first_i;
	int		first_j;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((i = find_start_point(s, &i, &j)) == -1)
		return (-1);
	first_i = i;
	first_j = j;
	convert_wall(s, &i, &j);
	print_all(s);
	if (s->map.map[first_i][first_j + 1] == 'w')
		return (0);
	else
		return (-1);
	return (0);
}

void	pos_check(t_all *s){
	char	c;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++i < s->map.y){
		while (++j < s->map.x){
			c = s->map.map[i][j];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W'){
				s->map.map[i][j] = '0';
				s->pos.y = (double)i + 0.5;
				s->pos.x = (double)j + 0.5;
				s->dir.x = (c == 'E' || c == 'W') ? 1 : 0;
				s->dir.x *= (c == 'W') ? -1 : 1;
				s->dir.y = (c == 'S' || c == 'N') ? 1 : 0;
				s->dir.y *= (c == 'N') ? -1 : 1;
				s->err.p++;
			}
		}
		j = -1;
	}
}

int		parse_check(t_all *s){
	if (s->win.x <= 0 || s->win.y <= 0)
		return (tool_error(-14));
	else if ((s->tex.n == NULL || s->tex.s == NULL || s->tex.e == NULL)
			|| (s->tex.w == NULL || s->tex.i == NULL))
		return (tool_error(-15));
	else if (s->tex.c == NONE || s->tex.f == NONE)
		return (tool_error(-16));
	else if (s->err.p == 0)
		return (tool_error(-17));
	else if (s->err.p > 1)
		return (tool_error(-18));
	else if (map_check(s) == -1)
		return (tool_error(-19));
	return (1);
}
