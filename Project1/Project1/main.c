#include <stdio.h>
#include <conio.h>
#include <Windows.h>

// ANSI 색상 코드
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

// ANSI 커서 이동
void gotoXY(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

int main() {
    char target[5] = { 'A', 'S', 'D', 'F', 'G' };
    int correct = 0;
    int wrong = 0;

    for (int i = 0; i < 5; i++) {
        system("cls");

        // 1. 문제 알파벳 출력
        gotoXY(0, 1);
        printf("문자 등장: %c", target[i]);

        // 2. 입력 대기: 1초 동안 _kbhit()로 감지, 입력되면 getch() 사용
        char input = 0;
        int time = 0;
        while (time < 10) { // 1초 = 100ms * 10
            if (_kbhit()) {
                input = _getch(); // 입력된 키
                break;
            }
            Sleep(100);
            time++;
        }

        // 3. 입력한 문자 출력
        gotoXY(0, 2);
        if (input != 0) {
            printf("%c", input);
        }
        else {
            printf("입력 없음");
        }

        // 4. 결과 판정 출력
        gotoXY(0, 3);
        if (input == target[i]) {
            printf(GREEN "완벽!!!" RESET);
            correct++;
        }
        else {
            printf(RED "에러!!!" RESET);
            wrong++;
        }

        // 5. 잠깐 멈춤
        Sleep(800);
    }

    // 6. 결과 화면
    system("cls");
    gotoXY(0, 5);
    printf(YELLOW "=== 결과 ===" RESET);
    gotoXY(0, 6);
    printf(YELLOW "정답 수: %d" RESET, correct);
    gotoXY(0, 7);
    printf(YELLOW "오답 수: %d" RESET, wrong);

    return 0;
}
