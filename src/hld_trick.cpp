void dfs_sz(int v = 0) {
    sz[v] = 1;
    for(auto &u: g[v]) {
        dfs_sz(u);
        sz[v] += sz[u];
        if(sz[u] > sz[g[v][0]]) {
            swap(u, g[v][0]);
        }
    }
}

void dfs_hld(int v = 0) {
    in[v] = t++;
    for(auto u: g[v]) {
        nxt[u] = (u == g[v][0] ? nxt[v] : u);
        dfs_hld(u);
    }
    out[v] = t;
}
/*Then you will have such array that subtree of  correspond to [in[v],out[v]]
 segment  and the path from v  to the last vertex in ascending heavy path
  from v  (which is nxt[v]) will be [in[nxt[v]],in[v]]  subsegment which gives you the opportunity to process
   queries on pathes and subtrees simultaneously in the same segment tree.
*/