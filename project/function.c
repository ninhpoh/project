#include <stdio.h>
#include <string.h>
#include "function.h"

void menuTeacher(){
		printf("\t=========MENU=========\n");
		printf("\t[1] them giao vien.\n");
		printf("\t[2] Hien thi giao vien.\n");
		printf("\t[3] Sua thong tin giao vien.\n");
		printf("\t[4] Tim kiem giao vien.\n");
		printf("\t[5] Xoa giao vien.\n");
		printf("\t[6] Them lop cho giao vien\n");
		printf("\t[0] Exit Program.\n");
		printf("\t======================\n");
}
void doMenuTeacher(){
	int teacher;
	do{
		menuTeacher();
		printf("\tthao tac cua ban: ");
		scanf("%d",&teacher);
		switch(teacher){
			case 1:
			
				break;
			case 2:
				break;
			case 0:
				printf("\tthoat\n");
				break;
			default:
				printf("\tLoi thao tac\n");
		}		
	}while(teacher!=0);
}
void admin(){
	
		printf("\t=========ROLE=========\n");
		printf("\t[1] Sinh vien.\n");
		printf("\t[2] Giao vien.\n");
		printf("\t[0] Exit Program.\n");
		printf("\t======================\n");
}
void menu(){
	
		printf("\t=========MENU=========\n");
		printf("\t[1] them sinh vien.\n");
		printf("\t[2] Hien thi sinh vien.\n");
		printf("\t[3] Sua thong tin sinh vien.\n");
		printf("\t[4] Tim kiem sinh vien.\n");
		printf("\t[5] Xoa sinh vien.\n");
		printf("\t[6] Sap xep sinh vien\n");
		printf("\t[0] Exit Program.\n");
		printf("\t======================\n");
}
void adminMenu(){
	int choose;
	do {
		menu();
		printf ("\tLua chon cua ban: ");
		scanf("%d",&choose);
		switch(choose){
			case 1:
				addStudent();
				break;
			case 2:
				displayStudents();
				break;
			case 3:
				editStudent();
				break;
			case 4:
				findStudent();
				break;
			case 5:
				deleteStudent();
				break;	
			case 6:
				arrangeStudent();
				break;
			case 0:
				break;
			default:
				printf("\tLoi thao tac!\n");
		}
	}while(choose!=0);
}
void addStudent() {
    FILE *ptr = fopen("student.dat", "rb+"); 
    if (ptr == NULL) {
        ptr = fopen("student.dat", "wb"); 
        if (ptr == NULL) {
            printf("\tLỗi mở file\n");
            return;
        }
    }

    Student students;

    int isDuplicate = 0;
    do {
        printf("ID sinh vien: ");
        scanf("%d", &students.id);
        getchar();

        
        Student tempStudent;
        isDuplicate = 0;
        rewind(ptr); 
        while (fread(&tempStudent, sizeof(Student), 1, ptr)) {
            if (tempStudent.id == students.id) {
                printf("\tID nay da ton tai\n");
                isDuplicate = 1;
                break;
            }
        }
    } while (isDuplicate);

    printf("Ten sinh vien: ");
    fgets(students.name, sizeof(students.name), stdin);
    students.name[strcspn(students.name, "\n")] = '\0';  

    printf("Email sinh vien: ");
    fgets(students.email, sizeof(students.email), stdin);
    students.email[strcspn(students.email, "\n")] = '\0';  

    printf("SDT sinh vien: ");
    fgets(students.phone, sizeof(students.phone), stdin);
    students.phone[strcspn(students.phone, "\n")] = '\0';  

    fseek(ptr, 0, SEEK_END); 
    fwrite(&students, sizeof(Student), 1, ptr);
    printf("\tLuu thanh cong\n");

    fclose(ptr);
    pressToExitOrReturn();
}


