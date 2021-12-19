template<class T,int MIN = 1>
struct LiChaoTree{
    const T linf = std::numeric_limits<T>::max();
private:
    using Line = std::pair<T,T>;

    int n;
    std::vector<T> xl;
    std::vector<Line> dat;

    T eval(Line f,T x){return f.first * x + f.second;}

    void inner_update(Line f,int k,int l,int r){
        f = Line(f.first * MIN,f.second * MIN);
        while(l != r){
            int m = (l + r) >> 1;
            T lx = xl[l],mx = xl[m],rx = xl[r - 1];
            Line &g = dat[k];
            if(eval(f,lx) < eval(g,lx) && eval(f,rx) < eval(g,rx)){
                g = f;
                return;
            }
            if(eval(f,lx) >= eval(g,lx) && eval(f,rx) >= eval(g,rx))return;
            if(eval(f,mx) < eval(g,mx))swap(f,g);
            if(eval(f,lx) < eval(g,lx)){
                k = (k << 1) + 1;
                r = m;
            }
            else{
                k = (k << 1) + 2;
                l = m;
            }
        }
    }
    
public:
    LiChaoTree(const std::vector<T>& _xl){
        xl = _xl;
        xl.push_back(std::numeric_limits<T>::max());
        xl.push_back(std::numeric_limits<T>::min());
        std::sort(xl.begin(),xl.end());xl.erase(std::unique(xl.begin(),xl.end()),xl.end());
        int _n = xl.size();
        n = 1;
        while(n < _n)n <<= 1;
        xl.resize(n,xl.back());
        dat = std::vector<Line>(n << 1,Line(0,linf));
    }
    
    void add_line(Line f){inner_update(f,0,0,n);}
    void add_line(T a,T b){inner_update(Line(a,b));}

    // [lx,rx)
    void add_segment(Line f,T lx,T rx){
        int l = std::lower_bound(xl.begin(),xl.end(),lx) - xl.begin(),r = std::lower_bound(xl.begin(),xl.end(),rx) - xl.begin();
        int a0 = l,b0 = r;
        l += n;r += n;
        int sz = 1;
        while(l < r){
            if(r & 1){
                r--;
                b0 -= sz;
                inner_update(f,r - 1,b0,b0 + sz);
            }
            if(l & 1){
                inner_update(f,l - 1,a0,a0 + sz);
                l++;
                a0 += sz;
            }
            l >>= 1;r >>= 1;
            sz <<= 1;
        }
    }

    // [lx,rx)
    void add_segment(T a,T b,T lx,T rx){add_segment(Line(a,b),lx,rx);}

    T get(T x){
        x *= MIN;
        int i = std::lower_bound(xl.begin(),xl.end(),x) - xl.begin();
        i += n - 1;
        T res = eval(dat[i],x);
        while(i){
            i = (i - 1) >> 1;
            res = std::min(res,eval(dat[i],x));
        }
        return res;
    }
};
