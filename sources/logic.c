/*
** logic.c for 42sh in /home/boulay_b/Work/SE2/PSU/42sh/PSU_2014_minishell2
**
** Made by Arnaud Boulay
** Login   <boulay_b@epitech.net>
**
** Started on  Fri May 15 04:24:39 2015 Arnaud Boulay
** Last update Sun May 24 19:20:28 2015 Sebastien BOULOC
*/

#include <stdlib.h>
#include "my.h"

static int	logic_sep_or_core(char **or, int pos, char **path,
				  t_env *env_list)
{
  int		i;
  int		ret;
  char		**tab;

  ret = 0;
  i = -1;
  while (ret == 0 && or[++i] != NULL)
    {
      if ((tab = exec_alias(or[i], path, env_list)) == NULL)
	return (-1);
      if ((pos != 0 && i == 0 && my_getnbr(get_env("?", env_list) + 2) == 0) ||
	  (pos == 0 && i == 0) ||
	  (i != 0 && my_getnbr(get_env("?", env_list) + 2) != 0))
	if ((ret = fcnt_ptr(tab, path, env_list)) == -1)
	  return (-1);
      free_tab(tab);
    }
  return (ret);
}

static int	logic_sep_or(char *and, int pos, char **path,
			     t_env *env_list)
{
  int		ret;
  char		**or;

  ret = 0;
  if ((or = my_strtowordtab(and, "||")) == NULL)
    return (-1);
  if ((ret = logic_sep_or_core(or, pos, path, env_list)) == -1)
    return (-1);
  free_tab(or);
  return (ret);
}

int		logic_sep_and(char *tabsep, char **path,
			      t_env *env_list)
{
  int		ret;
  int		i;
  char		**tab;
  char		**and;

  i = -1;
  ret = 0;
  if ((and = my_strtowordtab(tabsep, "&&")) == NULL)
    return (-1);
  while (ret == 0 && and[++i] != NULL)
    if (is_inside(and[i], "||") == 1)
      {
	if ((ret = logic_sep_or(and[i], i, path, env_list)) == -1)
	  return (-1);
      }
    else if (my_getnbr(get_env("?", env_list) + 2) == 0 || i == 0)
      {
	if ((tab = exec_alias(and[i], path, env_list)) == NULL ||
	    ((ret = fcnt_ptr(tab, path, env_list)) == -1))
	  return (-1);
	free_tab(tab);
      }
  free_tab(and);
  return (ret);
}
