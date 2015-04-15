#include <stdio.h>
#include <stdlib.h>

const double eps = 0.001;

double abs1(double x) {
	
	return x < 0 ? -x : x;
	
}

double maxi(double x, double y) {
	return x > y : x ? y;
}	

double find_root(double x,double st,  double dr) {
	
	double mid = (st + dr) / 2;
	if(abs1(mid * mid - x) < eps)
		return mid;


	if(mid * mid > x)
		return find_root(x, st, mid);
	else
		return find_root(x, mid, dr);
}

int main() {
		
	double x; scanf("%lf" , &x);
	printf("%0.3lf\n", find_root(x, 0, maxi(1, x)));
	return 0;
}
