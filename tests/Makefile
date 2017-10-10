cases_sources  = $(wildcard test_*.c)
cases_library  = libtests.so

cases_runner   = runtest


CFLAGS         = -std=c99 -m32 -Wall -Wextra -Werror


.PHONY: all clean

all: $(cases_runner) $(cases_library)
	./$(cases_runner) ./$(cases_library) \
		test_test \
		test_xorp


$(cases_library): $(cases_runner) $(cases_sources)
	$(CC) $(CFLAGS) -shared -fPIC \
		-Wl,--whole-archive ../libk.a \
		-Wl,--no-whole-archive \
		-o $@ $(filter-out $<, $^)


$(cases_runner): $(cases_runner).c
	$(CC) $(CFLAGS) -ldl -o $@ $^


clean:
	$(RM) $(cases_library)
	$(RM) $(cases_runner)
