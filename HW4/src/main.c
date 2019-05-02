#include <stdio.h>
#include <string.h>
#include "scrypt.h"

int main(int argc, char *argv[])
{
    // Question b
    unsigned char *b = (unsigned char*) "secret";
    size_t size = strlen((char*) b);
    uint32_t key = 0x98267351;
    unsigned char encrypt[size], decrypt[size];

    printf("Question 4.1)b):\n");
    printf("Before Encryption: %s (0x", b);

    for(int i = 0; i < size; i++)
    {
        printf("%x", b[i]);
    }
    printf(")\n");

    sc_enc_ecb(b, encrypt, size, key);

    printf("Encrypted text: %s (0x", encrypt);

    for(int i = 0; i < size; i++)
    {
        printf("%x", encrypt[i]);
    }
    printf(")\n");

    sc_dec_ecb(encrypt, decrypt, size, key);

    printf("After Encryption: %s (0x", decrypt);

    for(int i = 0; i < size; i++)
    {
        printf("%x", decrypt[i]);
    }
    printf(")\n\n\n");


    // Question c
	unsigned char *c = (unsigned char*) "hacker";
	size = strlen((char*) c);
	unsigned char encrypt2[size], decrypt2[size];
    uint8_t iv = 0x42;

    printf("Question 4.1)c): Cypher Block Chaining Encryption:\n");
    printf("Before Encryption: %s (0x", c);

    for(int i = 0; i < size; i++)
    {
        printf("%x", c[i]);
    }
    printf(")\n");

	sc_enc_cbc(c, encrypt2, size, key, iv);

    printf("Encrypted text: %s (0x", encrypt2);

    for(int i = 0; i < size; i++)
    {
        printf("%x", encrypt2[i]);
    }
    printf(")\n");

	sc_dec_cbc(encrypt2, decrypt2, size, key, iv);
	
    printf("After Encryption: %s (0x", decrypt2);

    for(int i = 0; i < size; i++)
    {
        printf("%x", decrypt2[i]);
    }
    printf(")\n\n\n");


    // Question d
    unsigned char d[] = {0xc6, 0x5e, 0x05, 0x94, 0x6b, 0x86, 0xeb, 0x2e, 0x33, 0xf5,0x8f, 0xda, 0xff, 0x0f, 0x42};
    size = sizeof(d);
    unsigned char decrypt3[size];

    printf("Question 4.1)c): Cypher Block Chaining Decryption:\n");

    printf("Before Decryption: ");
    for(int i = 0; i < size; i++)
    {
        printf("%c", (char)d[i]);
    }
    
    printf(" (0xc65e05946b86eb2e33f58fdaff0f42)\n");
    
    sc_dec_cbc(d, decrypt3, size, key, iv);
    
    printf("After Decrypted: %s (0x", decrypt3);

    for(int i = 0; i < size; i++)
    {
        printf("%x", decrypt3[i]);
    }

	printf(")\n");

    return 0;
}   