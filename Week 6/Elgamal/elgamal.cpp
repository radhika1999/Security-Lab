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
#include<gmp.h>
#include<random>
using namespace std;

void mulmod(mpz_t a, mpz_t b, mpz_t m, mpz_t ans){
    mpz_t x,y,two,temp;
    mpz_inits(x,y,two,temp,NULL);
    mpz_set_ui(x,0);
    mpz_set_ui(two,2);
    mpz_mod(y,a,m);
    while (mpz_cmp_si(b,0)>0){
        mpz_mod(temp,b,two);
        if(mpz_cmp_si(temp,1)==0){
            mpz_add(x,x,y);
            mpz_mod(x,x,m);
        }
        mpz_mul(y,y,two);
        mpz_mod(y,y,m);
        mpz_fdiv_q(b,b,two);
    }
    mpz_mod(ans,x,m);
}

void modulo(mpz_t base, mpz_t e, mpz_t m, mpz_t ans){
    mpz_t x,y,two,a;
    mpz_inits(x,y,two,a,NULL);
    mpz_set_ui(x,1);
    mpz_set_ui(two,2);
    mpz_set(y,base);
    while (mpz_cmp_si(e,0)>0){
        mpz_mod(a,e,two);
        if (mpz_cmp_ui(a,1)==0){
            mpz_mul(x,x,y);
            mpz_mod(x,x,m);
        }
        mpz_mul(y,y,y);
        mpz_mod(y,y,m);
        mpz_fdiv_q(e,e,two);
    }
    mpz_mod(ans,x,m);
}

int miller_rabin(mpz_t p, int k) {
    if(mpz_cmp_ui(p,2)<0){
        return 0;
    }
    mpz_t m,two,one,s,temp,a,p_1,mod,ans,temp1;
    mpz_inits(m,two,one,s,temp,a,p_1,mod,ans,temp1,NULL);
    mpz_set_ui(two,2);
    mpz_set_ui(one,1);
    mpz_mod(m,p,two);
    if (mpz_cmp_ui(p,2)!=0 && mpz_cmp_ui(m,0)==0) {
        return 0;
    }
    mpz_sub(s,p,one);
    mpz_mod(m,s,two);
    while(mpz_cmp_ui(m,0)==0){
        mpz_fdiv_q(s,s,two);
        mpz_mod(m,s,two);
    }
    for(int i=0; i<k; i++){
        long prime=mpz_get_si(p);
        long a_int=rand()%(prime-1)+1;
        mpz_set_ui(a,a_int);
        mpz_set(temp,s);
        mpz_sub(p_1,p,one);
        long val=mpz_get_si(temp);
        mpz_set_si(temp1, val);
        modulo(a, temp1, p, mod);
        while(mpz_cmp(temp,p_1)!=0 && mpz_cmp_si(mod,1)!=0 && mpz_cmp(mod,p_1)!=0){
            mulmod(mod, mod, p, ans);
            mpz_set(mod,ans);
            mpz_mul(temp,temp,two);
        }
        mpz_mod(m,temp,two);
        if(mpz_cmp(mod,p_1)!=0 && mpz_cmp_si(m,0)==0){
            return 0;
        }
    }
    return 1;
}

void generate_prime(mpz_t p, mpz_t x){
    int prime = rand()%10000;
    mpz_set_ui(p, prime);
    while(1){
        if(miller_rabin(p, 5)){
            return;
        }
        do{
            prime = rand()%10000;
        }while(mpz_cmp_ui(x, prime)>=0);  //p must be greater than message x
        mpz_set_ui(p, prime);
    }
    return;
}

void generate_num(mpz_t p, mpz_t a){
    do{
        long p_int=mpz_get_si(p);
        long a_int=rand()%(p_int-1);
        mpz_set_si(a,a_int);
    }while (mpz_cmp_ui(a, 2) < 0);
}
void modular_exponentiaion(mpz_t m, mpz_t e, mpz_t n, mpz_t ans){
    mpz_t temp;
    mpz_init(temp);
    mpz_set(temp,e);
    mpz_set_ui(ans,1);
    while(mpz_cmp_si(temp,0)!=0){
        mpz_mul(ans,ans,m);
        mpz_mod(ans,ans,n);
        mpz_sub_ui(temp,temp,1);
    }
}

void ecnryption(mpz_t x, mpz_t k, mpz_t p, mpz_t y){
    mpz_mul(y, x, k);
    mpz_mod(y, y, p);
}
void decryption(mpz_t y, mpz_t k, mpz_t p, mpz_t dt){
    mpz_t temp;
    mpz_init(temp);
    mpz_invert(temp, k, p);
    mpz_mul(dt, y, temp);
    mpz_mod(dt, dt, p);
}
int main(){
    srand(time(0));
    mpz_t x, p, alpha, a, b, A, B, k1, k2, y, dt;
    mpz_inits(x,p,alpha,a,b,A,B,k1,k2,y,dt,NULL);
    gmp_printf("Enter message x- ");
    gmp_scanf("%Zd", x);
    generate_prime(p, x);
    generate_num(p, alpha);
    gmp_printf("\nValue of prime p is: %Zd \n", p);
    gmp_printf("Value of alpha is: %Zd \n", alpha);
    
    generate_num(p, a);
    gmp_printf("\nValue of private key a is: %Zd \n", a);
    generate_num(p, b);
    gmp_printf("Value of private key b is: %Zd \n", b);    

    modular_exponentiaion(alpha,a,p,A);
    gmp_printf("\nValue of public key A is: %Zd \n", A);
    modular_exponentiaion(alpha,b,p,B);
    gmp_printf("Value of public key B is: %Zd \n", B);

    modular_exponentiaion(B,a,p,k1);
    gmp_printf("\nValue of shared key generated by A is: %Zd \n", k1);
    modular_exponentiaion(A,b,p,k2);
    gmp_printf("Value of shared key generated by B is: %Zd \n", k2);

    //Ecnryption
    ecnryption(x,k1,p,y);
    gmp_printf("\nEncrypted text y is: %Zd \n", y);
    //Decryption
    decryption(y,k2,p,dt);
    gmp_printf("Decrypted text dt is: %Zd \n", dt);
}