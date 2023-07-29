#include <string.h>  
#include <stdio.h>
   
 #include "match.h"  
 #include "build_tries.h"  
   
 void match_string_with_trie(  
 	_In_ struct TrieEntry* Trie,  
 	_In_ wchar_t* Target,  
 	_In_ int I,  
 	_Out_ bool *Matches,
    _In_ int C) {  
   
     C++;

 	struct CharLeaf* current_trie =   
 		(struct CharLeaf*)Trie;  
   
 	size_t len = wcslen(Target);  
 	if (I == len || Trie == NULL) {  
        printf("Num of passes: %d\n", C);
 		return;  
 	}  
 	  
 	struct CharLeaf* current =  
 		(struct CharLeaf*)Trie->Leavs[Target[I]];  
   
 	if (current != NULL) {  
 		if (current->outputNode == true) {  
 			Matches[current->wordIndex] = true;  
 		}  
   
 		I++;  
   
 	}  
 	else {  
 		if (current_trie->Root &&   
 			current_trie->FailureLink == current_trie) {  
 			I++;  
 		}  
   
 		current =  
 			current_trie->FailureLink;  
 	}  
   
 	match_string_with_trie(  
 		(struct TrieEntry*)current,  
 		Target,  
 		I,  
 		Matches,
        C);  
   
 } 