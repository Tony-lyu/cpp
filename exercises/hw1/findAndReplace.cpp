#include <iostream>
#include <string>
#include <list>
using namespace std;

// finds all occurance of target and returns list of positions
list<int> findAll(string paragraph, string target) {
    list<int> positions;
    //find the first occurance and remember its position
    int pos = paragraph.find(target, 0);
    while(pos != string::npos) {
        // add the position at the end of the list
        positions.push_back(pos);
        // keep finding next position, with offset of current position
        pos = paragraph.find(target, pos + target.length());
    }
    return positions;
}

// replace all <target> from given paragraph with <replacement>
string replaceAll(string paragraph, string target, string replacement) {
    // find first occurence of target
    int pos = paragraph.find(target);
    while(pos != string::npos) {
        // replace target with replacement string
        paragraph.replace(pos, target.length(), replacement);
        // keep replacing
        pos = paragraph.find(target, pos + replacement.length());
    }
    return paragraph;
}

int main() {
    string paragraph, target, replacement;
    cout << "Enter a paragraph: ";
    getline(cin, paragraph);

    cout << "Enter a word or a sentence to find: ";
    getline(cin, target);

    list<int> occurrences = findAll(paragraph, target);
    cout << "Occurrences found: " << occurrences.size() << endl;
    for (int pos = 0; pos < occurrences.size(); ++pos) {
        cout << "Found at position: " << pos << endl;
    }

    cout << "Enter a word or a sentence to replace it with: ";
    getline(cin, replacement);

    string replaced = replaceAll(paragraph, target, replacement);
    cout << "\nReplaced Paragraph:\n" << replaced << endl;

    return 0;
}
