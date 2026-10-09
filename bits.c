/* 
 * CS:APP Data Lab 
 * 
 * <Sixian Zhang 25303050005>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~(~x & y) & ~(x & ~y));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int sign = x >> 31;
  int neg = ~x + 1;
  return sign & neg;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int srcShift = src << 3;
  int dstShift = dst << 3;
  // 通过移位运算将两数字乘8
  int srcByte = (x >> srcShift) & 0xFF;
  // 提取源字节
  int mask = 0xFF << dstShift;
  // 构造目标字节空段
  return (x & ~mask) | (srcByte << dstShift);
  // 补齐原数其他段，并将源字节段放在目标字节空段
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  return ~(((1 << 31) >> n) << 1) & (x >> n);
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int maskF0 = 0xF0 | (0xF0 << 8);
  maskF0 = maskF0 | (maskF0 << 16);

  int mask0F = 0x0F | (0x0F << 8);
  mask0F = mask0F | (mask0F << 16);

  int highToLow = ((x & maskF0) >> 4) & mask0F;
  int lowToHigh = (x & mask0F) << 4;

  return highToLow | lowToHigh;
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int zeros = ~x;
  int lowestZero = zeros & (~zeros + 1);
  // 得到第一低位的0
  int remaining = zeros ^ lowestZero;
  // 去掉第一低位的0
  return remaining & (~remaining + 1);
  // 得到第二低位的0
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  // 利用异或折半法计算奇偶校验
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int right = (x >> n) & ~(((1 << 31) >> n) << 1);
  int left = x << ((~n + 1) & 31);
  return left | right;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int mask = (1 << n) + ~0;
  // + ~0 相当于 - 1
  int remainder = x & mask;
  // 得到余数
  int half = 1 << (n + ~0);
  // 得到中间数
  int quotient = x >> n;
  // 得到暂定商，商的最低位可表示其奇偶性

  // 判断进位条件：对half和remainder进行比较
  int belowHalf = (remainder + ~half) >> 31;
  // 如果余数小于中间数，则belowHalf为-1
  int equal = !(remainder ^ half);
  // 如果余数等于中间数，则equal为1
  int odd = quotient & 1;
  // 判断商是否为奇数

  int increment = (!belowHalf & !equal) | (equal & odd);
  // 余数大于中间数，或余数等于中间数且商为奇数时进位
  return (quotient + increment) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int halfx = x >> 1;
  int halfy = y >> 1;
  // 不直接加防止溢出
  int lowx = x & 1;
  int lowy = y & 1;
  // 得到低位，用于判断奇偶性

  int floormid = halfx + halfy + ((lowx + lowy) >> 1);
  int odd = lowx ^ lowy;
  // 判断低位是否为奇数

  int signsDiffer = (x ^ y) >> 31;
  // 判断符号是否不同, 相同为0，不同为-1
  int xNonnegative = !(x >> 31);
  // 判断x是否非负，非负为1，负为0
  int xGreaterSameSign = !((x + (~y + 1)) >> 31) & !!(x ^ y);
  // 判断在符号相同的情况下x是否大于y，x大于y为1，否则为0

  int xGreater = (signsDiffer & xNonnegative) | (~signsDiffer & xGreaterSameSign);
  // 判断x是否大于y，综合符号不同和符号相同的情况
  return floormid + (odd & xGreater);
  // 返回向下取整的中点加上根据奇偶性和大小判断的进位
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */

