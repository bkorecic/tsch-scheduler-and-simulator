#ifndef _DEBUG_H_
#define _DEBUG_H_

#define DEBUG 1

#define EXIT(...) do{fprintf(stderr, "\nAt %s (%s:%d) ", __func__, __FILE__, __LINE__); \
                    fprintf(stderr, __VA_ARGS__); \
                    fprintf(stderr, "\n"); \
                    fflush(stderr); exit(1);}while(0)

#define ERROR(...) do{fprintf(stderr, "\nAt %s (%s:%d) ", __func__, __FILE__, __LINE__); \
                    fprintf(stderr, __VA_ARGS__); \
                    fprintf(stderr, "\n");}while(0)

#if DEBUG
#define PRINTF(...) fprintf(stdout, __VA_ARGS__)
#else
#define PRINTF(...)
#endif // DEBUG

#endif // _DEBUG_H_
