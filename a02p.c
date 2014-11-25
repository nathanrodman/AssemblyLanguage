// starter file for Assignment 2p

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// function for checking that your assembly code is computing the correct result
double quadraticRootC(double a, double b, double c)
{
	return (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
}

double quadraticRoot(double a, double b, double c)
{
	double root;
	// write assembly code below to calculate the quadratic root
	asm(
		"	fldl	%[a]		\n" // st0 = a
		"	fld		%%st		\n" // st0 = a, st1 = a
		"	faddp				\n"	// st0 = 2a
		"	fstpl	%[a]		\n" // a = 2a
		"	fldl	%[c]		\n" // st0 = c
		"	fld		%%st		\n" // st1 = c, st2 = c
		"	faddp				\n" // st0 = 2c
		"	fldl	%[a]		\n" // st0 = 2a, st1 = 2c
		"	fmulp				\n" // st0 = 4ac
		"	fldl	%[b] 		\n" // st0 = b, st1 = 4ac
		"	fld 	%%st		\n" // st0 = b, st1 = b, st2 = 4ac
		"	fmulp				\n" // st0 = b^2, st1 = 4ac
		"	fsubp				\n" // st0 = b^2 - 4ac
		"	fsqrt				\n" // st0 = sqrt(b^2 - 4ac)
		"	fldl	%[b]		\n" // st0 = sqrt(b^2 - 4ac), st1 = b
		"	fsubrp				\n" // st0 = -b + sqrt(b^2 - 4ac)
		"	fldl	%[a]		\n" // st0 = 2a, st1 = -b + sqrt(b^2 - 4ac)
		"	fdivrp				\n" // st0 = (-b + sqrt(b^2 - 4ac))/2a
		"	fstpl	%[root]		\n"
		:	[root]	"=m"	(root)		// outputs
		: 	[a]		"m"		(a),
			[b]		"m"		(b),
			[c]		"m"		(c)			// inputs
		:	"eax", "ebx", "ecx"			//clobbers
	);

	return root;
}

// do not change this function, except to print your own name
int main(int argc, char **argv)
{
	double	a, b, c;
	double	root, rootC;

	printf("CS201 - Assignment 2p - Nathan Rodman\n");	// print your own name instead
	if (argc != 4) {
		printf("need 3 arguments: a, b, c\n");
		return -1;
		}
	a = atof(argv[1]);
	b = atof(argv[2]);
	c = atof(argv[3]);
	root = quadraticRoot(a, b, c);
	rootC = quadraticRootC(a, b, c);

	printf("quadraticRoot(%.3f, %.3f, %.3f) = %.3f, %.3f\n", a, b, c, root, rootC);

	return 0;
}
