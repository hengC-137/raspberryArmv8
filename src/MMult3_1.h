#include <stdio.h>

#define A(i,j) a[ (i)*lda + (j) ]
#define B(i,j) b[ (i)*ldb + (j) ]
#define C(i,j) c[ (i)*ldc + (j) ]


/* Create macro to let X( i ) equal the ith element of x */

#define Y(i) y[ (i)*incx ]

void AddDot( int k, float *x, int incx,  float *y, float *gamma )
{
    /* compute gamma := x' * y + gamma with vectors x and y of length n.
        Here x starts at location x with increment (stride) incx and y starts at location y and has (implicit) stride of 1.
    */
    
    int p;

    for ( p=0; p<k; p++ ){
	//printf("A = %f   B = %f \n", *(x), *(y));
        *gamma += (*x) * (*y);
        x ++;
        y += incx;     
    }
}

/* Routine for computing C = A * B + C */

void AddDot1x4( int k, float *a, int lda,  float *b, int ldb, float *c, int ldc )
{
    /* So, this routine computes four elements of C: 
            C( 0, 0 ), C( 0, 1 ), C( 0, 2 ), C( 0, 3 ).  
        Notice that this routine is called with c = C( i, j ) in the
        previous routine, so these are actually the elements 
            C( i, j ), C( i, j+1 ), C( i, j+2 ), C( i, j+3 ) 
        
        in the original matrix C */ 
    
    AddDot( k, &A( 0, 0 ), lda, &B( 0, 0 ), &C( 0, 0 ) );
    AddDot( k, &A( 0, 0 ), lda, &B( 0, 1 ), &C( 0, 1 ) );
    AddDot( k, &A( 0, 0 ), lda, &B( 0, 2 ), &C( 0, 2 ) );
    AddDot( k, &A( 0, 0 ), lda, &B( 0, 3 ), &C( 0, 3 ) );
}

void MY_MMult_1x4_3( int m, int n, int k, float *a, int lda, 
                                    float *b, int ldb,
                                    float *c, int ldc )
{
    //printf("3_1\n");
    int i, j;
    float *pb = b;
    for ( j=0; j<n; j+=4 ){        /* Loop over the columns of C, unrolled by 4 */
        float *pc = (c + j);
    	float *pa = a;
        for ( i=0; i<m; i+=1 ){        /* Loop over the rows of C */
            /* Update C( i,j ), C( i,j+1 ), C( i,j+2 ), and C( i,j+3 ) in
            one routine (four inner products) */

            //printf("C row = %d, col = %d\n", i, j);

            AddDot1x4( k, pa, lda, pb, ldb, pc, ldc );
            pa += lda;
            pc += ldc;
        }
        pb += 4;
    }
}