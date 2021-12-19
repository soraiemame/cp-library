namespace my_rand{
    // [0, 2^64 - 1)
    uint64_t rng(){
        static uint64_t x_ =
            uint64_t(std::chrono::duration_cast<std::chrono::nanoseconds>(
                        std::chrono::high_resolution_clock::now().time_since_epoch())
                        .count()) *
            10150724397891781847ULL;
        x_ ^= x_ << 7;
        return x_ ^= x_ >> 9;
    }

    // [l, r)
    int64_t randint(int64_t l,int64_t r) {
        assert(l < r);
        return l + rng() % (r - l);
    }

    // [0.0, 1.0)
    double rnd(){
        union raw_cast{
            double t;
            uint64_t u;
        };
        constexpr uint64_t p = uint64_t(1023 - 64) << 52;
        return rng() * ((raw_cast*)(&p))->t;
    }

    uint64_t rng128(){
        static uint64_t tx = 123456789,ty = 362436069,tz = 521288629,tw = 88675123;
        uint64_t tt = (tx^(tx<<11));
        tx = ty; ty = tz; tz = tw;
        return (tw=(tw^(tw>>19))^(tt^(tt>>8)));
    }

    int64_t xor128(int64_t l,int64_t r){
        assert(l < r);
        return l + rng128() % (r - l);
    }

    template <typename T>
    void randshf(std::vector<T>& v){
        int n = v.size();
        for(int loop = 0;loop < 2;loop++)for(int i = 0;i < n;i++)std::swap(v[i],v[randint(0, n)]);
    }

    std::vector<int64_t> randvec(int len,int64_t l,int64_t r){
        std::vector<int64_t> res(len);
        for(int i = 0;i < len;i++)res[i] = randint(l,r);
        return res;
    }

    std::vector<int64_t> randset(int64_t l,int64_t r,int64_t n) {
        assert(l <= r && n <= r - l);
        std::unordered_set<int64_t> s;
        for (int64_t i = n;i;--i) {
            int64_t m = randint(l, r + 1 - i);
            if (s.find(m) != s.end()) m = r - i;
            s.insert(m);
        }
        std::vector<int64_t> ret;
        for(auto& x : s)ret.push_back(x);
        return ret;
    }

    std::vector<std::pair<int,int>> randtree(int n,int start_index = 1){
        atcoder::dsu uf(n);
        std::vector<pair<int,int>> edges;
        std::vector<pair<int,int>> res;
        for(int i = 0;i < n;i++){
            for(int j = i + 1;j < n;j++){
                edges.push_back(std::make_pair(i,j));
            }
        }
        randshf(edges);
        for(auto&& e : edges){
            if(!uf.same(e.first,e.second)){
                res.push_back(std::make_pair(e.first + start_index,e.second + start_index));
                uf.merge(e.first,e.second);
            }
        }
        return res;
    }

    std::vector<std::pair<int,int>> randgraph(int n,int m,int start_index = 1){
        std::vector<std::pair<int,int>> res(m);
        std::set<std::pair<int,int>> used;
        for(int i = 0;i < m;i++){
            int fr = randint(0,n),to = randint(0,n);
            while(used.count(std::make_pair(fr,to))){
                fr = randint(0,n);
                to = randint(0,n);
            }
            used.insert(std::make_pair(fr,to));
            res[i] = std::make_pair(fr + start_index,to + start_index);
        }
        return res;
    }
};

using my_rand::randint;
using my_rand::rnd;
using my_rand::rng;
using my_rand::xor128;
using my_rand::rng128;
using my_rand::randshf;
using my_rand::randvec;
using my_rand::randset;
using my_rand::randtree;
using my_rand::randtree;
using my_rand::randgraph;
