/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:34:19 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/26 01:22:08 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

void	*philosopher_routine(void *ptr)
{
	t_philosopher	*philosopher;
	t_rules			*rules;

	philosopher = (t_philosopher *)ptr;
	rules = philosopher->rules;
	philosopher->last_meal = get_time();
	while (!try_ending(philosopher, rules))
	{
		try_thinking(philosopher, rules);
		try_grabbing_forks(philosopher, rules);
		try_eating(philosopher, rules);
		try_sleeping(philosopher, rules);
	}
	return (NULL);
}
