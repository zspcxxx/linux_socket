#include <stdarg.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "error_handing.h"

#ifdef __GNUC__
__attribute__ ((__noreturn__))
#endif

void
errExit(const char *format, ...)
{
	va_list argList;

	fflush(stdout);                   /* Flush any pending stdout */

	fprintf(stderr, "Exit: ");
	va_start(argList, format);
	vfprintf(stderr, format, argList);
	va_end(argList);

	fflush(stderr);                    /* In case stderr is not line-buffered */
	exit(EXIT_FAILURE);
}

void
usageErr(const char *format, ...)
{
	va_list argList;

	fflush(stdout);                   /* Flush any pending stdout */

	fprintf(stderr, "Usage: ");
	va_start(argList, format);
	vfprintf(stderr, format, argList);
	va_end(argList);

	fflush(stderr);                    /* In case stderr is not line-buffered */
	exit(EXIT_FAILURE);
}

void
cmdLineErr(const char *format, ...)
{
    va_list argList;

    fflush(stdout);           /* Flush any pending stdout */

    fprintf(stderr, "Command-line usage error: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);

    fflush(stderr);           /* In case stderr is not line-buffered */
    exit(EXIT_FAILURE);
}
