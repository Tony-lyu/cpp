Assume that your computer uses 12-bits registers to represent numbers. If your computer
can, what would be its 2’s complement binary representation for -13, 56, -1, -2048, 2048.

for all of the question below, I will first find the 12-bit binay represenation of the number, 
then find its 2's complement by inverting the bit and adding one for negative numbers. 

1)-13
13 in binary: 13 = 8 + 4 + 1 --> 0000 0000 1101
invert bits: 1111 1111 0010
add one: 1111 1111 0011
result: -13 = 1111 1111 0011

2)56
56 in binary: 56 = 32 + 16 + 8 --> 0000 0011 1000
56 is positive, therefore,
result: 56 = 0000 0011 1000

3)-1
1 in binary: 1 --> 0000 0000 0001
invert bits: 1111 1111 1110
add one: 1111 1111 1111
result: -1 = 1111 1111 1111

4)-2048
2048 in binary: 2048 = 2^11 --> 1000 0000 0000
invert bits: 0111 1111 1111
add one: 1000 0000 0000 
result: -2048 = 1000 0000 0000

5)2048
2048 in binary = 1000 0000 0000, but since the first bit in the 12-bit representation is signed bit, 
2048 will cause a overflow, that is, 2048 cannot be represented by signed 12-bits register. 
