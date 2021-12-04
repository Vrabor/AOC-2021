#include <stdio.h>

int main(){
    FILE* f = fopen("./input.txt", "r");

    if (f == NULL){
        printf("Can't open File");
        return 1;
    }

    int previous;
    int num_read = fscanf(f, "%d\n", &previous);
    int increases = 0;
    while(num_read == 1){
        int current;
        num_read = fscanf(f, "%d\n", &current);
        if (current > previous){
            increases++;
        }
        previous = current;
    }

    fclose(f);

    printf("Number of increases: %d\n", increases);
    return 0;
}
