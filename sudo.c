#include <memory.h>
#include <unistd.h>
#include <stdio.h>
#include <err.h>
#include "go.h"

void main (int argc, char *argu[]) {
	char *name, *pass;
	size_t n;
	int ii;
	name = "root";
	for (ii = 1; ii < argc; ii++) {
		if (argu[ii][0] != '-' || argu[ii][1] == 0) break;
		if (argu[ii][1] == '-' && argu[ii][2] == 0) {
			ii++;
			break;
		}
		switch (argu[ii][1]) {
		case 'u':
			name = argu[++ii];
			break;
		default:
			errx (1, "bad option %c", argu[ii][1]);
		}
	}
	
	if (ii > argc) errx (1, "bad arguments");
	pass = getpass ("Password: ");
	if (authorize (name, pass) == 0) {
		memset (pass, 0, strlen (pass));
		go (name, GoKeepEnviron | GoSearchPath, argu + ii);
	}
	fputs ("Denied\n", stdout);
	errx (1, "authorization failed");
}
