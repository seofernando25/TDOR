#include "l_config.h"

#define WINDOW_DEFAULT_W 1280
#define WINDOW_DEFAULT_H 720

bool LoadSettings(Settings *settings)
{
    if (!FileExists("config.txt"))
    {
        printf("No config file found, creating one\n");
        FILE *fp = fopen("config.txt", "w");
        fprintf(fp, "window_width=%d\n", WINDOW_DEFAULT_W);
        fprintf(fp, "window_height=%d\n", WINDOW_DEFAULT_H);
        fclose(fp);
    }

    return true;
}

bool SaveSettings(Settings *settings)
{
    return true;
}

Settings GetDefaultSettings(void)
{
    Settings settings = {0};
    return settings;
}