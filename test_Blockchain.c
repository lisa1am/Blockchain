/* Copyright 2014, Kenneth MacKay. Licensed under the BSD 2-clause license. */

#include "uECC.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
 





void vli_print(char *str, uint8_t *vli, unsigned int size) {
    printf("%s ", str);
    for(unsigned i=0; i<size; ++i) {
        printf("%02X ", (unsigned)vli[i]);
    }
    printf("\n");
}



int main() {
    int i;
    int success;
    uint8_t private[32], private2[32];
    uint8_t public[64], public2[64];
    uint8_t public_computed[64];
    
    int c;
    
    const struct uECC_Curve_t * curves[5];
    int num_curves = 0;
#if uECC_SUPPORTS_secp160r1
	curves[num_curves++] = uECC_secp160r1();
#endif
#if uECC_SUPPORTS_secp192r1
    curves[num_curves++] = uECC_secp192r1();
#endif
#if uECC_SUPPORTS_secp224r1
    curves[num_curves++] = uECC_secp224r1();
#endif
#if uECC_SUPPORTS_secp256r1
    curves[num_curves++] = uECC_secp256r1();
#endif
#if uECC_SUPPORTS_secp256k1
    curves[num_curves++] = uECC_secp256k1();
#endif

   
    	
    printf("********GENERATE**********\n");
    srand(time(0));
	uECC_make_key(public, private,curves[rand()%5]);
    uECC_make_key(public2, private2, curves[3]);
    i=0;
    printf("\nPrivate = \n");
	for(i=0; i<32;i++){
                printf("%hhu", private[i]);
    }
    printf("\nTO_STRING -------------------->\n");

   

    printf("\n");




        i=0;
	printf("\nPublic = ");
        for(i=0; i<64;i++){
                printf("%hhu", public[i]);
        }
	printf("\n");

        uECC_compute_public_key(private, public_computed, curves[3]);
	i=0;
	printf("\nCompted public = ");
        for(i=0; i<64;i++){
                printf("%hhu", public_computed[i]);
        }

	printf("\n");

	uint8_t sig[64];
	
	uint8_t hash[32];
	printf("\nHASH = ");
	memcpy(hash, public, sizeof(hash));
	for(i=0; i<32; i++){
                printf("%hhu",hash[i]);
        }

	printf("\n");

	uECC_sign(private, hash, sizeof(hash), sig, curves[3]);
	printf("\nSiganture=");
	for(i=0; i<32; i++){
		printf("%hhu",sig[i]);
	}

	printf("\n");

	if(uECC_verify(public2, hash, sizeof(hash), sig, curves[3])){
		printf("\nSIGNATURE VERIFIEE !\n");
	}
	else{
		printf("\nSIGNATURE FAKE !\n");
	}



    return 0;
}
