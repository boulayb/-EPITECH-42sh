/*
** my.h for minishell2 in /home/boulay_b/Rendu/SE2/PSU/PSU_2014_minishell2
**
** Made by Boulay Arnaud
** Login   <boulay_b@epitech.net>
**
** Started on  Wed Mar 11 20:35:31 2015 Boulay Arnaud
** Last update Fri Jun  5 17:27:33 2015 Arnaud Boulay
*/

#ifndef	MY_H_
# define MY_H_

# define BUFFER_SIZE	4096
# define LIGHT_BLUE	"\033[94m"
# define BLUE		"\033[34m"
# define GREEN		"\033[32m"
# define RED		"\033[31m"
# define DEFAULT	"\033[39m"
# define MY_PATH1	"PATH=/bin:/sbin:/usr/bin:/usr/sbin"
# define MY_PATH2	":/usr/heimdal/bin:/usr/heimdal/sbin"
# define MY_PATH	MY_PATH1 MY_PATH2

typedef struct		s_env
{
  char			*str;
  struct s_env		*next;
  struct s_env		*back;
}			t_env;

t_env			*g_env;

typedef struct		s_alias
{
  char			*name;
  char			*to;
  struct s_alias	*next;
  struct s_alias	*back;
}			t_alias;

t_alias			*g_alias;

typedef struct		s_status
{
  int			nb;
  char			*mess;
}			t_status;

typedef struct		s_builtins
{
  char			*str;
  int			(*ptr)(char **blabla, char **path, t_env *env_list);
}			t_builtins;

int			fcnt_ptr(char **blabla, char **path, t_env *env_list);
int			count_quotes(char *str);
int			alias_done(char **done, char *name);
int			my_alias(char **blabla, char **path, t_env *env_list);
int			my_prompt(char *str, char **path, t_env *env_list,
				  int prompt);
int			logic_sep_and(char *tabsep, char **path,
				      t_env *env_list);
int			check_syntax(char **line, t_env *env_list);
int			check_status(t_env *env_list, int status);
int			my_getnbr(char *str);
int			epur_str(char *str);
int			is_cinside(char *str, char c);
int			is_inside(char *str, char *str2);
int			add_alias(char *name, char *to);
int			is_cmd(char *str);
int			tablen(char **array);
int			add_path(char *str, t_env *env_list);
int			check_env(t_env *env_list);
int			cd_to_oldpath(t_env *env_list);
int			cd_null(char **, t_env *env_list);
int			cd_to_home(char **, t_env *env_list);
int			find_options(char **tab2, t_env *tmp_env, int *exec,
				     int *options);
int			exec_fake_env(char **tab2, char **path, t_env *tmp_env,
				      int options);
int			remove_path(t_env *env_list);
int			pwd_to_home(t_env *env_list);
int			swap_pwd(t_env *env_list);
int			add_chain(t_env *env_list, char *str);
int			my_echo(char **tab2, char **path, t_env *env_list);
int			my_env(char **tab2, char **path, t_env *env_list);
int			my_cd(char **tab2, char **path, t_env *env_list);
int			my_history(char **tab2, char **path, t_env *env_list);
int			my_setenv(char **tab2, char **path, t_env *env_list);
int			my_unsetenv(char **tab2, char **path, t_env *env_list);
int			my_strlen(char *str);
int			remove_env(t_env *env_list, char *str);
int			change_oldpwd(char **tab2, t_env *env_list);
int			my_strcmp(char *str1, char *str2);
int			exec_program(char **tab2, char **path,
				     t_env *env_list);
char			*change_for_home(char *str, t_env *env_list);
char			*get_next_line(const int fd);
char			*get_history_name(char *home);
char			*my_strdup(char *str);
char			*my_tabtostr(char **array);
char			*my_strcatdup(char *dest, char *src, int l, char c);
char			*my_strcpy(char *dest, char *src);
char			*get_env(char *str, t_env *env_list);
char			**exec_alias(char *str, char **path, t_env *env_list);
char			**is_alias(char *str);
char			**is_alias_done(char *str, char **done);
char			**done_alias(char **done, char *name);
char			**my_quotetowordtab(char *str, char *sep);
char			**my_str_to_wordtab(char *str);
char			**my_strtowordtab(char *str, char *sep);
char			**my_listtotab(char **env, t_env *env_list);
void			my_putchar(char c);
void			my_putstr(char *str);
void			my_putnbr(int nb);
void			free_tab(char **tab2);
void			rm_chain(t_env *chain);
void			rm_list(t_env *env_list);
void			disp_prompt(t_env *env_list);
void			disp_env(t_env *env_list);
void			my_signal(void);
void			rm_alias(t_alias *chain);
void			empty_list(t_env *env_list);
void			change_tild(char **, t_env *env);
void			catch_signal(int signal);
t_env			*create_env(t_env *env_list);
t_env			*create_list(char **env);
t_alias			*create_alias(void);
int			if_wordlen(char *, int *, int *);
int			my_strlen(char *str);

#endif /* !MY_H_ */
