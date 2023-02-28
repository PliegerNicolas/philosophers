/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:35:17 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/28 15:54:54 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

static void	clear_rules_sems(t_rules *rules)
{
	if (rules->forks_sem)
		sem_close(rules->forks_sem);
	if (rules->write_sem)
		sem_close(rules->write_sem);
	if (rules->grabbing_forks_sem)
		sem_close(rules->grabbing_forks_sem);
	if (rules->end_sem)
		sem_close(rules->end_sem);
	if (rules->eating_sem)
		sem_close(rules->eating_sem);
	if (rules->finish_sem)
		sem_close(rules->finish_sem);
}

t_bool	clear_and_free(t_rules *rules, t_philosopher *philosophers)
{
	clear_rules_sems(rules);
	if (philosophers)
		free(philosophers);
	return (TRUE);
}
