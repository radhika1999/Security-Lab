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

void find(char table[][5], char x, int &row, int &col){
	if(x=='j'){
		x='i';
	}
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(table[i][j]==x){
				row=i;
				col=j;
				break;
			}
		}
	}
}
int main(){
	char et[100];
	char key[100];
	int rfd=open("text_fifo", O_RDONLY);
	read(rfd, et, 100);
	int n=strlen(et);
	//Key is fixed between sender and receiver
	printf("Enter key: ");
	scanf("%[^\n]%*c", key);
	printf("Encrypted text received: %s\n", et);
	char table[5][5];
	int row=0,col=0;
	int visited[26]={0};
	printf("Key Grid: \n");
	for(int i=0;i<strlen(key);i++){
		if(key[i]==' '){
			continue;
		}
		if(!visited[key[i]-'a']){
			table[row][col]=key[i];
			cout<<table[row][col]<<" ";
			visited[key[i]-'a']=1;
			col=(col+1)%5;
			if(col==0){
				row++;
				cout<<endl;
			}
		}
	}
	char curr='a';
	while(row<5){
		if(!visited[curr-'a']&&curr!='j'){
			table[row][col]=curr;
			cout<<table[row][col]<<" ";
			visited[curr-'a']=1;
			col=(col+1)%5;
			if(col==0){
				row++;
				cout<<endl;
			}
		}
		curr++;
	}
	char pt[100];
	int row1,col1,row2,col2;
	for(int i=0;i<n;i=i+2){
		find(table, et[i], row1, col1);
		find(table, et[i+1], row2, col2);
		if(row1==row2){
			int pos1=(col1-1+5)%5;
			int pos2=(col2-1+5)%5;
			pt[i]=table[row1][pos1];
			pt[i+1]=table[row2][pos2];
		}
		else if(col1==col2){
			int pos1=(row1-1+5)%5;
			int pos2=(row2-1+5)%5;
			pt[i]=table[pos1][col1];
			pt[i+1]=table[pos2][col2];
		}
		else{
			pt[i]=table[row1][col2];
			pt[i+1]=table[row2][col1];
		}
	}

	pt[n]='\0';
	printf("Decrypted text is: %s\n", pt);
}