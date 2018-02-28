#include <stdio.h>
#include <limits.h>

int main (){

	int a=0, b=0;
	
	scanf("%d %d", &a, &b);
	
	if( (a > 0 && b > INT_MAX - a) || (a < 0 && b < INT_MIN - a) || (b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b) || (a == 0 && b > INT_MAX - a) || (b == 0 && a < INT_MIN - b)){
		
		printf("CUIDADO.\n");
		
	}else printf("Ola MMUUndOO %d + %d = %d.\n", a, b, a+b);
	
	return 0;
	
}

