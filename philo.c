/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:33:26 by rohidalg          #+#    #+#             */
/*   Updated: 2025/05/13 13:19:30 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, 0))
		return (printf("ft_get_time() FAILUREN\n"));
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	ft_write(char *str, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(philo->data->print_mutex);
	time = ft_get_time() - philo->data->start_time;
	if (philo->data->dead == 0 && ft_strcmp(DIED, str) == 0)
	{
		printf("%u %d %s\n", time, philo->id, str);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%u %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->data->print_mutex);
}

void	i_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].eating = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].status = 0;
		pthread_mutex_init(data->philos[i].lock, 0);
		i++;
	}
}

int	i_data(t_data *data, int argc, char **argv)
{
	data->n_philos = (int)ft_atoi(argv[1]);
	data->time_to_die = (int)ft_atoi(argv[2]);
	data->time_to_eat = (int)ft_atoi(argv[3]);
	data->time_to_sleep = (int)ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_required = (int)ft_atoi(argv[5]);
	else
		data->meals_required = -1;
	if (data->n_philos <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (printf("INVALID IMPUT\n"));
	data->dead = 0;
	data->finish = 0;
	pthread_mutex_init(data->print_mutex, 0);
	pthread_mutex_init(data->lock, 0);
	return (0);
}

int	i_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_init(&data->forks[i], 0);
		i++;
	}
	data->philos[0].left_fork = &data->forks[0];
	data->philos[0].right_fork = &data->forks[data->n_philos - 1];
	i = 1;
	while (i < data->n_philos)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	i_data(&data, argc, argv);
	ft_malloc(&data);
	i_forks(&data);
	i_philos(&data);
}

// filosofos morir comer dormir
// [number_of_times_each_philosopher_must_eat]

// 🧠 Funciones de memoria
// memset(void *s, int c, size_t n)
// Rellena los primeros n bytes del bloque de memoria apuntado por s con el byte c.
// 👉 Se usa para inicializar arrays o estructuras.

// malloc(size_t size)
// Reserva dinámicamente size bytes de memoria en el heap y devuelve un puntero al comienzo.
// 👉 Recuerda liberar con free.

// free(void *ptr)
// Libera memoria previamente reservada con malloc, calloc o realloc.
// 👉 Evita memory leaks.

// 🖨️ Entrada / Salida
// printf(const char *format, ...)
// Imprime texto formateado en la salida estándar (normalmente la pantalla).

// write(int fd, const void *buf, size_t count)
// Escribe count bytes desde buf al descriptor de archivo fd.
// 👉 fd = 1 es stdout.

// ⏱️ Temporización
// usleep(useconds_t microseconds)
// Pausa la ejecución actual durante la cantidad de microsegundos indicada.
// 👉 usleep(1000) duerme 1 milisegundo.

// gettimeofday(struct timeval *tv, struct timezone *tz)
// Llena la estructura tv con el tiempo actual (segundos y microsegundos desde Epoch).
// 👉 Se usa para medir tiempos con precisión.

// 🧵 Funciones de hilos (pthread)
// pthread_create(pthread_t *thread,	const pthread_attr_t *attr,void *(*start_routine)(void *),
//	void *arg)
// Crea un nuevo hilo que ejecuta la función start_routine con el argumento arg.

// pthread_detach(pthread_t thread)
// Desvincula un hilo del hilo principal,permitiendo que sus recursos se liberen automáticamente cuando termine.
// 👉 Ya no se puede hacer pthread_join sobre él.

// pthread_join(pthread_t thread, void **retval)
// Espera a que termine un hilo específico. Útil para sincronizar.

// 🔒 Mutex (exclusión mutua)
// pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
// Inicializa un mutex para sincronización entre hilos.

// pthread_mutex_destroy(pthread_mutex_t *mutex)
// Libera los recursos de un mutex previamente inicializado.

// pthread_mutex_lock(pthread_mutex_t *mutex)
// Bloquea el mutex. Si otro hilo ya lo tiene, espera.

// pthread_mutex_unlock(pthread_mutex_t *mutex)
// Libera el mutex para que otros hilos puedan usarlo.