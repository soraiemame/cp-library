template<class T>
struct sqrt_dec{
    struct bucket{
        std::vector<T> dat,so,wa;
        int l,r;
        T LM,min_val,max_val,add_val,low_val,high_val;
        bucket(const std::vector<T>& a,int l_,int r_,T LM_):l(l_),r(r_),LM(LM_),add_val(0),low_val(-LM),high_val(LM){
            dat = std::vector<T>(r - l);
            wa = std::vector<T>(r - l + 1);
            for(int i = l;i < r;i++)dat[i - l] = a[i];
            eval_calc();
        }

        void eval_update(){
            for(auto &i : dat)i = std::clamp(i + add_val,low_val,high_val);
            add_val = 0;
            low_val = -LM;
            high_val = LM;
        }
        void eval_calc(){
            so = dat;
            std::sort(so.begin(),so.end());
            for(int i = 0;i < int(so.size());i++)wa[i + 1] = wa[i] + so[i];
            min_val = LM;
            max_val = -LM;
            for(T &i : dat){
                if(min_val > i)min_val = i;
                if(max_val < i)max_val = i;
            }
        }
        void update_part(int a,int b,T add_val_,T low_val_,T high_val_){
            eval_update();
            for(int i = a;i < b;i++)dat[i] = std::clamp(dat[i] + add_val_,low_val_,high_val_);
            eval_calc();
        }
        void update_all(T add_val_,T low_val_,T high_val_){
            add_val += add_val_;
            low_val = std::clamp(low_val + add_val_,low_val_,high_val_);
            high_val = std::clamp(high_val + add_val_,low_val_,high_val_);
        }
        T sum_part(int a,int b){
            T res = 0;
            for(int i = a;i < b;i++)res += std::clamp(dat[i] + add_val,low_val,high_val);
            return res;
        }
        T sum_all(){
            int lb = std::lower_bound(so.begin(),so.end(),low_val - add_val) - so.begin();
            int ub = std::upper_bound(so.begin(),so.end(),high_val - add_val) - so.begin();
            return wa[ub] - wa[lb] + add_val * (ub - lb) + high_val * (r - l - ub) + low_val * lb;
        }
        T min_part(int a,int b){
            T res = LM;
            for(int i = a;i < b;i++)res = std::min(res,std::clamp(dat[i] + add_val,low_val,high_val));
            return res;
        }
        T min_all(){
            return std::clamp(min_val + add_val,low_val,high_val);
        }
        T max_part(int a,int b){
            T res = -LM;
            for(int i = a;i < b;i++)res = std::max(res,std::clamp(dat[i] + add_val,low_val,high_val));
            return res;
        }
        T max_all(){
            return std::clamp(max_val + add_val,low_val,high_val);
        }

        void range_update(int a,int b,T x){
            if(r <= a || b <= l)return;
            else if(a <= l && r <= b)update_all(0,x,x);
            else update_part(std::max(a,l) - l,std::min(b,r) - l,0,x,x);
        }
        void range_add(int a,int b,T x){
            if(r <= a || b <= l)return;
            else if(a <= l && r <= b)update_all(x,-LM,LM);
            else update_part(std::max(a,l) - l,std::min(b,r) - l,x,-LM,LM);
        }
        void range_chmin(int a,int b,T x){
            if(r <= a || b <= l)return;
            else if(a <= l && r <= b)update_all(0,-LM,x);
            else update_part(std::max(a,l) - l,std::min(b,r) - l,0,-LM,x);
        }
        void range_chmax(int a,int b,T x){
            if(r <= a || b <= l)return;
            else if(a <= l && r <= b)update_all(0,x,LM);
            else update_part(std::max(a,l) - l,std::min(b,r) - l,0,x,LM);
        }
        T range_min(int a,int b){
            if(r <= a || b <= l)return LM;
            else if(a <= l && r <= b)return min_all();
            else return min_part(std::max(a,l) - l,std::min(b,r) - l);
        }
        T range_max(int a,int b){
            if(r <= a || b <= l)return -LM;
            else if(a <= l && r <= b)return max_all();
            else return max_part(std::max(a,l) - l,std::min(b,r) - l);
        }
        T range_sum(int a,int b){
            if(r <= a || b <= l)return 0;
            else if(a <= l && r <= b)return sum_all();
            else return sum_part(std::max(a,l) - l,std::min(b,r) - l);
        }
    };
    sqrt_dec(const std::vector<T>& a,int bs,T LM_){init(a,bs,LM_);}
    sqrt_dec(int n_,int bs,T LM_){init(std::vector<T>(n_,bs,LM_));}
    void range_update(int a,int b,T x){
        for(auto &i : dat)i.range_update(a,b,x);
    }
    void range_chmin(int a,int b,T x){
        for(auto &i : dat)i.range_chmin(a,b,x);
    }
    void range_chmax(int a,int b,T x){
        for(auto &i : dat)i.range_chmax(a,b,x);
    }
    void range_add(int a,int b,T x){
        for(auto &i : dat)i.range_add(a,b,x);
    }
    T range_min(int a,int b){
        T res = LM;
        for(auto &i : dat)res = std::min(res,i.range_min(a,b));
        return res;
    }
    T range_max(int a,int b){
        T res = -LM;
        for(auto &i : dat)res = std::max(res,i.range_max(a,b));
        return res;
    }
    T range_sum(int a,int b){
        T res = 0;
        for(auto &i : dat)res += i.range_sum(a,b);
        return res;
    }
    T get(int a){
        return range_min(a,a + 1);
    }
    void deb(){
        std::cerr << "debug: [";
        for(int i = 0;i < n;i++)std::cerr << range_min(i,i + 1) << (i == n - 1 ? "]\n":",");
    }
    
private:
    int n;
    T LM;
    std::vector<bucket> dat;
    void init(const std::vector<T>& a,int bs,T LM_){
        LM = LM_;
        n = a.size();
        dat = std::vector<bucket>();
        for(int i = 0;i < int(a.size());i += bs)dat.push_back(bucket(a,i,std::min(int(i + bs),int(a.size())),LM));
    }
};
