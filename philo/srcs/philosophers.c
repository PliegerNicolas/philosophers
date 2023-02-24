/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:35:49 by nplieger          #+#    #+#             */
/*   Updated: 2023/02/24 10:39:45 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_rules			rules;
	t_philosopher	*philosophers;

	if (!verify_args(argc - 1, argv + 1))
		return (1);
	if (!initialize(&rules, &philosophers, argc - 1, argv + 1))
		return (clear_and_free(&rules, philosophers));
	if (!run_simulation(&rules, philosophers))
		return (clear_and_free(&rules, philosophers));
	clear_and_free(&rules, philosophers);
	return (0);
}
