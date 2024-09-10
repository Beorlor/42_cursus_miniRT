/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera_ambiant.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:24:12 by jedurand          #+#    #+#             */
/*   Updated: 2024/09/10 12:57:20 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_ambient_color(char **color_split, t_data *data)
{
	if (!color_split || !color_split[0] || !color_split[1] || !color_split[2])
	{
		free_split(color_split);
		ft_printf("Error: Invalid ambient light color format\n");
		return (1);
	}
	data->ambient.color.r = ft_atoi(color_split[0]);
	data->ambient.color.g = ft_atoi(color_split[1]);
	data->ambient.color.b = ft_atoi(color_split[2]);
	return (0);
}

int	parse_ambient(char **split, t_data *data)
{
	char	**color_split;

	if (data->ambient.ratio != -1)
	{
		ft_printf("Error: Ambient light already defined\n");
		return (1);
	}
	if (!split[1] || !split[2])
	{
		ft_printf("Error: Invalid ambient light format\n");
		return (1);
	}
	color_split = ft_split(split[2], ',');
	if (parse_ambient_color(color_split, data))
		return (1);
	data->ambient.ratio = ft_atof(split[1]);
	free_split(color_split);
	return (0);
}

int	parse_camera_position(char **pos_split, t_data *data)
{
	if (!pos_split || !pos_split[0] || !pos_split[1] || !pos_split[2])
	{
		free_split(pos_split);
		ft_printf("Error: Invalid camera position format\n");
		return (1);
	}
	data->camera.pos.x = ft_atof(pos_split[0]);
	data->camera.pos.y = ft_atof(pos_split[1]);
	data->camera.pos.z = ft_atof(pos_split[2]);
	return (0);
}

int	parse_camera_orientation(char **orient_split, t_data *data)
{
	if (!orient_split || !orient_split[0] || !orient_split[1]
		|| !orient_split[2])
	{
		free_split(orient_split);
		ft_printf("Error: Invalid camera orientation format\n");
		return (1);
	}
	data->camera.orient.x = ft_atof(orient_split[0]);
	data->camera.orient.y = ft_atof(orient_split[1]);
	data->camera.orient.z = ft_atof(orient_split[2]);
	return (0);
}

int	parse_camera(char **split, t_data *data)
{
	char	**pos_split;
	char	**orient_split;
	int		result;

	if (data->camera.fov != -1)
	{
		ft_printf("Error: Camera already defined\n");
		return (1);
	}
	if (!split[1] || !split[2] || !split[3])
	{
		ft_printf("Error: Invalid camera format\n");
		return (1);
	}
	pos_split = ft_split(split[1], ',');
	orient_split = ft_split(split[2], ',');
	result = parse_camera_position(pos_split, data);
	result += parse_camera_orientation(orient_split, data);
	if (result > 0)
		return (free_split(pos_split), free_split(orient_split), 1);
	data->camera.fov = ft_atoi(split[3]);
	free_split(pos_split);
	free_split(orient_split);
	return (0);
}
