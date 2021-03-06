#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

struct State{
    char color;
    int electoralVotes;
    string name;
    State(char cr, int c, string n):color(cr), electoralVotes(c), name(n){}
};

string inttostr(int n){
    string s;
    while(n){
        s += (n%10)+'0';
        n /= 10;
    }
    int i=0, j=s.size()-1;
    while(i<=j){
        char t = s[i];
        s[i] = s[j];
        s[j] = t;
        i++;
        j--;
    }
    return s;
}
class Solution{
    public:
        static void f(int i, int n, vector<State*> &BidenStates,
                vector<State*> &TrumpStates, vector<State*> &states){
            if(i>=n){
                int c=0;
                string s="";
                for(auto state: BidenStates){
                    s+=state->name+",";
                    c += state->electoralVotes;
                }
                s.pop_back();
                cout<<"<tr> <td>"<<inttostr(c)<<" ( "<<s<<" ) </td> ";
                c=0;
                s="";
                for(auto state: TrumpStates){
                    s+=state->name+",";
                    c+=state->electoralVotes;
                }
                s.pop_back();
                cout<<"<td>"<<inttostr(c)<<" ( "<<s<<" ) </td> </tr>"<<endl;
                return;
            }

            if(states[i]->color == 's'){
                BidenStates.push_back(states[i]);
                f(i+1, n, BidenStates, TrumpStates, states);
                BidenStates.pop_back();

                TrumpStates.push_back(states[i]);
                f(i+1, n, BidenStates, TrumpStates, states);
                TrumpStates.pop_back();
            }else if(states[i]->color == 'b'){
                BidenStates.push_back(states[i]);
                f(i+1, n, BidenStates, TrumpStates, states);
                BidenStates.pop_back();
            }else{
                TrumpStates.push_back(states[i]);
                f(i+1, n, BidenStates, TrumpStates, states);
                TrumpStates.pop_back();
            }
        }

        static void compute(vector<State*> &states){
            vector<State*> biden;
            vector<State*> trump;
            f(0, states.size(), biden, trump, states);
        }
};

int main(){
    string line;
    vector<State*> states;
    while(getline(cin, line)){
        char color;
        int electoralVotes;
        string name;
        string t;

        istringstream is(line);
        is>>color;
        is>>electoralVotes;
        while(is>>t) name+=t;

        states.push_back(new State(color, electoralVotes, name));
    }
    Solution::compute(states);
    return 0;
}
