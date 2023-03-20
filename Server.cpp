#include "time.h"
#include "stdlib.h"
#include "stdio.h"
#include <string.h>
#include<iostream>
#include<string>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
const int PORT = 5019;

#define MAX_STUDENT_NUM 500
#define MAX_LINE 512
#define MAX_CHAR_NUM 256
#define CHAR_LEN 64
#define MAX_COURSE_NUM 100

#define STU_INFO_NUM 2
#define COURSE_INFO_NUM 6

typedef struct Stu
{
    char name[CHAR_LEN];
    int course_code;
}Student;

typedef struct StuTitle
{
    char name_title[CHAR_LEN];
    char course_code_title[CHAR_LEN];
}StudentTitle;

typedef struct Cour
{
    int course_code;
    char course_title[CHAR_LEN];
    int section;
    char time[CHAR_LEN];
    char classroom[CHAR_LEN];
    char instructor[CHAR_LEN];
}Course;

typedef struct CourTitle
{
    char course_code[CHAR_LEN];
    char course_title[CHAR_LEN];
    char section[CHAR_LEN];
    char time[CHAR_LEN];
    char classroom[CHAR_LEN];
    char instructor[CHAR_LEN];
}CourseTitle;

//database
int InitStudentInfo(Student student_arr[],StudentTitle* student_title)
{
    int line = 0;
    char c = 0;
    int line_index = 0;
    int i = 0;
    size_t j = 0;
    size_t sz_len = 0;
    char sz_split[MAX_STUDENT_NUM][STU_INFO_NUM][CHAR_LEN] = { 0 };
    int split_index = 0;
    int split_line = 0;
    int start = 0;
    int split_num = 0;
    FILE *file = NULL;
    char sz_line[MAX_LINE][MAX_CHAR_NUM] = { 0 };
    memset(sz_line, 0, sizeof(sz_line));

    file = fopen("student.txt", "r");
    if (file == NULL)
    {
        printf("open error!\n");
        return 0;
    }

    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
        {
            ++line;
            line_index = 0;
        }
        else
        {
            if (c == '\t')
            {
                c = ' ';
            }
            sz_line[line][line_index++] = c;
        }
    }
    ++line;
    fclose(file);

    for (; i < line; ++i)
    {
        sz_len = strlen(sz_line[i]);
        if(sz_len == 0)
        {
            continue;
        }
        for (j = 0; j < sz_len; ++j)
        {
            c = sz_line[i][j];
            if (split_index == 0)
            {

            }
            if (c != ' ')
            {
                start = 1;
                sz_split[split_num][split_line][split_index++] = c;
            }
            else
            {
                if (start)
                {
                    start = 0;
                    ++split_line;
                    split_index = 0;
                }
            }
        }

        split_line = 0;
        split_index = 0;
        ++split_num;
    }


    strcpy(student_title->name_title,sz_split[0][0]);
    strcpy(student_title->course_code_title,sz_split[0][1]);

    for (i = 1; i < split_num; ++i)
    {
        strcpy(student_arr[i-1].name,sz_split[i][0]);
        student_arr[i-1].course_code = atoi(sz_split[i][1]);
    }

    return split_num-1;
}

void SaveStudentInfo(Student info[], int count,StudentTitle* student_title)
{
    FILE *fp = NULL;
    int i = 0;
    char sz_line[MAX_CHAR_NUM] = { 0 };
    size_t index = 0;
    char sz_num[12] = { 0 };
    size_t len = 0;
    int j = 0;

    fp = fopen("student.txt", "w");
    if (fp == NULL)
    {
        printf("open error!\n");
    }

    len = strlen(student_title->name_title);
    memcpy(sz_line + index, student_title->name_title, len);
    index += len;
    sz_line[index++] = ' ';

    len = strlen(student_title->course_code_title);
    memcpy(sz_line + index,student_title->course_code_title, len);
    fprintf(fp, "%s\n", sz_line);

    for (; i < count; ++i)
    {
        memset(sz_line, 0, sizeof(sz_line));
        index = 0;

        len = strlen(info[i].name);
        memcpy(sz_line + index, info[i].name, len);
        index += len;
        sz_line[index++] = ' ';

        _itoa(info[i].course_code, sz_num, 10);

        len = strlen(sz_num);
        memcpy(sz_line + index, sz_num, len);
        index += len;
        fprintf(fp, "%s\n", sz_line);
    }

    fclose(fp);
}

