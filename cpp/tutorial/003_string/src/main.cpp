#include <iostream>
#include <string>

using namespace std ; 

int main() 
{ 
    string str1 = "abcdefghijklm" ; 
    string str2 = "nopqrstuvwxyz" ; 

    cout << str1 << endl ; 

    cout << str2 << endl ; 

    cout << str1 + str2 << endl ; 

    cout << str1.substr( 3 , 5 ) << endl ; 

    cout << str1.substr( 3 ) << endl ; 
    
    return 0 ; 
} 










