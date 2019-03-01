#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 11;
const char INIT_CHAR = '#';
const char MARK_CHAR = 'X';
const char QUEEN = 'Q';

int count = 0;

void init_chessboard(void *cb) {

    memset(cb, INIT_CHAR, SIZE * SIZE);
}

void *copy_chessboard(void *cb, int size) {

    char *new_cb = malloc(sizeof(char) * size * size);

    size *= size;
    for (int i = 0; i < size; ++i) {

        new_cb[i] = ((char *) cb)[i];
    }

    return new_cb;
}

void print_an_answer(void *cb, int size) {

    for (int i = 0; i < size * size; ++i) {

        printf("%2c%c", ((char *) cb)[i], (i + 1) % size != 0 ? ' ' : '\n');
    }
}

void mark_chessboard(void *cb, int size, int row_index, int col_index) {

    char *tcb = cb;

    tcb[size * row_index + col_index] = QUEEN;

    for (int i = 0; i < size; ++i) {

        if (row_index != i) {

            tcb[size * i + col_index] = MARK_CHAR;

            int col = col_index - (row_index - i);

            if (col >= 0 && col < size) {
                tcb[size * i + col] = MARK_CHAR;
            }

            col = col_index + row_index - i;

            if (col < size && col >= 0) {
                tcb[size * i + col] = MARK_CHAR;
            }
        }

        if (col_index != i) {

            tcb[size * row_index + i] = MARK_CHAR;
        }
    }
}

void try_a_location(void *cb, int row_index, int size) {

    char *tcb = cb;

    for (int i = 0; i < size; ++i) {

        void *new_cb = copy_chessboard(cb, size);

        if (tcb[size * row_index + i] == INIT_CHAR) {

            mark_chessboard(new_cb, size, row_index, i);

            if (row_index < size - 1) {

                try_a_location(new_cb, row_index + 1, size);
            } else {

                printf("%2d\n", ++count);
                print_an_answer(new_cb, size);
            }
        }

        free(new_cb);
    }
}

int main() {

    char chessboard[SIZE][SIZE];
    init_chessboard(chessboard);
//    print_an_answer(chessboard, SIZE);
    try_a_location(chessboard, 0, SIZE);
    return 0;
}