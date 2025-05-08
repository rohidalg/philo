/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:24:05 by rohidalg          #+#    #+#             */
/*   Updated: 2025/05/08 13:50:10 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
#include <sys/time.h>
#include <stdint.h>


# define TAKE_FORKS "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef struct s_philo
{
	int				id;
	int				time_to_die;
    int             eaten;
	int				meals_eaten;
	long			last_meal_time;
    int             status;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	//pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
    int             dead;
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
    int             finish;
	long			start_time;
	t_philo			*philos;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*forks;
}					t_data;

//------------------------philo.c------------------------//
uint64_t ft_get_time();
void ft_write(char *str, t_philo *philo);
void i_philos(t_data *data);
int	i_data(t_data *data, int argc, char **argv);
int i_forks(t_data *data);



//------------------------utils.c------------------------//
int	ft_strcmp(char *s1, char *s2);
int	ft_atoi(const char *s);
int ft_usleep(__useconds_t time);


//------------------------options.c------------------------//
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);



#endif
