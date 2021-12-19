#ifndef SORAIE_BELLMAN_FORD
#define SORAIE_BELLMAN_FORD

#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

#include "../library-cpp/utils/graph_alias.hpp"

namespace spfa{
    int _s = -1;
    std::vector<int> from;

    template<class T>
    std::vector<T> get_dist(const std::vector<std::vector<edge<T>>>& G,const std::vector<int>& st,T LM = std::numeric_limits<T>::max()){
        int sz = G.size();
        from.resize(sz,-1);
        std::vector<T> res(sz,LM);
        std::vector<bool> pending(sz,false);
        std::vector<int> times(sz,0);
        std::queue<int> que;
        for(const int& p : st){
            que.push(p);
            times[p]++;
            pending[p] = true;
            res[p] = 0;
        }
        while(!que.empty()){
            int n = que.front();
            que.pop();
            pending[n] = false;
            for(const auto& e : G[n]){
                T nx = res[n] + e.cost;
                if(nx < res[e.to]){
                    res[e.to] = nx;
                    from[e.to] = n;
                    if(!pending[e.to]){
                        if(++times[e.to] >= sz)return {};
                        pending[e.to] = true;
                        que.push(e.to);
                    }
                }
            }
        }
        return res;
    }

    template<class T>
    std::vector<T> get_dist(const std::vector<std::vector<edge<T>>>& G,int s,T LM = std::numeric_limits<T>::max()){
        _s = s;
        std::vector<int> st = {s};
        return get_dist(G,st,LM);
    }

    std::vector<int> path(int s,int t){
        if(s == t)return {s};
        else if(from[t] == -1)return {};
        std::vector<int> res;
        for(int cur = t;cur != s;cur = from[cur])res.push_back(cur);
        res.push_back(s);
        std::reverse(res.begin(),res.end());
        return res;
    }

    std::vector<int> path(int t){
        assert(_s != -1);
        return path(_s,t);
    }
};
using spfa::get_dist;
using spfa::path;

#endif /*SORAIE_BELLMAN_FORD*/