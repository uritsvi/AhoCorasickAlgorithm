#ifndef __LIST__  
 #define __LIST__  
   
 #include <sal.h>  
   
 struct ListEntry {  
 	struct ListEntry* Next;  
 	struct ListEntry* IterCurrent;  
   
 	// Is used just with lists heads  
 	int Len;   
 };  
   
   
 void init_list(_Out_ struct ListEntry* Head);  
 void push_front(  
 	_In_ struct ListEntry* Head,  
 	_In_ struct ListEntry* Entry);  
   
 void* start_iter_list(_In_ struct ListEntry* Head);  
 void* iter_list_next(_In_ struct ListEntry* Head);  
   
 #endif  
 