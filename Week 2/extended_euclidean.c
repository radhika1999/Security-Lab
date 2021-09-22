#include<gmp.h>

int main(){
	mpz_t a,b,r,q;
	mpz_inits(a,b,r,q,NULL);
	gmp_printf("Enter a- ");
	gmp_scanf("%Zd",a);
	gmp_printf("\nEnter b- ");
	gmp_scanf("%Zd",b);
	mpz_t ti_1, ti_2, si_1, si_2, s, t, temp;
	mpz_inits(ti_1,ti_2,si_1,si_2,s,t, temp, NULL);
	mpz_set_si(ti_1,1);
	mpz_set_si(ti_2,0);
	mpz_set_si(si_1,0);
	mpz_set_si(si_2,1);
	while(mpz_cmp_ui(b,0)!=0){
		mpz_mod(r,a,b);
		mpz_fdiv_q(q,a,b);
		mpz_set(a,b);
		mpz_set(b,r);
		mpz_mul(temp,q,si_1);
		mpz_sub(s,si_2,temp);
		mpz_mul(temp,q,ti_1);
		mpz_sub(t,ti_2,temp);
		mpz_set(si_2,si_1);
		mpz_set(si_1,s);
		mpz_set(ti_2,ti_1);
		mpz_set(ti_1,t);
	}
	gmp_printf("Gcd is %Zd \n", a);
	gmp_printf("s is %Zd \n", si_2);
	gmp_printf("t is %Zd \n", ti_2);
	if(mpz_cmp_ui(a,1)==0){
		gmp_printf("Multiplicative inverse is: %Zd \n", ti_2);
	}
	else{
		gmp_printf("Multiplicative inverse does not exsist\n");
	}
}
