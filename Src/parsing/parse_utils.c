/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:24:31 by jedurand          #+#    #+#             */
/*   Updated: 2024/09/10 16:19:49 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	ft_atof_sign(const char **str)
{
	double	sign;

	sign = 1.0;
	while (**str == ' ' || (**str >= '\t' && **str <= '\r'))
	{
		(*str)++;
	}
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
		{
			sign = -1.0;
		}
		(*str)++;
	}
	return (sign);
}

double	ft_atof_integer(const char **str)
{
	double	result;

	result = 0.0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10.0 + (*(*str) - '0');
		(*str)++;
	}
	return (result);
}

double	ft_atof_fraction(const char **str)
{
	double	fraction;
	double	divisor;

	fraction = 0.0;
	divisor = 10.0;
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			fraction += (*(*str) - '0') / divisor;
			divisor *= 10.0;
			(*str)++;
		}
	}
	return (fraction);
}

double	ft_atof(const char *str)
{
	double	sign;
	double	integer;
	double	fraction;
	double	result;

	sign = ft_atof_sign(&str);
	integer = ft_atof_integer(&str);
	fraction = ft_atof_fraction(&str);
	result = sign * (integer + fraction);
	return (result);
}
