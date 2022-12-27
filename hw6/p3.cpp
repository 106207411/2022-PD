#include<iostream>
#include<cstring>
using namespace std;

const int MAX = 100;

int main() {
    char words[MAX+1] = {0};
    char modWords[2*MAX] = {0};
    cin.getline(words, 100);

    // remove multiple spaces from words and put one space between words
    for (unsigned int i = 0; i < strlen(words); i++) {
        if (isspace(words[i]) && isspace(words[i+1])) {
            for (unsigned int j = i; j < strlen(words); j++) {
                // assign the next character to the current character
                words[j] = words[j+1];
            }
            i--;
        }
    }

    int modLen = 0;
    cout << "the words[1] is " << isspace(words[1]) << endl;
    cout << "the words[1] is " << ispunct(words[1]) << endl;
    for (unsigned int i = 0; i < strlen(words); i++) {
        cout <<"i: " << i <<endl;
        // if the current character is a space
        if (isspace(words[i])) {
            cout << "we are in the space" << endl;
            bool notBlank = ispunct(words[i+1]) |
                            ((i > 0) & (words[i-1] == '(' || words[i-1] == '-')) |
                            ((i > 1) & ispunct(words[i-2]) & ispunct(words[i-1]));
            cout << "notBlank: " << notBlank << endl;
            if (!notBlank) {
                modWords[modLen] = ' ';
                modLen++;
            }
            cout << modWords << endl;

        }

        // if the current character is a punctuation
        else if (ispunct(words[i])) {

            // if the current character is (
            if (words[i] == '(') {
                if ((i > 0) & isspace(words[i-1])) {
                    modWords[modLen] = words[i];
                    modLen ++;
                }
                else {
                    modWords[modLen] = ' ';
                    modWords[modLen+1] = words[i];
                    modLen += 2;
                }
            }

            // if the current character is -
            else if (words[i] == '-') {
                modWords[modLen] = words[i];
                modLen ++;
            }

            // if the current character is others
            else {
                if ((i > 0) & !ispunct(words[i-1]) & !ispunct(words[i+1]) & !isspace(words[i+1])) {
                    modWords[modLen] = words[i];
                    modWords[modLen+1] = ' ';
                    modLen += 2;
                }
                else {
                    modWords[modLen] = words[i];
                    modLen ++;
                }
            }
        }
    
        // if the current character is a letter
        else {
            modWords[modLen] = words[i];
            modLen ++;
            cout << modWords << endl;

        }
    }
    cout << modWords << endl;
    cout << "123" <<  endl;
    return 0;
}