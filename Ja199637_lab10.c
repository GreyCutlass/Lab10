#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char ALPHABET[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

// Trie structure
typedef struct Trie
{	
    int count;
    struct Trie* children[26];
    
}Trie_t;

struct Trie *createTrie();

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    Trie_t *currentNode = pTrie;

    size_t wordSize = strlen(word);
    if(pTrie != NULL)
    {

        for(int wordIndex = 0; wordIndex < wordSize; ++wordIndex)
        {

            for(int alphabetIndex = 0; alphabetIndex < 26; ++alphabetIndex)
            {

                if(word[wordIndex] == ALPHABET[alphabetIndex] && currentNode->children[alphabetIndex] == NULL)
                {

                    currentNode->children[alphabetIndex] = createTrie();
                    currentNode = currentNode->children[alphabetIndex];
                    //currentNode->count += 1;
                    break;

                }
                else if (word[wordIndex] == ALPHABET[alphabetIndex])
                {

                    currentNode = currentNode->children[alphabetIndex];
                    break;
                }

            }

        }

    }

    currentNode->count += 1;

}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{

    if(pTrie == NULL || word == NULL)
    {

        return -1;

    }

    Trie_t *movingHead = pTrie;

    size_t wordLength = strlen(word);

    unsigned short Found = 0;

    for(int index = 0; index < wordLength; ++index)
    {

        for(unsigned short alphabetIndex = 0; alphabetIndex < 26; ++alphabetIndex)
        {
            Found = 0;

            if(ALPHABET[alphabetIndex] == word[index] && movingHead->children[alphabetIndex] != NULL)
            {

                movingHead = movingHead->children[alphabetIndex];

                Found = 1;
                break;

            }

            

        }

        if(!Found)
        {

            return 0;

        }

    }

    return movingHead->count;

}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{

    if(pTrie != NULL)
    {

        for(int index = 0; index < 26; ++index){
            if(pTrie->children[index] != NULL)
                deallocateTrie(pTrie->children[index]);
        }
    }

    free(pTrie);
    return NULL;

}

// Initializes a trie structure
struct Trie *createTrie()
{

    Trie_t *root = (Trie_t*)malloc(sizeof(Trie_t));
    for(int index = 0; index < 26; ++index)
    {

        root->children[index] = NULL;
        root->count = 0;


    }

    return root;

}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{

    FILE* dictionary = fopen(filename, "r");

    int sizeOfFile = 0;
    char tempString[256];
    if(dictionary != NULL)
    {
        fscanf(dictionary, "%d\n", &sizeOfFile);
        for(int index = 0; index < sizeOfFile; ++index)
        {

            fscanf(dictionary, "%s", tempString);
            int length = strlen(tempString);

            pInWords[index] = (char*)malloc(sizeof(char) * (length + 1));
            
            strncpy(pInWords[index], tempString, length);
            pInWords[index][length] = '\0';
        }
    }
}

int main(void)
{
	char *inWords[256];

    for(int index = 0; index < 256; ++index)
    {

        inWords[index] = NULL;

    }
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
        if(i == 4)
        {

            printf("Debug\n");

        }

		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}

    for(int index =0; index < numWords; ++index)
    {
        if(inWords[index] != NULL)
            free(inWords[index]);

    }

	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}