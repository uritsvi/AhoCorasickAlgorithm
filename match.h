#ifndef __MATCH__  
 #define __MATCH__  
   
 #include <stdbool.h>  
 #include <stdint.h>  
 #include <sal.h>  
   
 #include "trie.h"  
   
 void match_string_with_trie(  
 	_In_ struct TrieEntry* Trie,   
 	_In_ wchar_t* Target,  
 	_In_ int I,  
 	_Out_ bool *Matches,
    _In_ int c);  
   
 #endif 