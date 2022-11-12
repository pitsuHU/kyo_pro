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
    vector<ll> pre(N),mid(N);
    for(int i=0; i<N; i++) cin >> pre[i],pre[i]--;
    for(int i=0; i<N; i++) cin >> mid[i],mid[i]--;
    if(pre[0] != 0){
        cout << -1 << endl;
        return 0;
    }
    vector<ll> mid_pos(N);
    vector<ll> pre_pos(N);
    for(int i=0; i<N; i++){
        pre_pos[pre[i]] = i;
        mid_pos[mid[i]] = i;
    }
    queue<pair<ll,P>> que;
    vector<ll> L(N,-1),R(N,-1);
    que.emplace(0,P(0,N));
    vector<bool> used(N);
    while(que.size()){
        ll v = que.front().first;
        auto [l,r] = que.front().second;
        // cout << v << " " << l << " " << r << endl;
        que.pop();
        if(used[v]){
            cout << -1 << endl;
            return 0;
        }
        used[v] = true;
        ll l_size = mid_pos[v] - l;
        ll r_size = r - mid_pos[v] - 1;
        if(l_size > 0){
            if(pre_pos[v]+1 >= N){
                cout << -1 << endl;
                return 0;
            }
            ll nv = pre[pre_pos[v]+1];
            L[v] = nv;
            que.emplace(nv,P(l,mid_pos[v]));
        }
        if(r_size > 0){
            if(pre_pos[v]+l_size+1 >= N){
                cout << -1 << endl;
                return 0;
            }
            ll nv = pre[pre_pos[v]+l_size+1];
            R[v] = nv;
            que.emplace(nv,P(mid_pos[v]+1,r));
        }
    }
    for(int i=0; i<N; i++){
        cout << L[i]+1 << " " << R[i]+1 << "\n";
    }
}