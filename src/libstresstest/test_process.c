
#include <Test.h>

/**********************************
 *  Start process in background
 **********************************/
void run_test_in_background(int argc, char **argv, const char[] const workFolder)
{
    pid_t pid, sid;
    FILE *f;

    if(argv==NULL) {
            LOGE("Missing argv");
            exit(EXIT_FAILURE);
    }
    /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
            LOGE("Failed process fork");
            exit(EXIT_FAILURE);
    }

    if (pid > 0) {
            LOGE("Failed process fork");
            exit(EXIT_FAILURE);
    }

    /* Change the file mode mask */
    umask(0);

    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
            /* Log any failures here */
            LOGE("Failed to get process sid");
            exit(EXIT_FAILURE);
    }
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    /* Daemon-specific initialization goes here */
    char pidfile_name[1024] ="";

    strcat(pidfile_name, workFolder);
    strcat(pidfile_name, PATH_SEPARATOR);
    strcat(pidfile_name, argv[0]);
    strcat(pidfile_name, ".pid");

    if( (f = fopen(pidfile_name, "w")) == NULL) {
            LOGE("Unable to open file %s\n", pidfile_name);
            exit(EXIT_FAILURE);
        }
    fprintf(f, "%d", getpid());
    fclose(f);
}

