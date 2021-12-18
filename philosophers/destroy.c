/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferny <bferny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:15:00 by bferny            #+#    #+#             */
/*   Updated: 2021/12/15 22:40:50 by bferny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_all(t_data **data)
{
	if ((*data)->ph)
		destroy_philo(&(*data));
	if ((*data))
		free((*data));
}

void	destroy_forks(pthread_mutex_t *forks, t_data **data)
{
	unsigned int	i;

	i = 0;
	if ((*data)->nbr_of_philo == 1)
	{
		pthread_mutex_destroy(forks);
		pthread_mutex_destroy(forks + 1);
	}
	while (i < (*data)->nbr_of_philo)
	{
		if (forks + i)
			pthread_mutex_destroy(forks + i);
		i++;
	}
	if ((*data)->forks)
		free((*data)->forks);
}

void	destroy_philo(t_data **data)
{
	if ((*data)->forks)
		destroy_forks((*data)->forks, &(*data));
	pthread_mutex_destroy(&(*data)->message);
	if ((*data)->ph)
		free((*data)->ph);
}
