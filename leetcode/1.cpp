#include <iostream>
#include <string>
 using namespace std;
void deletestring(const char*pa,const char *pb)
{
    if (NULL == pa || NULL == pb)
    {
        return ;
    }
    
    int hash[256]={-1};
    while ( *pb != '\0')
    {
        hash[*pb] =1;
    }
    char* pslow =pa;
    char* pfast =pa;
    while (*pfast !='\0')
    {
        //如果遇到是不需要字符
        
        if  (hash[*pfast] == -1){
            *pslow =*pfast;
             pslow++;
        }
        //如果遇到需要擅长的字符
        pfast ++;
    }
    *pslow='\0';
    
}}
 int main()
 {
     //string s1, s2;
     //getline(cin, s1);
     //getline(cin, s2);
     char first[100];
     char second[100];
     gets(first);
     gets(second);
     deletestring(first,second);
     return 0;
 }
