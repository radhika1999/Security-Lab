#include<gmp.h>
int main(){
	mpz_t a,b;
	mpz_inits(a,b,NULL);
	gmp_printf("Enter a- ");
	gmp_scanf("%Zd", a);
	gmp_printf("Enter b- ");
	gmp_scanf("%Zd", b);
	if(mpz_cmp(a,b)>0){
		gmp_printf("a greater than b\n");
	}
	else if(mpz_cmp(a,b)==0){
		gmp_printf("a is equal to b\n");
	}
	else{
		gmp_printf("b greater than a\n");
	}
}
