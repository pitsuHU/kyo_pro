#include "atcoder/all"
#include <iostream> // cout, endl, cin
#include <string> // string, to_string, stoi
#include <vector> // vector
#include <algorithm> // min, max, swap, sort, reverse, lower_bound, upper_bound
#include <utility> // pair, make_pair
#include <tuple> // tuple, make_tuple
#include <cstdint> // int64_t, int*_t
#include <cstdio> // printf
#include <map> // map
#include <queue> // queue, priority_queue
#include <set> // set
#include <stack> // stack
#include <deque> // deque
#include <unordered_map> // unordered_map
#include <unordered_set> // unordered_set
#include <bitset> // bitset
#include <cctype> // isupper, islower, isdigit, toupper, tolower
#include <iomanip> // setprecision
#include <complex> // complex
#include <math.h>
#include <functional>
#include <cassert>
using namespace std;
using namespace atcoder;
using ll = long long;
using P = pair<ll,ll>;
constexpr ll INF = 1e18;
constexpr ll LLMAX = 9223372036854775807;
constexpr int inf = 1e9;
// constexpr ll mod = 1000000007;
constexpr ll mod = 998244353;
// 右下左上
const int dx[8] = {1, 0, -1, 0,1,1,-1,-1};
const int dy[8] = {0, 1, 0, -1,1,-1,1,-1};
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }
ll gcd(ll a,ll b){if(b==0){return a;}else{return gcd(b,a%b);}};
#define eb emplace_back
#define pb pop_back
#define eol endl
// ---------------------------------------------------------------------------

int main(){
    ll N;
    cin >> N;
    vector<ll> pre(N);
    vector<ll> prepos(N);
    for(int i=0; i<N; i++){
        cin >> pre[i];
        pre[i]--;
        prepos[pre[i]] = i;
    }
    vector<ll> in(N);
    vector<ll> inpos(N);
    for(int i=0; i<N; i++){
        cin >> in[i];
        in[i]--;
        inpos[in[i]] = i;
    }
    if(pre[0] != 0){
        cout << -1 << endl;
        return 0;
    }
    vector<ll> L(N,-1),R(N,-1);
    set<ll> npextpos;
    for(int i=0; i<N; i++) npextpos.emplace(i);
    npextpos.emplace(INF);
    vector<ll> par(N,-1);
    {
        set<ll> used;
        for(int i=0; i<N; i++){
            if(prepos[in[i]] != N-1){
                ll p = pre[prepos[in[i]]+1];
                if(used.count(p)){
                    if(L[in[i]] != -1){
                        cout << -1 << endl;
                        return 0;
                    }
                    par[p] = in[i];
                    L[in[i]] = p;
                    npextpos.erase(inpos[p]);
                }
            }
            used.emplace(in[i]);
        }
    }
    ll root = pre[0];
    npextpos.erase(inpos[root]);
    {
        for(int i=0; i<N; i++){
            if(in[i] == root){
                ll nroot = *npextpos.lower_bound(i);                
                if(nroot != INF){
                    if(R[root] != -1){
                        cout << -1 << endl;
                        return 0;
                    }
                    R[root] = in[nroot];
                    npextpos.erase(nroot);
                    root = in[nroot];
                }
                continue;
            }
            if(par[in[i]] != -1){
                ll r = *npextpos.lower_bound(i);
                // cout << i << " " << r << endl;
                if(r < inpos[par[in[i]]]){
                    if(R[in[i]] != -1){
                        cout << -1 << endl;
                        return 0;
                    }
                    R[in[i]] = in[r];
                    par[in[r]] = in[i];
                    npextpos.erase(r);
                }
            }
        }
    }
    {
        set<ll> used;
        for(int i=0; i<N; i++){
            if(L[in[i]]!=-1 && !used.count(L[in[i]])){
                cout << -1 << endl;
                return 0;
            }
            if(R[in[i]]!=-1 && used.count(R[in[i]])){
                cout << -1 << endl;
                return 0;
            }
            used.emplace(in[i]);
        }
    }
    for(int i=0; i<N; i++){
        cout << L[i]+1 << " " << R[i]+1 << "\n";
    }
}