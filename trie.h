#ifndef __TRIE__  
 #define __TRIE__  
   
 #include <sal.h>  
   
 #include "list.h"  
   
 #define MAX_LEAVS (1 << 16)  
   
 struct TrieEntry {  
 	struct TrieEntry* Leavs[MAX_LEAVS];  
 	struct TrieEntry* IterCurrent;  
 };  
   
   
 #endif 