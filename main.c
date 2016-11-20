#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

int cycles;

typedef struct {
    long tag;
    bool valid;
    int index;
    int accesses;
} line;

void killCache(line** cache) {
    free(*cache);
    free(cache);
}

int main() {

    int setNum;
    int lineNum;
    int blockSize;
    int addrBitsNum;
    char rp[3];
    int hTime;
    int mPenalty;
    int s;
    int b;
    line** cache;

    clock_t start, end, total;
    start = clock();
    printf("%ld\n", start);

    printf("What kind of cache are we dealing with here?\n");
    scanf("%d", &setNum);
    s = log2(setNum);
    scanf("%d", &lineNum);
    scanf("%d", &blockSize);
    b = log2(blockSize);
    scanf("%d", &addrBitsNum);
    scanf("%s", rp);
    scanf("%d", &hTime);
    scanf("%d", &mPenalty);

    cache =  malloc(sizeof(line *) * setNum);
    for (int i = 0; i < setNum; i++) {
        cache[i] = malloc(sizeof(line *) * lineNum);
    }
    for (int i = 0; i < setNum; i++) {
        for (int j = 0; j < lineNum; j++) {
            cache[i][j].tag = 0;
            cache[i][j].valid = false;
            cache[i][j].index = 0;
            cache[i][j].accesses = 0;
        }
    }

    long bMask = ~(~0 << b);
    long sMask = ~(~0 << s) << b;
    long tMask = ~0 << (s + b);

    end = clock();
    printf("%ld\n", end);

    printf("Please enter your addresses in hex form, or -1 to quit\n");
    long address = 0;
    while(address != -1) {
        scanf("%lu", &address);
    }
    
    killCache(cache);
    return 0;
}