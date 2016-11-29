#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "muzoku.h"

#define DATA_LEN 81

static void add_rows(DancingLinks *, int, int, int);
static char *arr2string(char *, int *, size_t);
static void MZ_shuffle(Muzoku *);
static int *rand9(int *);
static void shuffleArray(int *, size_t);


Muzoku *MZ_get_instance(void)
{
    Muzoku *MZ = malloc(sizeof(Muzoku));
    memset(MZ->Data, 0, sizeof(MZ->Data));
    MZ->DL = DL_get_instance(729, 324);
    return MZ;
}

int MZ_valid(Muzoku *MZ)
{
    int *Data = MZ->Data;
    DL_init(MZ->DL, 729, 324);

    for (int i = 0; i < DATA_LEN; i++)
        for (int k = 1; k <= 9; k++)
            if (!Data[i] || Data[i] == k)
                add_rows(MZ->DL, i / N, i % N, k);
    DL_dance(MZ->DL, 0);

    return MZ->DL->flag;
}

void Mrz(void *args)
{
    MrzArg *arg = (MrzArg *)args;
    Muzoku *MZ = arg->MZ;
    int pid = arg->pid, pos[DATA_LEN], fewest = 22;
    FILE *out = fopen("out.log", "a");
    for (int i = 0; i < DATA_LEN; i++)
        pos[i] = i;

    for (int _ = 0; _ < 10; _++) {
        char strBuf[DATA_LEN + 10];
        int bak[DATA_LEN], *Data = MZ->Data;
        MZ_shuffle(MZ);
        memcpy(bak, Data, sizeof(bak));
        for (int __ = 0; __ < 10000 ; __++) {
            memcpy(Data, bak, sizeof(bak));
            int crtLen = DATA_LEN;
            shuffleArray(pos, DATA_LEN);
            for (int i = 0; i < DATA_LEN; i++) {
                int x = pos[i];
                int val = Data[x];
                Data[x] = 0;
                if (MZ_valid(MZ) != 1) {
                    Data[x] = val;
                } else if (--crtLen < fewest) {
                    fewest--;
                    printf("%s [pid=%d,n=%d]\n", arr2string(strBuf, Data, DATA_LEN),
                           pid, crtLen);
                    fprintf(out, "%s %d\n", strBuf, crtLen);
                    fflush(out);
                }
            }
        }
    }
    free(MZ);
}


static void shuffleArray(int *arr, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        size_t index = rand() % n;
        int v = arr[index];
        arr[index] = arr[i];
        arr[i] = v;
    }
}

static const int arr9[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

static int *rand9(int *dest)
{
    memcpy(dest, arr9, sizeof(arr9));
    shuffleArray(dest, 9);
    return dest;
}

static char *arr2string(char *dest, int *arr, size_t n)
{
    char buf[20];
    dest[0] = '\0';
    for (size_t i = 0; i < n; i++) {
        sprintf(buf, "%d", arr[i]);
        strcat(dest, buf);
    }
    return dest;
}

static void add_rows(DancingLinks *DL, int x, int y, int k)
{
    int r = x * DATA_LEN + y * 9 + k;
    int c1 = x * 9 + y + 1;                           // cell
    int c2 = DATA_LEN + 9 * x + k;                          // row
    int c3 = 162 + 9 * y + k;                         // column
    int c4 = 243 + (x / 3 * 3 + y / 3) * 9 + k;       // block
    DL_link(DL, r, c1);
    DL_link(DL, r, c2);
    DL_link(DL, r, c3);
    DL_link(DL, r, c4);
}

static void MZ_shuffle(Muzoku *MZ)
{
    DancingLinks *DL = MZ->DL;
    int *Data = MZ->Data;
    int p1[9], p2[9];
    do {
        memset(Data, 0, sizeof(MZ->Data));
        rand9(p1);
        rand9(p2);
        for (int i = 0; i < 9; i++)
            Data[p1[i] * 9 + i] = p2[i];
    } while (!MZ_valid(MZ));
    DL_store_answers(DL, Data);
}