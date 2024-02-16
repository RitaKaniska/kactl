/**
 * Author: DeMen100ns
 * Date: 2023
 * Description: DeMen-Kuhn (Kuhn with Russian optimize)
 * Time: O(VE) but very fast in practice
 */

vector <int> a[N];
int f[N], ctf = 0;
int n, m, mr[N];
bool ml[N];

bool dfs(int u){
    if (f[u] == ctf) return false;
    f[u] = ctf;
    shuffle(a[u].begin(), a[u].end(), rng);
    for(int i : a[u]){
        if (!mr[i] || dfs(mr[i])){
            mr[i] = u;
            return true;
        }
    }
    return false;
}

int maximum_matching(){
    int cnt = 0;
    for(bool run = true; run;){
        run = false; ++ctf;
        for(int i = 1; i <= n; ++i){
            if (!ml[i] && dfs(i)){
                run = true;
                ++cnt;
                ml[i] = true;
            }
        }
    }
    return cnt;
}
