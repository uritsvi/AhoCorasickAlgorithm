#include <memory.h>  
#include <string.h>  
#include <stdlib.h>
   
 #include "build_tries.h"  
 #include "hash_table.h"  
   
 struct FullContext{  
 	struct HashTable Prefixes;  
 };  
   
 struct WordContext {  
 	struct FullContext* FullContex;  
   
 	int TravsFromRoot;  
 	size_t CurrentMaxLen;  
 };  
   
 struct Prefix {  
 	struct ListEntry Entry;  
 	wchar_t Prefix[1];  
 };  
   
 struct MapValue {  
 	struct ValueEntry Entry;  
 	struct TrieEntry* TrieEntry;  
 };  
   
 void handle_word(  
 	_In_ wchar_t* Buffer,  
 	_In_ int Index,  
 	_In_ struct TrieEntry* Trie,  
 	_In_ struct WordContext* WordContext,  
 	_In_ int WordIndex,  
 	_In_ int NumOfWords) {  
   
 	WordContext->TravsFromRoot++;  
   
 	struct CharLeaf* target_entry =   
 		(struct CharLeaf*)Trie->Leavs[Buffer[Index]];  
   
 	if (target_entry == NULL) {  
 		target_entry =   
 			(struct CharLeaf*)  
 			malloc(sizeof(struct CharLeaf));  
   
 		memset(  
 			target_entry,   
 			0,   
 			sizeof(struct CharLeaf));
   
 		init_list(&target_entry->Prefixes);  
   
 		target_entry->C = Buffer[Index];  
 		target_entry->TravsFromRoot = WordContext->TravsFromRoot;  
 		target_entry->outputNode = false;  
   
 		int c = WordContext->TravsFromRoot - 1;  
 		do {  
 			struct Prefix* prefix = (struct Prefix*)malloc(  
 				sizeof(struct Prefix) +  
                (WordContext->TravsFromRoot) * sizeof(wchar_t)
 			);  
        
            memset(
                prefix, 
                0, 
                sizeof(struct Prefix) +
                (WordContext->TravsFromRoot) * sizeof(wchar_t));

   
 			memcpy_s(  
 				(void*)prefix->Prefix,   
 				(WordContext->TravsFromRoot * sizeof(wchar_t)),  
 				Buffer + 1,   
 				(c) * sizeof(wchar_t));  
   
 			push_front(  
 				&target_entry->Prefixes,   
 				&prefix->Entry);  
   
   
 		} while (--c >= 0);  
 		  
   
 		struct MapValue* value = (struct MapValue*)malloc(  
 			sizeof(struct MapValue)  
 		);  
   
 		value->TrieEntry = &target_entry->Entrey;  
   
   
   
 		push_value_to_map(  
 			&WordContext->FullContex->Prefixes,  
 			Buffer,  
 			WordContext->TravsFromRoot,  
 			&value->Entry);   
   
 		Trie->Leavs[Buffer[Index]]= &target_entry->Entrey;  
 	}  
   
 	if (Index == WordContext->CurrentMaxLen - 1) {  
 		target_entry->wordIndex = NumOfWords - WordIndex - 1;  
 		target_entry->outputNode = true;  
 		return;  
 	}  
   
 	handle_word(  
 		Buffer,   
 		Index + 1,   
 		&target_entry->Entrey,   
 		WordContext,  
 		WordIndex,  
 		NumOfWords);  
 }  
   
   
 bool handle_prefix(  
 	_In_ struct FullContext* Context,  
 	_In_ struct ListEntry* Head,  
 	_In_ struct Prefix* Current,  
 	_Inout_ struct CharLeaf* CurrentLeaf) {  
   
 	if (Current != NULL) {   
 		bool res = handle_prefix(  
 			Context,  
 			Head,  
 			iter_list_next(Head),  
 			CurrentLeaf);  
 		if (res) {  
 			return res;  
 		}  
   
 		struct MapValue* entry;  
 		res = query_map_value(  
 			&Context->Prefixes,   
 			Current->Prefix,   
 			wcslen(Current->Prefix),  
 			(struct ValueEntry**)&entry);  
   
 		if (!res) {  
 			return false;  
 		}  
   
 		CurrentLeaf->FailureLink =   
 			(struct CharLeaf*)entry->TrieEntry;  
   
 		return true;  
 	}  
   
 	return false;  
 }  
   
 void handle_make_faliure_links(  
 	_In_ struct TrieEntry* Trie,  
 	_In_ struct FullContext* Context) {  
   
 	struct ListEntry* prefixes = NULL;  
 	for (int i = 0; i < MAX_KEYS; i++) {  
 		if (Trie->Leavs[i] == NULL) {  
 			continue;  
 		}  
   
 		struct CharLeaf* current = (struct CharLeaf*)Trie->Leavs[i];  
 		prefixes = &current->Prefixes;  
   
 		handle_prefix(  
 			Context,  
 			prefixes,  
 			(struct Prefix*)start_iter_list(prefixes),  
 			current);  
   
 		handle_make_faliure_links(  
 			Trie->Leavs[i],  
 			Context);  
 		  
 	}  
   
 	if (prefixes == NULL) {  
 		return;  
 	}  
   
 }  
   
 void build_trie(  
 	_In_ struct ListEntry* Paths,  
 	_Out_ struct TrieEntry* Trie) {  
   
 	memset(  
 		Trie,   
 		0,   
 		sizeof(struct CharLeaf));  
   
 	struct FullContext* full_context =   
 		(struct FullContext*)malloc(sizeof(struct FullContext));  
 	  
 	init_map(  
 		&full_context->Prefixes,   
 		true);  
   
 	int c = 0;  
 	for (  
 		struct PathInfo* current =   
 			(struct PathInfo*)start_iter_list(Paths);   
 		current != NULL;   
 		current = iter_list_next(Paths)) {  
   
 		struct WordContext word_context = { 0 };  
 		  
 		word_context.FullContex = full_context;  
 		word_context.CurrentMaxLen = current->len;  
   
 		handle_word(  
 			current->path,   
 			0,   
 			Trie,   
 			&word_context,   
 			c,  
 			Paths->Len);  
   
   
 		struct MapValue* rootValueEntry =   
 			malloc(sizeof(struct MapValue));  
   
 		rootValueEntry->TrieEntry = Trie;  
 		  
 		struct CharLeaf* rootLeaf = (struct CharLeaf*)Trie;  
   
 		rootLeaf->FailureLink = rootLeaf;  
 		rootLeaf->Root = true;  
   
 		push_value_to_map(  
 			&full_context->Prefixes,  
 			L"",  
 			1,  
 			(struct ValueEntry*)rootValueEntry);  
   
 		c++;  
 	}  
   
 	  
 	handle_make_faliure_links(  
 		Trie,   
 		full_context);  
 } 