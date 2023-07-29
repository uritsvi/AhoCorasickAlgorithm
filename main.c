#include <string.h>  
#include <sal.h>  
#include <stdbool.h>  
#include <stdio.h>
#include <stdlib.h>
   
 #include "trie.h"  
 #include "build_tries.h"  
 #include "match.h"  
 #include "hash_table.h"  
   
 struct TrieEntry g_Trie;  
   
 void init(
     _In_ wchar_t* Paths, 
     _Out_ int* NumOfPaths) {  
   
 	struct ListEntry pathsList = {0};  
   
 	size_t len =   
 		wcslen(Paths) + 1;  
   
 	wchar_t* buffer = malloc(  
 		len *   
 		sizeof(wchar_t));  
 	  
 	wcscpy_s(  
 		buffer,   
 		len,   
 		Paths);  
   
 	wchar_t* context = 0;  
 	wchar_t* current_path =   
 		wcstok_s(  
 			buffer,   
 			L",",   
 			&context);  
 	  
    int c = 1;
 	while (current_path != NULL) {   
   
 		size_t current_path_len =   
 			wcslen(current_path) + 1;  
   
 		struct PathInfo* info =   
 			(struct PathInfo*)malloc(  
 				current_path_len *   
 				sizeof(wchar_t) +   
 				sizeof(struct PathInfo));  
   
 		info->len = current_path_len - 1;  
   
 		wcscpy_s(  
 			info->path,   
 			current_path_len,  
 			current_path);  
   
 		push_front(  
 			&pathsList,   
 			&info->Entry);  
   
 		current_path =  
 			wcstok_s(  
 				NULL,   
 				L",",   
 				&context);  
        c++;
 	}  
   
 	build_trie(  
 		&pathsList,  
 		&g_Trie);

    *NumOfPaths = c;
 }  
   
  
 int main() {  
   
     wchar_t* paths = L"c:\\uri,c:\\tsvi, c:\\a";

    int num_of_paths;
 	init(
        paths, 
        &num_of_paths);
 	
    int size = num_of_paths * sizeof(bool) - 1;
    bool* matches = malloc(
        size
    );
    memset(
        matches, 
        0, 
        size);

    wchar_t* string = L"aac:\\uric:\\tsvibb";

    printf("String len is: %d\n", (int)wcslen(string));

 	match_string_with_trie(  
 		&g_Trie,  
 		string,
 		0,  
 		matches,
        0);  
   
    for (int i = 0; i < num_of_paths - 1; i++) {
        printf("string index %d found: %s\n", 
            i, 
            matches[i] == true ? "true" : "false");
    }

 	return 0;  
 }  
   
