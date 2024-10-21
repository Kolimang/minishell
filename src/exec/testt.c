


int	is_s_built(char *func_name, int cmd_pid)
{
	if (ft_strncmp(func_name, "echo", 5) == 0)
		return (0);
	else if (ft_strncmp(func_name, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(func_name, "exit", 5) == 0)
		return (is_in_child(2, cmd_pid));
	else if (ft_strncmp(func_name, "env", 4) == 0)
		return (3);
	else if (ft_strncmp(func_name, "cd", 3) == 0)
		return (4);
	else if (ft_strncmp(func_name, "export", 7) == 0)
		return (5);
	else if (ft_strncmp(func_name, "unset", 6) == 0)
		return (6);
	else if (ft_strncmp(func_name, "ft_local", 9) == 0)
		return (is_in_child(7, cmd_pid));
	else if (is_local(func_name))
		return (8);
	return (-1);
}


int exec_s_built_simple(char **av, char ***env, t_env **l_env, int self_builtin_nb)
{
    int res;

    if (self_builtin_nb == 0)
        res = ft_echo(av, env, l_env);
    else if (self_builtin_nb == 1)
        res = ft_pwd(av, env, l_env);
    else if (self_builtin_nb == 2)
        res = ft_exit(av, env, l_env);
    else if (self_builtin_nb == 3)
        res = ft_env(av, env, l_env);
    else if (self_builtin_nb == 4)
        res = ft_cd(av, env, l_env);
    else if (self_builtin_nb == 5)
        res = ft_export(av, env, l_env);
    else if (self_builtin_nb == 6)
        res = ft_unset(av, env, l_env);
    else if (self_builtin_nb == 7)
        res = ft_local(av, env, l_env);
    else if (self_builtin_nb == 8)
        res = ft_void(av, env, l_env);
    else
        res = -1;  // Error: unknown built-in command
    return res;
}