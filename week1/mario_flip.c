#include <cs50.h>
#include <stdio.h>

int main(void){
    int n;

    do{
        n = get_int("Height: ");
    }
    while (n < 1 || n > 36);

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if (j < i) {
                printf(" ");
            } else {
                printf("#");
            }
        }
        printf("  ");

        for (int k = 0; k < n + 1; k++) {
            if (k >= i){
                printf("#");
            }
        }

        printf("\n");
    }

}
