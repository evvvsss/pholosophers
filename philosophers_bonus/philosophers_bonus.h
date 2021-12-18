/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferny <bferny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:04:51 by bferny            #+#    #+#             */
/*   Updated: 2021/12/18 20:01:45 by bferny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>
# define MAX 922337203685477580
# define FORK "has taken a fork"
# define EAT "\033[36m is eating\033[0m"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "\033[31m died\033[0m"

typedef struct s_philo
{
	pid_t				pid;
	unsigned int		id;
	unsigned long		last_time_eat;
	int					eat_count;
	struct s_data		*data;
}				t_philo;

typedef struct s_data
{
	unsigned int		nbr_of_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					nmbr_of_eat;
	sem_t				*forks;
	sem_t				*message;
	sem_t				*end;
	sem_t				*process;
	sem_t				*finish_eat;
	unsigned long		start_time;
	t_philo				**ph;
}				t_data;

int				check_args_bonus(int argc, char **argv);
int				read_args_bonus(int argc, char **argv, t_data **data);
unsigned long	get_time(void);
void			increment_sem(sem_t *sem, int n);
void			*check_time_bonus(void *p_ph);
int				check_death(t_philo **ph, t_data **data);
void			eating_bonus(t_philo **ph, t_data **data);
void			thinking_bonus(t_philo *ph, t_data **data);
void			sleeping_bonus(t_philo *ph, t_data **data);
void			child(t_data **data, t_philo **ph);
int				finish_pr(t_data **data);
int				ft_atoi(const char *str);
size_t			ft_strlen(const char *s);
void			message_bonus(t_data **data, int id, char *s);
int				create_sem(t_data **data);
void			init_philo_params_bonus(t_data **data, int id);
int				new_philo_bonus(t_data *data);
int				create_pr(t_data **data);
t_data			*new_data_bonus(int argc, char **argv);
void			destroy_all_bonus(t_data **data);
void			decrement_sem(sem_t *sem, int n);

#endif