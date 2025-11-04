#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 10
#define MAX_NAME_LEN 50
#pragma warning(disable : 4996)

typedef struct {
    char name[MAX_NAME_LEN];
    int atk;
    int def;
    int hp;
} Student;

int max(int a, int b) {
    return a > b ? a : b;
}

int main(void) {
    char studentID[20];
    char userName[MAX_NAME_LEN];
    Student students[MAX_STUDENTS];

    // (1) 사용자 입력 받기
    printf("학번을 입력하세요: ");
    scanf_s("%19s", studentID, (unsigned)_countof(studentID)); // 크기 지정
    printf("이름을 입력하세요: ");
    scanf_s("%49s", userName, (unsigned)_countof(userName)); // 크기 지정

    // (2) students.csv 파일 열기
    FILE* fp = fopen("students.csv", "r");
    if (!fp) {
        printf("students.csv 파일을 열 수 없습니다.\n");
        return 1;
    }

    // (3) CSV 파일에서 학생 정보 읽기
    char line[100];
    int count = 0;
    while (fgets(line, sizeof(line), fp) != NULL && count < MAX_STUDENTS) {
        sscanf_s(line, "%[^,],%d,%d,%d",
            students[count].name, (unsigned)_countof(students[count].name),
            &students[count].atk, &students[count].def, &students[count].hp);
        count++;
    }
    fclose(fp);

    if (count < 8) {
        printf("학생 데이터가 8명 이상이어야 합니다.\n");
        return 1;
    }

    // (4) 가장 공격력 높은 사람 찾기
    int maxAtkIndex = 0;
    for (int i = 1; i < count; i++) {
        if (students[i].atk > students[maxAtkIndex].atk) {
            maxAtkIndex = i;
        }
    }

    // (5) 3번째와 8번째 학생 정보
    Student third = students[2];
    Student eighth = students[7];

    // (6) 전투 시뮬레이션
    int damageToThird = max(0, eighth.atk - third.def);
    int damageToEighth = max(0, third.atk - eighth.def);

    char winner[MAX_NAME_LEN];
    if (damageToThird == 0 && damageToEighth == 0) {
        strcpy_s(winner, sizeof(winner), "무승부");
    }
    else {
        int thirdHP = third.hp - damageToThird;
        int eighthHP = eighth.hp - damageToEighth;

        if (thirdHP <= 0 && eighthHP <= 0) {
            strcpy_s(winner, sizeof(winner), "무승부");
        }
        else if (thirdHP <= 0) {
            strcpy_s(winner, sizeof(winner), eighth.name);
        }
        else if (eighthHP <= 0) {
            strcpy_s(winner, sizeof(winner), third.name);
        }
        else {
            // 둘 다 살아남았을 경우, 더 피해를 많이 준 사람이 승자
            strcpy_s(winner, sizeof(winner),
                damageToThird > damageToEighth ? eighth.name : third.name);
        }
    }

    // (7) 결과를 Test.txt에 출력
    FILE* out = fopen("Test.txt", "w");
    if (!out) {
        printf("Test.txt 파일을 생성할 수 없습니다.\n");
        return 1;
    }

    fprintf(out, "%s : %s\n", studentID, userName);
    fprintf(out, "가장 공격력이 높은 사람: %s (ATK=%d)\n",
        students[maxAtkIndex].name, students[maxAtkIndex].atk);
    fprintf(out, "3번째: %s HP=%d\n", third.name, third.hp);
    fprintf(out, "8번째: %s HP=%d\n", eighth.name, eighth.hp);

    if (strcmp(winner, "무승부") == 0) {
        fprintf(out, "3번째 vs 8번째: 무승부\n");
    }
    else {
        fprintf(out, "3번째 vs 8번째 승자: %s\n", winner);
    }

    fprintf(out, "교수님 시험문제 너무 쉽습니다. 담주에 더 어렵게 내주세요\n");

    fclose(out);
    printf("결과가 Test.txt에 저장되었습니다.\n");

    return 0;
}
