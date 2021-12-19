namespace prime{
    long long inner_modmul(long long x,long long y,long long p){
        #ifdef __SIZEOF_INT128__
        return __int128_t(x) * y % p;
        #else
        unsigned long long q = long double(x) * y / p;
        long long res = long long(x * y - p * q) % p;
        return res < 0 ? res + p : res;
        #endif
    }

    long long inner_modpow(long long n,long long m,long long p){
        long long res = 1;
        while(m){
            if(m & 1)res = inner_modmul(res,n,p);
            m >>= 1;
            n = inner_modmul(n,n,p);
        }
        return res;
    }

    bool miller_rabin(long long n,const std::vector<long long> as){
        long long s = __builtin_ctzll(n - 1),d = n >> s;
        for(long long a : as){
            if(n <= a)break;
            long long t = d,y = inner_modpow(a,t,n);
            while(t != n - 1 && y != 1 && y != (n - 1)){
                y = inner_modmul(y,y,n);
                t = inner_modmul(t,2,n);
            }
            if(y != n - 1 && ~t & 1)return false;
        }
        return true;
    }

    bool is_prime(long long n){
        if(n <= 2)return n == 2;
        else if(~n & 1)return false;
        else if(n < 4'759'123'141)return miller_rabin(n,{2,7,61});
        else return miller_rabin(n,{2,325,9375,28178,450775,9780504,1795265022});
    }

    long long factor(long long n){
        if(~n & 1)return 2;
        else if(is_prime(n))return n;
        int c = 2;
        while(true){
            auto f = [&](long long x){
                long long r = inner_modmul(x,x,n) + c;
                if(r >= n)r -= n;
                return r;
            };
            long long x = c,g = 1,q = 1,xs,y;
            constexpr int m = 128;
            int l = 1;
            while(g == 1){
                y = x;
                for(int i = 1;i < l;i++){
                    x = f(x);
                }
                int k = 0;
                while(k < l && g == 1){
                    xs = x;
                    for(int i = 0;i < m && i < l - k;i++){
                        x = f(x);
                        q = inner_modmul(q,std::llabs(y - x),n);
                    }
                    g = std::__gcd(q,n);
                    k += m;
                }
                l *= 2;
            }
            if(g == n){
                do{
                    xs = f(xs);
                    g = std::__gcd(std::llabs(xs - y),n);
                }while(g == 1);
            }
            if(g != n)return g;
            c++;
        }
    }

    std::vector<long long> factorize_sub(long long n){
        if(n <= 1)return {};
        long long p = factor(n);
        if(p == n)return {p};
        auto l = factorize_sub(n / p);
        auto r = factorize_sub(p);
        copy(begin(r),end(r),back_inserter(l));
        return l;
    }

    std::vector<long long> factorize(long long n,bool sorted = true){
        auto res = factorize_sub(n);
        if(sorted)std::sort(res.begin(),res.end());
        return res;
    }
};

using prime::factorize;
using prime::is_prime;
