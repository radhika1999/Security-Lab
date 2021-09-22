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
#include<poll.h>
#include<algorithm>
#include "aes_headers.h"
using namespace std;

void subtract_round_key(unsigned char* state, unsigned char* round_key) {
	for (int i = 0; i < 16; i++){
		state[i] ^= round_key[i];
	}
}

void inverse_mix_coloumns(unsigned char* state) {

	//Using predefined tables

	unsigned char new_state[16];

	new_state[0] = (unsigned char)mul14[state[0]] ^ mul11[state[1]] ^ mul13[state[2]] ^ mul9[state[3]];
	new_state[1] = (unsigned char)mul9[state[0]] ^ mul14[state[1]] ^ mul11[state[2]] ^ mul13[state[3]];
	new_state[2] = (unsigned char)mul13[state[0]] ^ mul9[state[1]] ^ mul14[state[2]] ^ mul11[state[3]];
	new_state[3] = (unsigned char)mul11[state[0]] ^ mul13[state[1]] ^ mul9[state[2]] ^ mul14[state[3]];

	new_state[4] = (unsigned char)mul14[state[4]] ^ mul11[state[5]] ^ mul13[state[6]] ^ mul9[state[7]];
	new_state[5] = (unsigned char)mul9[state[4]] ^ mul14[state[5]] ^ mul11[state[6]] ^ mul13[state[7]];
	new_state[6] = (unsigned char)mul13[state[4]] ^ mul9[state[5]] ^ mul14[state[6]] ^ mul11[state[7]];
	new_state[7] = (unsigned char)mul11[state[4]] ^ mul13[state[5]] ^ mul9[state[6]] ^ mul14[state[7]];

	new_state[8] = (unsigned char)mul14[state[8]] ^ mul11[state[9]] ^ mul13[state[10]] ^ mul9[state[11]];
	new_state[9] = (unsigned char)mul9[state[8]] ^ mul14[state[9]] ^ mul11[state[10]] ^ mul13[state[11]];
	new_state[10] = (unsigned char)mul13[state[8]] ^ mul9[state[9]] ^ mul14[state[10]] ^ mul11[state[11]];
	new_state[11] = (unsigned char)mul11[state[8]] ^ mul13[state[9]] ^ mul9[state[10]] ^ mul14[state[11]];

	new_state[12] = (unsigned char)mul14[state[12]] ^ mul11[state[13]] ^ mul13[state[14]] ^ mul9[state[15]];
	new_state[13] = (unsigned char)mul9[state[12]] ^ mul14[state[13]] ^ mul11[state[14]] ^ mul13[state[15]];
	new_state[14] = (unsigned char)mul13[state[12]] ^ mul9[state[13]] ^ mul14[state[14]] ^ mul11[state[15]];
	new_state[15] = (unsigned char)mul11[state[12]] ^ mul13[state[13]] ^ mul9[state[14]] ^ mul14[state[15]];

	for (int i = 0; i < 16; i++){
		state[i] = new_state[i];
	}
	
}

void shift_rows(unsigned char* state) {
	unsigned char temp[16];

	//For coloumn 1
	temp[0] = state[0];
	temp[1] = state[13];
	temp[2] = state[10];
	temp[3] = state[7];

	//For coloumn 2
	temp[4] = state[4];
	temp[5] = state[1];
	temp[6] = state[14];
	temp[7] = state[11];

	//For coloumn 3
	temp[8] = state[8];
	temp[9] = state[5];
	temp[10] = state[2];
	temp[11] = state[15];

	//For coloumn 4
	temp[12] = state[12];
	temp[13] = state[9];
	temp[14] = state[6];
	temp[15] = state[3];

	for (int i=0; i<16; i++) {
		state[i] = temp[i];
	}
}

void s_box_substitution(unsigned char* state) {
	for (int i=0; i<16; i++){ 
		state[i] = inv_s[state[i]];
	}
}

void decryption_round(unsigned char* state, unsigned char* key) {
	subtract_round_key(state, key);
	inverse_mix_coloumns(state);
	shift_rows(state);
	s_box_substitution(state);
}

void first_round(unsigned char* state, unsigned char* key) {
	subtract_round_key(state, key);
	shift_rows(state);
	s_box_substitution(state);
}

void decryption(unsigned char* et, unsigned char* expanded_key, unsigned char* pt)
{
	unsigned char state[16];

	for (int i=0; i<16; i++) {
		state[i] = et[i];
	}

	first_round(state, expanded_key+160);

	int n = 9;
	for (int i = 8; i >= 0; i--) {
		decryption_round(state, expanded_key + (16 * (i + 1)));
	}

	subtract_round_key(state, expanded_key); 

	for (int i=0; i<16; i++)
		pt[i] = state[i];
}

unsigned char key[] = "aAbBcCdDeEfFgGhH";

int main(){
	
	unsigned char expanded_key[176];

	key_expansion(key, expanded_key);
	int rfd=open("text_fifo", O_RDONLY);
	unsigned char et[17];
	read(rfd,et,sizeof(et));
	et[16]='\0';
	cout<<"Encrypted text received is: "<<et<<"\n";
	unsigned char* pt = new unsigned char[17];
	
	decryption(et, expanded_key, pt);
	
	pt[16]='\0';
	cout<<"Decrpyted text is: "<<pt<<"\n";
}		
	
	