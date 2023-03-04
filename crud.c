#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// gcc -o crud crud.c
//./crud 1 input.txt

int checkthang(int thang)
{
    switch (thang)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return 28;
    }
}

int checkArgc(int argc, char *argv[])
{
    if (argc == 2 && (strcmp(argv[1], "--version") == 0))
        return 1;
    if (argc == 1 )
        return 2;
    if (argc == 2 && (strcmp(argv[1], "--help") == 0))
        return 2;
    if (argc == 3 && (strcmp(argv[1], "1") == 0)) //
        return 3;
    return 0;
}
int main(int argc, char *argv[])
{

    char *names1[] = {"Nguyen", "Tran", "Le", "Hoang", "Pham", "Vu", "Dang", "Ngo", "Do", "Phan", "Bui", "Duong", "Ly"};

    char *names2[] = {"Hoang", "Phuong", "Thanh", "Khanh", "Ngoc", "Hong"};

    char *names3[] = {"Anh", "Trang", "Linh", "Phuong", "Nhi", "Huong", "Nga", "Mai", "Gam", "Thu", "Hoa", "Mai", "Hien"};

    int soluongSV;

    int namecount1 = sizeof(names1) / sizeof(names1[1]);
    int namecount2 = sizeof(names2) / sizeof(names2[0]);
    int namecount3 = sizeof(names3) / sizeof(names3[0]);

    switch (checkArgc(argc, argv))
    {
    case 1:
    {
        printf("phan mem tao file test version 1.0 .\n");
        break;
    }
    case 2:
    {
        printf("./crud 1 [filename]\n");
        break;
    }
    case 3:
    {

        char fileout1[50];
        strcpy(fileout1, argv[2]);

        FILE *fo1 = fopen(fileout1, "w"); // mo file de ghi

        printf("so luong sinh vien:");
        scanf("%d", &soluongSV);
        fprintf(fo1, "%d\n", soluongSV);

        srand((int)time(0));

        for (int i = 1; i <= soluongSV; i++)
        {
            int j1 = 100 + rand() % (900 + 1 - 100);
            int j2 = 100 + rand() % (900 + 1 - 100);
            int L = 10 + rand() % (500 + 1 - 10);
            int W = 3 + rand() % (20 + 1 - 3);
            int d = 1 + rand() % (2);
            fprintf(fo1, "J%d J%d %s%s%s %d %d %d\n", j1, j2, names1[rand() % (namecount1)], names2[rand() % (namecount2)], names3[rand() % (namecount3)], L, W, d);
        }

        fclose(fo1); // dong file fo
    }
    }
}
