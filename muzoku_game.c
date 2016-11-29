#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "muzoku.h"

int main()
{
    pthread_t id[4];
    time_t bg = time(NULL);
    srand(bg);
    for (int i = 0; i < 4; i++) {
        Muzoku *mz = MZ_get_instance();
        MrzArg *arg = malloc(sizeof(MrzArg));
        arg->pid = i;
        arg->MZ = mz;
        pthread_create(&id[i], NULL, (void *)Mrz, (void *)arg);
    }
    for (int i = 0; i < 4; i++)
        pthread_join(id[i], NULL);
    printf("DONE, COST=%ld\n", time(NULL) - bg);
    return 0;
}
