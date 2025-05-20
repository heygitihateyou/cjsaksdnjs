#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <ctime>

// 함수 선언
void showIntro();
void showStartMenu();
void countdownToStart();
void playGame(int score, int speed);
void showResult(int score);

// 메인 함수
int main() {
    int score = 0;
    int speed = 1000; // 컵 섞는 속도 (ms)

    showIntro();
    showStartMenu();
    countdownToStart();
    playGame(score, speed);
    showResult(score);

    return 0;
}

// 인트로 화면
void showIntro() {
    system("cls");
    printf("==========================\n");
    printf("   야바위 게임에 오신 걸 환영합니다!\n");
    printf("   구슬이 들어간 컵을 맞혀 보세요!\n");
    printf("==========================\n");
    Sleep(2000);
}

// 시작 메뉴
void showStartMenu() {
    system("cls");
    printf("▶ 게임을 시작하려면 Enter를 누르세요.\n");
    printf("▶ 종료하려면 ESC를 누르세요.\n");

    while (1) {
        char key = _getch();
        if (key == 13) break;     // Enter
        if (key == 27) exit(0);   // ESC
    }
}

// 카운트다운
void countdownToStart() {
    system("cls");
    for (int i = 3; i >= 1; i--) {
        printf("게임 시작까지... %d초!\n", i);
        Sleep(1000);
        system("cls");
    }
    printf("시작!\n");
    Sleep(1000);
}

// 메인 게임 로직
void playGame(int score, int speed)
{
    while (1)
    {
        system("cls");
        srand((unsigned int)time(0));

        // 컵 배열 초기화
        int cups[3] = { 0, 0, 0 };
        int ballIndex = rand() % 3;
        cups[ballIndex] = 1;

        // 구슬 위치 보여주기
        printf("컵의 위치:\n");
        printf("[1]   [2]   [3]\n");
        printf("구슬은 %d번 컵 아래에 있습니다!\n", ballIndex + 1);
        Sleep(1500);
        system("cls");

        // 컵 섞기
        for (int i = 0; i < 5; i++)
        {
            int a = rand() % 3;
            int b = rand() % 3;
            while (b == a) b = rand() % 3;

            // swap
            int temp = cups[a];
            cups[a] = cups[b];
            cups[b] = temp;

            printf("컵을 섞는 중...\n");
            Sleep(speed);
            speed = max(200, speed - 100);
            system("cls");
        }

        // 사용자 입력
        int choice;
        printf("구슬이 어느 컵에 있을까요? (1~3): ");
        scanf_s("%d", &choice);

        if (choice < 1 || choice > 3) {
            printf("잘못된 입력입니다. 1~3 사이의 숫자를 입력하세요.\n");
            Sleep(1500);
            continue;
        }

        if (cups[choice - 1] == 1) {
            printf("정답입니다!\n");
            score++;
        }
        else {
            int correct = (int)(std::find(cups, cups + 3, 1) - cups) + 1;
            printf("틀렸습니다. 정답은 %d번 컵이었습니다.\n", correct);
        }

        printf("현재 점수: %d\n", score);

        // 최대 점수 5점 도달 시 종료
        if (score >= 5) {
            printf("\n축하합니다! 최고 점수에 도달하셨습니다!\n");
            Sleep(3000);
            return;
        }

        printf("계속하려면 Enter, 종료하려면 ESC를 누르세요...\n");

        while (1) {
            char key = _getch();
            if (key == 13) break;   // Enter
            if (key == 27) return;  // ESC
        }
    }
}
// 결과 출력
void showResult(int score)
{
    system("cls");
    printf("게임 종료!\n");
    printf("당신의 점수는: 100점 입니다!\n", score);
    Sleep(3000);
}
