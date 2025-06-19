/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:24:05 by rohidalg          #+#    #+#             */
/*   Updated: 2025/06/19 16:04:55 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <inttypes.h>
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TAKE_FORKS "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef struct s_philo
{
	int				id;
	uint64_t		time_to_die;
	int				eating;
	int				meals_eaten;
	long			last_meal_time;
	int				status;
	pthread_mutex_t	lock;
	pthread_mutex_t	meal_mutex;         
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		waiter;
	struct s_data	*data;
}					t_philo;


typedef struct s_data
{
	int				dead;
	int				n_philos;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				meals_required;
	int				finish;
	long			start_time;
	t_philo			*philos;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	lock;
	pthread_mutex_t	dead_mutex;        
	pthread_mutex_t	*forks;
	pthread_t		*tid;
}					t_data;

//------------------------philo.c------------------------//
uint64_t			ft_get_time(void);
void				ft_write(char *str, t_philo *philo);
void				i_philos(t_data *data);
int					i_data(t_data *data, int argc, char **argv);
int					i_forks(t_data *data);

//------------------------utils.c------------------------//
int					ft_strcmp(char *s1, char *s2);
int					ft_atoi(const char *s);
int					ft_usleep(__useconds_t time);
int					ft_exit(t_data *data);
int					ft_malloc(t_data *data);

//------------------------options.c------------------------//
void				take_forks(t_philo *philo);
void				drop_forks(t_philo *philo);
int					one_philo(t_data *data);
void				eat(t_philo *philo);
void				*manager(void *data_pointer);
void				*waiter(void *philo_pointer);
void				*actions(void *philo_pointer);
int					i_dinner(t_data *data);

#endif
