#include <stddef.h>

#include "list.h"  
   
 void init_list(_Out_ struct ListEntry* Head) {  
 	Head->Next = NULL;  
 	Head->IterCurrent = NULL;  
 	Head->Len = 0;  
 }  
   
 void push_front(  
 	_In_ struct ListEntry* Head,  
 	_In_ struct ListEntry* Entry) {  
   
 	struct ListEntry* temp = Head->Next;  
   
 	Entry->Next = NULL;  
 	Entry->IterCurrent = NULL;  
   
 	Head->Next = Entry;  
 	Entry->Next = temp;  
   
 	Head->Len++;  
 }  
   
 void* start_iter_list(_In_ struct ListEntry* Head) {  
 	Head->IterCurrent = Head->Next;  
 	return Head->IterCurrent;  
 }  
 void* iter_list_next(_In_ struct ListEntry* Head) {  
 	Head->IterCurrent = Head->IterCurrent->Next;  
 	return Head->IterCurrent;  
 } 