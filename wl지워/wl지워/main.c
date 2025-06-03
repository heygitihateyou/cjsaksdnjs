#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

// ANSI 색상
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

// 커서 이동
void gotoXY(int x, int y) {
    printf("\033[%d;%dH", y, x);
    fflush(stdout);
}

// 커서 숨기기
void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// 알파벳 후보
char choices[] = { 'Q', 'W', 'E', 'R', 'T' };

int main() {
    int correct = 0, wrong = 0;
    int totalQuestions = 10;
    const int totalLimit = 15; // 제한 시간 15초

    srand((unsigned int)time(NULL));
    hideCursor();

    time_t startTime = time(NULL);

    // 초기 화면 구성
    system("cls");
    gotoXY(0, 1); printf("⏳ 남은 시간: ");
    gotoXY(0, 2); printf("🔤 제시 문자: ");
    gotoXY(0, 3); printf("⌨️  입력 문자: ");
    gotoXY(0, 4); printf("💬 결과: ");
    gotoXY(0, 6); printf("진행 중입니다...");

    for (int i = 0; i < totalQuestions; i++) {
        if (difftime(time(NULL), startTime) > totalLimit) {
            gotoXY(0, 6);
            printf(RED "💥 제한 시간 초과! 폭탄이 터졌습니다!\n" RESET);
            gotoXY(0, 7);
            printf(YELLOW "=== 결과 ===\n" RESET);
            gotoXY(0, 8);
            printf(YELLOW "정답 수: %d\n" RESET, correct);
            gotoXY(0, 9);
            printf(YELLOW "오답 수: %d\n" RESET, wrong);
            return 0;
        }

        char currentChar = choices[rand() % 5];

        // 표시 영역 초기화 및 출력
        gotoXY(10, 1);
        printf("%2.0f초       ", totalLimit - difftime(time(NULL), startTime));
        gotoXY(10, 2);
        printf("%c    ", currentChar);
        gotoXY(10, 3);
        printf("      ");
        gotoXY(10, 4);
        printf("             ");

        int responded = 0;
        int waited = 0;

        while (waited < 15) { // 1.5초 대기
            // 실시간 시간 표시
            gotoXY(10, 1);
            printf("%2.0f초       ", totalLimit - difftime(time(NULL), startTime));

            if (difftime(time(NULL), startTime) > totalLimit) {
                gotoXY(0, 6);
                printf(RED "💥 제한 시간 초과! 폭탄이 터졌습니다!\n" RESET);
                gotoXY(0, 7);
                printf(YELLOW "=== 결과 ===\n" RESET);
                gotoXY(0, 8);
                printf(YELLOW "정답 수: %d\n" RESET, correct);
                gotoXY(0, 9);
                printf(YELLOW "오답 수: %d\n" RESET, wrong);
                return 0;
            }

            if (_kbhit()) {
                char ch = _getch();
                gotoXY(10, 3);
                printf("%c    ", ch);

                gotoXY(10, 4);
                if (ch == currentChar || ch == currentChar + 32) {
                    printf(GREEN "Safe!" RESET);
                    correct++;
                }
                else {
                    printf(RED "Boom!" RESET);
                    wrong++;
                }
                responded = 1;
                break;
            }

            Sleep(100);
            waited++;
        }

        if (!responded) {
            gotoXY(10, 4);
            printf(RED "시간 초과! Boom!" RESET);
            wrong++;
        }

        Sleep(500); // 다음 문제 넘어가기 전 잠깐 대기
    }

    // 종료 메시지
    gotoXY(0, 6);
    printf(GREEN "🎉 제한 시간 내에 모든 입력 완료!\n" RESET);
    gotoXY(0, 7);
    printf(YELLOW "=== 결과 ===\n" RESET);
    gotoXY(0, 8);
    printf(YELLOW "정답 수: %d\n" RESET, correct);
    gotoXY(0, 9);
    printf(YELLOW "오답 수: %d\n" RESET, wrong);

    return 0;
}