int InitCourseInfo(Course course_arr[],CourseTitle* course_title)
{
    int line = 0;
    char c = 0;
    int line_index = 0;
    int i = 0;
    size_t j = 0;
    size_t sz_len = 0;
    char sz_split[MAX_COURSE_NUM][COURSE_INFO_NUM][CHAR_LEN] = { 0 };
    int split_index = 0;
    int split_line = 0;
    int start = 0;
    int split_num = 0;
    FILE *file = NULL;
    char sz_line[MAX_LINE][MAX_CHAR_NUM] = { 0 };
    memset(sz_line, 0, sizeof(sz_line));

    file = fopen("timetable.txt", "r");
    if (file == NULL)
    {
        printf("open error!\n");
        return 0;
    }

    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
        {
            ++line;
            line_index = 0;
        }
        else
        {
            if (c == '\t')
            {
                c = ' ';
            }
            sz_line[line][line_index++] = c;
        }
    }
    ++line;
    fclose(file);

    for (; i < line; ++i)
    {
        sz_len = strlen(sz_line[i]);
        if(sz_len == 0)
        {
            continue;
        }
        for (j = 0; j < sz_len; ++j)
        {
            c = sz_line[i][j];
            if (split_index == 0)
            {

            }
            if (c != ' ')
            {
                start = 1;
                sz_split[split_num][split_line][split_index++] = c;
            }
            else
            {
                if (start)
                {
                    start = 0;
                    ++split_line;
                    split_index = 0;
                }
            }
        }

        split_line = 0;
        split_index = 0;
        ++split_num;
    }

    strcpy(course_title->course_code,sz_split[0][0]);
    strcpy(course_title->course_title,sz_split[0][1]);
    strcpy(course_title->section,sz_split[0][2]);
    strcpy(course_title->time,sz_split[0][3]);
    strcpy(course_title->classroom,sz_split[0][4]);
    strcpy(course_title->instructor,sz_split[0][5]);

    for (i = 1; i < split_num; ++i)
    {
        int index = i - 1;
        course_arr[index].course_code = atoi(sz_split[i][0]);
        strcpy(course_arr[index].course_title,sz_split[i][1]);
        course_arr[index].section = atoi(sz_split[i][2]);
        strcpy(course_arr[index].time,sz_split[i][3]);
        strcpy(course_arr[index].classroom,sz_split[i][4]);
        strcpy(course_arr[index].instructor,sz_split[i][5]);
    }

    return split_num-1;
}

void SaveCourseInfo(Course info[], int count,CourseTitle* course_title)
{
    FILE *fp = NULL;
    int i = 0;
    char sz_line[MAX_CHAR_NUM] = { 0 };
    size_t index = 0;
    char sz_num[12] = { 0 };
    size_t len = 0;
    int j = 0;

    fp = fopen("timetable.txt", "w");
    if (fp == NULL)
    {
        printf("open error!\n");
    }

    len = strlen(course_title->course_code);
    memcpy(sz_line + index, course_title->course_code, len);
    index += len;
    sz_line[index++] = ' ';

    len = strlen(course_title->course_title);
    memcpy(sz_line + index,course_title->course_title, len);
    index += len;
    sz_line[index++] = ' ';

    len = strlen(course_title->section);
    memcpy(sz_line + index,course_title->section, len);
    index += len;
    sz_line[index++] = ' ';

    len = strlen(course_title->time);
    memcpy(sz_line + index,course_title->time, len);
    index += len;
    sz_line[index++] = ' ';

    len = strlen(course_title->classroom);
    memcpy(sz_line + index,course_title->classroom, len);
    index += len;
    sz_line[index++] = ' ';

    len = strlen(course_title->instructor);
    memcpy(sz_line + index,course_title->instructor, len);
    index += len;
    sz_line[index++] = ' ';
    fprintf(fp, "%s\n", sz_line);

    for (; i < count; ++i)
    {
        memset(sz_line, 0, sizeof(sz_line));
        index = 0;

        _itoa(info[i].course_code, sz_num, 10);
        len = strlen(sz_num);
        memcpy(sz_line + index, sz_num, len);
        index += len;
        sz_line[index++] = ' ';

        len = strlen(info[i].course_title);
        memcpy(sz_line + index, info[i].course_title, len);
        index += len;
        sz_line[index++] = ' ';

        _itoa(info[i].section, sz_num, 10);
        len = strlen(sz_num);
        memcpy(sz_line + index, sz_num, len);
        index += len;
        sz_line[index++] = ' ';

        len = strlen(info[i].time);
        memcpy(sz_line + index, info[i].time, len);
        index += len;
        sz_line[index++] = ' ';

        len = strlen(info[i].classroom);
        memcpy(sz_line + index, info[i].classroom, len);
        index += len;
        sz_line[index++] = ' ';

        len = strlen(info[i].instructor);
        memcpy(sz_line + index, info[i].instructor, len);

        fprintf(fp, "%s\n", sz_line);
    }

    fclose(fp);
}

