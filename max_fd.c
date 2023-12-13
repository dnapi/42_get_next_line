#include <stdio.h>
#include <sys/resource.h>

int main() {
    struct rlimit rlim;

    // Get the current resource limits
    if (getrlimit(RLIMIT_NOFILE, &rlim) == 0) {
        printf("Current maximum number of file descriptors: %ld\n", rlim.rlim_cur);
        printf("Maximum allowed number of file descriptors: %ld\n", rlim.rlim_max);
    } else {
        perror("getrlimit");
        return 1;
    }

    return 0;
}