void displayStudents(){
	FILE *file = fopen("student.dat", "rb");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }
    
    Student student;
    printf("\n\tStudent list:\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("ID   | Name                    | Email                     | Phone    \n");
    printf("--------------------------------------------------------------------------------------\n");
   
    while (fread(&student, sizeof(Student), 1, file)) {
    	//printf ("\n");
        printf("%-4d | %-23s | %-25s | %-25s  ",
               student.id, student.name, student.email, student.phone);
        printf("\n--------------------------------------------------------------------------------------\n");
    }
    
    fclose(file);
    pressToExitOrReturn();
}

void editStudent(){
    FILE *file = fopen("student.dat", "rb+");  
    if (file == NULL) {
        printf("Loi mo file.\n");
        return;
    }

    int id;
    printf("Nhap ID cua sinh vien muon sua: ");
    scanf("%d", &id);
    getchar(); 

    Student student;
    int found = 0;
    while (fread(&student, sizeof(Student), 1, file)) {
        if (student.id == id) {
            found = 1;
            printf("da tin thay doi tuong:\n");
            printf("Ten cu: %s\n", student.name);
            printf("Nhap ten moi: ");
            fgets(student.name, sizeof(student.name), stdin);
            student.name[strcspn(student.name, "\n")] = '\0';  

            printf("Email hien tai: %s\n", student.email);
            printf("New email: ");
            fgets(student.email, sizeof(student.email), stdin);
            student.email[strcspn(student.email, "\n")] = '\0';  

            printf("sdt cu: %s", student.phone);			// /n
            printf("So dt moi: ");
            fgets(student.phone, sizeof(student.phone), stdin);
            student.phone[strcspn(student.phone, "\n")] = '\0';  

            
            fseek(file, -sizeof(Student), SEEK_CUR);
            fwrite(&student, sizeof(Student), 1, file);  
            printf("Thong tin da duoc sua.\n");
            break;
        }
    }

    if (!found) {
        printf("Sinh vien ID %d khong ton tai.\n", id);
    }

    fclose(file);
    pressToExitOrReturn();
}

void searchStudent() {
    FILE *file = fopen("student.dat", "rb");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    int id;
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);

    Student student;
    int found = 0;

    while (fread(&student, sizeof(Student), 1, file)) {
        if (student.id == id) {
            found = 1;
            printf("Sinh vien tim thay: \n");
            printf("ID: %d | Ten: %s | Email: %s | SDT: %s\n", student.id, student.name, student.email, student.phone);
            break;
        }
    }

    if (!found) {
        printf("Khong tim thay sinh vien voi ID %d.\n", id);
    }

    fclose(file);
    pressToExitOrReturn();
}

void pressToExitOrReturn() {
    char choice;
    printf("\n\t[0] Exit\t[b] Back to menu\n");
    printf("\tLua chon cua ban: ");
    scanf("%c", &choice);  
    getchar();  

    if (choice == '0') {
       printf("Exiting...\n");
       exit(0);
    } else if (choice == 'b') {
        return;
    } else {
        printf("Invalid choice. Returning to menu...\n");
        return;
    }
}

void findStudent() { 
    FILE *file = fopen("student.dat", "rb");
    if (file == NULL) {
        printf("Loi mo file.\n");
        return;
    }

    char name[50];
    printf("Ten sinh ban can tim: ");
    getchar();  
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; 

    Student student;
    int found = 0;

    while (fread(&student, sizeof(Student), 1, file)) {
        if (strstr(student.name, name) != NULL) { 
            found = 1;
            printf("Da 'bat' duoc  sinh vien ban can: \n");
            printf("ID: %d | Ten: %s | Email: %s | SDT: %s\n", student.id, student.name, student.email, student.phone);
        }
    }

    if (!found) {
        printf("Khong ton tai sinh vien %s trong danh sach.\n", name);
    }

    fclose(file);
    pressToExitOrReturn();
}

