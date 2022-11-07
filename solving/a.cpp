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
    ll H,W;
    cin >> H >> W;
    vector<string> G(H);
    for(int i=0; i<H; i++) cin >> G[i];
    ll sy,sx;
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++){
            if(G[i][j] == 'S'){
                sy = i;
                sx = j;
            }
        }
    }
    bool ans = false;
    for(int _=0; _<4; _++){
        ll ssy = sy + dy[_];
        ll ssx = sx + dx[_];
        if(ssy < 0 || ssy>=H || ssx<0 || ssx>=W) continue;
        if(G[ssy][ssx] == '#') continue;
        ll cnt = 0;
        vector<P> vec;
        vector<vector<bool>> used(H,vector<bool>(W));
        function<void(ll,ll,bool)> dfs = [&](ll y,ll x,bool ac){
            if(abs(sy-y)==1 && abs(sx-x)==1){
                if(cnt == 1){
                    if(!ac){
                        vec.emplace_back(y,x);
                        return;
                    }
                }
            }
            if(y==sy && x==sx){
                if(cnt >= 3){
                    ans = true;
                }
                return;
            }
            // cout << cnt << " " << y << " " << x << " " << ssy <<" " << ssx << endl;
            used[y][x] = true;
                cnt++;
            for(int k=0; k<4; k++){
                ll ny = y + dy[k];
                ll nx = x + dx[k];
                if(ny<0 || ny>=H || nx<0 || nx>=W) continue;
                if(used[ny][nx]) continue;
                if(G[ny][nx] == '#') continue;
                dfs(ny,nx,ac);
            }
                cnt--;
        };
        dfs(ssy,ssx,false);        
        // cout << vec.size() << endl;
        for(int i=0; i<vec.size(); i++){
            cnt = 1;
            dfs(vec[i].first,vec[i].second,true);
        }
    }
    if(ans){
        cout << "Yes" << endl;
    }else{
        cout << "No" << endl;
    }
    return 0;
}