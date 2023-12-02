#include <stdio.h>

#define buflen 3

int init_array(FILE* f, int* arr){
    int num_read;
    for (int i = 0; i < buflen; i++){
        num_read = fscanf(f, "%d\n", &arr[i]);
        if (num_read != 1){
            return 1;
        }
    }
    return 0;
}

int buf_sum(int* arr){
    int sum = 0;
    for (int i = 0; i < buflen; i++){
        sum += arr[i];
    }
    return sum;
}

int main(){
    FILE* f = fopen("./input.txt", "r");

    if (f == NULL){
        printf("Can't open File");
        return 1;
    }

    int previous;
    int window[buflen] = {0};
    int num_read = 1;
    int total_read = 0;
    int increases = 0;

    int err = init_array(f, window);
    if (err != 0){
        printf("Not enough values!\n");
    }
    total_read = buflen;
    previous = buf_sum(window);

    while(num_read == 1){
        num_read = fscanf(f, "%d\n", &window[total_read % buflen]);
        total_read++;
        int current = buf_sum(window);
        if (current > previous){
            increases++;
        }
        previous = current;
    }

    fclose(f);

    printf("Number of increases: %d\n", increases);
    return 0;
}
