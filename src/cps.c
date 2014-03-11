// NAME
//	cps - check process is running
//
// SYNOPSIS
//	cps INTERVAL[UNIT] PROCESS COUNT
//
// DESCRIPTION
//	Check that PROCESS is running every time INTERVAL has elapsed for 
//	COUNT times.
//	
//	TIME is the amount of alloted time to wait before rechecking, and
//	can be given a optional suffix of UNIT, where UNIT is anything in
//	[s|m|h|d] (meaning seconds, minutes, hours and days, respectively).
//	If no argument is given, then UNIT defaults to seconds.
//
//	For example, you can invoke it like so:
//	    `cps 40 x 4`
//	Which would check every 40 seconds to see if the process named `x`
//	is running, for a maximum of 4 times.
// 
//	If COUNT elapses and PROCESS is still running, then cps will echo 
//	'0' and terminate, if PROCESS terminates and cps is still running,
//	cps will echo '1' and then terminate.
//
// AUTHOR
//	Written by Finn O'leary.
//
// ENVIRONMENT
//	The commands `ps`, `grep` and `sleep` must be installed to use `cps`
//
// REPORTING BUGS
//	Please report any bugs to gallefray@inventati.org or @Gallefray
//	You may also report an issue on the github page:
//	http://github.com/Gallefray/cps
//	
// SEE ALSO
//	ps(1), grep(1),	sleep(1)
//
//


// NB: This is a rough draft of cps, I'll add in argument type checking and the like later.
 

#include <stdlib.h>
#include <stdio.h>
//#include <limits.h>	// use this instead of hard coding the string limit?

#define MCMDLEN 255	// Max CoMmanD LENgth

#define arg_debug()  \
    printf("%d ", argc);\
    printf("%s ", argv[(argc-1)]);\
    printf("%s ", argv[(argc-2)]);\
    printf("%s ", argv[(argc-3)]);


int cmd(char cmd[MCMDLEN]);
int ret_ps_stat(int in, char *ps_name);

char ps_cmd[MCMDLEN];
char w_cmd[MCMDLEN];
char *err = NULL;

int main(int argc, char **argv)
{
    //arg_debug()
    if (argc == 4) {
	int cnt = atoi(argv[(argc-1)]); 
	sprintf(w_cmd, "sleep %s", argv[argc-3]);
	sprintf(ps_cmd, "ps aux | grep -ic \"%s\" -", argv[argc-2]);
	if (cnt > 0) {
	    int i, tmp;
	    for (i = 0; i < cnt; i++) {
		tmp = cmd(ps_cmd);
		if ((ret_ps_stat(tmp, argv[argc-2])) == -1)
		    break;
	    }
	}
	else if (cnt == 0) {
	    int tmp;
	    int i = 0;
	    while (i == 0) {
		tmp = cmd(ps_cmd);
		if ((ret_ps_stat(tmp, argv[argc-2])) == -1)
		    break;
	    }	    
	}
	printf("Done.\n");
    }
    else if (argc > 4) {
	printf("Too many arguments.");
	return -1;
    }
    else if (argc < 4) {
	printf("Not enough arguments.");
	return -1;
    }
    return 1;
}

int cmd(char cmd[MCMDLEN])
{
    char ret[MCMDLEN];
    FILE *f = popen(cmd, "r");
    fgets(ret, MCMDLEN, f);
    pclose(f);
    
    int tmp = atoi(ret);
    tmp -= 3;
    return tmp;
}

int ret_ps_stat(int in, char *ps_name)
{
    if (in >= 1) {
	printf("The process `%s` is running, it currently has %d invocation(s).\n", ps_name, in);
	system(w_cmd);
    } else if (in < 1) {
	printf("The process `%s` is not running.\n", ps_name);
	return -1;
    }
    return 0;
}
