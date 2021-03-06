/*
** builtins.c for minishell1 in /home/boulay_b/Rendu/PSU/PSU_2014_minishell1
**
** Made by arnaud boulay
** Login   <boulay_b@epitech.net>
**
** Started on  Fri Jan 23 14:44:32 2015 arnaud boulay
** Last update Fri Jun  5 17:12:30 2015 Arnaud Boulay
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "my.h"

int	my_cd(char **tab, char **path, t_env *env_list)
{
  (void)path;
  if (tab[1] == NULL)
    {
      if (cd_null(tab, env_list) == -1)
	return (-1);
    }
  else if (tab[1][0] == '~')
    {
      if (cd_to_home(tab, env_list) == -1)
	return (-1);
    }
  else if (tab[1][0] == '-' && tab[1][1] == '\0')
    {
      if (cd_to_oldpath(env_list) == -1)
	return (-1);
    }
  else if (chdir(tab[1]) == -1)
    my_putstr("Error: cd: Wrong path.\n");
  else
    if (change_oldpwd(tab, env_list) == -1)
      return (-1);
  return (0);
}

int	my_setenv(char **tab, char **path, t_env *env_list)
{
  char	*env;
  int	i;

  (void)path;
  i = 0;
  while (tab[i] != NULL)
    ++i;
  if (i < 2 || i > 3)
    my_putstr("Error: setenv: Usage \"setenv 'name' 'value'\".\n");
  else
    {
      if (get_env(tab[1], env_list) != NULL)
	remove_env(env_list, tab[1]);
      if (i == 3 && (env = my_strcatdup(tab[1], tab[2], 2, '=')) == NULL)
	return (-1);
      else if (i == 2 && (env = my_strcatdup(tab[1], "", 2, '=')) == NULL)
	return (-1);
      if (add_chain(env_list, env) == -1)
	return (-1);
      free(env);
    }
  return (0);
}

int	my_unsetenv(char **tab, char **path, t_env *env_list)
{
  (void)env_list;
  (void)path;
  if (remove_env(env_list, tab[1]) == -1)
    my_putstr("Error: unsetenv: Can't find variable to unset.\n");
  return (0);
}

int		my_env(char **tab, char **path, t_env *env_list)
{
  char		**env;
  t_env		*tmp_env;
  int		exec;
  int		options;

  env = NULL;
  exec = 0;
  options = 1;
  if ((env = my_listtotab(env, env_list)) == NULL)
    return (-1);
  if ((tmp_env = create_list(env)) == NULL)
    return (-1);
  free_tab(env);
  if (tab[1] != NULL && find_options(tab, tmp_env, &exec, &options)
      == -1)
    return (-1);
  if (exec == 1)
    {
      if (exec_fake_env(tab, path, tmp_env, options) == -1)
	return (-1);
    }
  else
    disp_env(tmp_env);
  rm_list(tmp_env);
  return (0);
}

int	my_echo(char **tab, char **path, t_env *env_list)
{
  char	*str;

  (void)path;
  if (tab[1] != NULL)
    {
      if (my_strcmp("$", tab[1]) == 2)
	{
	  if ((str = get_env(tab[1] + 1, env_list)) != NULL)
	    printf("%s", str + my_strlen(tab[1]));
	}
      else
	printf("%s", tab[1]);
    }
  printf("\n");
  return (0);
}
