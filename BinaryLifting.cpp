#include <bits/stdc++.h>

using namespace std;
#define int     long long
static int mod = 1000000007;

class TreeAncestor {
public:
    vector<vector<int>> hash;
    TreeAncestor(int n, vector<int>& parent) {
        int NLog = log2(n)+1;
        // NLog is the no. of bits required to represent 'n' in binary!

        // hash : to store the ancestors of a node.
        // ONLY STORE ANCS WHICH ARE AT -----2^i UP----- (REAL-MAGIC)
        hash = vector<vector<int>>(n, vector<int>(NLog, 0));

        for(int i = 0; i <= n-1; i++){
            // 2^0 = 1 means immediate parent of i -> parent[i]
            hash[i][0] = parent[i];
        }

        for(int i = 0; i <= n-1; i++){
            for(int k = 1; k <= NLog-1; k++){

                // if node at 2^(k-1) doesn't exists then obv 2^(k) also doesn't exists.
                if(hash[i][k-1] == -1){
                    hash[i][k] = -1;
                    continue;
                }
                // suppose we need 2^xth ancs then.
                // 1. We have already stored 2^(x-1) of 'every' node!
                // 2. Go to 2^(x-1)th ancs of i and from there go to 2^(x-1)th of that.
                // 3. (U) --------   (V)   -------- (W)
                //     ^              ^ 
                //    2^x from W     2^x-1 from W   
                //    2^x-1 from V

                // U |<------------>| W  = 2^x go from (W -> U)

                // 2^x-1 | 2^x-1 == 2*(2^x-1) == 2^x that's we want.
                // hash[i][k-1] -> V
                // hash[v][k-1] -> U
                hash[i][k] = hash[hash[i][k-1]][k-1];
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
        // suppose k = 5 = 101 in binary:
        // 1 = 2^2 = 4 move 4 level UP 
        // 0 no change
        // 1 2^0 = 1 move 1 level UP
        // we are on required node.
        // k <= n i.e we had already stored all powers of 2 uptill N.
        // Hence for every possible k we can move greedily a level up and reach to required node!
        for(int bit = 0; bit <= log2(k); bit++){
            // k >> 1 & 1 means        k has set bit at position 'bit'
            if(((k >> bit) & 1) == 1){

                // (2^bit)th ancs of node doesn't exists. 
                if(hash[node][bit] == -1){
                    return -1;
                }

                // node is moved UP to (2^bit)th ancs 
                // logically substract (2^bit) from k remaining (101) -> (001) 
                // then remove 1 and get the required node k;
                node = hash[node][bit];
            }
        }
        return node;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */


int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("o.txt", "w", stdout);
    freopen("i.txt", "r", stdin);
#endif
    return 0;
}