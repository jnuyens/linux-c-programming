#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
        pid_t pid;
	char cwdir_child[100];
	char cwdir_parent[100];

	if ((pid = fork()) < 0) {
	        perror("fork error");
		exit(1);
	}

	if (pid == 0) {
	  /* We are in the childs thread 
	   *  lets change the directory to /tmp */
                if(chdir("/tmp") < 0) {
	                perror("chdir error");
		}
		/*  Let's print the current working directory of the child
		 */
		if (getcwd(cwdir_child, 100) != NULL) {
		        printf("The directory of the child is : %s\n", cwdir_child);
		} else {
		        perror("getcwd client error");
		}
	 /* end of the child process */
	} else {
	  /* Now we are in the parent process
	   * Let's check the current working directory */
	        if (getcwd(cwdir_parent, 100) != NULL) {
		        printf("The directory of the parent is : %s\n", cwdir_parent);
		} else {
		        perror("getcwd parent error");
		}
	}
	return(0);
}
