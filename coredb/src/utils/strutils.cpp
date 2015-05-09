#include <cctype>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "strutils.h"

//bool noCaseStringCompare(const string& parStr1, const string& parStr2)
//{
//    // MKP: [#153605] 16/12/11 01.32 make application faster
////    string str1Cpy(parStr1);
////    string str2Cpy(parStr2);
////
////    transform(str1Cpy.begin(), str1Cpy.end(), str1Cpy.begin(), ::tolower);
////    transform(str2Cpy.begin(), str2Cpy.end(), str2Cpy.begin(), ::tolower);
////    return (str1Cpy == str2Cpy);
//    return (strcasecmp(parStr1.c_str(), parStr2.c_str()) == 0);
//    // MKP: [#153605] 16/12/11 01.32 end make application faster
//}

void SaveBufferToFile(const string& fileName, const char* buffer, int size)
{
    fstream fileStr;

    try
    {
        fileStr.open(fileName.c_str(), fstream::out | fstream::trunc);

        if (fileStr.is_open())
        {
            fileStr.write(buffer, size);
            fileStr.close();
        }
    }
    catch (exception& e)
    {
        cout << "SaveBufferToFile exception:" << endl << e.what() << endl;
    }
}

void SaveStringToFile(const string& fileName, const string& strToSave)
{
    fstream fileStr;

    try
    {
        fileStr.open(fileName.c_str(), fstream::out | fstream::trunc);

        if (fileStr.is_open())
        {
            fileStr << strToSave;
            fileStr.close();
        }
    }
    catch (exception& e)
    {
        cout << "SaveStringToFile exception:" << endl << e.what() << endl;
    }
}

string convertFromUTF8toLatin1(const string &inputString)
{
    string convertedString = "";
    int destSize = inputString.size();
    int srcSize = inputString.size();
    char * dest = new char[destSize];
    int convDest = UTF8ToISOLatin1((unsigned char *) dest, &destSize,
                                   (unsigned char *) inputString.c_str(),
                                   &srcSize);

    if (convDest >= 0)
    {
        convertedString.assign(dest, convDest);
    }

    delete [] dest;

    if (convertedString == "")
    {
        convertedString.assign(inputString);
    }

    return convertedString;
}

int UTF8ToISOLatin1(unsigned char* outBuffer, int *outBuffLen,
                  const unsigned char* inBuffer, int *inBuffLen)
{
    const unsigned char* processed = inBuffer;
    const unsigned char* outBuffEnd;
    const unsigned char* outBuffStart = outBuffer;
    const unsigned char* inBuffStart = inBuffer;
    const unsigned char* inBuffEnd;
    unsigned int outChar, inChar;
    int trailing = 0;

    if (outBuffer == NULL || outBuffLen == NULL || inBuffLen == NULL
            || inBuffer == NULL)
        return (-1);

    inBuffEnd = inBuffer + (*inBuffLen);
    outBuffEnd = outBuffer + (*outBuffLen);

    while (inBuffer < inBuffEnd)
    {
        inChar = *inBuffer++;
        if (inChar < 0x80)
        {
            outChar = inChar;
            trailing = 0;
        }
        else if (inChar < 0xC0)
        {
            /* trailing byte in leading position */
            *outBuffLen = outBuffer - outBuffStart;
            *inBuffLen = processed - inBuffStart;
            return (-2);
        }
        else if (inChar < 0xE0)
        {
            outChar = inChar & 0x1F;
            trailing = 1;
        }
        else if (inChar < 0xF0)
        {
            outChar = inChar & 0x0F;
            trailing = 2;
        }
        else if (inChar < 0xF8)
        {
            outChar = inChar & 0x07;
            trailing = 3;
        }
        else
        {
            /* no chance for this in IsoLatin1 */
            *outBuffLen = outBuffer - outBuffStart;
            *inBuffLen = processed - inBuffStart;
            return (-2);
        }

        if ((inBuffEnd - inBuffer) < trailing)
        {
            break;
        }

        for (; trailing; trailing--)
        {
            if (inBuffer >= inBuffEnd)
                break;
            if (((inChar = *inBuffer++) & 0xC0) != 0x80)
            {
                *outBuffLen = outBuffer - outBuffStart;
                *inBuffLen = processed - inBuffStart;
                return (-2);
            }
            outChar <<= 6;
            outChar |= inChar & 0x3F;
        }

        /* assertion: outChar is a single UTF-4 value */
        if (outChar <= 0xFF)
        {
            if (outBuffer >= outBuffEnd)
                break;
            *outBuffer++ = outChar;
        }
        else
        {
            /* no chance for this in IsoLat1 */
            *outBuffLen = outBuffer - outBuffStart;
            *inBuffLen = processed - inBuffStart;
            return (-2);
        }
        processed = inBuffer;
    }
    *outBuffLen = outBuffer - outBuffStart;
    *inBuffLen = processed - inBuffStart;

    return (*outBuffLen);
}

void ReplaceString(string & srcString, const string & sFind,
                   const string & sReplace, const int iStartPos)
{
    int iFindPos = -1;

    iFindPos = srcString.find(sFind, iStartPos);
    if (iFindPos >= 0)
    {
        srcString.replace(iFindPos, sFind.size(), sReplace);
        if (iFindPos + sReplace.size() + 1 <= srcString.size())
        {
            ReplaceString(srcString, sFind, sReplace, iFindPos + sReplace.size() + 1);
        }
    }
}
