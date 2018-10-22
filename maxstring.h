#ifndef MAXSTRING_H_
#define MAXSTRING_H_
#include <iostream>
int strlen(const char * a);
void strcpy(char *a, const char *b);
class String
{
    char str[200]="";
public:
    String () {};
    String (const char * s)
    {
        strcpy(str,s);
    }
    String (const String & st)
    {
        strcpy(str,st.str);
    }
    ~String(){}
    int length() const {return strlen(str);};
    String & get(void);
    void show(void) const;
    String & operator=(const String & st);
    bool operator==(const char * s);
    bool operator!=(const char * s);

};

#endif // MAXSTRING_H_
