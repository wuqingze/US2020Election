#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_set>
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
        static void f(int i, int n, int count,
                vector<State*> &states, unordered_set<int> &ret){
            if(i>=n){
                if(ret.count(count)) return;
                ret.insert(count);
                cout<<"| "<<inttostr(count)<<" | "<<inttostr(538-count)<<" |"<<endl;
                return;
            }

            if(states[i]->color == 's'){
                f(i+1, n, count+states[i]->electoralVotes, states, ret);
                f(i+1, n, count, states, ret);
            }else if(states[i]->color == 'b'){ 
                f(i+1, n, count+states[i]->electoralVotes, states, ret);
            }else{
                f(i+1, n, count, states, ret);
            }

        }

        static void compute(vector<State*> &states){
            vector<State*> biden;
            vector<State*> trump;
            unordered_set<int> ret; 
            f(0, states.size(), 0, states, ret);
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
