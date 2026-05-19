#include <stdio.h>

/**
 * Reverse-engineered from the asm4 assembly function
 * 
 * The assembly was translated line-by-line:
 * - [ebp-0x10] → val (initialized to 0x267)
 * - [ebp-0xc]  → len (string length counter)
 * - [ebp-0x8]  → i (loop index)
 * 
 * First loop (assembly lines <+18> to <+44>): Count string length
 * Second loop (assembly lines <+46> to <+151>): Accumulate differences
 */
int asm4(char *str) {
    int val = 0x267;     // From <+11>: mov DWORD PTR [ebp-0x10],0x267
    int len = 0;          // From <+18>: mov DWORD PTR [ebp-0xc],0x0
    
    // FIRST LOOP: Find string length
    // Assembly: <+25> to <+44> - loops until null terminator
    while (str[len] != '\0') {
        len++;            // From <+27>: add DWORD PTR [ebp-0xc],0x1
    }
    
    // SECOND LOOP: Main calculation
    // Assembly: <+46> to <+151> - runs from i=1 to len-2
    for (int i = 1; i < len - 1; i++) {
        // DIFF1: current char minus previous char
        // Assembly lines <+55> to <+86>: calculates str[i] - str[i-1]
        int diff1 = str[i] - str[i-1];
        
        // DIFF2: next char minus current char  
        // Assembly lines <+98> to <+129>: calculates str[i+1] - str[i]
        int diff2 = str[i+1] - str[i];
        
        // Add both differences to running total
        // Assembly lines <+88> to <+135>: val = val + diff1 + diff2
        val = val + diff1 + diff2;
    }
    
    return val;  // From <+153>: mov eax, [ebp-0x10]
}

int main() {
    // Test with the required string from the challenge
    int result = asm4("picoCTF_e53f9");
    
    // Output as hex with 0x prefix (matching submission format)
    printf("0x%x\n", result);
    return 0;
}