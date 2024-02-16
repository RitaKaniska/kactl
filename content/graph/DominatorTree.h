/**
 * Author: Lamu
 * Date: 2024-02-16
 * Description: Build dominator tree with source S
 */

vector <int> adj[maxn],radj[maxn],tree[maxn],bucket[maxn];
int sdom[maxn],par[maxn],dom[maxn],dsu[maxn],label[maxn],arr[maxn],rev[maxn],cnt;
int Find(int u, int x=0) {
    if (dsu[u]==u) return x?-1:u;
    int v=Find(dsu[u],x+1); if (v<0) return u;
    if (sdom[label[dsu[u]]]<sdom[label[u]]) label[u]=label[dsu[u]];
    dsu[u]=v; return x?v:label[u];
}
void Union(int u, int v) { dsu[v]=u; }
void dfs0(int u) {
    cnt++; arr[u]=cnt; rev[cnt]=u;
    sdom[cnt]=label[cnt]=dsu[cnt]=cnt;
    for (int v:adj[u]) {
        if (!arr[v]) dfs0(v), par[arr[v]]=arr[u];
        radj[arr[v]].push_back(arr[u]);
    }
}
void build(int S=1) {
    cnt=0; dfs0(S); fill_n(ans,n+1,-1); int n=cnt;
    for (int i=n; i>=1; i--) {
        for (int j:radj[i]) sdom[i]=min(sdom[i],sdom[Find(j)]);
        if (i>1) bucket[sdom[i]].push_back(i);
        for (int w:bucket[i]) {
            int v=Find(w);
            if (sdom[v]==sdom[w]) dom[w]=sdom[w];
            else dom[w]=v;
        }
        if (i>1) Union(par[i],i);
    }
    for (int i=2; i<=n; i++) {
        if (sdom[i]!=dom[i]) dom[i]=dom[dom[i]];
        //(rev[dom[i]]] --> rev[i])
    }
}
