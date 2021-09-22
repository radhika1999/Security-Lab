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
	char et[100];
	char key[100];
	int rfd=open("text_fifo", O_RDONLY);
	read(rfd, et, 100);
	int n=strlen(et);
	printf("Enter key: ");
	scanf("%s", key);
	char pt[100];
	int key_i=0;
	int key_l=strlen(key);
	for(int i=0;i<n;i++){
		if(et[i]==' '){
			pt[i]=' ';
			continue;
		}
		int val1=(int)(et[i]-'a');
		int val2=(int)(key[key_i]-'a');
		int val=(val1-val2+26)%26;
		pt[i]='a'+val;
		key_i=(key_i+1)%key_l;
	}
	pt[n]='\0';
	printf("Decrypted text is: %s\n", pt);
}