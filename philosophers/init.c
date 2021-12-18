/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferny <bferny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:10:28 by bferny            #+#    #+#             */
/*   Updated: 2021/12/17 22:08:36 by bferny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_eating(t_philo *ph, t_data **data)
{
	if ((*data)->nmbr_of_eat == -1)
		ph->eat_count = -2;
	else
		ph->eat_count = 0;
}

void	init_philo_params(t_philo *ph, int id, t_data **data)
{
	ph->id = id;
	ph->death = 0;
	ph->last_time_eat = get_time() - (*data)->start_time;
	ph->data = *data;
	init_eating(ph, &(*data));
}
