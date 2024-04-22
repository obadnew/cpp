#include <iostream>
#include <string>
std::string reverse_string (const std::string& str){
    std::string new_string = "";
   for (int i = str.size(); i != 0; i--)
   new_string.append(1,str [i]);
   return new_string;
}

int main(){
    int obad [5];
    std::string str = "this is my houseccccccccc";
    int counter = 0;
    for (int i=0;i<5;i++) {
        std::cout << str << std::endl;
        for (char c : str){
            if (c == 'c')
            counter++;
        }
    }
std::cout << counter<< std::endl;
std::cout <<reverse_string(str);
}