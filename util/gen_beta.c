#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../util/list.h"
#include "../util/defs.h"
#include "debug.h"
#include "files.h"
#include "gen_beta.h"

float gen_beta(uint32_t a, uint32_t b)
{
    /* List of 'a + b + 1' uniform-distributed numbers */
    List listUniform;
    memset(&listUniform, 0, sizeof(List)); ListInit(&listUniform);

    /* Generate a + b + 1 uniform U(0,1) */
    for (uint32_t i = 0; i < a + b + 1; i++)
    {
        float *sample = (float *)malloc(sizeof(float));
        *sample = (float)(rand() % 100)/100.0;

        bool inserted = false;
        for (ListElem *elem = ListFirst(&listUniform); elem != NULL; elem = ListNext(&listUniform, elem))
        {
            float *number = (float *)elem->obj;

            if (*number >= *sample)
            {
                ListInsertBefore(&listUniform, (void *)sample, elem);
                inserted = true;
                break;
            }
        }

        if (!inserted)
        {
            ListAppend(&listUniform, (void *)sample);
        }
    }

    ListElem *elem = ListFirst(&listUniform);
    for (uint32_t i = 0; i < a; i++)
    {
        elem = ListNext(&listUniform, elem);
    }

    float *beta_number = (float *)elem->obj;

	return (*beta_number);
}

void testBeta(void)
{
    #define N 1000

    FILE *fp = NULL;
    openFile(&fp, "beta.csv", "w");

    /* Testing Beta(1,1) */
    for (uint16_t i = 0; i < N; i++)
    {
        fprintf(fp, "%f,",gen_beta(1,1));
    }
    fprintf(fp, "\n");

    /* Testing Beta(3,3) */
    for (uint16_t i = 0; i < N; i++)
    {
        fprintf(fp, "%f,",gen_beta(3,3));
    }
    fprintf(fp, "\n");

    /* Testing Beta(1,2) */
    for (uint16_t i = 0; i < N; i++)
    {
        fprintf(fp, "%f,",gen_beta(1,2));
    }
    fprintf(fp, "\n");

    /* Testing Beta(5,7) */
    for (uint16_t i = 0; i < N; i++)
    {
        fprintf(fp, "%f,",gen_beta(5,7));
    }
    fprintf(fp, "\n");

    /* Testing Beta(7,10) */
    for (uint16_t i = 0; i < N; i++)
    {
        fprintf(fp, "%f,",gen_beta(7,10));
    }
    fprintf(fp, "\n");

    /* Testing Beta(15,20) */
    for (uint16_t i = 0; i < N; i++)
    {
        fprintf(fp, "%f,",gen_beta(15,20));
    }
    fprintf(fp, "\n");

    fclose(fp);
}
