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
using namespace std;

int main(){
	char pt[100];
	printf("Enter plain text: ");
	scanf("%[^\n]%*c", pt);
	int key;
	printf("Enter key: ");
	scanf("%d", &key);
	int n=strlen(pt);
	char et[100];
	for(int i=0;i<n;i++){
		if(pt[i]==' '){
			et[i]=' ';
			continue;
		}
		int val=(int)(pt[i]-'a');
		int pos=(val+key)%26;
		et[i]='a'+pos;
	}
	et[n]='\0';
	printf("Encrypted text is: %s\n", et);
	mkfifo("text_fifo", 0666);
	int wfd=open("text_fifo", O_WRONLY);
	write(wfd, et, (strlen(et)+1));
}