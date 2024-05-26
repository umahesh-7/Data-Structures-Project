#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
# define CHAR 26 
# define WORD 30 
struct Node 
{ 
	bool isEnd; 
	unsigned frequency; 
	int indexMinHeap; 
	Node* child[CHAR]; 
}; 
struct MinHeapNode 
{ 
	Node* root;  
	unsigned frequency; 
	char* word; 
}; 
struct MinHeap 
{ 
	unsigned capacity; 
	int count; 
	MinHeapNode* array; 
}; 
Node* newNode() 
{
	Node* node = new Node; 
	node->isEnd = 0; 
	node->frequency = 0; 
	node->indexMinHeap = -1; 
	for( int i = 0; i < CHAR; ++i ) 
		node->child[i] = NULL; 
	return node; 
} 
MinHeap* createMinHeap( int capacity ) 
{ 
	MinHeap* minHeap = new MinHeap; 
	minHeap->capacity = capacity; 
	minHeap->count = 0; 
	minHeap->array = new MinHeapNode [ minHeap->capacity ]; 
	return minHeap; 
} 
void swapMinHeapNodes ( MinHeapNode* a, MinHeapNode* b ) 
{ 
	MinHeapNode temp = *a; 
	*a = *b; 
	*b = temp; 
} 
void minHeapify( MinHeap* minHeap, int idx ) 
{ 
	int left, right, smallest; 
left = 2 * idx + 1;
	right = 2 * idx + 2; 
	smallest = idx; 
	if ( left < minHeap->count && 
		minHeap->array[ left ]. frequency < 
		minHeap->array[ smallest ]. frequency 
	) 
		smallest = left; 

	if ( right < minHeap->count && 
		minHeap->array[ right ]. frequency < 
		minHeap->array[ smallest ]. frequency 
	) 
		smallest = right; 

	if( smallest != idx ) 
	{  
		minHeap->array[ smallest ]. root->indexMinHeap = idx; 
		minHeap->array[ idx ]. root->indexMinHeap = smallest; 
		swapMinHeapNodes (&minHeap->array[ smallest ], &minHeap->array[ idx ]); 

		minHeapify( minHeap, smallest ); 
	} 
} 
void buildMinHeap( MinHeap* minHeap ) 
{ 
	int n, i; 
	n = minHeap->count - 1; 
for( i = ( n - 1 ) / 2; i >= 0; --i ) 
		minHeapify( minHeap, i ); 
} 
void insertInMinHeap( MinHeap* minHeap, Node** root, const char* word ) 
{ 
	if( (*root)->indexMinHeap != -1 ) 
	{ 
		++( minHeap->array[ (*root)->indexMinHeap ]. frequency ); 
		minHeapify( minHeap, (*root)->indexMinHeap ); 
	} 
	else if( minHeap->count < minHeap->capacity ) 
	{ 
		int count = minHeap->count; 
		minHeap->array[ count ]. frequency = (*root)->frequency; 
		minHeap->array[ count ]. word = new char [strlen( word ) + 1]; 
		strcpy( minHeap->array[ count ]. word, word ); 

		minHeap->array[ count ]. root = *root; 
		(*root)->indexMinHeap = minHeap->count; 

		++( minHeap->count ); 
		buildMinHeap( minHeap ); 
	} 
	else if ( (*root)->frequency > minHeap->array[0]. frequency ) 
	{ 
		minHeap->array[ 0 ]. root->indexMinHeap = -1; 
		minHeap->array[ 0 ]. root = *root; 
		minHeap->array[ 0 ]. root->indexMinHeap = 0; 
		minHeap->array[ 0 ]. frequency = (*root)->frequency; 
		delete [] minHeap->array[ 0 ]. word; 
		minHeap->array[ 0 ]. word = new char [strlen( word ) + 1]; 
		strcpy( minHeap->array[ 0 ]. word, word ); 

		minHeapify ( minHeap, 0 ); 
	} 
} 
void insertUtil ( Node** root, MinHeap* minHeap, 
						const char* word, const char* dupWord ) 
{ 
	if ( *root == NULL ) 
		*root = newNode(); 
	if ( *word != '\0' ) 
		insertUtil ( &((*root)->child[ tolower( *word ) - 97 ]), 
						minHeap, word + 1, dupWord ); 
	else 
	{  
		if ( (*root)->isEnd ) 
			++( (*root)->frequency ); 
		else
		{ 
			(*root)->isEnd = 1; 
			(*root)->frequency = 1; 
		} 
		insertInMinHeap( minHeap, root, dupWord ); 
	} 
} 
void insertTrieAndHeap(const char *word, Node** root, MinHeap* minHeap) 
{ 
	insertUtil( root, minHeap, word, word ); 
} 

void displayMinHeap( MinHeap* minHeap ) 
{ 
	int i; 
	for( i = 0; i < minHeap->count; ++i ) 
	{ 
		printf( "%-4s : %d\n", minHeap->array[i].word, 
							minHeap->array[i].frequency ); 
	} 
} 
void printKMostFreq( FILE* fp, int k ) 
{ 
	MinHeap* minHeap = createMinHeap( k ); 
	Node* root = NULL; 
	char buffer[WORD];  
	while( fscanf( fp, "%s", buffer ) != EOF ) 
		insertTrieAndHeap(buffer, &root, minHeap); 
	displayMinHeap( minHeap ); 
} 

int main() 
{ 
	int k ;
	printf("enter number of words to be searched\n");
	scanf("%d",&k); 
	FILE *fp = fopen ("file.txt", "r"); 
	if (fp == NULL) 
		printf ("File doesn't exist "); 
	else
		printKMostFreq (fp,   k); 
	return 0; 
}
