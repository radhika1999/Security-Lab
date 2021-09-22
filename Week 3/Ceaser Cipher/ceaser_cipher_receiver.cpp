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
	char et[100];
	int key;
	int rfd=open("text_fifo", O_RDONLY);
	read(rfd, et, 100);
	int n=strlen(et);
	//Key is fixed between sender and receiver
	printf("Enter key: ");
	scanf("%d", &key);
	printf("Encrypted text received: %s\n", et);
	char pt[100];
	for(int i=0;i<n;i++){
		if(et[i]==' '){
			pt[i]=' ';
			continue;
		}
		int val=(int)(et[i]-'a');
		int pos=(val-key+26)%26;
		pt[i]='a'+pos;
	}
	pt[n]='\0';
	printf("Decrypted text is: %s\n", pt);
}