#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int v, e; cin >> v >> e;
        char s; cin >> s;
        vector<vector<int>> adj(v);
        int int_s = (int)s - 65;
        vector<int>shaded = {int_s}; //Set S
        vector<vector<int>> dist(v, vector<int>(v, 200000));
        vector<vector<int>> weight(v, vector<int>(v, 200000));
        
        set<int>unset; //Collection of distinct values that are NOT SHADED 

        for (int i = 0; i < e; i++) {
            char st, en;
            int w; //Weight of an edge
            cin >> st >> en >> w;

            int int_st = st - 'A';
            int int_en = en - 'A';

            weight[int_st][int_en] = w;
            weight[int_en][int_st] = w;

            if (int_st != int_s) { //Insert any node that is not the source node
                unset.insert(int_st);
            }

            if (int_en != int_s) { //Insert any node that is not the source node
                unset.insert(int_en);
            }
            
            adj[int_st].push_back(int_en); 
            adj[int_en].push_back(int_st); //This one is for undirected graph. 
            //For directed, pls delete this line
        }

        vector<int>unshaded(unset.begin(), unset.end()); //Convert a set to a vector for easier reference

        dist[int_s][int_s] = 0;

        while (unshaded.size() != 0) {
            vector<int>val; // val = value
            vector<int>let; // let = letter
            unordered_map<int, unordered_set<int>> cnt_back;
            int minval = 1e9;
            
            for (int i = 0; i < shaded.size(); i++) {
                for (int j = 0; j < adj[shaded[i]].size(); j++) {
                    if (find(unshaded.begin(), unshaded.end(), adj[shaded[i]][j]) != unshaded.end()) {
                        dist[int_s][adj[shaded[i]][j]] = min(dist[int_s][adj[shaded[i]][j]], dist[int_s][shaded[i]] + weight[shaded[i]][adj[shaded[i]][j]]);
                        val.push_back(dist[int_s][adj[shaded[i]][j]]);
                        let.push_back(adj[shaded[i]][j]);
                        cnt_back[dist[int_s][adj[shaded[i]][j]]].insert(adj[shaded[i]][j]);
                    }
                }
            }

            for (int i = 0; i < val.size(); i++) {
                minval = min(minval, val[i]);
            }
            
            for (int x: cnt_back[minval]) {
                auto idxmin = find(unshaded.begin(), unshaded.end(), x);
                int idxk = distance(unshaded.begin(), idxmin);
                shaded.push_back(unshaded[idxk]);
                unshaded.erase(unshaded.begin() + idxk);
            }  

        }

        for (int j = 0; j <= v-1; j++) {
            cout << dist[int_s][j] << " ";
        }
        cout << "\n";
        
    }
    return 0;
}

