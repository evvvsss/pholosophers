/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferny <bferny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:35:58 by bferny            #+#    #+#             */
/*   Updated: 2021/12/14 22:50:14 by bferny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	data = new_data(argc, argv);
	if (data == NULL)
		return (0);
	if (new_philo(&data) == -1)
	{	
		destroy_philo(&data);
		return (0);
	}
	if (create_th(&data) == -1)
		printf("threads error!\n");
	destroy_all(&data);
	return (0);
}
