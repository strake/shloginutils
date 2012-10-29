#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "util.h"

char *selfname;

void vdie (int n, const char *fmt, va_list ap) {
	vfprintf (stderr, fmt, ap);
	if (fmt[strlen (fmt) - 1] == ':') fprintf (stderr, " %s\n", strerror (errno));
	exit (n);
}

void die (int n, const char *fmt, ...) {
	va_list ap;
	va_start (ap, fmt);
	vdie (n, fmt, ap);
	va_end (ap);
}
