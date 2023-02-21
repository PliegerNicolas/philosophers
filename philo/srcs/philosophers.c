/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:35:49 by nplieger          #+#    #+#             */
/*   Updated: 2023/02/11 19:47:28 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_rules			rules;

	if (!verify_args(argc - 1, argv + 1))
		return (1);
	initialize_rules(&rules, argc - 1, argv + 1);
	if (!initialize_philosophers(&rules))
		return (1);
	return (0);
}
