
#include "cub3d.h"

int is_color_line(char *line)
{
    if (!line || ft_strlen(line) < 2)
        return (0);
    if (line[0] == 'F' || line[0] == 'C')
        if (line[1] == ' ')
            return (1);
    return (0);
}

int parse_color(char *line, t_color *color)
{
    char **split;
    char **rgb;
    int r;
    int g;
    int b;
    int i;
    printf("Parsing color line: '%s'\n", line);

    split = ft_split(line, ' ');
    if (!split || !split[1])
    {
        printf("Failed to split line by space\n");
        return (0);
    }
    
    printf("RGB part: '%s'\n", split[1]);
    
    rgb = ft_split(split[1], ',');
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
    {
        printf("Failed to split RGB values\n");
        if (split)
        {
            i = 0;
            while (split[i])
                free(split[i++]);
            free(split);
        }
        return (0);
    }
    
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
//todo error message
        int i = 0;
        while (split[i])
            free(split[i++]);
        free(split);
        i = 0;
        while (rgb[i])
            free(rgb[i++]);
        free(rgb);
        return (0);
    }

    if (!color)
    {
        //todo: error message
        return (0);
    }
    
    color->r = r;
    color->g = g;
    color->b = b;
    
    i = 0;
    while (split[i])
        free(split[i++]);
    free(split);
    i = 0;
    while (rgb[i])
        free(rgb[i++]);
    free(rgb);
    
    return (1);
}