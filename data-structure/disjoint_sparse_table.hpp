template<class T,T (*op)(T,T)>
struct DisjointSparseTable{
private:
    int _n,log,sz;
    std::vector<std::vector<T>> table;
    static int msb(int x){
    #ifdef __has_builtin
        return 31 ^ __builtin_clz(x);
    #else
        int res = 0;
        if(x >> 16){
            res += 16;x >>= 16;
        }
        if(x >> 8){
            res += 8;x >>= 8;
        }
        if(x >> 4){
            res += 4;x >>= 4;
        }
        if(x >> 2){
            res += 2;x >>= 2;
        }
        return res + (x >> 1);
    #endif
    }
    void build(const std::vector<T>& dat){
        int w = sz;
        for(int lv = 0;lv < log;lv++){
            int l = 0,r = w;
            for(;l < sz;l += w,r += w){
                int m = (l + r) >> 1;

                table[lv][m] = dat[m];
                for(int i = m + 1;i < r;i++)table[lv][i] = op(table[lv][i - 1],dat[i]);

                table[lv][m - 1] = dat[m - 1];
                for(int i = m - 2;i >= l;i--)table[lv][i] = op(table[lv][i + 1],dat[i]);
            }
            w >>= 1;
        }
    }

public:
    DisjointSparseTable(const std::vector<T>& dat){
        _n = dat.size();
        sz = 1;
        log = 0;
        while(sz < _n)sz <<= 1,log++;
        table = std::vector<std::vector<T>>(log,std::vector<T>(sz));
        std::vector<T> _dat = dat;
        _dat.resize(sz);
        if(log)build(_dat);
        else table = std::vector<std::vector<T>>(1,dat);
    }
    // [l,r)
    T query(int l,int r)const{
        assert(0 <= l && l < r && r <= _n);
        r--;
        if(l == r)return table.back()[l];
        int clz = msb(l ^ r);
        int lev = log - clz - 1;
        T res = op(table[lev][l],table[lev][r]);
        return res;
    }
    inline T operator[](int k)const{
        assert(k < _n);
        return table.back()[k];
    }
};
