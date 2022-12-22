#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "8192.h"
// #include "params.h"

#define N 8192
#define GFBITS 13
#define GFMASK ((1 << GFBITS) - 1)

// GF(2^8)
// static const unsigned short gf[N] = {0, 1, 2, 4, 8, 16, 32, 64, 128, 29, 58, 116, 232, 205, 135, 19, 38, 76, 152, 45, 90, 180, 117, 234, 201, 143, 3, 6, 12, 24, 48, 96, 192, 157, 39, 78, 156, 37, 74, 148, 53, 106, 212, 181, 119, 238, 193, 159, 35, 70, 140, 5, 10, 20, 40, 80, 160, 93, 186, 105, 210, 185, 111, 222, 161, 95, 190, 97, 194, 153, 47, 94, 188, 101, 202, 137, 15, 30, 60, 120, 240, 253, 231, 211, 187, 107, 214, 177, 127, 254, 225, 223, 163, 91, 182, 113, 226, 217, 175, 67, 134, 17, 34, 68, 136, 13, 26, 52, 104, 208, 189, 103, 206, 129, 31, 62, 124, 248, 237, 199, 147, 59, 118, 236, 197, 151, 51, 102, 204, 133, 23, 46, 92, 184, 109, 218, 169, 79, 158, 33, 66, 132, 21, 42, 84, 168, 77, 154, 41, 82, 164, 85, 170, 73, 146, 57, 114, 228, 213, 183, 115, 230, 209, 191, 99, 198, 145, 63, 126, 252, 229, 215, 179, 123, 246, 241, 255, 227, 219, 171, 75, 150, 49, 98, 196, 149, 55, 110, 220, 165, 87, 174, 65, 130, 25, 50, 100, 200, 141, 7, 14, 28, 56, 112, 224, 221, 167, 83, 166, 81, 162, 89, 178, 121, 242, 249, 239, 195, 155, 43, 86, 172, 69, 138, 9, 18, 36, 72, 144, 61, 122, 244, 245, 247, 243, 251, 235, 203, 139, 11, 22, 44, 88, 176, 125, 250, 233, 207, 131, 27, 54, 108, 216, 173, 71, 142};
// static const unsigned short fg[N] = {0, 1, 2, 26, 3, 51, 27, 199, 4, 224, 52, 239, 28, 105, 200, 76, 5, 101, 225, 15, 53, 142, 240, 130, 29, 194, 106, 249, 201, 9, 77, 114, 6, 139, 102, 48, 226, 37, 16, 34, 54, 148, 143, 219, 241, 19, 131, 70, 30, 182, 195, 126, 107, 40, 250, 186, 202, 155, 10, 121, 78, 229, 115, 167, 7, 192, 140, 99, 103, 222, 49, 254, 227, 153, 38, 180, 17, 146, 35, 137, 55, 209, 149, 207, 144, 151, 220, 190, 242, 211, 20, 93, 132, 57, 71, 65, 31, 67, 183, 164, 196, 73, 127, 111, 108, 59, 41, 85, 251, 134, 187, 62, 203, 95, 156, 160, 11, 22, 122, 44, 79, 213, 230, 173, 116, 244, 168, 88, 8, 113, 193, 248, 141, 129, 100, 14, 104, 75, 223, 238, 50, 198, 255, 25, 228, 166, 154, 120, 39, 185, 181, 125, 18, 69, 147, 218, 36, 33, 138, 47, 56, 64, 210, 92, 150, 189, 208, 206, 145, 136, 152, 179, 221, 253, 191, 98, 243, 87, 212, 172, 21, 43, 94, 159, 133, 61, 58, 84, 72, 110, 66, 163, 32, 46, 68, 217, 184, 124, 165, 119, 197, 24, 74, 237, 128, 13, 112, 247, 109, 162, 60, 83, 42, 158, 86, 171, 252, 97, 135, 178, 188, 205, 63, 91, 204, 90, 96, 177, 157, 170, 161, 82, 12, 246, 23, 236, 123, 118, 45, 216, 80, 175, 214, 234, 231, 232, 174, 233, 117, 215, 245, 235, 169, 81, 89, 176};

unsigned short gf_mlt(unsigned short x, unsigned short y)
{

	if (x == 0 || y == 0)
		return 0;

	return ((x + y - 2) % (N - 1)) + 1;
}

uint64_t gf_mul(uint64_t in0, uint64_t in1)
{
	int i;

	uint64_t tmp;
	uint64_t t0;
	uint64_t t1;
	uint64_t t;

	t0 = in0;
	t1 = in1;

	tmp = t0 * (t1 & 1);

	for (i = 1; i < GFBITS; i++)
		tmp ^= (t0 * (t1 & (1 << i)));

	//

	t = tmp & 0x1FF0000;
	tmp ^= (t >> 9) ^ (t >> 10) ^ (t >> 12) ^ (t >> 13);

	t = tmp & 0x000E000;
	tmp ^= (t >> 9) ^ (t >> 10) ^ (t >> 12) ^ (t >> 13);

	return tmp & GFMASK;
}

static inline unsigned int gf_pow(unsigned int n, unsigned int u)
{
	if (n % N == 0)
		return 1;
	return (u * n - n) % (N - 1) + 1;
}

// 繰り返し自乗法（遅い）
static inline unsigned int gf_exp(unsigned int n, unsigned int x)
{
	unsigned int ret = 1;
	while (n > 0)
	{
		if (n & 1)
			ret = gf_mlt(ret, x); // n の最下位bitが 1 ならば x^(2^i) をかける
		x = gf_mlt(x, x);
		n >>= 1; // n を1bit 左にずらす
	}
	return ret;
}

