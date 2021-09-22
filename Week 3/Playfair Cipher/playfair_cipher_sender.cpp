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
	char pt[100];
	printf("Enter plain text: ");
	scanf("%[^\n]%*c", pt);
	char key[100];
	printf("Enter key: ");
	scanf("%[^\n]%*c", key);
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
	int n=strlen(pt);
	//removing all spaces from plain text
	int count=0;
	for(int i=0;i<n;i++){
		if(pt[i]!=' '){
			pt[count++]=pt[i];
		}
	}
	pt[count]='\0';
	n=strlen(pt);
	char et[100];
	for(int i=0;i<n;i=i+2){
		if(i==(n-1)){
			pt[n]='z';
			n++;
			pt[n]='\0';
			break;
		}
		if(pt[i]==pt[i+1]){
			for(int j=n+1;j>(i+1);j--){
				pt[j]=pt[j-1];
			}
			pt[i+1]='x';
			n=strlen(pt);
		}
	}
	int row1,col1,row2,col2;
	for(int i=0;i<n;i=i+2){
		find(table, pt[i], row1, col1);
		find(table, pt[i+1], row2, col2);
		if(row1==row2){
			int pos1=(col1+1)%5;
			int pos2=(col2+1)%5;
			et[i]=table[row1][pos1];
			et[i+1]=table[row2][pos2];
		}
		else if(col1==col2){
			int pos1=(row1+1)%5;
			int pos2=(row2+1)%5;
			et[i]=table[pos1][col1];
			et[i+1]=table[pos2][col2];
		}
		else{
			et[i]=table[row1][col2];
			et[i+1]=table[row2][col1];
		}
	}

	et[n]='\0';
	printf("Encrypted text is: %s\n", et);
	mkfifo("text_fifo", 0666);
	int wfd=open("text_fifo", O_WRONLY);
	write(wfd, et, (strlen(et)+1));
}