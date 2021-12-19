std::vector<int> topological_sort(const std::vector<std::vector<int>>& G){
    int v = G.size();
    std::vector<int> in(v);
    for(int i = 0;i < v;i++){
        for(auto&& e : G[i])in[e]++;
    }

    std::queue<int> que;
    std::vector<int> res;
    for(int i = 0;i < v;i++){
        if(in[i] == 0)que.push(i);
    }

    while(!que.empty()){
        int n = que.front();
        que.pop();
        res.push_back(n);
        for(auto&& e : G[n]){
            assert(in[e]);
            in[e]--;
            if(in[e] == 0)que.push(e);
        }
    }
    return res;
}
