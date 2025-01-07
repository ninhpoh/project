#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
int role;     

	int n;
	do{
		admin();
		printf ("\tLua chon cua ban: ");
		scanf("%d",&role);
		switch(role){
			case 1:
				adminMenu();
				break;
			case 2:
				doMenuTeacher();
				break;
//			case 3:=
//				printf("cho cap nhat\n");
//				break;3
			case 0:
				break;
			default:
				printf("\tLoi thao tac!\n");
		}
	}while(role!=0);
	return 0;
}
