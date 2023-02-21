/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:52:47 by nplieger          #+#    #+#             */
/*   Updated: 2023/02/17 12:26:00 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

t_bool	perror_wrong_nbr_of_args(int nbr_of_given_args)
{
	printf("%sError. %d given arguments while 4 or 5 are expected.%s\n",
		RED, nbr_of_given_args, DEFAULT_COLOR);
	put_usage_indication();
	return (TRUE);
}

t_bool	perror_not_a_valid_int(int arg_nbr)
{
	printf("%sError. Argument %d exceeds integer storage limit.%s",
		RED, arg_nbr, DEFAULT_COLOR);
	printf("%s Argument %d should be a positive integer.%s\n",
		RED, arg_nbr, DEFAULT_COLOR);
	put_usage_indication();
	return (TRUE);
}

t_bool	perror_int_expected(int arg_nbr)
{
	printf("%sError. Argument %d should be a positive integer.%s\n",
		RED, arg_nbr, DEFAULT_COLOR);
	put_usage_indication();
	return (TRUE);
}

t_bool	perror_wrong_nbr_of_philosophers(void)
{
	printf("%sError. Maximum philosophers is %d.%s\n",
		RED, MAX_PHILOSOPHERS, DEFAULT_COLOR);
	put_usage_indication();
	return (TRUE);
}

t_bool	perror_not_enough_memory(void)
{
	printf("%sError. Not enough memory available.%s\n",
		RED, DEFAULT_COLOR);
	put_usage_indication();
	return (TRUE);
}
