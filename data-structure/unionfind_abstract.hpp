template<class T = int>
struct UnionFind{
    int n;
    std::vector<int> par;
    std::vector<T> dat;
    using FX = std::function<void(T&,T&)>;
    FX fx;
    UnionFind(int n_,FX fx_ = [](T &a,T &b)->void{return;}):n(n_),par(n_,-1),dat(n_),fx(fx_){}
    void set(int a,T m){
        assert(0 <= a && a < n);
        dat[a] = m;
    }
    int find(int a){
        assert(0 <= a && a < n);
        if(par[a] < 0)return a;
        else return par[a] = find(par[a]);
    }
    void unite(int a,int b){
        assert(0 <= a && a < n && 0 <= b && b < n);
        a = find(a);
        b = find(b);
        if(a == b)return;
        if(par[a] > par[b])std::swap(a,b);
        par[a] += par[b];
        par[b] = a;
        fx(dat[a],dat[b]);
    }
    bool same(int a,int b){
        assert(0 <= a && a < n && 0 <= b && b < n);
        return find(a) == find(b);
    }
    int size(int v){
        assert(0 <= v && v < n);
        return -par[v];
    }
};
