#include <stdbool.h>
typedef struct{
	int id;
	char name[50];
	char email[50];
	char phone[20];
	char classRoom[20];
}Student;

typedef struct{
	int id;
	char teacherName[50];
	char classRoomId[20];
	char email[50];
	char phone[50];
}Teacher;