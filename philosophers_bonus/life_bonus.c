/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferny <bferny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 20:01:54 by bferny            #+#    #+#             */
/*   Updated: 2021/12/18 20:35:17 by bferny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	eating_bonus(t_philo **ph, t_data **data)
{
	sem_wait((*data)->forks);
	message_bonus(data, (*ph)->id, FORK);
	sem_wait((*data)->forks);
	message_bonus(data, (*ph)->id, FORK);
	message_bonus(data, (*ph)->id, EAT);
	(*ph)->last_time_eat = get_time() - (*data)->start_time;
	usleep((*data)->time_to_eat * 1000);
	if ((*data)->nmbr_of_eat >= 0)
		(*ph)->eat_count++;
	sem_post((*data)->forks);
	sem_post((*data)->forks);
	if ((*ph)->eat_count >= (*data)->nmbr_of_eat && (*data)->nmbr_of_eat > 0)
		sem_post((*data)->finish_eat);
}

void	thinking_bonus(t_philo *ph, t_data **data)
{
	message_bonus(data, ph->id, THINK);
}

void	sleeping_bonus(t_philo *ph, t_data **data)
{	
	message_bonus(data, ph->id, SLEEP);
	usleep((*data)->time_to_sleep * 1000);
}
