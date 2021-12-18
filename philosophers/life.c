/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferny <bferny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 19:18:06 by bferny            #+#    #+#             */
/*   Updated: 2021/12/17 22:08:24 by bferny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_philo *ph)
{
	if (ph->death == -1)
		return ;
	pthread_mutex_lock(ph->data->forks + ph->id - 1);
	message(*ph, FORK, &ph->data);
	if (ph->id == 1)
		pthread_mutex_lock(ph->data->forks + ph->data->nbr_of_philo - 1);
	else
		pthread_mutex_lock(ph->data->forks + ph->id - 2);
	message(*ph, FORK, &ph->data);
	message(*ph, EAT, &ph->data);
	ph->last_time_eat = get_time() - ph->data->start_time;
	usleep(ph->data->time_to_eat * 1000);
	if (ph->data->nmbr_of_eat >= 0)
		ph->eat_count++;
	pthread_mutex_unlock(ph->data->forks + ph->id - 1);
	if (ph->id == 1)
		pthread_mutex_unlock(ph->data->forks + ph->data->nbr_of_philo - 1);
	else
		pthread_mutex_unlock(ph->data->forks + ph->id - 2);
}

void	thinking(t_philo *ph)
{
	if (ph->death == -1)
		return ;
	message(*ph, THINK, &ph->data);
}

void	sleeping(t_philo *ph)
{
	if (ph->death == -1)
		return ;
	message(*ph, SLEEP, &ph->data);
	usleep(ph->data->time_to_sleep * 1000);
}

void	*life(void *p_philo)
{
	t_philo	*ph;
	t_data	*data;

	ph = (t_philo *)p_philo;
	data = ph->data;
	ph->last_time_eat = get_time() - data->start_time;
	if (ph->id % 2 == 0)
		usleep(data->time_to_eat);
	while (1)
	{
		eating(ph);
		if (ph->eat_count == data->nmbr_of_eat)
			break ;
		sleeping(ph);
		thinking(ph);
	}
	return (NULL);
}
