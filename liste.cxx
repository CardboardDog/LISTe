#include "interpret.hxx"
int main(){
    LISTe liste = LISTe();
    string input;
    while(liste.running){
        getline(cin,input);
        liste.interpret(input);
    }
}