/* input: field element in */
/* return: (in^2)^2 */
static inline unsigned short gf_sq2(unsigned short in)
{
	int i;

	const uint64_t B[] = {0x1111111111111111,
						  0x0303030303030303,
						  0x000F000F000F000F,
						  0x000000FF000000FF};

	const uint64_t M[] = {0x0001FF0000000000,
						  0x000000FF80000000,
						  0x000000007FC00000,
						  0x00000000003FE000};

	uint64_t x = in;
	uint64_t t;

	x = (x | (x << 24)) & B[3];
	x = (x | (x << 12)) & B[2];
	x = (x | (x << 6)) & B[1];
	x = (x | (x << 3)) & B[0];

	for (i = 0; i < 4; i++)
	{
		t = x & M[i];
		x ^= (t >> 9) ^ (t >> 10) ^ (t >> 12) ^ (t >> 13);
	}

	return x & GFMASK;
}

/* input: field element in, m */
/* return: (in^2)*m */
static inline unsigned short gf_sqmul(unsigned short in, unsigned short m)
{
	int i;

	uint64_t x;
	uint64_t t0;
	uint64_t t1;
	uint64_t t;

	const uint64_t M[] = {0x0000001FF0000000,
						  0x000000000FF80000,
						  0x000000000007E000};

	t0 = in;
	t1 = m;

	x = (t1 << 6) * (t0 & (1 << 6));

	t0 ^= (t0 << 7);

	x ^= (t1 * (t0 & (0x04001)));
	x ^= (t1 * (t0 & (0x08002))) << 1;
	x ^= (t1 * (t0 & (0x10004))) << 2;
	x ^= (t1 * (t0 & (0x20008))) << 3;
	x ^= (t1 * (t0 & (0x40010))) << 4;
	x ^= (t1 * (t0 & (0x80020))) << 5;

	for (i = 0; i < 3; i++)
	{
		t = x & M[i];
		x ^= (t >> 9) ^ (t >> 10) ^ (t >> 12) ^ (t >> 13);
	}

	return x & GFMASK;
}

/* input: field element in, m */
/* return: ((in^2)^2)*m */
static inline unsigned short gf_sq2mul(unsigned short in, unsigned short m)
{
	int i;

	uint64_t x;
	uint64_t t0;
	uint64_t t1;
	uint64_t t;

	const uint64_t M[] = {0x1FF0000000000000,
						  0x000FF80000000000,
						  0x000007FC00000000,
						  0x00000003FE000000,
						  0x0000000001FE0000,
						  0x000000000001E000};

	t0 = in;
	t1 = m;

	x = (t1 << 18) * (t0 & (1 << 6));

	t0 ^= (t0 << 21);

	x ^= (t1 * (t0 & (0x010000001)));
	x ^= (t1 * (t0 & (0x020000002))) << 3;
	x ^= (t1 * (t0 & (0x040000004))) << 6;
	x ^= (t1 * (t0 & (0x080000008))) << 9;
	x ^= (t1 * (t0 & (0x100000010))) << 12;
	x ^= (t1 * (t0 & (0x200000020))) << 15;

	for (i = 0; i < 6; i++)
	{
		t = x & M[i];
		x ^= (t >> 9) ^ (t >> 10) ^ (t >> 12) ^ (t >> 13);
	}

	return x & GFMASK;
}

/* input: field element den, num */
/* return: (num/den) */
unsigned short gf_frac(unsigned short den, unsigned short num)
{
	unsigned short tmp_11;
	unsigned short tmp_1111;
	unsigned short out;

	tmp_11 = gf_sqmul(den, den);		  // ^11
	tmp_1111 = gf_sq2mul(tmp_11, tmp_11); // ^1111
	out = gf_sq2(tmp_1111);
	out = gf_sq2mul(out, tmp_1111); // ^11111111
	out = gf_sq2(out);
	out = gf_sq2mul(out, tmp_1111); // ^111111111111

	return gf_sqmul(out, num); // ^1111111111110 = ^-1
}

unsigned short gf_inv(unsigned short den)
{
	return gf_frac(den, ((unsigned short)1));
}

// 有限体の元の逆数
unsigned short
oinv(unsigned short a)
{
	int i;

	if (a == 0)
		return 0;

	return N - fg[a] + 1;

	printf("no return \n");

	exit(1);
}

uint16_t g_mul(uint16_t in0, uint16_t in1)
{
	int i;

	uint32_t tmp;
	uint32_t t0;
	uint32_t t1;
	uint32_t t;

	t0 = in0;
	t1 = in1;

	tmp = t0 * (t1 & 1);

	for (i = 1; i < GFBITS; i++)
		tmp ^= (t0 * (t1 & (1 << i)));

	t = tmp & 0x7FC000;
	tmp ^= t >> 9;
	tmp ^= t >> 12;

	t = tmp & 0x3000;
	tmp ^= t >> 9;
	tmp ^= t >> 12;

	return tmp & ((1 << GFBITS) - 1);
}

int main()
{
	unsigned long long int i;

	for (i = 0; i < 10000000000; i++)
	{
		// printf("%d %d\n",gf_inv(i%N),gf[oinv(i%N)]);
		// printf("%d %d\n",
		// gf[gf_mlt(oinv(123),fg[456])];
		// gf_frac(123,456);
		gf[oinv(1234)];
		// gf_inv(1234);
		// printf("%d\n",
		// g_mul(333,222);
		// printf("%d\n",
		// gf[gf_mlt(fg[333],fg[222])];
	}
}
// 10000000000
// inv
// inv
// mul
// mul 0m28.880s
