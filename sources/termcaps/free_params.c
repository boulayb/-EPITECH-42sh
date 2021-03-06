/*
** free_params.c for  in /home/cassin_f/42sh_cassin
** 
** Made by François CASSIN
** Login   <cassin_f@epitech.net>
** 
** Started on  Wed May 20 14:58:39 2015 François CASSIN
** Last update Sun May 24 20:01:10 2015 Sebastien BOULOC
*/

#include <stdlib.h>
#include "my_get_line.h"

static void	free_history(t_history *history)
{
  int		i;

  i = 0;
  while (i < (history->nb_max - 1))
    {
      if (history->history_tab[i] != NULL)
	free(history->history_tab[i]);
      ++i;
    }
}

void		free_params(t_params *params)
{
  g_line = NULL;
  g_caps = NULL;
  free_complete(params->completion->path);
  free_complete(params->completion->local);
  free_history(params->history);
}
