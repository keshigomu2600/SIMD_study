// libgeom.cpp : スタティック ライブラリ用の関数を定義します。
//
#include "pch.h"
#include <intrin.h>
#include "../include/libgeom.h"

// 4つのfloat が num個の配列をsrcからdstにコピー
void copy_vector4_array(float* dst, const float* src, int num)
{
#if 1
	// ToDo: SIMD計算を使って実装して下さい
	float* pd = dst;
	const float* ps = src;

	for (int i = 0; i < num * 4; i += 4)
	{
		__m128 a = _mm_loadr_ps((ps + i));

		_mm_storer_ps((pd + i), a);
	}
#else
	float* pd = dst;
	const float* ps = src;

	for (int i = 0; i < num; i++) {
		pd[0] = ps[0];
		pd[1] = ps[1];
		pd[2] = ps[2];
		pd[3] = ps[3];

		pd += 4;
		ps += 4;
	}
#endif
}

// 4つのfloat が num個の配列 src0, src1を足してdstに出力
void add_vector4_array(float* dst, const float* src0, const float* src1, int num)
{
#if 1
	// ToDo: SIMD計算を使って実装して下さい
	float* pd = dst;
	const float* ps0 = src0;
	const float* ps1 = src1;

	for (int i = 0; i < num * 4; i += 4)
	{
		__m128 a = _mm_loadr_ps((ps0 + i));
		__m128 b = _mm_loadr_ps((ps1 + i));

		a = _mm_add_ps(a, b);

		_mm_storer_ps((pd + i), a);
	}

#else
	float* pd = dst;
	const float* ps0 = src0;
	const float* ps1 = src1;

	for (int i = 0; i < num; i++) {
		pd[0] = ps0[0] + ps1[0];
		pd[1] = ps0[1] + ps1[1];
		pd[2] = ps0[2] + ps1[2];
		pd[3] = ps0[3] + ps1[3];

		pd += 4;
		ps0 += 4;
		ps1 += 4;
	}
#endif
}

// 4つのfloat に num個の配列 src にmatrix[4][4] の行列を掛けてdstに出力
void apply_matrix_vector4_array(float* dst, const float* src, const float* matrix, int num)
{
#if 1
	// ToDo: SIMD計算を使って実装して下さい
	float* pd = dst;
	const float* ps = src;

	__m128 b0n, b1n, b2n, b3n;
	b0n = _mm_load_ps(ps);
	b1n = _mm_load_ps(ps + 1);
	b2n = _mm_load_ps(ps + 2);
	b3n = _mm_load_ps(ps + 3);

	for (int i = 0; i < num * 4; i += 4)
	{
		__m128 ai0, ai1, ai2, ai3;
		ai0 = _mm_broadcast_ss(matrix + 4 * i);
		ai1 = _mm_broadcast_ss(matrix + 4 * i + 1);
		ai2 = _mm_broadcast_ss(matrix + 4 * i + 2);
		ai3 = _mm_broadcast_ss(matrix + 4 * i + 3);

		ai0 = _mm_mul_ps(ai0, b0n);
		ai0 = _mm_fmadd_ps(ai1, b1n, ai0); // ai0 = ai1 .* b1n + ai0
		ai0 = _mm_fmadd_ps(ai2, b2n, ai0);
		ai0 = _mm_fmadd_ps(ai3, b3n, ai0);
		_mm_store_ps(pd + i, ai0);
	}
#else
	float* pd = dst;
	const float* ps = src;

	for (int i = 0; i < num; i++) {
		pd[0] = matrix[4*0+0]*ps[0] + matrix[4*0+1]*ps[1] + matrix[4*0+2]*ps[2] + matrix[4*0+3]*ps[3];
		pd[1] = matrix[4*1+0]*ps[0] + matrix[4*1+1]*ps[1] + matrix[4*1+2]*ps[2] + matrix[4*1+3]*ps[3];
		pd[2] = matrix[4*2+0]*ps[0] + matrix[4*2+1]*ps[1] + matrix[4*2+2]*ps[2] + matrix[4*2+3]*ps[3];
		pd[3] = matrix[4*3+0]*ps[0] + matrix[4*3+1]*ps[1] + matrix[4*3+2]*ps[2] + matrix[4*3+3]*ps[3];

		pd += 4;
		ps += 4;
	}
#endif
}
