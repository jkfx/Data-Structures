#include <stdio.h>
#include <stdlib.h>
#include "List.h"

struct Node {
    ElementType Element;
    Position Next;
};

/* Return true if L is empty */
int IsEmpty( List L ) {
    return L->Next == NULL;
}

/* Return tyue if P is the last position in list L */
/* Parameter L is unused in this implementation */
int IsLast( Position P, List L ) {
    return P->Next == NULL;
}

/* Return Position of X in L; NULL if not found */
Position Find( ElementType X, List L ) {
    Position P;
    P = L->Next;
    while ( P != NULL && P->Element != X ) {
        P = P->Next;
    }
    return P;
}
