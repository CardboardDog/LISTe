#include<iostream>
#include<string>
#include<map>
#include <utility>
using namespace std;
#define L_STRING 0
#define L_LIST 1
#define L_FUNCTION 2
class LISTe{
public:
    bool running = true;
    map<string,pair<char,string>> varMap;
    string substitute(string input){
        bool open = false;
        string varName = "";
        int start = 0;
        string output = input;
        int i = 0;
        while(i<output.length()){
            if(output[i]=='*'){
                if(open){
                    // close on *
                    open = false;
                    output.replace(start,abs(i-start)+1,get<1>(this->varMap[varName]));
                    cout<<i;
                    i = 0;
                }else{
                    // open on *
                    open = true;
                    start = i;
                    varName = "";
                }
            }else{
                varName = varName + output[i];
            }
            i++;
        }
        return output;
    }
    int interpret(string input){
        string statement = "";
        string variableName = "";
        string variableValue = "";
        char variableType;
        bool finished = false;
        bool functionEnded = false;
        int ii = 0;
        for(int i=0;i<input.length();i++){
            //cout<<input[i];
            // check if we are defining a variable
            if(input[i]=='$'){
                finished = false;
                ii = i+1; // start after $
                variableName = "";
                variableValue = "";
                variableType = L_STRING;
                // get variable name
                while(!finished){
                    if(input[ii]==':'){
                        finished = true;
                    }else{
                        variableName = variableName + input[ii];
                        if(input[ii]=='('){
                            variableType = L_FUNCTION;
                            //cout<<"e";
                        }
                    }
                    ii++;
                    if(ii>input.length()){
                        return 1;
                    }
                }
                // get variable value
                finished = false;
                functionEnded = false;
                while(!finished){
                    if(variableType==L_FUNCTION && input[ii]=='!'){
                        while(input[ii]!='&'){
                            variableValue = variableValue + input[ii];
                            ii++;
                        }
                        functionEnded = true;
                    }
                    if(input[ii]=='&'){
                        // functions handle & differently
                        if(variableType!=L_FUNCTION || functionEnded){
                            finished = true;
                        }
                    }else{
                        variableValue = variableValue + input[ii];
                        if(variableType==L_STRING && input[ii]==','){
                            variableType = L_LIST;
                        }
                    }
                    ii++;
                    if(ii>input.length()){
                        return 1;
                    }
                }
                // check if variables are set with other variables ex: $*var1*:*var2*&
                variableName = this->substitute(variableName);
                if(variableType!=L_FUNCTION){
                    variableValue = this->substitute(variableValue);
                }
                cout<<"[var: "<<variableName<<" val: "<<variableValue<<" type: "<<(int)variableType<<"]";
                // allocate variable
                this->varMap[variableName] = make_pair(variableType,variableValue);
                string statement = "";
            }else{
                statement=statement+input[i];
            }
        }
        cout<<endl;
        return 0;
    }
};