extern int sum(int a, int b, int c, int d, int e, int f);
int g = 0;
int main(void)
{
	int a,b,c,d,e,f;
	a = b =c =d=e=f = 1;
	g = sum(a,b,c,d,e,f);
	return 0;
}
