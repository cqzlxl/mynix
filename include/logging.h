#ifndef LOGGING_H
#define LOGGING_H


#define LOGGING_DEBUG   0
#define LOGGING_INFO    1
#define LOGGING_WARN    2
#define LOGGING_ERROR   3

#define LOGGER_MAIN     "MAIN"
#define LOGGER_MM       "MM"
#define LOGGER_PM       "PM"
#define LOGGER_INT      "INT"

extern void logging_init();

extern int log_debug(const char *logger, const char *format, ...);
extern int log_info(const char *logger, const char *format, ...);
extern int log_warn(const char *logger, const char *format, ...);
extern int log_error(const char *logger, const char *format, ...);


#endif
