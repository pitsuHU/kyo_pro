#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <climits>
using namespace std;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
using ll = long long;

struct SegmentTree{
  private:
  int n;
  vector<ll> node;
  public:
  SegmentTree(vector<ll> v){
    int sz = v.size();
    n = 1;
    while(n < sz) n *= 2;
    node.resize(2*n-1,0);
    for(int i=0; i<sz; i++) node[i+n-1] = v[i];
    for(int i=n-2; i>=0; i--) node[i] = node[i*2+1] + node[i*2+2];
  }
  void add(int k,ll val){
    k += (n-1);
    node[k] += val;
    while(k>0){
      k = (k-1)/2;
      node[k] = node[2*k+1] + node[2*k+2];
    }
  }
  ll getsum(int a,int b,int k=0,int l=0,int r=-1){
    if(r < 0) r = n;
    if(b <= l || r <= a) return 0;
    if(a <= l && r <= b) return node[k];
    ll vl = getsum(a,b,2*k+1,l,(l+r)/2);
    ll vr = getsum(a,b,2*k+2,(l+r)/2,r);
    return vl + vr;
  }
};


vector<vector<int>> G;

vector<int> sz;
void dfs_sz(int v,int p=-1){
  int ret = 1;
  for(int nv: G[v]){
    if(nv == p) continue;
    dfs_sz(nv,v);
    ret += sz[nv];
  }
  sz[v] = ret;
}

vector<int> parent;
vector<int> depth;
void dfs_dep(int v,int p=-1){
  parent[v] = p;
  for(int nv: G[v]){
    if(p == nv) continue;
    depth[nv] = depth[v] + 1;
    dfs_dep(nv,v);
  }
}

vector<int> pos;
vector<int> hld;
vector<int> A;
void HLD(int v,int a,int p=-1){
  pos[v] = hld.size();
  hld.emplace_back(v);
  A[v] = a;
  if(sz[v] == 1) return;
  int mx = 0;
  int mx_idx;
  for(int nv: G[v]){
    if(nv == p) continue;
    if(chmax(mx,sz[nv])){
      mx_idx = nv;
    }
  }
  HLD(mx_idx,a,v);
  for(int nv: G[v]){
    if(nv == p) continue;
    if(nv == mx_idx) continue;
    HLD(nv,nv,v);
  }
}

ll query(int u,int v,SegmentTree &seg){
  ll ret = 0;
  while(A[u] != A[v]){
    if(depth[A[u]] < depth[A[v]]) swap(u,v);
    ret += seg.getsum(pos[A[u]],pos[u]+1);
    u = parent[A[u]];
  }
  if(depth[u] > depth[v]) swap(u,v);
  ret += seg.getsum(pos[u],pos[v]+1);
  return ret;
}

int main(void){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  int Q;
  cin >> Q;
  vector<ll> w(N);
  for(int i=0; i<N; i++) cin >> w[i];
  G.resize(N);
  for(int i=0; i<N-1; i++){
    int a,b;
    cin >> a >> b;
    G[a].emplace_back(b);
    G[b].emplace_back(a);
  }  

  sz.resize(N);
  dfs_sz(0);

  depth.resize(N);
  parent.resize(N);
  depth[0] = 0;
  dfs_dep(0);

  A.resize(N);
  pos.resize(N);
  HLD(0,0);
 

  vector<ll> temp = w;
  for(int i=0; i<N; i++){
    w[i] = temp[hld[i]];
  }
  SegmentTree seg(w);

  
  for(int q=0; q<Q; q++){
    int id;
    cin >> id;
    if(id == 0){
      ll u,v;
      cin >> u >> v;
      seg.add(pos[u],v);
    }else{      
      ll u,v;
      cin >> u >> v;
      cout << query(u,v,seg) << "\n";
    }
  }
  return 0;
}