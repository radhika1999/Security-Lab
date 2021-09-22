#include<iostream>
#include<sys/types.h>
#include<sys/sem.h>
#include<sys/ipc.h> 
#include<sys/shm.h> 
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<string.h>
#include<cstring>
#include<stdio.h>
#include<sstream>
#include<algorithm>
using namespace std;

int main(){
	char pt[100];
	printf("Enter plain text: ");
	scanf("%[^\n]%*c", pt);
	char key[100];
	printf("Enter key: ");
	scanf("%s", key);
	int n=strlen(pt);
	char et[100];
	int key_i=0;
	int key_l=strlen(key);
	printf("Numeric form of key: ");
	for(int i=0;i<key_l;i++){
		int val=(int)(key[i]-'a');
		printf("%d ", val);
	}
	printf("\nPlain text addition values:\n");
	for(int i=0;i<n;i++){
		if(pt[i]==' '){
			et[i]=' ';
			continue;
		}
		int val1=(int)(pt[i]-'a');
		int val2=(int)(key[key_i]-'a');
		printf("%c: %d ", pt[i], val2);
		int val=(val1+val2)%26;
		et[i]='a'+val;
		key_i=(key_i+1)%key_l;
	}
	et[n]='\0';
	printf("\nEncrypted text is: %s\n", et);
	mkfifo("text_fifo", 0666);
	int wfd=open("text_fifo", O_WRONLY);
	write(wfd, et, (strlen(et)+1));
}