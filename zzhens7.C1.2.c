/** CS 2506 Fall 2014
 *  Assignment 1: Generic Deque Interface
 *  Student:      Zhenshu Zhao
 *  PID:          zzhens7
 */
#ifndef DEQUE_H
#define DEQUE_H
#include <stddef.h>
#include <stdbool.h>



// Deque node:
struct _QNode {
   struct _QNode *prev;     /* Previous list element. */
   struct _QNode *next;     /* Next list element.    */
};
typedef struct _QNode QNode;

// Deque object:
struct _Deque {
   QNode fGuard;    // sentinel node at the front of the queue
   QNode rGuard;     // sentinel node at the tail of the queue
};
typedef struct _Deque Deque;

// Deque_Entry() is a useful macro; there is a full discussion of a similar
// macro for a generic doubly-linked list implementation in the CS 2505 notes.
// Converts pointer to queue element NODE into a pointer to the structure that
// NODE is embedded inside.  Supply the name of the outer structure STRUCT and
// the member name MEMBER of the NODE.  See the big comment at the top of the
// file for an example.
#define Deque_Entry(NODE, STRUCT, MEMBER)                              \
        ((STRUCT *) ((uint8_t *) (NODE) - offsetof (STRUCT, MEMBER)))

// Initialize QNode pointers to NULL.
//
// Pre:  pN points to a QNode object
// Post: pN->prev and pN->next are NULL
//
void QNode_Init(QNode* const pN){
	pN->prev = NULL;
	pN->next = NULL;
};

// Initialize Deque to empty state.
//
// Pre:  pQ points to a Deque object
// Post: *pQ has been set to an empty state (see preceding comment
//
void Deque_Init(Deque* const pQ){
	pQ->fGuard.prev = NULL;
	pQ->fGuard.next = &(pQ->rGuard);
	pQ->rGuard.prev = &(pQ->fGuard);
	pQ->rGuard.next = NULL;
}

// Return whether Deque is empty.
//
// Pre:  pQ points to a Deque object
// Returns true if *pQ is empty, false otherwise
//
bool Deque_Empty(const Deque* const pQ){
	if (pQ->fGuard.next == &(pQ->rGuard) && pQ->rGuard.prev == &(pQ->fGuard)) {
        return true;
}
	return false;
};

// Insert *pNode as first interior element of Deque.
//
// Pre:  pQ points to a Deque object
//       pNode points to a QNode object
// Post: *pNode has been inserted at the front of *pQ
//
void Deque_Prepend(Deque* const pQ, QNode* const pNode){
	
        pQ->fGuard.next->prev = pNode;
	pNode->next = pQ->fGuard.next;
	pNode->prev = &(pQ->fGuard);
	pQ->fGuard.next = pNode;
	
	

};

// Insert *pNode as last interior element of Deque.
//
// Pre:  pQ points to a Deque object
//       pNode points to a QNode object
// Post: *pNode has been inserted at the rear of *pQ
//
void Deque_Append(Deque* const pQ, QNode* const pNode){

	pQ->rGuard.prev->next = pNode;
	pNode->prev = pQ->rGuard.prev;


	pNode->next = &(pQ->rGuard);
	pQ->rGuard.prev = pNode;
};

// Remove first interior element of Deque and return it.
//
// Pre:  pQ points to a proper Deque object
// Post: the interior QNode that was at the front of *pQ has been removed
// Returns pointer to the QNode that was removed, NULL if *pQ was empty
//
QNode* Deque_RmFront(Deque* const pQ){
	if (pQ->fGuard.next == &(pQ->rGuard) && pQ->rGuard.prev == &(pQ->fGuard)){
		return NULL;
} else{
	QNode *removef = pQ->fGuard.next;
	pQ->fGuard.next = pQ->fGuard.next->next;
	pQ->fGuard.next->prev = &(pQ->fGuard);
	return removef;}
};

// Remove last interior element of Deque and return it.
//
// Pre:  pQ points to a proper Deque object
// Post: the interior QNode that was at the back of *pQ has been removed
// Returns pointer to the QNode that was removed, NULL if *pQ was empty
//
QNode* Deque_RmBack(Deque* const pQ){
 	if (Deque_Empty(pQ)){
		return NULL;
}
	QNode *removeb = pQ->rGuard.prev;
	pQ->rGuard.prev = pQ->rGuard.prev->prev;
	pQ->rGuard.prev->next = &(pQ->rGuard);
	return removeb;
};

// Return pointer to the first interior element, if any; does not remove
// the element.
//
// Pre:  pQ points to a proper Deque object
// Returns pointer first interior QNode in *pQ, NULL if *pQ is empty
//
const QNode* Deque_Front(const Deque* const pQ){
	if (Deque_Empty(pQ)){
	return NULL;
}
	return pQ->fGuard.next;
};

// Return pointer to the last interior element, if any; useful for client-
// side traversal code.
//
// Pre:  pQ points to a proper Deque object
// Returns pointer last interior QNode in *pQ, NULL if *pQ is empty
//
const QNode* Deque_Back(const Deque* const pQ){
	if (Deque_Empty(pQ)){
	return NULL;
}
	return pQ->rGuard.prev;
};

// Reverse the order of the interior nodes in the Deque.
//
// Pre:  pQ points to a proper Deque object
// Post: *pQ contains exactly the same nodes as before, but in reverse order
//
void Deque_Reverse(Deque* const pQ){
	QNode *first = pQ->fGuard.next;
	while (first->next != &(pQ->rGuard)){
	QNode *Second = first->next;
	first->next = first->next->next;
	first->next->prev = first;
        Deque_Prepend(pQ, Second);

}

	
}

#endif
// On my honor: 
// 
// - I have not discussed the C language code in my program with 
// anyone other than my instructor or the teaching assistants 
// assigned to this course. 
// 
// - I have not used C language code obtained from another student, 
// or any other unauthorized source, either modified or unmodified. 
// 
// - If any C language code or documentation used in my program 
// was obtained from another source, such as a text book or course 
// notes, that has been clearly noted with a proper citation in 
// the comments of my program. 
// 
// Zhenshu Zhao