int isBetweenEitherOrder(int x, int a, int b) {
  int xa = x + (~a + 1);  // x - a
  int xb = x + (~b + 1);  // x - b

  int sx = x >> 31;
  int sa = a >> 31;
  int sb = b >> 31;

  // x-a / x-b 溢出时，真实差值符号由 x 的符号决定
  int overflowA = (sx ^ sa) & ((xa >> 31) ^ sx);
  int overflowB = (sx ^ sb) & ((xb >> 31) ^ sx);

  int signA = (overflowA & sx) | (~overflowA & (xa >> 31));
  int signB = (overflowB & sx) | (~overflowB & (xb >> 31));

  int opposite = (signA ^ signB) & 1;
  int equalA = !(xa ^ 0);
  int equalB = !(xb ^ 0);

  return opposite | equalA | equalB;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
    // 逐步计算 2x、4x、5x
    int twice = x + x;
    int four = twice + twice;
    int five = four + x;

    // 任一步出现符号变化，说明发生溢出
    // 溢出时得到 -1，否则为 0
    int overflow =
        ((x ^ twice) | (twice ^ four) | (four ^ five)) >> 31;

    // 根据输入符号选择 INT_MAX 或 INT_MIN
    int sign = x >> 31;
    int saturation = ~(1 << 31) ^ sign;

    // 溢出时返回饱和值，否则返回 5x
    return (overflow & saturation) | (~overflow & five);
}


// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int sx = x >> 31;
  int sy = y >> 31;
  // 得到两数符号位
  int res1 = x + y;
  int sr1 = res1 >> 31;
  // 得到和符号位

  // 溢出情况判断方法：当两个操作数符号相同且与结果符号不同，则发生溢出
  int pos1 = (~sx & ~sy & sr1) & 1;
  int neg1 = (sx & sy & ~sr1) & 1;
  // 判断第一次和溢出情况
  int ovf1 = pos1 + (~neg1 + 1);

  int sz = z >> 31;
  // 得到第三个操作数符号位
  int res2 = res1 + z;
  int sr2 = res2 >> 31;
  // 得到第二次和符号位

  int pos2 = (~sr1 & ~sz & sr2) & 1;
  int neg2 = (sr1 & sz & ~sr2) & 1;
  // 判断第二次和溢出情况
  int ovf2 = pos2 + (~neg2 + 1);

  int k = ovf1 + ovf2;
  // 根据两次溢出情况计算最终的溢出标志

  int isPos = ~((k + ~0) >> 31) & 1;
  int isNeg = (k >> 31) & 1;
  return isPos + (~isNeg + 1);
  // 按照最终的溢出情况进行输出
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
    unsigned sign = uf & 0x80000000u;
    unsigned exp = (uf >> 23) & 0xffu;
    unsigned frac = uf & 0x7fffffu;

    // NaN 和无穷保持原位模式
    if (exp == 0xffu)
        return uf;

    // 正负零保持符号
    if (exp == 0 && frac == 0)
        return uf;

    // m * 2^k 表示输入绝对值
    unsigned m = frac | (exp ? 0x800000u : 0u);
    int k = exp ? exp - 150 : -149;

    // 结果精确表示为 (3*m) * 2^(k-1)
    unsigned n = 3u * m;
    int p = k - 1;

    // 确定规格化指数：让有效数位于 [2^23, 2^24)
    int top = 0;
    unsigned t = n;
    while (t >>= 1)
        top++;

    int e = top + p + 127;

    // 溢出为带符号无穷
    if (e >= 255)
        return sign | 0x7f800000u;

    // 正规数：保留 24 位有效数，剩余部分按最近偶数舍入
    if (e > 0) {
        int shift = top - 23;
        unsigned sig;

        if (shift > 0) {
            unsigned q = n >> shift;
            unsigned rem = n & ((1u << shift) - 1u);
            unsigned half = 1u << (shift - 1);

            q += (rem > half) | ((rem == half) & (q & 1u));
            sig = q;

            // 舍入可能产生进位，指数随之加一
            if (sig == 0x1000000u) {
                sig >>= 1;
                e++;
                if (e >= 255)
                    return sign | 0x7f800000u;
            }
        } else {
            sig = n << -shift;
        }

        return sign | (e << 23) | (sig & 0x7fffffu);
    }

    // 非正规数以 2^-149 为单位，统一右移并只舍入一次
    {
        int shift = -(p + 149);
        unsigned q;
        unsigned rem;
        unsigned half;

        if (shift <= 0)
            return sign | (n << -shift);

        if (shift > 32)
            return sign;

        q = n >> shift;
        rem = n & ((1u << shift) - 1u);
        half = 1u << (shift - 1);

        q += (rem > half) | ((rem == half) & (q & 1u));

        // 舍入进到最小正规数
        if (q >= 0x800000u)
            return sign | 0x00800000u;

        return sign | q;
    }
}


// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
    unsigned sign = uf & 0x80000000u;
    unsigned exp  = (uf >> 23) & 0xffu;
    unsigned frac = uf & 0x7fffffu;

    // NaN 或无穷大：原样返回
    if (exp == 0xffu)
        return uf;

    // 绝对值小于 0.5：舍入为带原符号的零
    if (exp < 126)
        return sign;

    // 0.5 <= 绝对值 < 1：恰好 0.5 时舍入到偶数 0，其余舍入到 ±1
    if (exp == 126) {
        if (frac == 0)
            return sign;
        return sign | 0x3f800000u;
    }

    // 绝对值至少为 2^23：已经是整数
    if (exp >= 150)
        return uf;

    // 小数位数为 150 - exp
    {
        int shift = 150 - exp;
        unsigned mask = (1u << shift) - 1u;
        unsigned rem = frac & mask;
        unsigned half = 1u << (shift - 1);
        unsigned rounded = uf & ~mask;

        // 大于一半时进位；正好一半时，保留结果为奇数才进位
        if (rem > half || (rem == half && ((rounded >> shift) & 1u)))
            rounded += 1u << shift;

        return rounded;
    }
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
    int sign = x >> 31;
    int absx = (x ^ sign) + (sign & 1);
    int msb = 31;
    int exp;
    int shift;
    int sig;
    int guard;
    int sticky;

    if (x == 0)
        return 0;

    // 找到最高位 1
    while (((absx >> msb) & 1) == 0)
        msb--;

    exp = msb + 127;

    // 最高位不超过第 23 位时，可直接左移对齐
    if (msb <= 23) {
        sig = absx << (23 - msb);
    } else {
        // 保留 24 位有效数，并用 guard/sticky 位做最近偶数舍入
        shift = msb - 23;
        sig = absx >> shift;
        guard = (absx >> (shift - 1)) & 1;
        sticky = (shift > 1) &&
                 ((absx & ((1 << (shift - 1)) + ~0)) != 0);

        if (guard && (sticky || (sig & 1))) {
            sig++;
            if (sig == 0x1000000) {
                sig >>= 1;
                exp++;
            }
        }
    }

    return (sign & 0x80000000) |
           (exp << 23) |
           (sig & 0x7fffff);
}


// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
    int m1 = 0x55 | (0x55 << 8);
    int m2 = 0x33 | (0x33 << 8);
    int m4 = 0x0f | (0x0f << 8);

    m1 = m1 | (m1 << 16);
    m2 = m2 | (m2 << 16);
    m4 = m4 | (m4 << 16);

    x = (x & m1) + ((x >> 1) & m1);
    x = (x & m2) + ((x >> 2) & m2);
    x = (x & m4) + ((x >> 4) & m4);
    x = x + (x >> 8);
    x = x + (x >> 16);

    return x & 0x3f;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x) {
    int m16 = 0xff | (0xff << 8);
    int m8 = m16 ^ (m16 << 8);
    int m4 = m8 ^ (m8 << 4);
    int m2 = m4 ^ (m4 << 2);
    int m1 = m2 ^ (m2 << 1);

    // 交换高低 16 位，并清除右移的符号扩展
    x = ((x >> 16) & m16) | (x << 16);

    // 依次交换每组中的两半
    x = ((x >> 8) & m8) | ((x & m8) << 8);
    x = ((x >> 4) & m4) | ((x & m4) << 4);
    x = ((x >> 2) & m2) | ((x & m2) << 2);
    x = ((x >> 1) & m1) | ((x & m1) << 1);

    return x;
}