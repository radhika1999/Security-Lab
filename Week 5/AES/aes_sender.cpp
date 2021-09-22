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
#include "aes_headers.h"
using namespace std;

void s_box_substitution(unsigned char * state) {
	for (int i = 0; i < 16; i++) {
		state[i] = s[state[i]];
	}
}

void shift_rows(unsigned char * state) {
	unsigned char new_state[16];

	//For coloumn 1
	new_state[0] = state[0];
	new_state[1] = state[5];
	new_state[2] = state[10];
	new_state[3] = state[15];
	
	//For coloumn 2
	new_state[4] = state[4];
	new_state[5] = state[9];
	new_state[6] = state[14];
	new_state[7] = state[3];

	//For coloumn 3
	new_state[8] = state[8];
	new_state[9] = state[13];
	new_state[10] = state[2];
	new_state[11] = state[7];
	
	//For coloumn 4
	new_state[12] = state[12];
	new_state[13] = state[1];
	new_state[14] = state[6];
	new_state[15] = state[11];

	for (int i = 0; i < 16; i++){
		state[i] = new_state[i];
	}
	
}

void mix_coloumns(unsigned char * state) {
	//Using constant matrix m
	// string mat[4][4]={
	// {"02", "03", "01", "01"},
	// {"01", "02", "03", "01"},
	// {"01", "01", "02", "03"},
	// {"03", "01", "01", "02"}
	// };
	unsigned char temp[16];

	//Using predefined tables

	temp[0] = (unsigned char) mul2[state[0]] ^ mul3[state[1]] ^ state[2] ^ state[3];
	temp[1] = (unsigned char) state[0] ^ mul2[state[1]] ^ mul3[state[2]] ^ state[3];
	temp[2] = (unsigned char) state[0] ^ state[1] ^ mul2[state[2]] ^ mul3[state[3]];
	temp[3] = (unsigned char) mul3[state[0]] ^ state[1] ^ state[2] ^ mul2[state[3]];

	temp[4] = (unsigned char)mul2[state[4]] ^ mul3[state[5]] ^ state[6] ^ state[7];
	temp[5] = (unsigned char)state[4] ^ mul2[state[5]] ^ mul3[state[6]] ^ state[7];
	temp[6] = (unsigned char)state[4] ^ state[5] ^ mul2[state[6]] ^ mul3[state[7]];
	temp[7] = (unsigned char)mul3[state[4]] ^ state[5] ^ state[6] ^ mul2[state[7]];

	temp[8] = (unsigned char)mul2[state[8]] ^ mul3[state[9]] ^ state[10] ^ state[11];
	temp[9] = (unsigned char)state[8] ^ mul2[state[9]] ^ mul3[state[10]] ^ state[11];
	temp[10] = (unsigned char)state[8] ^ state[9] ^ mul2[state[10]] ^ mul3[state[11]];
	temp[11] = (unsigned char)mul3[state[8]] ^ state[9] ^ state[10] ^ mul2[state[11]];

	temp[12] = (unsigned char)mul2[state[12]] ^ mul3[state[13]] ^ state[14] ^ state[15];
	temp[13] = (unsigned char)state[12] ^ mul2[state[13]] ^ mul3[state[14]] ^ state[15];
	temp[14] = (unsigned char)state[12] ^ state[13] ^ mul2[state[14]] ^ mul3[state[15]];
	temp[15] = (unsigned char)mul3[state[12]] ^ state[13] ^ state[14] ^ mul2[state[15]];

	for (int i = 0; i < 16; i++){
		state[i] = temp[i];
	}
	
}

void add_round_key(unsigned char* state, unsigned char* round_key) {
	for (int i = 0; i < 16; i++) {
		state[i] ^= round_key[i];
	}
}

void encryption_round(unsigned char* state, unsigned char* key) {
	s_box_substitution(state);
	shift_rows(state);
	mix_coloumns(state);
	add_round_key(state, key);
}

void final_round(unsigned char * state, unsigned char * key) {
	//No mix coloumns in final round
	s_box_substitution(state);
	shift_rows(state);
	add_round_key(state, key);
}

void encryption(unsigned char* pt, unsigned char* expanded_key, unsigned char* et) {
	unsigned char state[16]; 

	for (int i = 0; i < 16; i++){
		state[i] = pt[i];
	}
	int n = 9;
	//Add round key before first round
	add_round_key(state, expanded_key);

	for (int i=0; i<n; i++) {
		encryption_round(state, expanded_key + (16 * (i+1)));
	}

	final_round(state, expanded_key + 160);

	for (int i = 0; i < 16; i++){
		et[i] = state[i];
	}
}

unsigned char key[] = "aAbBcCdDeEfFgGhH";

int main(){
	unsigned char expanded_key[176];
	key_expansion(key, expanded_key);
	cout<<"Enter plain text: ";
	char pt[17];
	cin.getline(pt, sizeof(pt));
	unsigned char *msg = new unsigned char[16];
	
	for(int i=0;i<16;i++){
		msg[i] = pt[i];
	}
	
	unsigned char et[17];
	encryption(msg,expanded_key,et);
	
	et[16]='\0';
	cout<<"Encrypted text is : "<<et<<"\n";
	mkfifo("text_fifo",0666);
	int wfd = open("text_fifo",O_WRONLY);
	write(wfd,et,sizeof(et)+1);
}		
	
	