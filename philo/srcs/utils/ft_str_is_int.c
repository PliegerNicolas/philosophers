/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:03:11 by nplieger          #+#    #+#             */
/*   Updated: 2023/02/11 19:40:57 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

/* Returns TRUE if given string represents an integer. Else returns FALSE.*/
/* Doesn't work with floats or doubles. */
t_bool	ft_str_is_int(char *arg)
{
	if (!arg)
		return (FALSE);
	if (*arg == '-' || *arg == '+')
		arg++;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (FALSE);
		arg++;
	}
	return (TRUE);
}
