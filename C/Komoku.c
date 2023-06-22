#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 15

// 오목판을 표현하는 2차원 배열
char board[SIZE][SIZE];

// 오목판 초기화
void initBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '.';
        }
    }
}

// 오목판 출력
void printBoard() {
    printf("  ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// 돌을 놓는 함수
void placeStone(int row, int col, char stone) {
    board[row][col] = stone;
}

// 게임 실행
void playGame() {
    int row, col;
    char stone = 'X';  // 플레이어의 돌
    int turn = 1;

    while (1) {
        printf("턴 %d, 플레이어 %c 차례입니다.\n", turn, stone);
        printf("돌을 놓을 좌표를 입력하세요 (행 열): ");
        scanf("%d %d", &row, &col);

        // 유효한 좌표인지 확인
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            printf("잘못된 좌표입니다. 다시 입력하세요.\n");
            continue;
        }

        // 이미 돌이 있는 위치인지 확인
        if (board[row][col] != '.') {
            printf("이미 돌이 있는 위치입니다. 다시 입력하세요.\n");
            continue;
        }

        // 돌을 놓고 오목판 출력
        placeStone(row, col, stone);
        printBoard();

        // 오목 여부 체크

        // 가로 체크
        int count = 0;
        for (int i = 0; i < SIZE; i++) {
            if (board[row][i] == stone) {
                count++;
                if (count == 5) {
                    printf("플레이어 %c가 이겼습니다!\n", stone);
                    return;
                }
            }
            else {
                count = 0;
            }
        }

        // 세로 체크
        count = 0;
        for (int i = 0; i < SIZE; i++) {
            if (board[i][col] == stone) {
                count++;
                if (count == 5) {
                    printf("플레이어 %c가 이겼습니다!\n", stone);
                    return;
                }
            }
            else {
                count = 0;
            }
        }

        // 대각선 체크 (왼쪽 위에서 오른쪽 아래로)
        count = 0;
        int i = row, j = col;
        while (i >= 0 && j >= 0) {
            if (board[i][j] == stone) {
                count++;
                if (count == 5) {
                    printf("플레이어 %c가 이겼습니다!\n", stone);
                    return;
                }
            }
            else {
                count = 0;
            }
            i--;
            j--;
        }
        i = row + 1;
        j = col + 1;
        while (i < SIZE && j < SIZE) {
            if (board[i][j] == stone) {
                count++;
                if (count == 5) {
                    printf("플레이어 %c가 이겼습니다!\n", stone);
                    return;
                }
            }
            else {
                count = 0;
            }
            i++;
            j++;
        }

        // 대각선 체크 (오른쪽 위에서 왼쪽 아래로)
        count = 0;
        i = row, j = col;
        while (i >= 0 && j < SIZE) {
            if (board[i][j] == stone) {
                count++;
                if (count == 5) {
                    printf("플레이어 %c가 이겼습니다!\n", stone);
                    return;
                }
            }
            else {
                count = 0;
            }
            i--;
            j++;
        }
        i = row + 1;
        j = col - 1;
        while (i < SIZE && j >= 0) {
            if (board[i][j] == stone) {
                count++;
                if (count == 5) {
                    printf("플레이어 %c가 이겼습니다!\n", stone);
                    return;
                }
            }
            else {
                count = 0;
            }
            i++;
            j--;
        }

        // 무승부 체크
        int isDraw = 1;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == '.') {
                    isDraw = 0;
                    break;
                }
            }
            if (!isDraw) {
                break;
            }
        }
        if (isDraw) {
            printf("무승부입니다.\n");
            return;
        }

        // 턴 변경
        if (stone == 'X') {
            stone = 'O';
        }
        else {
            stone = 'X';
        }
        turn++;
    }
}

int main() {
    initBoard();
    printBoard();
    playGame();

    return 0;
}
