#include <stdlib.h>
#include <stdio.h>
int main() {

    FILE *fp;
    char tmp[256];
    char space = ' ';
    fp = fopen("input", "r");
    while(fgets(tmp, sizeof tmp, fp)) {
        char lineTmp[85];
        int i = 0;
        int j = 0;
        unsigned int a = -1;
        unsigned int b = -1;
        unsigned int c = -1;
        char done = 0;
        while(!done) {
            if(tmp[i] == '\n') done = 1;
            if(tmp[i] == space || tmp[i] == '\n'){
                j = 0;
                if(a == -1) {
                    a = atoi(lineTmp);
                } else if(b == -1) {
                    b = atoi(lineTmp);
                } else if(c == -1) {
                    c = atoi(lineTmp);
                }
                for(int k = 0; k < 85; ++k) {
                    lineTmp[k] = space;
                }
            } else {
                lineTmp[j] = tmp[i];
            }
            ++i;
            ++j;
        }
        printf("\n");
        printf("a: %d, b: %d, c: %d\n", a, b, c);
    }
    return 0;
}
