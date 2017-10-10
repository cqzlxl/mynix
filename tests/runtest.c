#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


static int logging(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int m = vfprintf(stderr, format, ap);
    int n = fprintf(stderr, "\n");
    va_end(ap);
    return m+n;
}


int main(int argc, char *argv[])
{
    const char *cases_lib = argv[1];

    void *cases = dlopen(cases_lib, RTLD_LAZY);
    if (! cases) {
        logging("error while load cases from: %s: %s", cases_lib, dlerror());
        exit(EXIT_FAILURE);
    } else {
        // clear any errors
        dlerror();
    }

    for (int i = 2; i < argc; ++i) {
        const char *case_name = argv[i];

        pid_t child = fork();
        if (child < 0) {
            logging("failed to start: %s: %s", case_name, strerror(errno));
            break;
        }

        if (child > 0) {
            int status;
            waitpid(child, &status, 0);
            if (WEXITSTATUS(status)) {
                logging("failed: %s", case_name);
            } else {
                logging("passed: %s", case_name);
            }
        } else {
            void (*test_func)() = dlsym(cases, case_name);
            const char *error = dlerror();
            if (error) {
                logging("failed to pull test func: %s: %s", case_name, error);
                exit(EXIT_FAILURE);
            } else {
                (*test_func)();
                exit(EXIT_SUCCESS);
            }
        }
    }

    dlclose(cases);

    return 0;
}