void deleteStudent() {
	
    FILE *file = fopen("student.dat", "rb");
    if (file == NULL) {
        printf("Loi mo file goc.\n");
        return;
    }

    FILE *tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL) {
        printf("Loi mo file tam.\n");
        fclose(file);
        return;
    }

    int id;
    printf("Nhap id sinh vien ban muon kick: ");
    scanf("%d", &id);

    Student student;
    int found = 0;

    
    while (fread(&student, sizeof(Student), 1, file)) {
        if (student.id == id) {
            found = 1;  
            printf("Sinh vien ID %d: %s co ton tai.\n", student.id, student.name);
		    printf("ID: %d | Ten: %s | Email: %s | SDT: %s\n", student.id, student.name, student.email, student.phone);

            
            char confirm;
            printf("Co chac muon kick khong zay? (y/n): ");
            getchar();  
            scanf("%c", &confirm);

            if (confirm == 'y' || confirm == 'Y') {
              //  printf("dang xoa sv ID %d...\n", student.id);
                continue;  
            } else {
                printf("Ru long tu bi khong xoa sv id %d nua \n", student.id);
                fwrite(&student, sizeof(Student), 1, tempFile);  
                fclose(file);
                fclose(tempFile);
                pressToExitOrReturn();
                return;
            }
        }
        fwrite(&student, sizeof(Student), 1, tempFile);  
    }

    if (!found) {
        printf("Khong co sinh vien ID %d.\n", id);
    } else {
        printf("Sinh vien voi ID %d da duoc xoa.\n", id);
    }

    fclose(file);
    fclose(tempFile);

    remove("student.dat");
    rename("temp.dat", "student.dat");

    pressToExitOrReturn();
}

void arrangeStudent(){
	int arrange;
	do{
		printf("\t=========ARRANGE=========\n");
		printf("\t[1] Theo ten.\n");
		printf("\t[2] Theo Id.\n");
		printf("\t[0] Exit Program.\n");
		printf("\t=========================\n");
		printf ("\tLua chon cua ban: ");
		scanf("%d",&arrange);
		switch (arrange){
		case 1:
			printf("cho cap nhat\n");
			break;
		case 2:
			arrangeId();
			break;
		case 0:
			break;
		default:
			printf("\tThao tac khong hop le\n");
		}
	}while(arrange!=0);
//	pressToExitOrReturn();
}

void arrangeId(){
	FILE *file = fopen("student.dat", "rb");
    if (file == NULL) {
        printf("Lỗi mở file gốc.\n");
        return;
    }

    
    fseek(file, 0, SEEK_END);
    int count = ftell(file) / sizeof(Student);
    rewind(file);

    if (count == 0) {
        printf("Không có sinh viên để sắp xếp.\n");
        fclose(file);
        return;
    }

   
    Student *students = (Student *)malloc(count * sizeof(Student));
    if (students == NULL) {
        printf("Không đủ bộ nhớ.\n");
        fclose(file);
        return;
    }
    fread(students, sizeof(Student), count, file);
    fclose(file);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].id > students[j + 1].id) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    FILE *tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL) {
        printf("Lỗi mở file tạm.\n");
        free(students);
        return;
    }
    fwrite(students, sizeof(Student), count, tempFile);
	fclose(tempFile);
	
	FILE *temp = fopen("temp.dat", "rb");
    if (temp == NULL) {
        printf("Unable to open the file.\n");
        return;
    }
    
    Student student;
    printf("\n\tStudent list:\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("ID   | Name                    | Email                     | Phone    \n");
    printf("--------------------------------------------------------------------------------------\n");
   
    while (fread(&student, sizeof(Student), 1, temp)) {
    	//printf ("\n");
        printf("%-4d | %-23s | %-25s | %-25s  ",
               student.id, student.name, student.email, student.phone);
        printf("\n--------------------------------------------------------------------------------------\n");
    }
    


    fclose(tempFile);
    pressToExitOrReturn();
}

void addTeacher(){
	
}