#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include "go.h"

extern char **environ;

/* set up login environment, then start argu[0] with arguments argu,
 * which must be null-terminated,
 * or login shell if argu null
 */
void go (const char *name, int flags, char *argu[]) {
	struct passwd *up;
	char *env[6];
	pid_t pid = 0;
	
	up = getpwnam (name);
	if (!up) err (1, "failed to getpwnam");
	
	if (setuid (up -> pw_uid) < 0) err (1, "failed to setuid");
	if (chdir  (up -> pw_dir) < 0) err (1, "failed to chdir home");

	if (! (flags & GoKeepEnviron)) {
		if (asprintf (&env[0],  "HOME=%s", up -> pw_dir)   < 0 ||
		    asprintf (&env[1], "SHELL=%s", up -> pw_shell) < 0 ||
		    asprintf (&env[2],  "USER=%s", up -> pw_name)  < 0 ||
		    asprintf (&env[3],  "PATH=%s", up -> pw_uid == 0 ? "/sbin:/bin:/usr/sbin:/usr/bin" : "/usr/local/bin:/bin:/usr/bin:.") < 0 ||
		    getenv ("TERM") ?
		    asprintf (&env[4],  "TERM=%s", getenv ("TERM")) < 0 :
		    (env[4] = 0)) err (1, "failed to allocate memory");
		env[5] = 0;
	}
	
	if (flags & GoFork) pid = fork ();
	if (pid < 0) err (1, "failed to fork");
	if (pid > 0) exit (0);
	
	if (flags & GoSetSID) if (setsid () < 0) err (1, "failed to setsid");
	
	if (!argu) argu = (char * []){ up -> pw_shell, "-l", 0 };
	if (execve (argu[0], argu, flags & GoKeepEnviron ? environ : env) < 0) err (1, "failed to exec");
}