int stu_count = 0;
StudentTitle student_title;
Student student_arr[MAX_STUDENT_NUM];

int course_count = 0;
Course course_arr[MAX_COURSE_NUM];
CourseTitle course_title;

void InitData()
{
    memset(student_arr,0,sizeof(student_arr));
    stu_count = InitStudentInfo(student_arr,&student_title);

    memset(course_arr,0,sizeof(course_arr));
    course_count = InitCourseInfo(course_arr,&course_title);
}

void PrintCourse(int course_code, SOCKET *ClientSocket, char* szBuff)
{
    int i = 0;
    //char szBuff[1300];
    char temp[1300];
    int receByt;
    //memset(szBuff,0,sizeof(szBuff));
    for(;i < course_count;++i)
    {
        if(course_arr[i].course_code == course_code)
        {
            itoa(course_arr[i].course_code, temp, 10);
            strcat(szBuff, "course_code: ");
            strcat(szBuff, temp);
            memset(temp,0,sizeof(temp));
            strcat(szBuff, ". course_title: ");
            strcat(szBuff, course_arr[i].course_title);
            itoa(course_arr[i].section, temp, 10);
            strcat(szBuff, ". section: ");
            strcat(szBuff, temp);
            memset(temp,0,sizeof(temp));
            strcat(szBuff, ". time: ");
            strcat(szBuff, course_arr[i].time);
            strcat(szBuff, ". classroom: ");
            strcat(szBuff, course_arr[i].classroom);
            strcat(szBuff, ". instructor: ");
            strcat(szBuff, course_arr[i].instructor);
            strcat(szBuff, ".\n");
        }
    }
}

void SearchStudent(SOCKET *ClientSocket)
{
    char name[1300];
    char szBuff[1300];
    int i = 0;
    int nametimes = 0;
    int receByt;
    send(*ClientSocket, "Input name:", sizeof("Input name:"), 0);
    memset(name,0,sizeof(name));
    receByt = recv(*ClientSocket, name, sizeof(name), 0);
    //printf("Bytes Received: %d, message: %s from client\n", receByt, name);
    //receByt = send(*ClientSocket, szBuff, sizeof(szBuff), 0);
    //memset(name,0,sizeof(name));

    memset(szBuff,0,sizeof(szBuff));
    for(;i < stu_count;++i)
    {
        if(strcmp(name,student_arr[i].name) == 0)
        {
            PrintCourse(student_arr[i].course_code, ClientSocket, szBuff);
            nametimes++;
        }
    }

    if(nametimes == 0)
    {
        strcat(name, " didn't find!\n");
        send(*ClientSocket, name, sizeof(name), 0);
    }
    send(*ClientSocket, szBuff, sizeof(szBuff), 0);
}

void AddStudent(SOCKET *ClientSocket)
{
    int code = 0;
    char szBuff[1300];
    char name[CHAR_LEN];
    int i = 0;
    int receByt;
    //Input name
    memset(szBuff,0,sizeof(szBuff));
    send(*ClientSocket, "Input name:", sizeof("Input name:"), 0);
    receByt = recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    strcpy(name, szBuff);
    memset(szBuff,0,sizeof(szBuff));
    //Input course_code
    send(*ClientSocket, "Input course_code:", sizeof("Input course_code:"), 0);
    receByt = recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    code = atoi(szBuff);
    memset(szBuff,0,sizeof(szBuff));

    strcpy(student_arr[stu_count].name,name);
    student_arr[stu_count].course_code = code;
    ++stu_count;
    //printf("Student added!\n");

    send(*ClientSocket, "Student added!", sizeof("Student added!"), 0);
    memset(szBuff,0,sizeof(szBuff));
}

