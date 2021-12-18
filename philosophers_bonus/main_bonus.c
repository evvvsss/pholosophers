/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferny <bferny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:04:39 by bferny            #+#    #+#             */
/*   Updated: 2021/12/17 22:22:12 by bferny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = new_data_bonus(argc, argv);
	if (data == NULL)
		return (0);
	if (new_philo_bonus(data) == -1)
		return (0);
	if (data->nmbr_of_eat != 0)
		create_pr(&data);
	destroy_all_bonus(&data);
	exit (0);
}
