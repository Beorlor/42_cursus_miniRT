/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone_cy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:24:15 by jedurand          #+#    #+#             */
/*   Updated: 2024/09/10 13:21:34 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_cylinder_data(char **split, t_object *obj)
{
	char	**pos_split;
	char	**axis_split;
	char	**color_split;

    if (!split[1] || !split[2] || !split[3]|| !split[4]|| !split[5])
    {
        ft_printf("Error: Invalid cylinder format\n");
        return (1);
    }
	pos_split = ft_split(split[1], ',');
	axis_split = ft_split(split[2], ',');
	color_split = ft_split(split[5], ',');
	if (!pos_split || !pos_split[0] || !pos_split[1] || !pos_split[2] ||
    	!axis_split || !axis_split[0] || !axis_split[1] || !axis_split[2] ||
    	!color_split || !color_split[0] || !color_split[1] || !color_split[2])
		return (free_split(pos_split), free_split(axis_split),
			free_split(color_split),
			ft_printf("Error: Invalid cylinder format\n"), 1);
	obj->pos.x = ft_atof(pos_split[0]);
	obj->pos.y = ft_atof(pos_split[1]);
	obj->pos.z = ft_atof(pos_split[2]);
	obj->specific.cylinder.axis.x = ft_atof(axis_split[0]);
	obj->specific.cylinder.axis.y = ft_atof(axis_split[1]);
	obj->specific.cylinder.axis.z = ft_atof(axis_split[2]);
	obj->specific.cylinder.diameter = ft_atof(split[3]);
	obj->specific.cylinder.height = ft_atof(split[4]);
	obj->color.r = ft_atoi(color_split[0]);
	obj->color.g = ft_atoi(color_split[1]);
	obj->color.b = ft_atoi(color_split[2]);
	free_split(pos_split);
	free_split(axis_split);
	return (free_split(color_split), 0);
}

int	parse_cylinder(char **split, t_data *data)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		ft_printf("Error: Memory allocation failed\n");
		return (1);
	}
	ft_memset(obj, 0, sizeof(t_object));
	if (parse_cylinder_data(split, obj))
		return (free(obj), 1);
	obj->type = CYLINDER;
	if (parse_object_options(split, obj))
		return (1);
	obj->next = data->objects;
	data->objects = obj;
	data->object_count++;
	return (0);
}

int	parse_cone_data(char **split, t_object *obj)
{
	char	**pos_split;
	char	**axis_split;
	char	**color_split;

    if (!split[1] || !split[2] || !split[3]|| !split[4]|| !split[5])
    {
        ft_printf("Error: Invalid cone format\n");
        return (1);
    }
	pos_split = ft_split(split[1], ',');
	axis_split = ft_split(split[2], ',');
	color_split = ft_split(split[5], ',');
	if (!pos_split || !pos_split[0] || !pos_split[1] || !pos_split[2] ||
    	!axis_split || !axis_split[0] || !axis_split[1] || !axis_split[2] ||
    	!color_split || !color_split[0] || !color_split[1] || !color_split[2])
		return (free_split(pos_split), free_split(axis_split),
			free_split(axis_split), free_split(color_split),
			ft_printf("Error: Invalid cone format\n"), 1);
	obj->pos.x = ft_atof(pos_split[0]);
	obj->pos.y = ft_atof(pos_split[1]);
	obj->pos.z = ft_atof(pos_split[2]);
	obj->specific.cone.axis.x = ft_atof(axis_split[0]);
	obj->specific.cone.axis.y = ft_atof(axis_split[1]);
	obj->specific.cone.axis.z = ft_atof(axis_split[2]);
	obj->specific.cone.diameter = ft_atof(split[3]);
	obj->specific.cone.height = ft_atof(split[4]);
	obj->color.r = ft_atoi(color_split[0]);
	obj->color.g = ft_atoi(color_split[1]);
	obj->color.b = ft_atoi(color_split[2]);
	free_split(pos_split);
	free_split(axis_split);
	return (free_split(color_split), 0);
}

int	parse_cone(char **split, t_data *data)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		ft_printf("Error: Memory allocation failed\n");
		return (1);
	}
	ft_memset(obj, 0, sizeof(t_object));
	if (parse_cone_data(split, obj))
		return (free(obj), 1);
	obj->type = CONE;
	if (parse_object_options(split, obj))
		return (1);
	obj->next = data->objects;
	data->objects = obj;
	data->object_count++;
	return (0);
}
