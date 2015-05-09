#ifndef STRUTILS_H_
#define STRUTILS_H_

#include <string>

using namespace std;

/**
 * @brief Function performs case insensitive string comparison
 * */
//bool noCaseStringCompare(const string& parStr1, const string& parStr2);

void SaveBufferToFile(const string& fileName, const char* buffer, int size);
void SaveStringToFile(const string& fileName, const string& strToSave);
string convertFromUTF8toLatin1(const string &inputString);
int UTF8ToISOLatin1(unsigned char* outBuffer, int *outBuffLen,
                    const unsigned char* inBuffer, int *inBuffLen);
void ReplaceString(string & pString, const string & sFind,
                   const string & sReplace, const int iStartPos = 0);

#endif /* STRUTILS_H_ */
