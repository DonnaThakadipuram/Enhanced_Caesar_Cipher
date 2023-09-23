/*
name: donna thakadipuram
date: august 31, 2023
description: enhanced caesar cipher with encryption, decryption with key, and brute force description using given vocabulary
*/

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
vector<string> vocab;

int file_read() {
  string filename;
  cout << "Enter vocabulary file name: ";
  cin >> filename;
  cout << endl;

  ifstream din;
  din.open(filename);

  if (din.fail()) {
    cout << "Could not open file.\n";
    return 0;
  }
  string temp_word;

  while (din >> temp_word) {
    temp_word = regex_replace(temp_word, regex("[^a-zA-Z0-9]"), "");
    for (int i = 0; i < temp_word.length(); i++) {
      temp_word[i] = tolower(temp_word[i]);
    }
    vocab.push_back(temp_word);
  }
  cin.ignore();
  return 1;
}

void encrypt() {
  string sentence;
  int shift;

  cout << "Enter a message to encrypt: ";
  getline(cin, sentence);

  cout << endl << "Enter an integer to shift by: ";
  cin >> shift;

  cout << endl;

  string encrypted = sentence;

  for (int i = 0; i < sentence.length(); i++) {
    if (isupper(sentence[i])) {
      encrypted[i] = char(int(sentence[i] + shift - 65) % 26 + 65);
    }

    else if (islower(sentence[i])) {
      sentence[i] = toupper(sentence[i]);
      encrypted[i] = tolower(char(int(sentence[i] + shift - 65) % 26 + 65));
    }

    else {
    }
  }

  cout << "Encrypted string: " << encrypted << endl << endl;
}

string decrypt(string d_sentence, int d_shift) {
  string decrypted = d_sentence;

  for (int i = 0; i < d_sentence.length(); i++) {
    if (isupper(d_sentence[i])) {
      decrypted[i] = char(int(d_sentence[i] - d_shift - 65 + 26) % 26 + 65);
    }

    else if (islower(d_sentence[i])) {
      d_sentence[i] = toupper(d_sentence[i]);
      decrypted[i] =
          tolower(char(int(d_sentence[i] - d_shift - 65 + 26) % 26 + 65));
    }

    else {
    }
  }

  return decrypted;
}

void brute_force(string d_sentence) {
  bool match_found = false;
  int curr_shift = 0;
  string decrypted = "";

  while (!match_found && curr_shift < 26) {
    vector<string> d_vector;
    decrypted = decrypt(d_sentence, curr_shift);
    string temp_word;

    for (int i = 0; i < decrypted.length(); i++) {
      if (decrypted[i] == ' ') {
        d_vector.push_back(temp_word);
        temp_word = "";
      } else {
        temp_word += tolower(decrypted[i]);
      }
    }
    d_vector.push_back(temp_word);

    for (int i = 0; i < d_vector.size(); i++) {
      bool word_match = false;
      for (int j = 0; j < vocab.size(); j++) {
        if (d_vector[i] == vocab[j]) {
          word_match = true;
          break;
        }
      }
      if (word_match) {
        match_found = true;
        break;
      }
    }

    curr_shift++;
  }

  if (match_found) {
    cout << "Decrypted string: " << decrypted << endl;
    cout << "Shift: " << curr_shift - 1 << endl << endl;
  } else {
    cout << "No match found." << endl;
  }
}


int main() {
  char option;
  while (option != '0') {
    cout << "Welcome. What would you like to do?" << endl;
    cout << "0) Quit" << endl;
    cout << "1) Encrypt" << endl;
    cout << "2) Decrypt (if key is known)" << endl;
    cout << "3) Brute force decryption" << endl;
    cout << "Enter command: ";
    cin >> option;
    cin.ignore();
    cout << endl;

    switch(option){
      case '0':
        break;
      case '1':
        encrypt();
        break;
      case '2':
        {
        string to_decrypt = "";
        int key;
        
        cout << "Enter sentence to decrypt: ";
        getline(cin, to_decrypt);
        cout << endl << "Enter key: ";
        cin >> key;

        cout << "Decrypted Message: " << decrypt(to_decrypt, key) << endl << endl;
        }
        break;
      case '3':
        file_read();
        string to_bf;
        cout << "Enter sentence to decrypt: ";
        cin.clear();
        getline(cin, to_bf);
        brute_force(to_bf);
        break;
        
    };
  }

}
