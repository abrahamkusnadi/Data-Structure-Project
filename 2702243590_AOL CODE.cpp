#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>

int angka = 0;
int isi = 0;

struct trieNode{
	char character;
	char desc[1001];
	int word;
	struct trieNode *children[128];	
}*root = NULL;

void createNode();
void insertWord(struct trieNode *root, char str[], char desc[]);
void printTrieContents(struct trieNode *node, char buffer[], int depth);
void searchPrefix();
void searchSlang(struct trieNode *root, char search[]);
void searchSlangPrefix(struct trieNode *curr, char buffer[], int depth, char search[]);

// Validation
// fungsi untuk mengetahui sudah lebih dari atau sama dengan 2 kata atau belumm
int twoWords(char string[]){
	int wordCount = 0;
	for(int i = 0 ; string[i] != '\0' ; i++){
		if(string[i] == ' '){
			wordCount++;
		}
	}
	
	if(wordCount >= 2){
		return 1;
	}else{
		return 0;
	}
}

//fungsi untuk mengetahui apakah ada spasi di dalam string yang dicek
int hasSpace(char string[]){
	int flag = 1;
	for(int i = 0 ; i < strlen(string) ; i++){
		if(string[i] == ' '){
			flag = 0;
			break;
		}else{
			continue;
		}
	}
	
	if(flag == 1){
		return 1;
	}else{
		return 0;
	}
}

struct trieNode *createNode(char ch){
	struct trieNode *newNode = (struct trieNode*)malloc(sizeof(struct trieNode));
	newNode->character = ch;
	newNode->word = 0;
	strcpy(newNode->desc, "\0");
	for(int i = 0 ; i < 128 ; i++){
		newNode->children[i] = 0;
	}
	return newNode;
}

//fungsi memasukkan kata ke trie nya
void insertWord(struct trieNode *root, char str[], char desc[]){
	if(*str == '\0'){
		root->word = 1;
		
		if(strcmp(root->desc, "\0") != 0){
			printf("\nSuccesfully updated a slang word.\n");
		}else{
			printf("\nSuccesfully released a new slang word\n");
		}
		strcpy(root->desc, desc);
	}else{
		char lower = tolower(*str);
		int idx = (int) lower - 'a';
		
		if(root->children[idx] == NULL){
			root->children[idx] = createNode(lower);
		}
		
		insertWord(root->children[idx], str + 1, desc);
		
	}
	
}


//2 function buat ngeview all data in trie
void printAll(struct trieNode *curr, char buffer[], int depth){
	if(curr->word == 1){
		buffer[depth] = '\0';
		printf("%d. %s\n", angka, buffer);
		angka++;
	}
	
	for(int i = 0 ; i < 128 ; i++){
		if(curr->children[i] != NULL){
			buffer[depth] = i + 'a';
			printAll(curr->children[i], buffer, depth + 1);
		}
	}
}

void printTrieContents(){
	char buffer[1001];
	if(isi  == 0){
		printf("\nThere is no slang word yet in the dictionary.\n");
	}else{
		angka = 1;
		printf("\nList of all slang words in the dictionary: \n");
		printAll(root, buffer, 0);
	}
}




//2 fungsi untuk mencari kata dari sebuah prefix
void searchPrefix(){
	char search[1001];

	int spaceflag = 0;
	
	do{
		printf("Input a prefix to be searched [Must be more than 1 characters and contains no space]: ");
		scanf("%[^\n]", search);
		getchar();
		spaceflag = hasSpace(search); 
	}while(strlen(search) <= 1 || spaceflag == 0);
	
	char kata[1001];
	angka = 1;
	
	searchSlangPrefix(root, kata, 0, search);
	
	if(angka == 1){
		printf("\nThere is no prefix \"%s\" in the dictionary.\n", search);
	}
}

void searchSlangPrefix(struct trieNode *curr, char buffer[], int depth, char search[]){
	if(curr->word && strncmp(buffer, search, strlen(search)) == 0){
		if(angka == 1){
			printf("\nWords starts with \"%s\":\n", search);

		}
		buffer[depth] = '\0';
		printf("%d. %s\n", angka, buffer);
		angka++;
		
	}
	
	for(int i = 0 ; i < 128 ; i++){
		if(curr->children[i] != NULL){
			buffer[depth] = i + 'a';
			searchSlangPrefix(curr->children[i], buffer, depth + 1, search);
		}
	}
}


//ini buat fungsi menu mencari slang
void searchSlang(struct trieNode *root, char search[]){
	struct trieNode *curr =root;
	
	for(int i = 0 ; search[i] != '\0' ; i++ ){
		int idx = search[i] - 'a';
		if(curr->children[idx] == NULL){
			printf("There is no word \"%s\" in the dictionary.\n", search);
			return;
		}
		curr = curr->children[idx];
	}
	
	if(curr != NULL && curr->word == 1){
		printf("\nSlang word : %s\n", search);
		printf("Description : %s\n", curr->desc);
	}else{
		printf("There is no word \"%s\" in the dictionary\n", search);
	}
}

int main(){
	
	int choice = 0;
	char newSlang[1001];
	char desc[1001];
	int spaceflag = 0;
	int moreflag = 0;
	char search[1001];
	

	root = createNode('\0');
	
	do{
		system("cls");
		printf("1. Release a new slang word\n");
		printf("2. Search a slang word\n");
		printf("3. View all slang words starting with a certain prefix word\n");
		printf("4. View all slang word\n");
		printf("5. Exit\n");
		
		do{
			printf(">> ");
			scanf("%d", &choice);
			getchar();			
		}while(choice < 1 || choice > 5);
		
		switch(choice){
			case 1:
				do{
					printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
					scanf("%[^\n]", newSlang);
					getchar();
					spaceflag = hasSpace(newSlang); 
					
				}while(strlen(newSlang) <= 1 || spaceflag == 0);
				
				do{
					printf("Input a new slang word description [Must be more than 2 words]: ");
					scanf("%[^\n]", desc);
					getchar();
					moreflag = twoWords(desc);
					
				}while(moreflag == 0);
				
				insertWord(root, newSlang, desc);
				isi = 1;
				
				printf("\nPress Enter to continue. . .\n");	
				break;
			case 2:
				do{
					printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
					scanf("%[^\n]", search);
					getchar();
					spaceflag = hasSpace(search); 
				}while(strlen(search) <= 1 || spaceflag == 0);
	
				searchSlang(root, search);
				
				printf("\nPress Enter to continue. . .\n");	
				break;
				
			case 3:
				searchPrefix();
				printf("\nPress Enter to continue. . .\n");		
				break;
				
			case 4:
				printTrieContents();
				printf("\nPress Enter to continue. . .\n");	
				break;
				
			case 5:
				printf("\nThank you... Have a nice day :)\nPress Enter to exit!\n");
		}
	
		getchar();
	}while(choice != 5);
	
	
}
