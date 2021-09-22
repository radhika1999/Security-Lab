#include<gmp.h>
int main(){
	mpz_t a,b,t;
	mpz_inits(a,b,t,NULL);
	gmp_printf("Enter a-");
	gmp_scanf("%Zd", a);
	gmp_printf("Enter b-");
	gmp_scanf("%Zd", b);
	if(mpz_cmp(b,a)>0){
		mpz_swap(a,b);
	}
	while(mpz_cmp_ui(b,0)!=0){
		mpz_set(t,b);
		mpz_mod(b,a,b);
		mpz_set(a,t);
	}
	gmp_printf("gcd is %Zd\n", a);
}	
