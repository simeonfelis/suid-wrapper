/*****************************************************************************
 * suid-wrapper
 *
 * This program can destroy the integrity of your system. Use at your own
 * risk!
 *
 * Author: Simeon Felis
 * Date: 6 May, 2012
 * Licence: WTFPL:  http://sam.zoy.org/wtfpl/
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 *
 * Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 * TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *               0. You just DO WHAT THE FUCK YOU WANT TO.
 *
 ****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef SCRIPT_PATH
#error "SCRIPT_PATH not defined"
#endif

#ifndef SCRIPT_NAME
#error "SCRIPT_NAME not defined"
#endif

#ifndef ALLOWED_UID
#error "ALLOWED_UID not defined"
#endif

#ifndef ALLOWED_GID
#error "ALLOWED_GID not defined"
#endif

#define STR(s) #s

int main( int argc, char ** argv, char ** envp )
{
	pid_t nPid;
	int status;
	int exit_status;
	const int allowed_uid = ALLOWED_UID;
	const int allowed_gid = ALLOWED_GID;
	
	if( argc > 5) {
		printf( "The wrapper only supports up to 4 arguments\n" );
		exit( 255 );
	}

	if( getuid() != allowed_gid ) { /* as of /etc/passwd */
		printf( "You don't have permissions to run this wrapper\n" );
		exit( 255 );
	}
	if( getgid() != allowed_sid ) { /* as of /etc/passwd */
		printf( "You don't belong to group with permissions to run run this wrapper\n" );
		exit( 255 );
	}

	if( setgid(getegid()) ) 
		perror( "set setgid" );

	if( setuid(geteuid()) ) 
		perror( "set setuid" );


	nPid = fork();

	if ( nPid < 0 ) {
		perror( "fork() did not succeed");
		exit( 255 );
	}
	else if ( nPid == 0 ) {
		/* I'm the parent, waiting for childs to come home */
		waitpid(nPid, &status, 0);
		exit_status = WEXITSTATUS(status);
		//printf("exit_status: %i\n", exit_status);
		exit( exit_status );
	}
	else {
		/* I'm the child */
		/* if you know a better way to SAFELY determine the arguments 
		 * passed to the wrapper, let me know */
		if( argc == 2)
			execlp( STR(SCRIPT_PATH), STR(SCRIPT_NAME), argv[1], NULL);
		else if( argc == 3)
			execlp( STR(SCRIPT_PATH), STR(SCRIPT_NAME), argv[1], argv[2], NULL);
		else if( argc == 4 )
			execlp( STR(SCRIPT_PATH), STR(SCRIPT_NAME), argv[1], argv[2], argv[3], NULL);
		else if( argc == 5 )
			execlp( STR(SCRIPT_PATH), STR(SCRIPT_NAME), argv[1], argv[2], argv[3], argv[4], NULL);

		perror( "execlp of script failed?" );
	}

	exit( 255 );
}

