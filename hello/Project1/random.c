#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

int main()
{
    srand((unsigned int)time(NULL));

    int numbers[6];

    printf("������ �ζ� ��ȣ!:\n");

    for (int i = 0; i < 6; i++)
    {
        int randomNumber;
        int isDuplicate;

        do
        {
            isDuplicate = 0;
            randomNumber = (rand() % 45) + 1;
            for (int j = 0; j < i; j++)
            {
                if (numbers[j] == randomNumber)
                {
                    isDuplicate = 1;
                    break;
                }
            }

        } while (isDuplicate);

        numbers[i] = randomNumber;
        printf("%d ", numbers[i]);
    }

    printf("\n\n����� ���ϴ�...");
    _getch();

    return 0;
}
