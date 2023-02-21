/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:09:33 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/15 16:17:57 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

/* If wrong status or dead, return dead status. If TRUE, exits loop. */
/* If false, goes to next action. */
/* Updates philosopher status, puts action and waits time_to_sleep. */
/* usleep is in microseconds. Our values are in milliseconds. Thus nbr x 1000 */
t_bool	try_sleeping(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->status != eating || try_ending(philosopher, rules))
		return (rules->end);
	philosopher->status = sleeping;
	put_philosopher_action(philosopher, sleeping);
	usleep(rules->time_to_sleep * 1000);
	if (try_ending(philosopher, rules))
		return (rules->end);
	return (rules->end);
}
