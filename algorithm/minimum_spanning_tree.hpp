#ifndef SORAIE_MST
#define SORAIE_MST

#include <vector>
#include <algorithm>

#include "../data-structure/unionfind.hpp"
#include "../utils/graph_alias.hpp"

template<class T>
std::pair<T,std::vector<edge<T>>> minimum_spanning_tree(const std::vector<edge<T>> &_es,bool sorted = false){
    std::vector<edge<T>> es = _es;
    if(!sorted)std::sort(es.begin(),es.end(),[](const edge<T> a,const edge<T> b){return a.cost < b.cost;});
    int n = 0;
    for(auto&& e : es)n = std::max({n,e.from,e.to});
    std::pair<T,std::vector<edge<T>>> res;
    UnionFind UF(n + 1);
    for(auto&& e : es){
        if(!UF.same(e.from,e.to)){
            res.first += e.cost;
            res.second.push_back(e);
            UF.unite(e.from,e.to);
        }
    }
    return res;
}

#endif /*SORAIE_MST*/