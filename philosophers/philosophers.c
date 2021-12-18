/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferny <bferny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:11:32 by bferny            #+#    #+#             */
/*   Updated: 2021/12/17 22:14:20 by bferny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	message(t_philo ph, char *message, t_data **data)
{
	pthread_mutex_lock(&(*data)->message);
	printf("%ld %d %s\n", get_time() - (*data)->start_time, ph.id, message);
	pthread_mutex_unlock(&(*data)->message);
}

t_data	*new_data(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	if (read_args(argc, argv, data) == -1)
	{	
		free(data);
		return (NULL);
	}
	data->forks = NULL;
	data->nbr_th = 0;
	data->ph = NULL;
	if (data->nmbr_of_eat == 0)
	{	
		free(data);
		return (NULL);
	}
	pthread_mutex_init(&data->message, NULL);
	return (data);
}

void	new_forks(t_data **data)
{
	if ((*data)->nbr_of_philo > 1)
		(*data)->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
				* (*data)->nbr_of_philo);
	else
		(*data)->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 2);
	if ((*data)->forks && (*data)->nbr_of_philo == 1)
	{
		pthread_mutex_init((*data)->forks, NULL);
		pthread_mutex_init((*data)->forks + 1, NULL);
		pthread_mutex_lock((*data)->forks);
	}
}

int	new_philo(t_data **data)
{
	unsigned int	id;

	id = 0;
	new_forks(data);
	(*data)->ph = (t_philo *)malloc(sizeof(t_philo) * (*data)->nbr_of_philo);
	if ((*data)->ph == NULL || (*data)->forks == NULL)
		return (-1);
	while (id < (*data)->nbr_of_philo)
	{
		pthread_mutex_init(&(*data)->forks[id], NULL);
		init_philo_params((*data)->ph + id, id + 1, &(*data));
		id++;
	}
	return (1);
}

int	create_th(t_data **data)
{
	unsigned int	i;

	i = 0;
	while (i < (*data)->nbr_of_philo)
	{
		if (pthread_create(&(*data)->ph[i].th, NULL, &life,
				(void *)((*data)->ph + i)))
			return (-1);
		i++;
		(*data)->nbr_th++;
	}
	if ((*data)->nbr_th == (*data)->nbr_of_philo)
	{
		while (i-- > 0)
			pthread_detach((*data)->ph[i].th);
	}
	if (check_death(&(*data)->ph) == -1)
		return (-2);
	return (1);
}
