#include <shadow.h>
#include <string.h>
#include <stdio.h>
#include "auth.h"
#include "util.h"

/* return 0 iff user authorized
 * pass argument in the clear
 */
int authorize (const char *name, const char *pass) {
	struct spwd *shp;
	char *x; /* password hash */

	shp = getspnam (name);
	if (!shp) {
		fprintf (stderr, "%s: failed to find password\n", selfname);
		return 1;
	}
	
	switch (shp -> sp_pwdp[0]) {
	case '!': return 1;
	case '$': break;
	default : fprintf (stderr, "%s: bad password format\n", selfname);
	          return 1;
	}
	x = crypt (pass, shp -> sp_pwdp);
	if (!x) {
		fprintf (stderr, "%s: failed to compute password hash\n", selfname);
		return 1;
	}
	
	return (strcmp (x, shp -> sp_pwdp));
}
