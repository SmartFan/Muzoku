#include <string.h>
#include <stdlib.h>
#include "dancing_links.h"


DancingLinks *DL_get_instance(int n, int m)
{
    DancingLinks *DL = malloc(sizeof(DancingLinks));
    DL_init(DL, n, m);
    return DL;
}

void DL_init(DancingLinks *DL, int n, int m)
{
    memset(DL, 0, sizeof(DancingLinks));
    DL->n = n;
    DL->m = m;
    for (int i = 0; i <= m; i++) {
        DL->U[i] = DL->D[i] = i;
        DL->L[i] = i - 1;
        DL->R[i] = i + 1;
    }
    DL->L[0] = m;
    DL->R[m] = 0;
    DL->tot = m + 1;
    for (int i = 1; i <= n; i++)
        DL->H[i] = -1;
}

void DL_link(DancingLinks *DL, int r, int c)
{
    int *U = DL->U;
    int *D = DL->D;
    int *L = DL->L;
    int *R = DL->R;
    int *H = DL->H;
    int *S = DL->S;
    int *Row = DL->Row;
    int *Col = DL->Col;
    int tot = DL->tot;

    U[tot] = c;
    D[tot] = D[c];
    U[D[c]] = tot;
    D[c] = tot;
    if (~H[r]) {
        L[tot] = H[r];
        R[tot] = R[H[r]];
        L[R[H[r]]] = tot;
        R[H[r]] = tot;
    } else {
        H[r] = L[tot] = R[tot] = tot;
    }
    Col[tot] = c;
    Row[tot] = r;
    S[c]++;
    DL->tot++;
}

void DL_remove(DancingLinks *DL, int c)
{
    int *U = DL->U;
    int *D = DL->D;
    int *L = DL->L;
    int *R = DL->R;
    int *S = DL->S;
    int *Col = DL->Col;

    L[R[c]] = L[c];
    R[L[c]] = R[c];
    for (int i = D[c]; i != c; i = D[i]) {
        for (int j = R[i]; j != i; j = R[j]) {
            U[D[j]] = U[j];
            D[U[j]] = D[j];
            S[Col[j]]--;
        }
    }
}

void DL_restore(DancingLinks *DL, int c)
{
    int *U = DL->U;
    int *D = DL->D;
    int *L = DL->L;
    int *R = DL->R;
    int *S = DL->S;
    int *Col = DL->Col;

    for (int i = U[c]; i != c; i = U[i]) {
        for (int j = L[i]; j != i; j = L[j]) {
            U[D[j]] = D[U[j]] = j;
            S[Col[j]]++;
        }
    }
    L[R[c]] = R[L[c]] = c;
}

void DL_dance(DancingLinks *DL, int d)
{
    int *D = DL->D;
    int *L = DL->L;
    int *R = DL->R;
    int *S = DL->S;
    int *use = DL->use;
    int *Row = DL->Row;
    int *Col = DL->Col;

    if (DL->flag == 2)
        return;
    if (R[0] == 0) {
        DL->C = d;
        if (DL->flag <= 1)
            DL->flag++;
        return;
    }

    int c = R[0];
    for (int i = R[0]; i; i = R[i])
        if (S[i] < S[c])
            c = i;
    DL_remove(DL, c);

    for (int i = D[c]; i != c; i = D[i]) {
        use[d] = Row[i];
        for (int j = R[i]; j != i; j = R[j])
            DL_remove(DL, Col[j]);
        DL_dance(DL, d + 1);
        if (DL->flag == 2)
            return;
        for (int j = L[i]; j != i; j = L[j])
            DL_restore(DL, Col[j]);
    }
    DL_restore(DL, c);
}

void DL_store_answers(DancingLinks *DL, int *dest)
{
    int *use = DL->use;
    for (int i = 0; i < DL->C; i++) {
        int id = (use[i] - 1) / N, num = (use[i] - 1) % N + 1;
        dest[id] = (int) num;
    }
}