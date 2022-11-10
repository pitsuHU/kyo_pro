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

ll Q;
map<ll,ll> mp;
vector<P> query;
map<ll,vector<ll>> saved;
map<ll,ll> pos_cnt;
vector<ll> ans;
vector<ll> vec;
vector<bool> used;
void dfs(ll pos){
    if(pos == Q) return;
    if(query[pos].first == 0){
        vec.emplace_back(query[pos].second);
        ans[pos] = vec.back();
        dfs(pos+1);
        vec.pop_back();
    }else if(query[pos].first == 1){
        ll bk = -1;
        if(vec.back() != -1){
            bk = vec.back();
            vec.pop_back();
        }
        ans[pos] = vec.back();
        dfs(pos+1);
        if(bk != -1) vec.emplace_back(bk);
    }else if(query[pos].first == 2){
        ans[pos] = vec.back();
        for(auto x: saved[pos_cnt[pos]]){
            if(vec.size() == 0){
                ans[x] = -1;
            }else{
                ans[x] = vec.back();
            }
            dfs(x+1);
        }
        dfs(pos+1);
    }else{
        if(!used[pos]){
            vec.emplace_back(-1);
            dfs(pos+1);
            vec.pop_back();
        }
    }
}

int main(){
    cin >> Q;
    used = vector<bool>(Q);
    ans = vector<ll>(Q,-1);
    for(int i=0; i<Q; i++){
        string S;
        cin >> S;
        ll x;
        if(S != "DELETE"){
            cin >> x;
        }
        if(S == "ADD") query.emplace_back(0,x);
        else if(S == "DELETE") query.emplace_back(1,x);
        else if(S == "SAVE") query.emplace_back(2,x);
        else query.emplace_back(3,x);
    }
    {
        ll cnt = 1;
        for(int i=0; i<Q; i++){
            if(query[i].first == 2){
                pos_cnt[i] = cnt;
                mp[query[i].second] = cnt;
                cnt++;
            }
            if(query[i].first == 3){
                if(mp[query[i].second] != 0) used[i] = true;
                saved[mp[query[i].second]].emplace_back(i);
            }
        }
    }
    vec.emplace_back(-1);
    dfs(0);
    for(int i=0; i<Q; i++){
        cout << ans[i] << " \n"[i+1 == Q];
    }
    return 0;
}