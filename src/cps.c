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
#include <limits.h> // use this instead of hard coding the string limit

#define arg_debug()  \
    printf("%d ", argc);\
    printf("%s ", argv[(argc-1)]);\
    printf("%s ", argv[(argc-2)]);\
    printf("%s ", argv[(argc-3)]);


char ps_cmd[255];
char w_cmd[255];
char ret[2]; 
char *err = NULL;

int main(int argc, char **argv)
{
    //arg_debug()
    int cnt = atoi(argv[(argc-1)]); 
    sprintf(w_cmd, "sleep %s", argv[argc-3]);
    sprintf(ps_cmd, "ps aux | grep -ic \"%s\" -", argv[argc-2]);
    
    int i;
    for (i = 0; i < cnt; i++) {
	FILE *f = popen(ps_cmd, "r");
	fgets(ret, 2, f);
	pclose(f);
	
	int tmp = atoi(ret);
	tmp -= 3;

	if (tmp >= 1) {
	    printf("The process `%s` is running, it currently has %d invocation(s).\n", argv[argc-2], tmp);
	    system(w_cmd);
	} else if (tmp < 1) {
	    printf("The process `%s` is not running.\n", argv[argc-2]);
	    break;
	} 	    
    }
    printf("Done.\n");
    return 0;
}


