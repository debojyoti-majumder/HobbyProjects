void veryBadLogging(char *logString) {
    char *logFile = "/var/log/stuidsoft/something.log";
    FILE *fp = NULL;

    time_t t;
    time(&t);
    pid_t caller = getpid();

    fp = fopen(logFile, "a");
    char *ctime_no_newline = strtok(ctime(&t), "\n");

    if( fp != NULL ) {
        fprintf(fp, "%s [%d] %s\n", ctime_no_newline, caller, logString);
        fclose(fp);
    }
}
