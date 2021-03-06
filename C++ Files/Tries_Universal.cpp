#include <iostream>
#include <map>

using namespace std;
/* In this implementation of Tries, the endOfWord is marked by a '*' character.
   Therefore, the Trie can contain any character except for '*'
*/
typedef struct TrieNode {
	map<char,TrieNode *> table;
	bool isEndOfWord;
}Trie;

Trie * newNode() {
	Trie * new_node = new Trie();
	new_node -> isEndOfWord = false; 
	new_node -> table['*'] = NULL;
	return new_node;
}

void insert(Trie * root,string key) {

	Trie * root_ref = root;
	map<char,Trie *>::iterator iter;
	for (int i = 0; key[i] != '\0'; i++)
	{
		iter = root_ref -> table.find(key[i]);
		if (iter == root_ref -> table.end()) {//If character does not exist in the Trie
			root_ref -> table.erase('*'); //Erase the * entry from the current node's table
			root_ref -> table[key[i]] = newNode();//Add referene of the new node to the current key
		}

		root_ref = root_ref -> table[key[i]];//Move the pointer ahead 
	}
	root_ref -> isEndOfWord = true;//Mark the end of word as true
}

bool search(Trie * root, string key) {
	Trie * root_ref = root;
	map<char, Trie *> :: iterator iter;
	for (int i = 0; key[i] != '\0'; i++)
	{
		iter = root_ref -> table.find(key[i]);
		if (iter == root_ref -> table.end())//Character not found
			return false;
		root_ref = root_ref -> table[key[i]];
	}
	if (root_ref -> isEndOfWord)
		return true;
	return false;
}

bool delete_util(Trie * root, string key, int i, int length) {
	if (i == length) {
		if (root -> table.find('*') != root -> table.end()) //If reached endOfWord, then delete this node
			return false;
		root -> isEndOfWord = false;
		return true;//If the last node was not empty
	}
	if (delete_util(root -> table[key[i]],key,i+1,length))//If the last node was not empty,then simply return
		return true;
	else {
		root -> table[key[i]] = NULL; //Delete the previous entry
		root -> table.erase(key[i]); //Clear the current entry from map
		if (root -> isEndOfWord) {//If the current entry is an end of word of an another word
			root -> table['*'] = NULL;//Set the current node as the last node (denoted by '*')
			return true;
		}
		else
			if (root -> table.size() < 1) //Check if there is any other Non-NULL child node present
				return false;//If the map is empty, then delete the current node
	}
	return true;
}

void delete_node(Trie * root, string key) {
	int i = 0;
	int deleted = 0;
	if (key.length() > 0) {
		if (search(root,key)) {
			if (delete_util(root,key,i,key.length()))
				deleted = 1;
		}
	}
	if (deleted)
		cout<<"Deleted"<<endl;
	else
		cout<<"Not Deleted (Not a word in Trie)"<<endl;
}

int main() {
	string keys[] = {"b","by","bye","byes","bicycle"};
	int n = sizeof(keys)/sizeof(keys[0]);
	Trie * root = newNode();
	for (int i = 0; i < n; i++)	
		insert(root,keys[i]);
	delete_node(root,"bicycleb");
	search(root,"bicycle") ? cout<<"Found"<<endl : cout<<"Not Found"<<endl;
	return 0;
}