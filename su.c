#include <unistd.h>
#include <stdio.h>
#include "go.h"
#include "util.h"

void main (int argc, char *argu[]) {
	char *name, *pass;
	size_t n;
	int ii;
	selfname = argu[0];
	for (ii = 1; ii < argc; ii++) {
		if (argu[ii][0] != '-' || argu[ii][1] == 0) break;
		if (argu[ii][1] == '-' && argu[ii][2] == 0) {
			ii++;
			break;
		}
	}
	
	name = ii >= argc ? "root" : argu[ii];
	pass = getpass ("Password: ");
	if (authorize (name, pass) == 0) {
		memset (pass, 0, strlen (pass));
		go (name, 0, 0);
	}
	fputs ("Denied\n", stdout);
	die (1, "%s: authorization failed\n", argu[0]);
}
