#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "scrypt.h"

void SBox(uint8_t *m)
{
    uint8_t upper, lower;

    upper = *m >> 4;
    upper = ((upper + 1) * 7) % (16);
    upper = upper << 4;
    lower = *m << 4;
    lower = lower >> 4;
    lower = ((lower + 1) * 7) % (16);

    *m = upper;
    *m = *m | lower;
}

void InvSBox(uint8_t *c)
{
    for(int i = 0; i < 3; i++)
        SBox(c);
}


void PBox(uint8_t *m)
{
    *m = (*m >> 6) | (*m << 2) ;
}

void InvPBox(uint8_t *c)
{
    for(int i = 0; i < 3; i++)
        PBox(c);
}

uint8_t sc_enc8(uint8_t m, uint32_t k)
{
    uint8_t c;

    // Round 0
    c = m ^ (k >> 24);
    // Round 1
    SBox(&c);
    PBox(&c);
    c = c ^ (k >> 16);
    // Round 2
    SBox(&c);
    PBox(&c);
    c = c ^ (k >> 8);
    // Round 3
    SBox(&c);
    c = c ^ k;

    return c;
}

uint8_t sc_dec8(uint8_t c, uint32_t k)
{
    uint8_t m;
    
    // Round 0
    m = c ^ k;
    InvSBox(&m);
    // Round 1
    m = m ^ (k >> 8);
    InvPBox(&m);
    InvSBox(&m);
    // Round 2
    m = m ^ (k >> 16);
    InvPBox(&m);
    InvSBox(&m);
    // Round 3
    m = m ^ (k >> 24);

    return m;
}


void sc_enc_ecb(unsigned char *m, unsigned char *c, size_t len, uint32_t k)
{    
    int i = 0;
    while(len > 0)
    {
        c[i] = sc_enc8(m[i], k);
        i++; len--;
    }
}

void sc_dec_ecb(unsigned char *c, unsigned char *m, size_t len, uint32_t k)
{   
    int i = 0;
    while(len > 0)
    {
        m[i] = sc_dec8(c[i], k);
        i++; len--;
    }
}

void sc_enc_cbc(unsigned char *m, unsigned char *c, size_t len, uint32_t k, uint8_t iv)
{
    int i = 0;
    while(len > 0)
    {
		c[i] = sc_enc8(iv ^ m[i], k);
        iv = c[i];
        i++; len--;
    }
}

void sc_dec_cbc(unsigned char *c, unsigned char *m, size_t len, uint32_t k, uint8_t iv)
{
    int i = 0;
    while(len > 0)
    {
		m[i] = iv ^ sc_dec8(c[i], k);
        iv = c[i];
        i++; len--;
    }
}