void DeleteStudentByIndex(int index)
{
    int i = 0;
    stu_count--;
    for(i = index;i < stu_count;++i)
    {
        memcpy(&student_arr[i],&student_arr[i+1],sizeof(Student));
    }
}

void DeleteStudent(SOCKET *ClientSocket)
{
    int i = 0;
    int index = 0;
    int nametimes = 0;
    char name[CHAR_LEN];
    char szBuff[1300];
    Student tmp[MAX_STUDENT_NUM];

    send(*ClientSocket, "Input name:", sizeof("Input name:"), 0);
    memset(szBuff,0,sizeof(szBuff));
    recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    strcpy(name, szBuff);
    memset(tmp,0,sizeof(tmp));

    for(;i < stu_count;++i)
    {
        if(strcmp(name,student_arr[i].name) != 0)
        {
            memcpy(&tmp[index++],&student_arr[i],sizeof(Student));
        }
        else
        {
            nametimes++;
        }
    }

    memset(student_arr,0,sizeof(student_arr));
    memcpy(student_arr,tmp,sizeof(tmp));
    stu_count = index;

    if(nametimes != 0)
    {
        send(*ClientSocket, "Student deleted!", sizeof("Student deleted!"), 0);
    }
    else
    {
        strcat(name, " didn't find!");
        send(*ClientSocket, name, sizeof(name), 0);
    }
}

void UpdateStudent(SOCKET *ClientSocket)
{
    int i = 0;
    char szBuff[1300];
    int nametimes = 0;
    int receByt;
    int old_code = 0;
    int new_code = 0;
    char name[CHAR_LEN];
    //Input name
    memset(szBuff,0,sizeof(szBuff));
    send(*ClientSocket, "Input name:", sizeof("Input name:"), 0);
    receByt = recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    strcpy(name, szBuff);
    memset(szBuff,0,sizeof(szBuff));
    //Input old course_code
    send(*ClientSocket, "Input old course_code:", sizeof("Input old course_code:"), 0);
    receByt = recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    old_code = atoi(szBuff);
    memset(szBuff,0,sizeof(szBuff));
    //Input new course_code
    send(*ClientSocket, "Input new course_code:", sizeof("Input new course_code:"), 0);
    receByt = recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    new_code = atoi(szBuff);
    memset(szBuff,0,sizeof(szBuff));

    for(;i < stu_count;++i)
    {
        if(strcmp(name,student_arr[i].name) == 0 && student_arr[i].course_code == old_code)
        {
            if(new_code != 0)
            {
                student_arr[i].course_code = new_code;
            }
            else
            {
                DeleteStudentByIndex(i);
            }
            nametimes++;
            break;
        }
    }

    if(nametimes != 0)
    {
        send(*ClientSocket, "Student updated!", sizeof("Student updated!"), 0);
        memset(szBuff, 0, sizeof(szBuff));
    }
    else
    {
        send(*ClientSocket, "Name error or course_code error!", sizeof("Name error or course_code error!"), 0);
    }
}

