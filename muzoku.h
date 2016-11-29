#ifndef __RF_MUZOKU_H__

#include "dancing_links.h"

struct _Muzoku_T {
    int Data[81];
    DancingLinks *DL;
};
typedef struct _Muzoku_T Muzoku;

struct _MrzArg_T {
    Muzoku *MZ;
    int pid;
};
typedef struct _MrzArg_T MrzArg;

Muzoku *MZ_get_instance(void);
int MZ_valid(Muzoku *);
void Mrz(void *);

#define __RF_MUZOKU_H__
#endif /*__RF_MUZOKU_H__*/