#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <ctime>

// �Լ� ����
void showIntro();
void countdownToStart();
void playGame(int* score, int speed);
void showResult(int score);

// ���� �Լ�
int main() {
    int score = 0;
    int speed = 1000; // �� ���� �ӵ� (ms)

    showIntro();
    countdownToStart();
    playGame(&score, speed);
    showResult(score);

    return 0;
}

// ��Ʈ�� ȭ��
void showIntro() {
    while (1) {
        system("cls");
        printf("\033[45m=======================================\033[0m\n");
        printf("   \033[95m�߹��� ����\033[0m�� ���� �� ȯ���մϴ�!\n");
        printf("   ���ڸ� ���� \033[33m����\033[0m�� ȹ���ϼ���!\n");
        printf("\033[45m=======================================\033[0m\n");
        printf("\n   �� \033[92mEnter\033[0m Ű�� ������ ��� �����մϴ�...\n");
        printf("   �� \033[31mESC\033[0m Ű�� ������ �����մϴ�...\n");

        // 0.1�ʾ� 20�� �ݺ� (�� 2��)
        for (int i = 0; i < 20; i++) {
            Sleep(100);
            if (_kbhit()) {
                char key = _getch();
                if (key == 13) return;      // Enter
                if (key == 27) {
                    system("cls");
                    printf("�ȳ��� ������.\n");
                    Sleep(1500);
                    exit(0);
                }
            }
        }
    }
}


// ī��Ʈ�ٿ�
void countdownToStart() {
    system("cls");
    for (int i = 3; i >= 1; i--) {
        printf("\033[91m10��\033[0m�� �����ø� �˴ϴ�... %d!\n", i);
        Sleep(1000);
        system("cls");
    }
    printf("\033[92m����!\033[0m\n");
    Sleep(1000);
}

// ���� ���� ����
void playGame(int* score, int speed)
{
    while (1)
    {
        system("cls");
        srand((unsigned int)time(0));

        int cups[3] = { 0, 0, 0 };
        int ballIndex = rand() % 3;
        cups[ballIndex] = 1;

        printf("���� ��ġ:\n");
        printf("\033[42m[1]\033[0m   \033[43m[2]\033[0m   \033[41m[3]\033[0m\n");
        printf("������ %d�� �� �Ʒ��� �ֽ��ϴ�.\n", ballIndex + 1);
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

            printf("\033[31m��\033[0m�� \033[31m��\033[0m�� \033[31m��\033[0m...\n");
            Sleep(speed);
            speed = max(200, speed - 100);
            system("cls");
        }

        int choice;
        printf("\033[45m�� ��󺸽���...\033[0m [1~3]: ");
        scanf_s("%d", &choice);

        if (choice < 1 || choice > 3) {
            printf("�߸��� �Է��Դϴ�. 1~3 ������ ���ڸ� �Է��ϼ���.\n");
            Sleep(1500);
            continue;
        }

        if (cups[choice - 1] == 1) {
            printf("\033[32m�����Դϴ�!\033[0m\n");
            (*score)++;  // ������ ����� ���� �ø���
        }
        else {
            int correct = (int)(std::find(cups, cups + 3, 1) - cups) + 1;
            printf("\033[31m�ƽ�����.\033[0m ������ %d�� ���̾����ϴ�.\n", correct);
        }

        printf("���� ����: \033[42m\033[30m%d\033[0m\033[0m\n", *score);

        if (*score >= 10) {
            printf("\n\033[96m�����մϴ�!\033[0m �ְ� ������ �����ϼ̽��ϴ�!\n");
            Sleep(3000);
            return;
        }

        printf("����Ϸ��� \033[32mEnter\033[0m, �����Ϸ��� \033[31mESC\033[0m�� ��������\n");

        while (1) {
            char key = _getch();
            if (key == 13) break;
            if (key == 27) return;
        }
    }
}

// ��� ���
void showResult(int score)
{
    system("cls");

    if (score >= 10) {
        printf("���� ����!\n");
        printf("����� ������: \033[92m100\033[0m�� �Դϴ�!\n");
        printf("                                                               \n");
        printf("                                                               \n");
        printf("                                                               \n");
        printf("                                   \033[44m��������������\033[0m   \033[43m��\033[0m                      \n");
        printf("   \033[92m _____    ______    ______\033[0m            \033[44m��\033[0m         \033[43m��\033[0m        \n");
        printf("  \033[92m /    |   /      \\  /      \\\033[0m          \033[44m��\033[0m \033[44m��\033[0m       \033[43m��\033[0m     \n");
        printf(" \033[92m |��   |   |  __  |  |  __  |\033[0m         \033[44m��\033[0m   \033[44m��\033[0m  \033[43m�ää�\033[0m   \n");
        printf("   \033[92m |   |   | |  | |  | |  | |\033[0m        \033[44m��\033[0m     \033[44m��\033[0m     \033[43m��\033[0m   \n");
        printf("    \033[92m|   |   | |__| |  | |__| |\033[0m       \033[44m��\033[0m       \033[44m��\033[0m    \033[43m��\033[0m   \n");
        printf("    \033[92m|   |   |      |  |      |\033[0m        \033[42m����������\033[0m    \033[43m��\033[0m    \n");
        printf("   \033[92m -----   \\------/  \\------/\033[0m        \033[42m��\033[0m      \033[42m��\033[0m    \033[43m��\033[0m            \n");
        printf("                                      \033[42m��\033[0m      \033[42m��\033[0m   \n");
        printf("                                      \033[42m��\033[0m      \033[42m��\033[0m \n");
        printf("                                      \033[42m����������\033[0m          \n");
    }
    else {
        printf("���� ����!\n");
        printf("����� ������: \033[31m0\033[0m�� �Դϴ�!\n");
    }

    Sleep(3000);
}