void AddCourse(SOCKET *ClientSocket)
{
    int i = 0;
    int course_code = 0;
    char course_title[CHAR_LEN];
    int section = 0;
    char time[CHAR_LEN];
    char classroom[CHAR_LEN];
    char instructor[CHAR_LEN];
    char szBuff[1300];
    int receByt = 0;


    //Input name
    memset(szBuff,0,sizeof(szBuff));
    send(*ClientSocket, "Input course_code:", sizeof("Input course_code:"), 0);
    receByt = recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    course_code = atoi(szBuff);
    memset(szBuff,0,sizeof(szBuff));
    //Input course_title
    send(*ClientSocket, "Input course_title:", sizeof("Input course_title:"), 0);
    receByt = recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    strcpy(course_title, szBuff);
    memset(szBuff,0,sizeof(szBuff));
    //Input section
    send(*ClientSocket, "Input section:", sizeof("Input section:"), 0);
    receByt = recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    section = atoi(szBuff);
    memset(szBuff,0,sizeof(szBuff));
    //Input time
    memset(szBuff,0,sizeof(szBuff));
    send(*ClientSocket, "Input time:", sizeof("Input time:"), 0);
    receByt = recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    strcpy(time, szBuff);
    memset(szBuff,0,sizeof(szBuff));
    //Input old course_code
    send(*ClientSocket, "Input classroom:", sizeof("Input classroom:"), 0);
    receByt = recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    strcpy(classroom, szBuff);
    memset(szBuff,0,sizeof(szBuff));
    //Input new course_code
    send(*ClientSocket, "Input instructor:", sizeof("Input instructor:"), 0);
    receByt = recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    strcpy(instructor, szBuff);
    memset(szBuff,0,sizeof(szBuff));
    /*
    printf("input course_code:");
    scanf("%d",&course_code);
    printf("input course_title:");
    scanf("%s",course_title);
    printf("input section:");
    scanf("%d",&section);
    printf("input time:");
    scanf("%s",time);
    printf("input classroom:");
    scanf("%s",classroom);
    printf("input instructor:");
    scanf("%s",instructor);
     */


    for(;i < course_count;++i)
    {
        if(course_arr[i].course_code == course_code)
        {
            printf("Course is existed\n");
            send(*ClientSocket, "Course is existed", sizeof("Course is existed"), 0);
            return;
        }
    }

    course_arr[course_count].course_code = course_code;
    course_arr[course_count].section = section;
    strcpy(course_arr[course_count].course_title,course_title);
    strcpy(course_arr[course_count].time,time);
    strcpy(course_arr[course_count].classroom,classroom);
    strcpy(course_arr[course_count].instructor,instructor);
    ++course_count;

    printf("Course added!\n");
    send(*ClientSocket, "Course added!", sizeof("Course added!"), 0);
}

void UpdateStudentCode(int old_code,int new_code)
{
    int i = 0;
    for(;i < stu_count;++i)
    {
        if(student_arr[i].course_code == old_code)
        {
            student_arr[i].course_code = new_code;
        }
    }
}

void UpdateCourse(SOCKET *ClientSocket)
{
    int i = 0;
    int old_course_code = 0;
    int new_course_code = 0;
    char course_title[CHAR_LEN];
    int section = 0;
    char time[CHAR_LEN];
    char classroom[CHAR_LEN];
    char instructor[CHAR_LEN];
    char szBuff[1300];
    int coursetimes = 0;
    int receByt = 0;

    //Input name
    memset(szBuff,0,sizeof(szBuff));
    send(*ClientSocket, "Input old_course_code:", sizeof("Input old_course_code:"), 0);
    receByt = recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    old_course_code = atoi(szBuff);
    //Input name
    memset(szBuff,0,sizeof(szBuff));
    send(*ClientSocket, "Input new_course_code:", sizeof("Input new_course_code:"), 0);
    receByt = recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    new_course_code = atoi(szBuff);
    memset(szBuff,0,sizeof(szBuff));
    //Input course_title
    send(*ClientSocket, "Input course_title:", sizeof("Input course_title:"), 0);
    receByt = recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    strcpy(course_title, szBuff);
    memset(szBuff,0,sizeof(szBuff));
    //Input section
    send(*ClientSocket, "Input section:", sizeof("Input section:"), 0);
    receByt = recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    section = atoi(szBuff);
    memset(szBuff,0,sizeof(szBuff));
    //Input time
    memset(szBuff,0,sizeof(szBuff));
    send(*ClientSocket, "Input time:", sizeof("Input time:"), 0);
    receByt = recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    strcpy(time, szBuff);
    memset(szBuff,0,sizeof(szBuff));
    //Input old course_code
    send(*ClientSocket, "Input classroom:", sizeof("Input classroom:"), 0);
    receByt = recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    strcpy(classroom, szBuff);
    memset(szBuff,0,sizeof(szBuff));
    //Input new course_code
    send(*ClientSocket, "Input instructor:", sizeof("Input instructor:"), 0);
    receByt = recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    strcpy(instructor, szBuff);
    memset(szBuff,0,sizeof(szBuff));
    /*
    printf("input old_course_code:");
    scanf("%d",&old_course_code);
    printf("input new_course_code:");
    scanf("%d",&new_course_code);
    printf("input course_title:");
    scanf("%s",course_title);
    printf("input section:");
    scanf("%d",&section);
    printf("input time:");
    scanf("%s",time);
    printf("input classroom:");
    scanf("%s",classroom);
    printf("input instructor:");
    scanf("%s",instructor);
     */

    for(;i < course_count;++i)
    {
        if(course_arr[i].course_code == old_course_code)
        {
            course_arr[i].course_code = new_course_code;
            course_arr[i].section = section;
            strcpy(course_arr[i].course_title,course_title);
            strcpy(course_arr[i].time,time);
            strcpy(course_arr[i].classroom,classroom);
            strcpy(course_arr[i].instructor,instructor);

            UpdateStudentCode(old_course_code,new_course_code);
            coursetimes++;
        }
    }

    if(coursetimes != 0)
    {
        send(*ClientSocket, "Course updated!", sizeof("Course updated!"), 0);
    }
    else
    {
        send(*ClientSocket, "Cannot find this course!", sizeof("Cannot find this course!"), 0);
    }
}

