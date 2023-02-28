#include <stdio.h>
#include <assert.h>

int toLower(int c);
int isSpace(int c);
int isLetter(int c);
int charBit(int c);

void addToSet(unsigned int *s, int c) {
    *s |= charBit(c);
}

int isKeyExists(unsigned int s, int c) {
    return ((s & charBit(c)) != 0);
}

int toLower(int c) {
    return (c >= 'A' && c <= 'Z' ? c - 'A' + 'a' : c);
}

int isSpace(int c) {
    return (c == ' ' || c == ',' || c == '\n' || c == '\t');
}

int isLetter(int c) {
    return (c >= 'a' && c <= 'z');
}

int charBit(int c) {
    return (1 << (c - 'a'));
}

void testIsSpace(){
    assert(isSpace(' ') == 1);
    assert(isSpace('a') == 0);
}

void testToLower(){
    assert(toLower('a') == (int) 'a');
    assert(toLower('A') == (int) 'a');
}

void testIsLetter(){
    assert(isLetter('a') == 1);
    assert(isLetter('{') == 0);
}

void testAll(){
    testIsLetter();
    testIsSpace();
    testToLower();
}

int main() {
    testAll();

    int ch, letterFound = 0, isWordFound = 0, isSkip = 0, isInput = 0, num = 0, numFirst = 0;
    unsigned int soglSet = 0, glasSet = 0;

    addToSet(&glasSet, 'a');
    addToSet(&glasSet, 'o');
    addToSet(&glasSet, 'i');
    addToSet(&glasSet, 'u');
    addToSet(&glasSet, 'y');
    addToSet(&glasSet, 'e');

    addToSet(&soglSet, 'v');
    addToSet(&soglSet, 'b');
    addToSet(&soglSet, 'g');
    addToSet(&soglSet, 'd');
    addToSet(&soglSet, 'z');
    addToSet(&soglSet, 'l');
    addToSet(&soglSet, 'm');
    addToSet(&soglSet, 'n');
    addToSet(&soglSet, 'r');

    while ((ch = getchar()) != '1') {
        ch = toLower(ch);

        if (!isSpace(ch)) {
            if (isSkip) continue;

            if (!isInput) {
                num++;
                isInput = 1;
            }

            if (isLetter(ch)) {
                if (!letterFound) {
                    if (!isKeyExists(glasSet, ch)) {
                        if (!isKeyExists(soglSet, ch)) isSkip = 1;
                        else {
                            letterFound = 1;
                            isWordFound = 1;
                        }
                    }
                }
                else if (!isKeyExists(glasSet, ch) && !isKeyExists(soglSet, ch)) isWordFound = 0;
            }
        }
        else {
            if (isWordFound && !numFirst) numFirst = num;

            isInput = 0;
            letterFound = 0;
            isSkip = 0;
        }
    }

    if (numFirst > 0) printf("Слово #%d - содержит только звонкие согласные\n", numFirst);
    else printf("Не найдено слова только со звонкими согласными\n");

    return 0;
}

