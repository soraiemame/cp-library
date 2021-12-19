template<class T = long long>
struct rationary{
    using D = long double;
    T den,num;
    rationary(T num_ = T(0),T den_ = T(1)):den(den_),num(num_){
        norm();
    }
    void norm(){
        assert(den != 0);
        if(den < 0)den = -den,num = -num;
        T g = std::gcd(den,num);
        den /= g;num /= g;
    }
    inline rationary operator-(){(*this).num *= -1;return (*this);}
    inline const rationary& operator+=(const rationary& a)noexcept{
        num = num * a.den + a.num * den;
        den = den * a.den;
        norm();
        return *this;
    }
    inline const rationary& operator-=(const rationary& a)noexcept{
        num = num * a.den - a.num * den;
        den = den * a.den;
        norm();
        return *this;
    }
    inline const rationary& operator*=(const rationary& a)noexcept{
        num *= a.num;
        den *= a.den;
        norm();
        return *this;
    }
    inline const rationary& operator/=(const rationary& a)noexcept{
        num *= a.den;
        den *= a.num;
        norm();
        return *this;
    }
    inline constexpr const rationary operator+(const rationary& a)const noexcept{return rationary(*this) += a;}
    inline constexpr const rationary operator-(const rationary& a)const noexcept{return rationary(*this) -= a;}
    inline constexpr const rationary operator*(const rationary& a)const noexcept{return rationary(*this) *= a;}
    inline constexpr const rationary operator/(const rationary& a)const noexcept{return rationary(*this) /= a;}
    inline rationary inv()const{return rationary(den,num);}
    inline bool operator==(const rationary& a)const noexcept{return num == a.num && den == a.den;}
    inline bool operator!=(const rationary& a)const noexcept{return !(rationary(*this) == a);}
    inline bool operator<(const rationary& a)const noexcept{return __int128_t(num) * a.den < __int128_t(a.num) * den;}
    inline bool operator>(const rationary& a)const noexcept{return a < rationary(*this);}
    inline bool operator<=(const rationary& a)const noexcept{return !(rationary(*this) > a);}
    inline bool operator>=(const rationary& a)const noexcept{return !(rationary(*this) < a);}
    inline D to_D()const{return D(num) / den;}

    inline friend std::ostream& operator<<(std::ostream& os,const rationary& a){
        if(a.den == 1)return os << a.num;
        else return os << a.num << " / " << a.den;
    }
    inline friend const rationary abs(const rationary& a){return (a.num < 0 ? rationary(-a.num,a.den) : rationary(a.num,a.den));}
};
using frac = rationary<long long>;