void DeleteStudentByCode(int code)
{
    int i = 0;
    int index = 0;
    Student tmp[MAX_STUDENT_NUM];
    memset(tmp,0,sizeof(tmp));

    for(;i < stu_count;++i)
    {
        if(student_arr[i].course_code != code)
        {
            memcpy(&tmp[index++],&student_arr[i],sizeof(Student));
        }
    }

    memset(student_arr,0,sizeof(student_arr));
    memcpy(student_arr,tmp,sizeof(tmp));
    stu_count = index;
}

int DeleteCourse(SOCKET *ClientSocket)
{
    int i = 0;
    int course_code = 0;
    char szBuff[1300];
    char tmp[1300];
    int nametimes = 0;
    //printf("input course_code:");
    //scanf("%d",&course_code);

    send(*ClientSocket, "Input course_code:", sizeof("Input course_code:"), 0);
    memset(szBuff,0,sizeof(szBuff));
    recv(*ClientSocket, szBuff, sizeof(szBuff), 0);
    course_code = atoi(szBuff);
    memset(tmp,0,sizeof(tmp));

    for(;i < course_count;++i)
    {
        if(course_arr[i].course_code == course_code)
        {
            nametimes++;
            break;
        }
    }

    if(i != course_count)
    {
        course_count--;
        for(;i < course_count;++i)
        {
            memcpy(&course_arr[i],&course_arr[i+1],sizeof(Course));
        }
        DeleteStudentByCode(course_code);
    }


    if(nametimes != 0)
    {
        send(*ClientSocket, "Course deleted!", sizeof("Course deleted!"), 0);
    }
    else
    {
        strcat(szBuff, " didn't find!");
        send(*ClientSocket, szBuff, sizeof(szBuff), 0);
    }
    return 1;
}

//server

void output_file(const char* filename,const char*  text)
{
    FILE *fp  = NULL;
    printf("filename:%s,%s",filename,text);
    do{
        fp  = fopen(filename, "a+");
        if(fp==NULL)
        {
            fprintf(fp, "open file :%s\n", filename);
            fclose(fp);
            break;
        }
        fprintf(fp, "%s\n", text);
    }while(0);

    if(fp)
        fclose(fp);

    return;
}

