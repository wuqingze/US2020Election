#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

struct State{
    int electoralVotes;
    string name;
    State(int c, string n):electoralVotes(c), name(n){}
};

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
                if(s.size()>0) s.pop_back();
                cout<<"| "<<c;
                if(c){ cout<<"( "<<s<<" )";}
                cout<<" | ";

                c=0;
                s="";
                for(auto state: TrumpStates){
                    s+=state->name+",";
                    c+=state->electoralVotes;
                }
                if(s.size()>0) s.pop_back();
                cout<<c;
                if(c){ cout<<"( "<<s<<" )";}
                cout<<" | "<<endl<<endl;
                
                return;
            }

            BidenStates.push_back(states[i]);
            f(i+1, n, BidenStates, TrumpStates, states);
            BidenStates.pop_back();

            TrumpStates.push_back(states[i]);
            f(i+1, n, BidenStates, TrumpStates, states);
            TrumpStates.pop_back();
        }

        static void compute(vector<State*> &states){
            vector<State*> biden;
            vector<State*> trump;
            f(0, states.size(), biden, trump, states);
        }
};

int strToInt(string s){
    int ret = 0;
    int n = s.size();
    for(int i=n-1;i>=0;i--){
        ret += pow(s[i]-'0', n-1-i);
    }
    return ret;
}

int main(){
    string line;
    vector<State*> states;
    while(getline(cin, line)){
        int gap = line.find(' ');
        istringstream is(line.substr(0, gap));
        int votes;
        is>>votes;
        string name = line.substr(gap+1, line.size()-gap-1);
        states.push_back(new State(votes, name));
    }
    for(auto s:states) cout<<s->electoralVotes<<" "<<s->name<<endl;
    Solution::compute(states);
    return 0;
}
