/*
 *	main.c    -     demo of led api
 *	
 *	Author: 	li ming <admin@lumit.org>
 *	Date:		2005-6-3
 *	Copyleft:	http://www.lumit.org
 */

char a;
short b;
char c;
int d;


char a2;
char c2;
short b2;
int d2;

int f(void);
int g(void); // f()和 g()不访问全局变量errs
int errs; // 全局变量

int f( void )
{
	return 1;
}

int g( void )
{
	return 2;
}

void test1(void)
{ 
	errs += f();
	errs += g();
}

void test2(void)
{ 
	int localerrs = errs; // 定义冗余的局部变量
	localerrs += f();
	localerrs += g();
	errs = localerrs;
}

int wordinc( int a )
{
	return a+1;
}

short shortinc( short a )
{
	return a+1;
}

char charinc( char a )
{
	return a+1;
}

int param( int a1, int a2, int a3, int a4 )
{
	return a1+a2+a3+a4;	
}	

int param2( int a1, int a2, int a3, int a4, int a5 )
{
	return a1+a2+a3+a4+a5;	
}	
 

int fact1( int limit )
{
	int fact = 1;
	int i = 1;
	
	while( i++ < limit )
	{
		fact = fact * i;			
	}	
	
	return fact;
}


int fact2( int limit )
{
	int fact = 1;
	int i = limit;
	
	while( --i )
	{
		fact = fact * i;			
	}	
	
	return fact;
}

int main( void )
{
	a = 1;
	b = 2;
	c = 3;
	d = 4;
	
	a2 = 11;
	b2 = 22;
	c2 = 33;
	d2 = 44;
	
	test1();
	
	test2();

	param( a, b, c, d );
	
	param2( a, b, c, d, a2 );
		
	return 0;
}


void __rt_entry( void )
{
	main();	
}
