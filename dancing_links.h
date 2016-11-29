#ifndef __DANCING_LINKS_H__
#define __DANCING_LINKS_H__


#define	N 9
#define	MAXN 750
#define	MAXM 350
#define	MAXD 3500

struct _Dancing_Links_T {
    int n, m, tot, C, flag;
    int U[MAXD], D[MAXD], L[MAXD], R[MAXD];
    int Row[MAXD], Col[MAXD];
    int S[MAXM], H[MAXN], use[MAXN];
};
typedef struct _Dancing_Links_T DancingLinks;

DancingLinks *DL_get_instance(int, int);
void DL_init(DancingLinks *, int, int);
void DL_link(DancingLinks *, int, int);
void DL_remove(DancingLinks *, int);
void DL_restore(DancingLinks *, int);
void DL_dance(DancingLinks *, int);
void DL_store_answers(DancingLinks *, int *);


#endif /*__DANCING_LINKS_H__*/