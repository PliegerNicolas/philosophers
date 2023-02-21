/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:41:24 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/21 19:50:02 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

void	*philosopher_routine(void *ptr)
{
	t_philosopher	*philosopher;
	t_rules			*rules;

	philosopher = (t_philosopher *)ptr;
	rules = philosopher->rules;
	while (!try_ending(philosopher, rules))
	{
		if (try_thinking(philosopher, rules))
			continue ;
		if (try_grabbing_forks(philosopher, rules))
			continue ;
		if (try_eating(philosopher, rules))
			continue ;
		if (try_sleeping(philosopher, rules))
			continue ;
	}
	return (NULL);
}
