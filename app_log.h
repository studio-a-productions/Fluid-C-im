#ifndef APP_LOG_H
#define APP_LOG_H
/*
** A useful logging API that allows you to know exactly what went wrong.
**
** If you are having problems with ##__VA_ARGS__, you can replace the ## but you'll have to add to each call a last (empty) argument if there happens to be none
*/

#define LOG_INIT "Init"
#define LOG_QUIT "Quit"
#define LOG_GFX "Graphics"
#define LOG_GFX_INIT "Init:Graphics"
#define LOG_GFX_QUIT "Quit:Graphics"
#define LOG_GFX_TEXTURE "Graphics:Texture"
#define LOG_SYS "System"
#define LOG_SYS_INIT "Init System"
#define LOG_SYS_QUIT "Quit System"



#include <SDL.h>


#define APP_LOG_FORMAT "[%s] (%s:%d) "

#define AppLog(origin, fmt, ...) \
    SDL_Log("[%s] " fmt, origin, ##__VA_ARGS__)

#define AppLogInfo(origin, fmt, ...) \
    SDL_Log(APP_LOG_FORMAT fmt, origin, __FILE__, __LINE__, ##__VA_ARGS__)

#define AppLogWarn(origin, fmt, ...) \
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, APP_LOG_FORMAT fmt, origin, __FILE__, __LINE__, ##__VA_ARGS__)

#define AppLogError(origin, fmt, ...) \
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, APP_LOG_FORMAT fmt, origin, __FILE__, __LINE__, ##__VA_ARGS__)

#define AppLogCrit(origin, fmt, ...) \
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, APP_LOG_FORMAT fmt, origin, __FILE__, __LINE__, ##__VA_ARGS__)

#endif