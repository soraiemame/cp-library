struct ConvexHullTrick{
private:
    bool MIN;
    long long lim;
    struct line{
        long long a,b,lim;
        line(long long a_,long long b_,long long _lim = 1LL << 60):a(a_),b(b_),lim(_lim){}
        bool operator<(const line& l)const{return std::make_pair(-a,b) < std::make_pair(-l.a,l.b);}
    };
    struct rational{
        long long u,s,lim;//xがu/s
        rational(long long u_ = 0,long long s_ = 1,long long _lim = 1LL << 60):u(u_),s(s_),lim(_lim){
            if(s < 0)u = -u,s = -s;
        }
        bool operator<(const rational& CP_)const{
            if(u == lim || CP_.u == -lim)return false;
            if(u == -lim || CP_.u == lim)return true;
            return (__int128_t)u * CP_.s < (__int128_t)CP_.u * s;
        }
    };
    using it = std::set<line>::iterator;
    std::set<line> S;
    std::map<rational,line> C;
    void C_erase(it from,it to){
        for(;from != to;++from)C.erase(cp(*from,*next(from)));
    }
    rational cp(line l1,line l2){
        if(l1.a == lim)return rational(-lim);
        if(l2.a == -lim)return rational(lim);
        return rational(l1.b - l2.b,l2.a - l1.a);
    }
    bool need(line l1,line l2,line l3){
        if(l1.a == l2.a && l1.b <= l2.b)return false;
        if(l1.a == lim || l3.a == -lim)return true;
        return (__int128_t)(l2.a - l1.a) * (l3.b - l2.b) < (__int128_t)(l2.b - l1.b) * (l3.a - l2.a);
    }
public:
    ConvexHullTrick(bool MIN_ = true,long long _lim = 1LL << 60):MIN(MIN_),lim(_lim){
        S.insert({lim,0});
        S.insert({-lim,0});
        C.emplace(rational(-lim),line(-lim,0));
    }
    void add_line(long long a,long long b){
        if(!MIN)a = -a,b = -b;
        it ite = S.insert({a,b}).first;
        if(!need(*prev(ite),{a,b},*next(ite))){
            S.erase(ite);
            return;
        }
        C.erase(cp(*prev(ite),*next(ite)));
        auto ju1 = prev(ite);
        while(ju1 != S.begin() && !need(*prev(ju1),*ju1,{a,b}))--ju1;
        C_erase(ju1,prev(ite));
        ite = S.erase(++ju1,ite);
        auto ju2 = next(ite);
        while(next(ju2) != S.end() && !need({a,b},*ju2,*next(ju2)))++ju2;
        C_erase(++ite,ju2);
        ite = prev(S.erase(ite,ju2));
        C.emplace(cp(*prev(ite),*ite),*ite);
        C.emplace(cp(*ite,*next(ite)),*next(ite));
    }
    long long query(long long x){
        line f = std::prev(C.lower_bound(rational(x)))->second;
        return (f.a * x + f.b) * (MIN ? 1 : -1);
    }
};
