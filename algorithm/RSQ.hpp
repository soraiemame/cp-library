template<class T>
struct RangeSumQuery{
    int n;
    std::vector<T> dat;
    RangeSumQuery(const std::vector<T>& _dat):n(_dat.size()){
        dat.resize(n + 1);
        for(int i = 0;i < n;i++)dat[i + 1] = dat[i] + _dat[i];
    }
    // [l,r)
    T query(int l,int r){
        assert(0 <= l && l <= r && r <= n);
        return dat[r] - dat[l];
    }
};
template<class T>
struct RangeSumQuery2{
    int n,m;
    std::vector<std::vector<T>> dat;
    RangeSumQuery2(const std::vector<std::vector<T>>& _dat):n(_dat.size()),m(_dat[0].size()){
        dat = std::vector<std::vector<T>>(n + 1,std::vector<T>(m + 1));
        for(int i = 0;i < n;i++)for(int j = 0;j < m;j++)dat[i + 1][j + 1] = _dat[i][j];
        for(int i = 1;i <= n;i++)for(int j = 0;j < m;j++)dat[i][j + 1] += dat[i][j];
        for(int i = 0;i < n;i++)for(int j = 1;j <= m;j++)dat[i + 1][j] += dat[i][j];
    }

    // lx <= x < rx , ly <= y < ry
    T query(int lx,int ly,int rx,int ry){
        assert(0 <= lx && lx <= rx && rx <= n);
        assert(0 <= ly && ly <= ry && ry <= m);
        return dat[rx][ry] - dat[rx][ly] - dat[lx][ry] + dat[lx][ly];
    }
};
