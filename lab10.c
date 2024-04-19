#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    struct Trie *children[26];
    int count;
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *pCrawl = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (pCrawl->children[index] == NULL) {
            pCrawl->children[index] = (struct Trie *)malloc(sizeof(struct Trie));
            for (int j = 0; j < 26; j++) {
                pCrawl->children[index]->children[j] = NULL;
            }
            pCrawl->children[index]->count = 0;
        }
        pCrawl = pCrawl->children[index];
    }
    pCrawl->count++;
}

// computes the number of occurrences of the word
int numberOfOccurrences(struct Trie *pTrie, char *word)
{
    struct Trie *pCrawl = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (pCrawl->children[index] == NULL) {
            return 0;
        }
        pCrawl = pCrawl->children[index];
    }
    return pCrawl->count;
}

// deallocates the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < 26; i++) {
        deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *root = (struct Trie *)malloc(sizeof(struct Trie));
    for (int i = 0; i < 26; i++) {
        root->children[i] = NULL;
    }
    root->count = 0;
    return root;
}

// this function will return the number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* inFile = fopen(filename, "r");
    if (inFile == NULL) return -1;

    int count=0;

    fscanf(inFile, "%d\n", &count);
    char word[100];
    for (int i = 0; i <  count; i++){
        fscanf(inFile, "%s\n", word);
        pInWords[i] = (char*)calloc(strlen(word), sizeof(char));
        strcpy(pInWords[i], word);
    }
    return count;

}

int main(void)
{
    char *inWords[256];
	
    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    printf("Number of words in the dictionary: %d\n", numWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }
	
    // Initialize a trie structure
    struct Trie *pTrie = createTrie();
    // Insert each word from the dictionary into the trie
    for (int i = 0; i < numWords; i++) {
        insert(pTrie, inWords[i]);
    }
    // Parse each word in pWords and print the number of occurrences in the trie
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }
    // Deallocate the trie
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}

