#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Line{
    int tag;
    int index;
    int offset;
} ;

struct Line** generateCache(int sets, int lines) {
    struct Line** cache = malloc(sizeof(struct Line) * (lines * sets));
    return cache;
}

void killCache(struct Line** cache) {
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

    printf("What kind of cache are we dealing with here?\n");
    scanf("%d", &setNum);
    scanf("%d", &lineNum);
    scanf("%d", &blockSize);
    scanf("%d", &addrBitsNum);
    scanf("%s", rp);
    scanf("%d", &hTime);
    scanf("%d", &mPenalty);
    printf("Please enter your addresses in hex form, or -1 to quit\n");
    
    return 0;
}