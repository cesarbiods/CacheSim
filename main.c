#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    long tag;
    bool valid;
    int index;
    int accesses;
    long time;
} line;

void killCache(line** cache) {
    free(*cache);
    free(cache);
}

bool check_hit(long address, line* l, long tagMask) {
  bool ret_value = (l->valid && (l->tag == (address & tagMask)));
  if (ret_value) {
    l->accesses++;
    l->time = clock();
  }
  return ret_value;
}

int main() {
    clock_t start = clock();

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
    float references = 0;
    float misses = 0;
    float hits = 0;

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
            cache[i][j].time = 0;
        }
    }

    long bMask = ~(~0 << b);
    long sMask = ~(~0 << s) << b;
    long tMask = ~0 << (s + b);

    printf("Please enter your addresses in hex form, or -1 to quit\n");
    char input[9];
    unsigned long address = 0;

    while(strcmp("-1", input) != 0) {
        scanf("%s", input);
        if (strcmp("-1", input) == 0) {
            break; 
        } else {
            sscanf(input, "%lx", &address);
        }

        bool hit = false;
        for (int i = 0; i < lineNum; i++) {
            if (check_hit(address, &cache[(address & sMask) >> b][i], tMask)) {
                hit = true;
                break;
            }
        }
        if (hit) {
            references++;
            hits++;
            printf("%lx H\n", address);
        }
        else {
            references++;
            misses++;
            bool done = false;
            while (!done) {
                for (int i = 0; i < lineNum; i++) {
                    if (!cache[(address & sMask) >> b][i].valid) {
                        cache[(address & sMask) >> b][i].valid = true;
                        cache[(address & sMask) >> b][i].tag = (address & tMask);
                        printf("%lx M\n", address);
                        done = true;
                        break;
                    }
                }
                if (done) {
                    break;
                }
                if (strcmp(rp, "LFU") != 0) {
                    int temp = 100000;
                    for (int i = 0; i < lineNum; i++) {
                        if (!(temp < cache[(address & sMask) >> b][i].accesses)) {
                            temp = cache[(address & sMask) >> b][i].accesses;
                        }
                    }
                    for (int i = 0; i < lineNum; i++) {
                        if (temp == cache[(address & sMask) >> b][i].accesses) {
                            cache[(address & sMask) >> b][i].valid = true;
                            cache[(address & sMask) >> b][i].tag = (address & tMask);
                            printf("%lx M\n", address);
                            done = true;
                            break;
                        }
                    }
                } else {
                    long temp = 99999999999;
                    for (int i = 0; i < lineNum; i++) {
                        if (!(temp < cache[(address & sMask) >> b][i].time)) {
                            temp = cache[(address & sMask) >> b][i].time;
                        }
                    }
                    for (int i = 0; i < lineNum; i++) {
                        if (temp == cache[(address & sMask) >> b][i].time) {
                            cache[(address & sMask) >> b][i].valid = true;
                            cache[(address & sMask) >> b][i].tag = (address & tMask);
                            printf("%lx M\n", address);
                            done = true;
                            break;
                        }
                    }
                }
            }
        }
    }
    clock_t end = clock();
    int total = (hTime*hits) + ((hTime+mPenalty)*misses);
    float mRate = ((misses/references) * 100);
    int final = (int)(mRate < 0 ? (mRate - 0.5) : (mRate + 0.5));
    printf("%d %d\n", final, total);
    
    killCache(cache);
    return 0;
}