DWORD WINAPI ServerThread(LPVOID lpParameter)
{
    struct tm t;
    time_t now;
    //to get time
    int instru;
    char szBuff[1300];
    SOCKET *ClientSocket=(SOCKET*)lpParameter;
    int receByt=0;

    struct sockaddr_in client_addr;
    memset(&client_addr,0,sizeof(client_addr));
    int len = sizeof(client_addr);
    getpeername(*ClientSocket,(struct sockaddr *)&client_addr,&len);

    char log_str[256]={0};

    while(1)
    {
        InitData();

        receByt = recv(*ClientSocket,szBuff,sizeof(szBuff),0);

        if(receByt>0)
        {
            instru = atoi(szBuff);//To get instruction
            printf("Instru = %d\n", instru);
        }
        else
        {
            time(&now);
            localtime_s(&t, &now);
            memset(log_str,0,strlen(log_str));
            sprintf(log_str, "Client closed connection. Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
            output_file("log.txt",log_str);
            break;
        }
        //CmdTips();
        switch(instru)
        {
            case 1:
                SearchStudent(ClientSocket);
                break;
            case 2:
                AddStudent(ClientSocket);
                SaveStudentInfo(student_arr,stu_count,&student_title);
                break;
            case 3:
                UpdateStudent(ClientSocket);
                SaveStudentInfo(student_arr,stu_count,&student_title);
                break;
            case 4:
                DeleteStudent(ClientSocket);
                SaveStudentInfo(student_arr,stu_count,&student_title);
                break;
            case 5:
                AddCourse(ClientSocket);
                SaveCourseInfo(course_arr,course_count,&course_title);
                break;
            case 6:
                UpdateCourse(ClientSocket);
                SaveCourseInfo(course_arr,course_count,&course_title);
                SaveStudentInfo(student_arr,stu_count,&student_title);
                break;
            case 7:
                DeleteCourse(ClientSocket);
                SaveCourseInfo(course_arr,course_count,&course_title);
                SaveStudentInfo(student_arr,stu_count,&student_title);
                break;
            case 8:
                break;
        }

        memset(szBuff,0,sizeof(szBuff));
        if (receByt == 0)
        {
            time(&now);
            localtime_s(&t, &now);
            memset(log_str,0,strlen(log_str));
            sprintf(log_str, "Client closed connection. Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
            output_file("log.txt",log_str);
            break;
        }
    }//while


    closesocket(*ClientSocket);
    free(ClientSocket);
    return 0;
}

int main()
{
    struct sockaddr_in local, client_addr;
    struct tm t;
    time_t now;
    //to get time

    WSAData wsd;
    WSAStartup(MAKEWORD(2,2),&wsd);
    SOCKET ListenSocket = socket(AF_INET,SOCK_STREAM,0);
    SOCKADDR_IN ListenAddr;
    ListenAddr.sin_family=AF_INET;
    ListenAddr.sin_addr.S_un.S_addr=INADDR_ANY;//local ip
    ListenAddr.sin_port=htons(PORT);

    int addr_len;
    int msg_sock;
    int n;
    char log_str[256]={0};

    time(&now);
    localtime_s(&t, &now);
    memset(log_str,0,strlen(log_str));
    sprintf(log_str, "Server started. Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
    output_file("log.txt",log_str);

    n=bind(ListenSocket,(LPSOCKADDR)&ListenAddr,sizeof(ListenAddr));
    if(n==SOCKET_ERROR)
    {
        time(&now);
        localtime_s(&t, &now);
        memset(log_str,0,strlen(log_str));
        sprintf(log_str, "bind() failed. Time: %d/%d/%d %d:%d:%d\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        output_file("log.txt",log_str);
        return -1;
    }
    else
    {
        time(&now);
        localtime_s(&t, &now);
        memset(log_str,0,strlen(log_str));
        sprintf(log_str, "Bind port %d successful. Time: %d/%d/%d %d:%d:%d\n", PORT, t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        output_file("log.txt",log_str);
    }

    if (listen(ListenSocket, 20) == SOCKET_ERROR)
    {
        fprintf(stderr, "listen() failed with error %d\n", WSAGetLastError());
        time(&now);
        localtime_s(&t, &now);
        memset(log_str,0,strlen(log_str));
        sprintf(log_str, "listen() failed. Time: %d/%d/%d %d:%d:%d\n", PORT, t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        output_file("log.txt",log_str);
        WSACleanup();
        return -1;
    }
    printf("Start listening...\n");
    addr_len = sizeof(client_addr);

    while(1)
    {
        //create threads
        SOCKET *ClientSocket;
        ClientSocket = (SOCKET*)malloc(sizeof(SOCKET));
        //receive from client
        int SockAddrlen = sizeof(sockaddr);
        *ClientSocket = accept(ListenSocket, (struct sockaddr*)&client_addr, &addr_len);

        time(&now);
        localtime_s(&t, &now);
        memset(log_str,0,strlen(log_str));
        sprintf(log_str, "One client connected! Time: %d/%d/%d %d:%d:%d. Socket: %d. Client address: %s\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec, *ClientSocket, inet_ntoa(client_addr.sin_addr));
        output_file("log.txt",log_str);
        CreateThread(NULL,0,&ServerThread,ClientSocket,0,NULL);
    }//while
    closesocket(ListenSocket);
    WSACleanup();
    return(0);
}//main