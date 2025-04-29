/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:13:40 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/29 15:19:22 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_export(t_cmd *cmd, t_env **env)
{
    t_token *tok    = cmd->args->next;
    int       status = 0;

    if (!tok)
        return print_export_list(*env);

    while (tok)
    {
        if (handle_one_export(tok->value, env))
            status = 1;
        tok = tok->next;
    }
    return status;
}
int print_export_list(t_env *env)
{
    t_env  **arr;
    size_t  count;

    arr = build_env_array(env, &count);
    if (!arr)
        return 1;
    sort_env_array(arr, count);
    print_env_array(arr, count);
    free(arr);
    return 0;
}
t_env **build_env_array(t_env *env, size_t *out_n)
{
    size_t  cnt = 0;
    t_env  *cur = env;
    t_env **arr;

    while (cur)           // count
    {
        cnt++;
        cur = cur->next;
    }
    arr = malloc(cnt * sizeof *arr);
    if (!arr)
        return NULL;

    cur = env;
    cnt = 0;
    while (cur)           // fill
    {
        arr[cnt++] = cur;
        cur = cur->next;
    }
    *out_n = cnt;
    return arr;
}
void sort_env_array(t_env **arr, size_t n)
{
    size_t  i = 0, j;
    t_env  *tmp;

    while (i + 1 < n)
    {
        j = 0;
        while (j + 1 < n)
        {
            if (ft_strcmp(arr[j]->name, arr[j+1]->name) > 0)
            {
                tmp       = arr[j];
                arr[j]    = arr[j+1];
                arr[j+1]  = tmp;
            }
            j++;
        }
        i++;
    }
}
void print_env_array(t_env **arr, size_t n)
{
    size_t i = 0;
    while (i < n)
    {
        if (arr[i]->value != NULL)
            printf("declare -x %s=\"%s\"\n",
                   arr[i]->name, arr[i]->value);
        else
            printf("declare -x %s\n", arr[i]->name);
        i++;
    }
}
int handle_one_export(const char *arg, t_env **env)
{
    char *copy = ft_strdup(arg);
    int   err  = 0;

    if (!copy)
        return 1;
    if (ft_strstr(copy, "+="))
        err = apply_append(copy, env);
    else
        err = apply_assign(copy, env);
    free(copy);
    return err;
}
int apply_assign(char *copy, t_env **env)
{
    char *eq  = ft_strchr(copy, '=');
    int   err = 0;

    if (eq)
    {
        *eq = '\0';
        if (!is_valid_id(copy))
        {
            print_export_error(copy);
            err = 1;
        }
        else
            env_set(env, copy, eq + 1);
        *eq = '=';
    }
    else
    {
        if (!is_valid_id(copy))
        {
            print_export_error(copy);
            err = 1;
        }
        else if (!ft_getenv(*env, copy))
            env_set(env, copy, "");
    }
    return err;
}
int apply_append(char *copy, t_env **env)
{
    char *pos   = ft_strstr(copy, "+=");
    char *oldv;
    char *newv;
    int   err   = 0;

    *pos = '\0';  // split
    if (!is_valid_id(copy))
    {
        print_export_error(copy);
        err = 1;
    }
    else
    {
        oldv = ft_getenv(*env, copy);
        if (!oldv) oldv = "";
        newv = ft_strjoin(oldv, pos + 2);
        env_set(env, copy, newv);
        free(newv);
    }
    *pos = '+';
    return err;
}
