# Slang Word Dictionary (Trie Implementation)

This project is an implementation of the **Trie data structure** in C, designed to create a slang word dictionary.  
The program allows users to add new slang, search for specific slang, view slang words by prefix, and display all stored slang.

---

## 📌 Features
1. **Release a new slang word**  
   Add a new slang word with its description into the Trie.
2. **Search a slang word**  
   Search for a slang word and display its description.
3. **View all slang words starting with a certain prefix**  
   Display all slang words beginning with a given prefix.
4. **View all slang words**  
   Display all slang words stored in the Trie.
5. **Exit**  
   Exit the program.

---

## 🏗️ Data Structure
The program uses a **Trie** consisting of:
- `character` → stores a character at the node.
- `desc` → stores the slang description.
- `word` → marks the end of a valid word.
- `children[128]` → pointers to child nodes based on ASCII values.

---

## ⚙️ Key Functions
### Insert a Word
```c
void insertWord(struct trieNode *root, char str[], char desc[]) {
    if (*str == '\0') {
        root->word = 1;
        strcpy(root->desc, desc);
    } else {
        char lower = tolower(*str);
        int idx = (int) lower - 'a';
        if (root->children[idx] == NULL) {
            root->children[idx] = createNode(lower);
        }
        insertWord(root->children[idx], str + 1, desc);
    }
}
```
### Search a Word
```c
void searchSlang(struct trieNode *root, char search[]) {
    struct trieNode *curr = root;
    for (int i = 0; search[i] != '\0'; i++) {
        int idx = search[i] - 'a';
        if (curr->children[idx] == NULL) {
            printf("Word not found.\n");
            return;
        }
        curr = curr->children[idx];
    }
    if (curr != NULL && curr->word == 1) {
        printf("Slang word: %s\n", search);
        printf("Description: %s\n", curr->desc);
    } else {
        printf("Word not found.\n");
    }
}
