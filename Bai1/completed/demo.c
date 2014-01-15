#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_WORD 32
#define MAX_TEXT_LENGTH 10000

// ===========================================
//                 STRUCTURE
//============================================


typedef struct word {
char *str;              
int freq;               
struct word *pNext;     
} Word;

// ===========================================
//             FUNCTION PROTOTYPES
//============================================

int getNextWord(FILE *fp, char *buf, int bufsize);  /* Given function to get words */
void addWord(char *pWord);                          /* Adds a word to the list or updates exisiting word */
void show(Word *pWordcounter);        		    /* Outputs a word and its count of occurrences */
Word* createWordCounter(char *word);                /* Creates a new WordCounter structure */
int isUnusual(char *word);

// ===========================================
//             GLOBAL VARIABLES
//============================================

Word *pStart = NULL;                                /* Pointer to first word counter in the list */

int totalcount = 0;                                 /* Total amount of words */
int uniquecount = 0;                                /* Amount of unique words */



// ===========================================
//                 MAIN
//============================================      


int main () {
    
    FILE * fp;
    fp = fopen("vanban.txt","r");
    
    char buf[MAX_WORD];
    
    int size = MAX_TEXT_LENGTH;

    Word *pCounter = NULL;

    while (getNextWord(fp, buf, size)) {
        if(isUnusual(buf)){
	addWord(buf);         
        totalcount++;
	}
    }
    
    pCounter = pStart;
    while(pCounter != NULL)
    {
        uniquecount++;
        pCounter = pCounter->pNext;
    }

    /* Print Summary */

    printf("\nSUMMARY:\n\n");
    printf("   %d words\n", totalcount); 
    printf("   %d unique words\n", uniquecount); 

    pCounter = pStart;
    while(pCounter != NULL)
    {
        show(pCounter);
        pCounter = pCounter->pNext;
    }
    printf("\n");


    /* Free the allocated  memory*/
    pCounter = pStart;
    while(pCounter != NULL)
    {
        free(pCounter->str);        
        pStart = pCounter;           
        pCounter = pCounter->pNext;  
        free(pStart);                  
    }

    fclose(fp);
    
    return 0;
}


// ===========================================
//                 FUNCTIONS
//============================================


void show(Word *pWordcounter)
{
  /* output the word and it's count */
  printf("\n%-30s   %5d", pWordcounter->str,pWordcounter->freq);

}

void addWord(char *word)
{
  Word *pCounter = NULL;
  Word *pLast = NULL;

  if(pStart == NULL)
  {
    pStart = createWordCounter(word);
    return;
  }

  
  pCounter = pStart;
  while(pCounter != NULL)
  {
    if(strcmp(word, pCounter->str) == 0)
    {
      ++pCounter->freq;

      return;
    }
    pLast = pCounter;            
    pCounter = pCounter->pNext;  
  }

  
  pLast->pNext = createWordCounter(word);
}

Word* createWordCounter(char *word)
{
  Word *pCounter = NULL;
  pCounter = (Word*)malloc(sizeof(Word));
  pCounter->str = (char*)malloc(strlen(word)+1);
  strcpy(pCounter->str, word);
  pCounter->freq = 1;
  pCounter->pNext = NULL;
  return pCounter;
}

int getNextWord(FILE *fp, char *buf, int bufsize) {
    char *p = buf;
    char c;
    
    do {
        c = fgetc(fp);
        if (c == EOF) 
            return 0;
        } while (!isalpha(c));

    do {
        if (p - buf < bufsize - 1)
        *p++ = tolower(c);
        c = fgetc(fp);
        } while (isalpha(c));
	
        *p = '\0';
        return 1;
}
int isUnusual(char *word){
    FILE * fp;
    fp = fopen("stopw.txt","r");
    
    char buf[MAX_WORD];
        
    int size = MAX_TEXT_LENGTH;    

    while (getNextWord(fp, buf, size)) {        
	if(strcmp(word,buf) == 0){
	  return 0;	  
	}               
    }
    return 1;
}