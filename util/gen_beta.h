#ifndef _GEN_BETA_H_
#define _GEN_BETA_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../util/list.h"
#include "../util/defs.h"

/* This function generates beta(a,b) random numbers, where a and b are integers */
float gen_beta(uint32_t a, uint32_t b);

#endif // _GEN_BETA_H_
