/*
** main.c for minishell1 in /home/boulay_b/Rendu/PSU/PSU_2014_minishell1
**
** Made by arnaud boulay
** Login   <boulay_b@epitech.net>
**
** Started on  Mon Jan 19 11:23:19 2015 arnaud boulay
** Last update Sun Jun  7 20:27:40 2015 Arnaud Boulay
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_get_line.h"
#include "my.h"
#include "sh42.h"

extern t_alias		*g_alias;
extern t_env		*g_env;

static t_builtins	g_builtins[] =
  {
    {"cd", &my_cd},
    {"setenv", &my_setenv},
    {"env", &my_env},
    {"alias", &my_alias},
    {"history", &my_history},
    {"unsetenv", &my_unsetenv},
    {"echo", &my_echo},
    {NULL, NULL}
  };

void			disp_prompt(t_env *env_list)
{
  static int		i = 1;

  my_putstr(LIGHT_BLUE);
  my_putchar('(');
  if (env_list != NULL && get_env("USER=", env_list) != NULL)
    my_putstr(get_env("USER=", env_list) + 5);
  else
    my_putstr("user");
  my_putstr(BLUE);
  my_putstr(" - ");
  my_putstr(LIGHT_BLUE);
  if (env_list != NULL && get_env("PWD=/", env_list) != NULL)
    my_putstr(get_env("PWD=/", env_list) + 4);
  else
    my_putstr("42sh");
  my_putchar(' ');
  my_putstr(BLUE);
  my_putnbr(i++);
  my_putstr(LIGHT_BLUE);
  my_putchar(')');
  my_putstr(BLUE);
  my_putstr("$>");
  my_putstr(DEFAULT);
}

int			fcnt_ptr(char **tab, char **path, t_env *env_list)
{
  int			status;
  int			i;

  i = -1;
  if (tab == NULL || tab[0] == NULL)
    return (0);
  if (my_strcmp("exit", tab[0]) == 1)
    {
      if (tab[1] != NULL)
	return (my_getnbr(tab[1]));
      return (-2);
    }
  while (g_builtins[++i].str != NULL)
    if (my_strcmp(tab[0], g_builtins[i].str) == 1)
      {
	if (g_builtins[i].ptr(tab, path, env_list) == -1)
	  return (-1);
	return (0);
      }
  if ((status = exec_program(tab, path, env_list)) == -1)
    return (-1);
  if (check_status(env_list, status) == -1)
    return (-1);
  return (0);
}

int			my_prompt(char *str, char **path, t_env *env_list,
				  int prompt)
{
  char			**syntax;
  char			**tabsep;
  int			ret;
  int			i;

  g_prompt = &prompt;
  tabsep = NULL;
  i = -1;
  ret = 0;
  if ((syntax = my_str_to_cmdtab(str)) == NULL)
    return (-1);
  if (check_syntax(syntax, env_list) == -1)
    return (0);
  if ((tabsep = my_strtowordtab(str, ";")) == NULL)
    return (-1);
  while (ret == 0 && tabsep[++i] != NULL)
    if ((ret = logic_sep_and(tabsep[i], path, env_list)) == -1)
      return (-1);
  if (ret == 0 && prompt != 2)
    disp_prompt(env_list);
  free(str);
  free_tab(tabsep);
  return (ret);
}

static int		my_minishell(char **env)
{
  int			ret;
  char			**path;
  char			*str;

  path = NULL;
  ret = 2;
  if ((g_env = create_list(env)) == NULL || (g_alias = create_alias()) == NULL)
    return (-1);
  my_signal();
  while ((ret == 0 || ret == 2) && (str = shell_get_line(g_env, &ret)) != NULL)
    {
      epur_str(str);
      if (ret == 1 && str[0] == 0)
	return (0);
      if (check_env(g_env) == -1)
	return (-1);
      if ((path = my_strtowordtab(get_env("PATH=", g_env) + 5, ":"))
	  == NULL)
	return (-1);
      if ((ret = my_prompt(str, path, g_env, ret)) == -1)
	return (-1);
      free_tab(path);
    }
  rm_list(g_env);
  return (ret);
}

int			main(int ac, char **av, char **env)
{
  int			ret;

  (void)ac;
  (void)av;
  if ((ret = my_minishell(env)) == -1)
    return (-1);
  printf("exit\n");
  my_putstr(DEFAULT);
  if (ret == -2)
    return (0);
  return (ret);
}
