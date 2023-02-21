/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:05:11 by nplieger          #+#    #+#             */
/*   Updated: 2023/02/17 12:25:43 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

static t_bool	is_valid_int(long long int llint)
{
	if (llint > MAX_INT || llint < MIN_INT)
		return (FALSE);
	return (TRUE);
}

static t_bool	validate_int_arg(char *arg, int arg_nbr)
{
	long long int	temp_llint;

	temp_llint = ft_atolli(arg);
	if (!is_valid_int(temp_llint))
		return (!perror_not_a_valid_int(arg_nbr));
	if (!(ft_str_is_int(arg) && (int)temp_llint >= 0))
		return (!perror_int_expected(arg_nbr));
	if (arg_nbr == 1 && (int)temp_llint > MAX_PHILOSOPHERS)
		return (!perror_wrong_nbr_of_philosophers());
	return (TRUE);
}

t_bool	verify_args(int argc, char **argv)
{
	int		i;

	if (argc < 4 || argc > 5)
		return (!perror_wrong_nbr_of_args(argc));
	i = 0;
	while (i < argc)
	{
		if (!validate_int_arg(argv[i], i + 1))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
