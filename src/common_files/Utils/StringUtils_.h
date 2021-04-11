#pragma once


namespace SU
{
    char *Strcat(char *dest, pchar source);

    void SplitToWords(pchar symbols, uint number, std::vector<std::string> &out);

    int Length(pchar str);

    int Compare(pchar str1, pchar str2);

    void ReplaceSymbols(std::string &string, char old, char young);

    // Возвращает true, если строка string начинается с последовательности символов symbols
    bool BeginWith(pchar string, pchar symbols);

    bool VerifyOnMask(pchar string, pchar mask);
}
