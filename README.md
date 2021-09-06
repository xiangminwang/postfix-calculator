# postfix-calculator
A small program for study purpose, improving C skills

## Features
- Supports `+` `-` `*` `/`
- Supports multi bits and negative operands
- Converts infix expressions into postfix ones
- Calculating while converting

## Build
```
gcc -o postfix-calculator main.c
```

## Tests
```
input: 15+3*120/-40 
output: 15 3 120 * -40 / +  == 6  

input: 3+2*{1+2*[-4/(8-6)+7]} 
output: 3 2 1 2 -4 8 6 - / 7 + * + * +  == 25  

input: 3+2*{1+2*[4/(8-6)+7]} 
output: 3 2 1 2 4 8 6 - / 7 + * + * +  == 41  

input: 1+2*3-4*5 
output: 1 2 3 * + 4 5 * - ->  ==3  

input: 5-3+9*6*(6-10-2) 
output: 5 3 - 9 6 * 6 10 - 2 - * + ->  == 22  

input: 3*5+8-0*3-6+0+0 
output: 3 5 * 8 + 0 3 * - 6 - 0 + 0 +  == 17  

input: 4+(6*(4*7-9*(0-8-4)*2)) 
output: 4 6 4 7 * 9 0 8 - 4 - * 2 * - * +  == 1468  

input: 3-10+(0+(10+5+3)-10) 
output: 3 10 - 0 10 5 + 3 + + 10 - +  == 1  
```
