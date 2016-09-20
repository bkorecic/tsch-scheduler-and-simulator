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
        float *num = (float *)elem->obj;
        elem = ListNext(&listUniform, elem);
    }

    float *beta_number = (float *)elem->obj;

	return (*beta_number);
}
