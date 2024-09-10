/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sp_pl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:24:28 by jedurand          #+#    #+#             */
/*   Updated: 2024/09/10 16:19:12 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_sphere_data(char **split, t_object *obj)
{
	char	**pos_split;
	char	**color_split;

	if (!split[1] || !split[2] || !split[3])
		return (1);
	pos_split = ft_split(split[1], ',');
	color_split = ft_split(split[3], ',');
	if (!pos_split || !pos_split[0] || !pos_split[1] || !pos_split[2]
		|| !color_split || !color_split[0] || !color_split[1]
		|| !color_split[2])
	{
		free_split(pos_split);
		free_split(color_split);
		return (ft_printf("Error: Invalid sphere format\n"), 1);
	}
	obj->pos.x = ft_atof(pos_split[0]);
	obj->pos.y = ft_atof(pos_split[1]);
	obj->pos.z = ft_atof(pos_split[2]);
	obj->color.r = ft_atoi(color_split[0]);
	obj->color.g = ft_atoi(color_split[1]);
	obj->color.b = ft_atoi(color_split[2]);
	obj->specific.sphere.diameter = ft_atof(split[2]);
	free_split(pos_split);
	free_split(color_split);
	return (0);
}

int	parse_sphere(char **split, t_data *data)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		ft_printf("Error: Memory allocation failed\n");
		return (1);
	}
	ft_memset(obj, 0, sizeof(t_object));
	if (parse_sphere_data(split, obj))
		return (free(obj), 1);
	obj->type = SPHERE;
	if (parse_object_options(split, obj))
		return (free(obj), 1);
	obj->next = data->objects;
	data->objects = obj;
	data->object_count++;
	return (0);
}

int	parse_plane_data(char **split, t_object *obj)
{
	char	**pos_split;
	char	**normal_split;
	char	**color_split;

	if (!split[1] || !split[2] || !split[3])
		return (1);
	pos_split = ft_split(split[1], ',');
	normal_split = ft_split(split[2], ',');
	color_split = ft_split(split[3], ',');
	if (!is_split_valid(pos_split, normal_split, color_split))
		return (free_split(pos_split),
			free_split(normal_split), free_split(color_split),
			ft_printf("Error: Invalid plane format\n"), 1);
	obj->pos.x = ft_atof(pos_split[0]);
	obj->pos.y = ft_atof(pos_split[1]);
	obj->pos.z = ft_atof(pos_split[2]);
	obj->specific.plane.normal.x = ft_atof(normal_split[0]);
	obj->specific.plane.normal.y = ft_atof(normal_split[1]);
	obj->specific.plane.normal.z = ft_atof(normal_split[2]);
	obj->color.r = ft_atoi(color_split[0]);
	obj->color.g = ft_atoi(color_split[1]);
	obj->color.b = ft_atoi(color_split[2]);
	free_split(pos_split);
	free_split(normal_split);
	return (free_split(color_split), 0);
}

int	parse_plane(char **split, t_data *data)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		ft_printf("Error: Memory allocation failed\n");
		return (1);
	}
	ft_memset(obj, 0, sizeof(t_object));
	if (parse_plane_data(split, obj))
		return (free(obj), 1);
	obj->type = PLANE;
	obj->checkerboard = false;
	ft_memset(&obj->noise, 0, sizeof(t_noise));
	if (parse_object_options(split, obj))
	{
		free(obj);
		return (1);
	}
	obj->next = data->objects;
	data->objects = obj;
	data->object_count++;
	return (0);
}
