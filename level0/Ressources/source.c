#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#define _GNU_SOURCE

int		main(int ac, char **av)
{
	int		nb;
	char	*cmd_args[2];
	gid_t	gid;
	uid_t	uid;
	
	nb = atoi(av[1]);
	if (nb != 423)
		fwrite("No !\n", 5, 1, stderr);
	else
	{
		cmd_args[0] = strdup("/bin/sh");
		cmd_args[1] = NULL;

		gid = getegid();
		uid = geteuid();
		setresgid(gid, gid, gid);
		setresuid(uid, uid, uid);

		execv("/bin/sh", cmd_args);
	}
	return (0);
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>

// int main(int argc, char *argv[]) {
//     int value;
//     char *str;
//     gid_t egid, euid;

//     if (argc > 1) {
//         value = atoi(argv[1]);
//     } else {
//         value = 0; // Default value if no argument is provided
//     }

//     if (value != 423) { // 0x1a7 in decimal is 423
//         FILE *file = fopen("/path/to/file", "rb"); // Replace with actual file path
//         if (file) {
//             fwrite(&value, sizeof(int), 1, file);
//             fclose(file);
//         }
//     } else {
//         str = strdup("/path/to/command"); // Replace with actual command path
//         egid = getegid();
//         euid = geteuid();
//         setresgid(egid, egid, egid);
//         setresuid(euid, euid, euid);
//         execv(str, argv);
//         free(str);
//     }

//     return 0;
// }

