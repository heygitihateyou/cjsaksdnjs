#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <ctime>

// 함수 선언
void showIntro();
void countdownToStart();
void playGame(int* score, int speed);
void showResult(int score);

// 메인 함수
int main() {
    int score = 0;
    int speed = 1000; // 컵 섞는 속도 (ms)

    showIntro();
    countdownToStart();
    playGame(&score, speed);
    showResult(score);

    return 0;
}

// 인트로 화면
void showIntro() {
    while (1) {
        system("cls");
        printf("\033[45m=======================================\033[0m\n");
        printf("   \033[95m야바위 게임\033[0m에 오신 걸 환영합니다!\n");
        printf("   숫자를 맞춰 \033[33m점수\033[0m를 획득하세요!\n");
        printf("\033[45m=======================================\033[0m\n");
        printf("\n   ▶ \033[92mEnter\033[0m 키를 누르면 계속 진행합니다...\n");
        printf("   ▶ \033[31mESC\033[0m 키를 누르면 종료합니다...\n");

        // 0.1초씩 20번 반복 (총 2초)
        for (int i = 0; i < 20; i++) {
            Sleep(100);
            if (_kbhit()) {
                char key = _getch();
                if (key == 13) return;      // Enter
                if (key == 27) {
                    system("cls");
                    printf("안녕히 가세요.\n");
                    Sleep(1500);
                    exit(0);
                }
            }
        }
    }
}


// 카운트다운
void countdownToStart() {
    system("cls");
    for (int i = 3; i >= 1; i--) {
        printf("\033[91m10점\033[0m을 얻으시면 됩니다... %d!\n", i);
        Sleep(1000);
        system("cls");
    }
    printf("\033[92m시작!\033[0m\n");
    Sleep(1000);
}

// 메인 게임 로직
void playGame(int* score, int speed)
{
    while (1)
    {
        system("cls");
        srand((unsigned int)time(0));

        int cups[3] = { 0, 0, 0 };
        int ballIndex = rand() % 3;
        cups[ballIndex] = 1;

        printf("컵의 위치:\n");
        printf("\033[42m[1]\033[0m   \033[43m[2]\033[0m   \033[41m[3]\033[0m\n");
        printf("구슬은 %d번 컵 아래에 있습니다.\n", ballIndex + 1);
        Sleep(1500);
        system("cls");

        for (int i = 0; i < 5; i++)
        {
            int a = rand() % 3;
            int b = rand() % 3;
            while (b == a) b = rand() % 3;

            int temp = cups[a];
            cups[a] = cups[b];
            cups[b] = temp;

            printf("\033[31m컵\033[0m을 \033[31m섞\033[0m는 \033[31m중\033[0m...\n");
            Sleep(speed);
            speed = max(200, speed - 100);
            system("cls");
        }

        int choice;
        printf("\033[45m잘 골라보시죠...\033[0m [1~3]: ");
        scanf_s("%d", &choice);

        if (choice < 1 || choice > 3) {
            printf("잘못된 입력입니다. 1~3 사이의 숫자를 입력하세요.\n");
            Sleep(1500);
            continue;
        }

        if (cups[choice - 1] == 1) {
            printf("\033[32m정답입니다!\033[0m\n");
            (*score)++;  // 포인터 사용해 점수 올리기
        }
        else {
            int correct = (int)(std::find(cups, cups + 3, 1) - cups) + 1;
            printf("\033[31m아쉽군요.\033[0m 정답은 %d번 컵이었습니다.\n", correct);
        }

        printf("현재 점수: \033[42m\033[30m%d\033[0m\033[0m\n", *score);

        if (*score >= 10) {
            printf("\n\033[96m축하합니다!\033[0m 최고 점수에 도달하셨습니다!\n");
            Sleep(3000);
            return;
        }

        printf("계속하려면 \033[32mEnter\033[0m, 종료하려면 \033[31mESC\033[0m를 누르세요\n");

        while (1) {
            char key = _getch();
            if (key == 13) break;
            if (key == 27) return;
        }
    }
}

// 결과 출력
void showResult(int score)
{
    system("cls");

    if (score >= 10) {
        printf("게임 종료!\n");
        printf("당신의 점수는: \033[92m100\033[0m점 입니다!\n");
        printf("                                                               \n");
        printf("                                                               \n");
        printf("                                                               \n");
        printf("                                   \033[44mㅈㅈㅈㅈㅈㅈㅈ\033[0m   \033[43mㅓ\033[0m                      \n");
        printf("   \033[92m _____    ______    ______\033[0m            \033[44mㅈ\033[0m         \033[43mㅓ\033[0m        \n");
        printf("  \033[92m /    |   /      \\  /      \\\033[0m          \033[44mㅈ\033[0m \033[44mㅈ\033[0m       \033[43mㅓ\033[0m     \n");
        printf(" \033[92m |ㅡ   |   |  __  |  |  __  |\033[0m         \033[44mㅈ\033[0m   \033[44mㅈ\033[0m  \033[43mㅓㅓㅓ\033[0m   \n");
        printf("   \033[92m |   |   | |  | |  | |  | |\033[0m        \033[44mㅈ\033[0m     \033[44mㅈ\033[0m     \033[43mㅓ\033[0m   \n");
        printf("    \033[92m|   |   | |__| |  | |__| |\033[0m       \033[44mㅈ\033[0m       \033[44mㅈ\033[0m    \033[43mㅓ\033[0m   \n");
        printf("    \033[92m|   |   |      |  |      |\033[0m        \033[42mㅁㅁㅁㅁㅁ\033[0m    \033[43mㅓ\033[0m    \n");
        printf("   \033[92m -----   \\------/  \\------/\033[0m        \033[42mㅁ\033[0m      \033[42mㅁ\033[0m    \033[43mㅓ\033[0m            \n");
        printf("                                      \033[42mㅁ\033[0m      \033[42mㅁ\033[0m   \n");
        printf("                                      \033[42mㅁ\033[0m      \033[42mㅁ\033[0m \n");
        printf("                                      \033[42mㅁㅁㅁㅁㅁ\033[0m          \n");
    }
    else {
        printf("게임 종료!\n");
        printf("당신의 점수는: \033[31m0\033[0m점 입니다!\n");
    }

    Sleep(3000);
}
