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

string decimal_to_binary(int n){
	string s="0000";
	int i=3;
	while(n>0){
		if(n%2==0){
			s[i]='0';
		}
		else{
			s[i]='1';
		}
		n/=2;
		i--;
	}
	return s;
}
int binary_to_decimal(string s){
	int l=s.length();
	int p=1;
	int n=0;
	for(int i=l-1;i>=0;i--){
		n=n+(s[i]-'0')*p;
		p=p*2;
	}
	return n;
}
string remove_parity_from_key(string key){
	int pc1[56] = { 
	57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18, 
	10, 2, 59, 51, 43, 35, 27, 
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4 
	};
	string key_without_parity;
	for(int i=0;i<56;i++){
		key_without_parity+=key[pc1[i]-1];
	}
	return key_without_parity;
}
string pc2(string k){
	int pc2[] = {
	14, 17, 11, 24, 1, 5, 3, 28,
	15, 6, 21, 10, 23, 19, 12, 4,
	26, 8, 16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55, 30, 40,
	51, 45, 33, 48, 44, 49, 39, 56,
	34, 53, 46, 42, 50, 36, 29, 32
	};
	string new_k="";
	for(int i=0;i<48;i++){
		new_k+=k[pc2[i]-1];
	}
	return new_k;
}
string initial_permutation(string pt){
	int ip[] = {
	58 ,50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
	};
	string pt_after_ip="";
	for(int i=0;i<64;i++){
		pt_after_ip+=pt[ip[i]-1];
	}
	return pt_after_ip;
}
string final_permutation(string pt_16){
	int ip_1[] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25
	};
	string et="";
	for(int i=0;i<64;i++){
		et+=pt_16[ip_1[i]-1];
	}
	return et;
}
string expansion(string r){
	int e[] = {
	32, 1, 2, 3, 4, 5,
	4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1
	};
	string expanded_r="";
	for(int i=0;i<48;i++){
		expanded_r+=r[e[i]-1];
	}
	return expanded_r;
}
string xor_operation(string r, string k){
	string result="";
	for(int i=0;i<48;i++){
		if(r[i]==k[i]){
			result+="0";
		}
		else{
			result+="1";
		}
	}
	return result;
}
string s_box(string r){
	int s1[4][16] = {
	{ 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7}, 
	{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8}, 
	{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0}, 
	{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
	};
	int s2[4][16] = {
	{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
	{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
	{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
	{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
	};
	int s3[4][16] = {
	{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
	{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
	{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
	{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
	};
	int s4[4][16] = {
	{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
	{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
	{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
	{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
	};
	int s5[4][16] = {
	{2, 12, 4, 01, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
	{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
	{4, 2, 01, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
	{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
	};
	int s6[4][16] = {
	{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
	{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
	{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
	{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
	};
	int s7[4][16] = {
	{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
	{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
	{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
	{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
	};
	int s8[4][16] = {
	{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
	{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
	{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
	{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
	};
	int part=1;
	string new_r="";
	for(int i=0;i<48;i+=6){
		string ri=r.substr(i,6);
		string row=string(1,ri[0])+string(1,ri[5]);
		string col=ri.substr(1,4);
		// cout<<"row: "<<row<<endl;
		// cout<<"col: "<<col<<endl;
		int rown=binary_to_decimal(row);
		int coln=binary_to_decimal(col);
		// cout<<"rown: "<<rown<<endl;
		// cout<<"coln: "<<coln<<endl;
		if(part==1){
			int n=s1[rown][coln];
			new_r+=decimal_to_binary(n);
			// cout<<"n: "<<n<<endl;
			// cout<<"new_r: "<<new_r<<endl;
		}
		else if(part==2){
			int n=s2[rown][coln];
			new_r+=decimal_to_binary(n);
		}
		else if(part==3){
			int n=s3[rown][coln];
			new_r+=decimal_to_binary(n);
		}
		else if(part==4){
			int n=s4[rown][coln];
			new_r+=decimal_to_binary(n);
		}
		else if(part==5){
			int n=s5[rown][coln];
			new_r+=decimal_to_binary(n);
		}
		else if(part==6){
			int n=s6[rown][coln];
			new_r+=decimal_to_binary(n);
		}
		else if(part==7){
			int n=s7[rown][coln];
			new_r+=decimal_to_binary(n);
		}
		else if(part==8){
			int n=s8[rown][coln];
			new_r+=decimal_to_binary(n);
		}
		part++;
	}
	return new_r;
}
string permutation_p(string r){
	int p[] = {
	16, 7, 20, 21, 29, 12, 28, 17,
	1, 15, 23, 26, 5, 18, 31, 10,
	2, 8, 24, 14, 32, 27, 3, 9,
	19, 13, 30, 6, 22, 11, 4, 25,
	};
	string new_r="";
	for(int i=0;i<32;i++){
		new_r+=r[p[i]-1];
	}
	return new_r;
}
string f(string r, string k){
	//1. Performing expansion
	string expanded_r=expansion(r);
	//2. R_i XOR K_i
	string r_xor_k=xor_operation(expanded_r, k);
	//3. Pass through S Box
	string r_32_bit=s_box(r_xor_k);
	//4. Perform permutation p
	string r_final=permutation_p(r_32_bit);
	return r_final;
}

string right_shift_1(string s){
	string ans=s;
	char last=s[s.length()-1];
	for(int i=1;i<s.length();i++){
		ans[i]=s[i-1];
	}
	ans[0]=last;
	return ans;
}
string right_shift_2(string s){
	string ans=s;
	char last=s[s.length()-1];
	char second_last=s[s.length()-2];
	for(int i=2;i<s.length();i++){
		ans[i]=s[i-2];
	}
	ans[1]=last;
	ans[0]=second_last;
	return ans;
}
int main(){
	string key, et;
	cout<<"Enter key: ";
	cin>>key;
	char et1[1024];
	int rfd=open("text_fifo", O_RDONLY);
	read(rfd, et1, 100);
	et=et1;
	et=initial_permutation(et);
	string l=et.substr(0,32);
	string r=et.substr(32,32);
	string key1=remove_parity_from_key(key);
	string c=key1.substr(0,28);
	string d=key1.substr(28,28);
	for(int i=1;i<=16;i++){
		if(i==1){
			;
		}
		else if(i==2||i==9||i==16){
			c=right_shift_1(c);
			d=right_shift_1(d);
		}
		else{
			c=right_shift_2(c);
			d=right_shift_2(d);
		}
		string k_i=c+d;
		k_i=pc2(k_i);
		cout<<"k "<<i<<" : "<<k_i<<endl;
		string new_r=f(r,k_i);
		new_r=xor_operation(new_r, l);
		l=r;
		r=new_r;
		cout<<"l "<<i<<" : "<<l.substr(0,32)<<endl;
		cout<<"r "<<i<<" : "<<r.substr(0,32)<<endl;
	}
	//Swapping L_16 and R_16
	string temp=r.substr(0,32)+l.substr(0,32);
	string pt=final_permutation(temp);
	cout<<"Decrypted text is: "<<pt<<endl;
}