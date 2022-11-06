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
    ll N,M;
    cin >> N >> M;
    vector<ll> A(N);
    for(int i=0; i<N; i++) cin >> A[i];
    ll dp[N+1][M+1][2];
    for(int i=0; i<=N; i++){
        for(int j=0; j<=M; j++){
            for(int k=0; k<2; k++) dp[i][j][k] = INF;
        }
    }
    dp[0][0][1] = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<=M; j++){
            if(j+A[i] <= M){
                chmin(dp[i+1][j+A[i]][1],dp[i][j][0]);
                chmin(dp[i+1][j+A[i]][1],dp[i][j][1]);
            }
            chmin(dp[i+1][j][0],dp[i][j][1]+1);
            chmin(dp[i+1][j][0],dp[i][j][0]);
        }
    }
    for(int i=1; i<=M; i++){
        ll ans = min(dp[N][i][0],dp[N][i][1]);
        if(ans == INF){
            cout << -1 << "\n";
        }else{
            cout << ans << "\n";
        }
    }
}