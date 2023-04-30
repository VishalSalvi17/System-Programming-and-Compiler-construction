/*
Vishal Salvi
Batch c
2019230069
Roll No : 52
*/
/*
production in the form of non_terminal and transition space seprated
example :

input :
3 3 5 
A aB
A Bb
B Ca
C $
C Ac



CFG:
numberOfNonTerminal= 3
numberOfTerminal=3
number_of_productions=6
rules =
A -> Bb |aB 
B -> Ca |
C -> $ |Ac |Bb 

compiled with 
g++ -std=c++17 SPCC_EXP5.cpp
*/

#include<bits/stdc++.h>
using namespace std;


 
map<string,set<string>> rules;
set<string> nonTerminal;

bool removeBackEdge(string currentState){
    for(auto trans : rules[currentState]){
        string previousState(1,trans[0]);
        if (trans.size()>1 and trans[1]=='\'')
            continue;
        if("A"<=previousState and previousState<currentState){
            // cout<<currentState<<' '<<previousState<<'\n';
            string rem= trans.substr(1,trans.size()-1);
            rules[currentState].erase(trans);
            for(auto ptar:rules[previousState]){
                rules[currentState].insert(ptar+rem);
            }
            return true;
        }
    }
    return false;
}


void test_case(){ 
    int numberOfNonTerminal,numberOfTerminal,numberOfProduction;
    
    //$ is nulll
    cin>>numberOfNonTerminal>>numberOfTerminal>>numberOfProduction;
    for(int i=0;i<numberOfProduction;i++){
        string c; string s; 
        cin>>c>>s;
        rules[c].insert(s);
        nonTerminal.insert(c);
    }
    cout<<"\nCNF\n\n";
    for(auto x:nonTerminal){
        cout<<x<<" -> ";
        for(auto s:rules[x]){
            cout<<s<<" | ";
        }
        cout<<'\n';
    }
    cout<<"\n\n";
    //order all the non terminal and remove back edges and self loops 
    //first remove back edges than self loops.Create a topological order 
    for(auto currentState:nonTerminal){
        while(removeBackEdge(currentState)){}  //remove 
        vector<string> a,b;
        for(auto trans : rules[currentState]){
            if (string(1,trans[0])!=currentState){
                b.push_back(trans);
            }else{
                a.push_back(trans);
            }
        }  
        rules[currentState].clear();
        string newState=currentState+"\'";
        for(auto trans:b){
            if(trans!="$"){
                rules[currentState].insert(trans+newState);
            }else{
                rules[currentState].insert(newState);
            }
        }
        rules[newState].insert("$");
        for(auto trans:a){
            string rem=trans.substr(1,trans.size()-1);
            rules[newState].insert(rem+newState);
        }
    }
    cout<<"\n After Removing left Recurssion\n\n";
    for(auto x:nonTerminal){
        cout<<x<<" -> ";
        for(auto s:rules[x]) cout<<s<<" | "; cout<<"\n";
        x=x+"\'"; cout<<x<<" -> ";
        for(auto s:rules[x]) cout<<s<<" | "; cout<<'\n';
    }
}
 
int main(int argc, char** argv){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    t=1;
    // cin>>t;
    while(t--){
        test_case();
    }
}
