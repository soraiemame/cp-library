priority_queue<pll,vector<pll>,greater<pll>> que;
vector<ll> dist(N,INF);
que.emplace(0,0);
dist[0] = 0;
while(!que.empty()){
    auto p = que.top();
    que.pop();
    if(dist[p.second] < p.first)continue;
    for(auto x : G[p.second]){
        if(chmin(dist[x.first],dist[p.second] + x.second))que.emplace(dist[x.first],x.first);
    }
}