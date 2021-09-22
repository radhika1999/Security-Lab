#include<gmp.h>

int main(){
	mpz_t a,b,c;
	mpz_inits(a,b,c,NULL);
	gmp_printf("Enter a- ");
	gmp_scanf("%Zd",a);
	gmp_printf("\nEnter b- ");
	gmp_scanf("%Zd",b);
	mpz_add(c,a,b);
	gmp_printf("a + b = %Zd\n",c);
	mpz_sub(c,a,b);
	gmp_printf("a - b = %Zd\n",c);
	mpz_mul(c,a,b);
	gmp_printf("a * b = %Zd\n",c);
	mpz_fdiv_q(c,a,b);
	gmp_printf("a / b = %Zd\n",c);
	mpz_mod(c,a,b);
	gmp_printf("a % b = %Zd\n",c);
}
