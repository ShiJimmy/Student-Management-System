#include <iostream>
#include <cstdio>

int userinq(char* usern);
int addusr(char* usern);
int updusr(char* usern);
int delusr(char* usern);

int main() {
    printf("Client\n");

    while (true)
    {
        int inputins;
        printf("\n|********* Welcome to use info system ***********|");
        printf("\n|------------1:  Inquiry my timetable -----------|");
        printf("\n|------------2:  Add one user -------------------|");
        printf("\n|------------3:  Update one user ----------------|");
        printf("\n|------------4:  Delete one user ----------------|");
        printf("\n|------------5:  Edit one course ----------------|");
        printf("\n|------------0:  Exit ---------------------------|");
        printf("\n|************************************************|\n");
        puts("Please input an instruction:");
        scanf("%d", &inputins);
        if (inputins == 0)
        {
            puts("Good bye!\n");
            break;
        }
        else if (inputins == 1)
        {
            char usern[50];
            puts("Please inpot your user name:");
            scanf("%s", &usern);
            userinq(usern);
        }
        else if (inputins == 2)
        {
            char usern[50];
            puts("Please input user name:");
            scanf("%s", &usern);
            addusr(usern);
        }
        else if (inputins == 3)
        {
            char usern[50];
            puts("Please input user name:");
            scanf("%s", &usern);
            updusr(usern);
        }
        else if (inputins == 4)
        {
            char usern[50];
            puts("Please input user name:");
            scanf("%s", &usern);
            delusr(usern);
        }
        else if (inputins == 5)
        {
            puts("5\n");
        }
        else
        {
            puts("Input invalid! Please try again.\n");
        }
    }

    return 0;
}

int userinq(char* usern)
{
    printf("%s's Timetable\n", usern);
    return 0;
}

int addusr(char* usern)
{
    printf("User %s is added!\n", usern);
    return 0;
}

int updusr(char* usern)
{
    printf("User %s is updated!\n", usern);
    return 0;
}
int delusr(char* usern)
{
    printf("User %s is deleted!\n", usern);
    return 0;
}
