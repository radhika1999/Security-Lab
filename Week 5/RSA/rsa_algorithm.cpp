#include<gmp.h>
#include<random>
#include<iostream>
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

void generate_prime(mpz_t p){
	int prime = rand()%10000;
	mpz_set_ui(p, prime);
	while(1){
		if(miller_rabin(p, 5)){
			return;
		}
		prime = rand()%10000;
		mpz_set_ui(p, prime);
	}
	return;
}

void generate_e(mpz_t phi, mpz_t e){
	mpz_t temp;
	mpz_init(temp);
	do{
		long phi_int=mpz_get_si(phi);
		long e_int=rand()%(phi_int);
		mpz_set_si(e,e_int);
		mpz_gcd(temp, phi, e); //temp=gcd(e,phi)
	}while (mpz_cmp_ui(temp, 1) != 0);
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

int main(){
	mpz_t m, p, q, n, phi, e, d, c, dc,temp1,temp2;
	mpz_inits(m,p,q,n,phi,e,d,c,dc,temp1,temp2,NULL);
	gmp_printf("Enter message m- ");
	gmp_scanf("%Zd", m);
	generate_prime(p);
	generate_prime(q);
	gmp_printf("Value of p is: %Zd \n", p);
	gmp_printf("Value of q is: %Zd \n", q);
	mpz_mul(n,p,q);
	gmp_printf("Value of n is: %Zd \n", n);

	mpz_sub_ui(temp1, q, 1); //temp1=q-1
	mpz_sub_ui(temp2, p, 1); //temp2=p-1
    //phi=(p-1)(q-1)
    mpz_mul(phi, temp1, temp2);
    gmp_printf("Value of phi is: %Zd \n", phi);
    generate_e(phi, e);
    gmp_printf("Value of e is: %Zd \n", e);
    // extended Euclidean
    mpz_invert(d, e, phi);
    gmp_printf("Value of d is: %Zd \n", d);
    modular_exponentiaion(m,e,n,c);
    gmp_printf("Encrypted text c is: %Zd \n", c);
    modular_exponentiaion(c,d,n,dc);
    gmp_printf("Decrypted text dc is: %Zd \n", dc);
}