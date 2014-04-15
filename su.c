#include <memory.h>
#include <unistd.h>
#include <stdio.h>
#include <err.h>
#include "go.h"

void main (int argc, char *argu[]) {
	char *name, *pass;
	size_t n;
	int ii, flags = GoKeepEnviron;
	for (ii = 1; ii < argc; ii++) {
		if (argu[ii][0] != '-' || argu[ii][1] == 0) break;
		if (argu[ii][1] == '-' && argu[ii][2] == 0) {
			ii++;
			break;
		}
		for (int jj = 1; argu[ii][jj]; jj++) switch (argu[ii][jj]) {
		case 'l':
			flags |=  GoChdirHome;
			flags &= ~GoKeepEnviron;
			break;
		default:
			errx ("bad option %c", argu[ii][jj]);
		}
	}
	
	name = ii >= argc ? "root" : argu[ii];
	pass = getpass ("Password: ");
	if (authorize (name, pass) == 0) {
		memset (pass, 0, strlen (pass));
		go (name, flags, 0);
	}
	fputs ("Denied\n", stdout);
	errx (1, "authorization failed");
}
