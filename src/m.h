#ifndef MAT_H
#define MAT_H

#include <stdlib.h>

struct m;
typedef struct m M;

M *M_new(const size_t d);
M *M_mul(const M *a, const M *b);
M *M_I(const size_t d);
void M_delete(M *m);

#endif // !MAT_H
