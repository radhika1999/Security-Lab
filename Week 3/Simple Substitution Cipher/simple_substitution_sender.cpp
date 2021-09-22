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
	string key="abcdefghijklmnopqrstuvwxyz";
	string temp=key;
	srand(time(0));
	random_shuffle(key.begin(), key.end());
	cout<<"Original: "<<temp<<endl;
	cout<<"Key is:   "<<key<<endl;
	int n=strlen(pt);
	char et[100];
	for(int i=0;i<n;i++){
		if(pt[i]==' '){
			et[i]=' ';
			continue;
		}
		int val=(int)(pt[i]-'a');
		et[i]=key[val];
	}
	et[n]='\0';
	printf("Encrypted text is: %s\n", et);
	mkfifo("text_fifo", 0666);
	int wfd=open("text_fifo", O_WRONLY);
	write(wfd, et, (strlen(et)+1));
}