#ifndef __BUILD__TRIES__  
 #define __BUILD__TRIES__  
   
 #include <sal.h>  
 #include <stdint.h>  
 #include <stdbool.h>  
   
 #include "trie.h"  
 #include "list.h"  
   
 struct PathInfo {  
 	struct ListEntry Entry;  
 	size_t len;  
 	wchar_t path[];  
 };  
   
 struct TrieLeafInfo {  
 	struct TrieEntry Entry;  
 };  
   
 struct CharLeaf {  
 	struct TrieEntry Entrey;  
 	int TravsFromRoot;  
   
 	bool Root;  
   
 	wchar_t C;  
 	struct ListEntry Prefixes;  
 	struct CharLeaf* FailureLink;  
   
 	bool outputNode;  
 	int wordIndex;  
 };  
   
 void build_trie(  
 	_In_ struct ListEntry* Paths,  
 	_Out_ struct TrieEntry* Trie);  
   
   
   
 #endif 