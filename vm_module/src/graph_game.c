/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:24:49 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/29 11:27:34 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "graph.h"
#include <pthread.h>
#include <unistd.h>

extern pthread_cond_t g_condition;
extern pthread_cond_t g_condition2;
extern pthread_mutex_t g_mutex;

void		game_mutex(t_core *c)
{
	if (c->visu && c->graph->proc_aff)
	{
		pthread_mutex_lock(&g_mutex);
		pthread_cond_signal(&g_condition);
		pthread_cond_wait(&g_condition2, &g_mutex);
		pthread_mutex_unlock(&g_mutex);
	}
}

void		game_refresh(t_core *c)
{
	if (c->visu)
	{
		refresh_all_wins(c);
		print_process(c);
		print_infos(c);
	}
}

void		game_fps(t_core *c)
{
	if (c->visu)
		usleep(1000000 / c->graph->fps);
}
