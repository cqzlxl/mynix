#include <arg.h>
#include <drivers.h>
#include <file.h>
#include <logging.h>
#include <printf.h>


static file_t oappender;
static file_t *appender;


static int do_log(const char *logger, int level, const char *format, va_list ap)
{
    const char *slevel;
    switch (level) {
        default:
            slevel = " ";
            break;

        case LOGGING_DEBUG:
            slevel = "DEBUG";
            break;

        case LOGGING_INFO:
            slevel = "INFO";
            break;

        case LOGGING_WARN:
            slevel = "WARN";
            break;

        case LOGGING_ERROR:
            slevel = "ERROR";
            break;
    }

    int count = 0;

    int n;
    n = printf_e(appender, "[%s] [%+5s] ", logger, slevel);
    if (n == -1) {
        return -1;
    } else {
        count += n;
    }
    n = printf_v(appender, format, ap);
    if (n == -1) {
        return -1;
    } else {
        count += n;
    }
    n = printf_e(appender, "\n");
    if (n == -1) {
        return -1;
    } else {
        count += n;
    }

    return count;
}


void logging_init()
{
    serial_init();

    oappender.magic = FILE_SERIAL;
    oappender.writec = serial_writec;
    oappender.writes = serial_writes;
    oappender.data = NULL;
    appender = &oappender;
}


#define impl_level(L, LN) \
int log_ ## L(const char *logger, const char *format, ...)              \
{                                                                       \
    va_list ap;                                                         \
    va_start(ap, format);                                               \
    int n = do_log(logger, LOGGING_ ## LN, format, ap);                 \
    va_end(ap);                                                         \
    return n;                                                           \
}


impl_level(debug, DEBUG)

impl_level(info, INFO)

impl_level(warn, WARN)

impl_level(error, ERROR)
