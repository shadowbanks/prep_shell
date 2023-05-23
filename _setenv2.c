int _setenv(const char *name, const char *value, int overwrite)
{
    int j = 0, size = 0;
    char **my_env = NULL, *new_env = NULL;

    while (environ[size])/*get the number of environment*/
        size++;

    my_env = malloc(sizeof(char *) * (size + 1));
    if (!my_env)
        return (1);
    while (environ[j])
    {
        my_env[j] = malloc(_strlen(environ[j]) + 1);
        if (!my_env[j])
        {
            while (j)
                free(my_env[--j]);
            free(my_env);
            return (1);
        }
        _strcpy(my_env[j], environ[j]);
        j++;
    }
    my_env[j] = NULL;

    new_env = new_env_var(name, value);
    if (new_env == NULL)
    {
        free_my_env(my_env);
        return (1);
    }
    if (check_env(my_env, new_env, overwrite, name) == 1)
    {
        free_my_env(my_env);
        free(new_env);
        return (1);
    }
    if (set_new_env(my_env, size, new_env) == 1)
        return (1);
    return (0);
}

void free_my_env(char **my_env)
{
    int l = 0;

    while (my_env[l])
        free(my_env[l++]);
    free(my_env);
}

int set_new_env(char **my_env, int size, char *new_env)
{
    int k = 0, i = 0, j = 0;
    char **temp_env;

    while (my_env[k])
        k++;

    if (my_env[k] == NULL)
    {
        temp_env = malloc(sizeof(char *) * (size + 2));
        if (!temp_env)
            return (1);

        for (i = 0; i < size; i++)
            temp_env[i] = my_env[i];

        temp_env[size++] = new_env;
        temp_env[size] = NULL;
    }

    while (environ[j])
        free(environ[j--]);

    environ = temp_env;
    return (0);
}

int check_env(char **my_env, char *new_env, int overwrite, const char *name)
{
    int k = 0, l;
    char *temp = NULL;

    /*search for "name", replace it's value if overwrite != 0*/
    while (my_env[k])
    {
        if (_strncmp(my_env[k], name, _strlen(name)) == 0)
        {
            if (my_env[k][_strlen(name)] == '=')
            {
                if (overwrite != 0)
                {
                    temp = my_env[k];
                    my_env[k] = new_env;
                    free(temp);
                }
                else
                {
                    l = 0;
                    while (my_env[l])
                        free(my_env[l++]);
                    free(my_env);
                    free(new_env);
                    return (1);
                }
            }
            break;
        }
        k++;
    }
    return (0);
}
char *new_env_var(const char *name, const char *value)
{
    char *new_env = NULL;

    new_env = malloc(_strlen(name) + _strlen(value) + 2);
    if (!new_env)
        return (NULL);
    strcpy(new_env, name);
    strcat(new_env, "=");
    strcat(new_env, value);

    return (new_env);
}

