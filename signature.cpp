

#include <stdlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


#include "uECC.h"


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


void to_string(uint8_t arr[], char* str) {
	/* à compléter */
}

void from_string(char* str, uint8_t arr[]){
	/* à compléter */
}

void generatePairKey(char private[], char public[]){

	uint8_t privateKeyInt[32];
	uint8_t publicKeyInt[64];

	uECC_make_key(publicKeyInt, privateKeyInt,curves[rand()%5]);

	to_string(publicKeyInt, public);
	to_string(privateKeyInt, private);
}


void sign(char private[], char hash[], char signature[]){
	
	uint8_t privateKeyInt[32];
	uint8_t hashInt[32];
	uint8_t sigInt[64];

	from_string(private,privateKeyInt);
	from_string(hash, hashInt);

	uECC_sign(privateKeyInt, hashInt, sizeof(hashInt), sigInt, curves[rand()%5]);

	to_string(sigInt, signature);
}

bool verify(char public[], char hash[], char signature[]){

	uint8_t publicKeyInt[64];
	uint8_t hashInt[32];
	uint8_t sigInt[64];

	from_string(public, publicKeyInt);
	from_string(hash, hashInt);

	if(uECC_verify(publicKeyInt, hashInt, sizeof(hashInt), sigInt, curves[rand()%5])){
		to_string(sigInt, signature);
		return true;
	}
	else{
		return false;
	}
}




