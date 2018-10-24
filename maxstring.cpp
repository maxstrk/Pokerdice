#include<iostream>
#include "maxstring.h"
String & String::get(void)
{
    char stringe[200];
    std::cin >>stringe;
    strcpy(str,stringe);
    return *this;
}
void String::show(void) const
{
    std::cout << str;
}
String & String::operator=(const String & st)
{
    if (this==&st) return *this;
    strcpy(str,st.str);
    return *this;
}
bool String::operator==(const char * s)
{
    if(this->length()!=strlen(s)) return false;
    for (int i=0; i < strlen(s); i++) if (str[i]!=s[i]) return false;
    return true;
}
bool String::operator!=(const char * s)
{
    for (int i=0; i < strlen(s); i++) if (str[i]!=s[i]) return true;
    return false;
}
int strlen(const char * a)
{
    int i=0;
    while(a[i]!='\0') i++;
    return i;
}
void strcpy(char *a, const char *b)
{
    int la=strlen(a);
    for (int i=0; i < la; i++)
        a[i]='\0';
    for (int i=0; i < strlen(b); i++)
        a[i]=b[i];
    a[strlen(b)]='\0';
}


