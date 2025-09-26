# Slang Word Dictionary (Trie Implementation)

![Language](https://img.shields.io/badge/language-C-blue.svg)
![Status](https://img.shields.io/badge/status-active-success.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

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

## 🔧 Requirements
- A C++ compiler (GCC, MinGW, or Clang)
- Works on **Windows, Linux, or macOS**

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
```

---

## 📂 Project Structure
```
📦 Data Structure - Slang Dictionary
 ┣ 📜 2702243590_AOL CODE.cpp       # Main program (C++)
 ┣ 📜 README.md                     # Documentation
 ┗ 📜 2702243590_Documentation.pdf  # Original documentation
```

---

## ▶️ How to Run
1. Make sure you have a C++ compiler (e.g., g++) installed.  
2. Compile the program:
   ```bash
   g++ "2702243590_AOL CODE.cpp" -o slang_dict
   ```
3. Run the executable:
   ```bash
   ./slang_dict
   ```

---

## ▶️ Usage Example
```
1. Release a new slang word
2. Search a slang word
3. View all slang words starting with a certain prefix
4. View all slang words
5. Exit
>> 1
Input a new slang word [Must be more than 1 characters and contains no space]: lol
Input a new slang word description [Must be more than 2 words]: laughing out loud
Successfully released a new slang word
```

---

## 🖼️ Example Screenshots
### Main Menu
![Main Menu](screenshots/menu.png)

### Adding a New Slang Word
![Add Slang](screenshots/add_slang.png)

### Searching for a Slang Word
![Search Slang](screenshots/search_slang.png)

### Viewing Words by Prefix
![Prefix Search](screenshots/prefix_search.png)

### Viewing All Slang Words
![View All](screenshots/view_all.png)

---

## 🤝 Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

---

## 📄 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
