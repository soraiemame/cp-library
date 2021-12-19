template<class T>
struct Matrix{
    int h,w;
    std::vector<std::vector<T>> dat;
    Matrix(const std::vector<std::vector<T>>& _dat):h(_dat.size()),w(_dat[0].size()),dat(_dat){}
    Matrix(const int& _h,const int& _w):h(_h),w(_w),dat(std::vector<std::vector<T>>(_h,std::vector<T>(_w))){}

    std::vector<T>& operator[](int k){return dat[k];}

    inline constexpr Matrix &operator+=(const Matrix& a) noexcept {
        assert(a.h == h && a.w == w);
        for(int i = 0;i < h;i++){
            for(int j = 0;j < w;j++){
                dat[i][j] += a.dat[i][j];
            }
        }
        return *this;
    }

    inline constexpr Matrix &operator*=(const Matrix& a) noexcept {
        assert(w == a.h);
        Matrix res(h,a.w);
        for(int i = 0;i < h;i++){
            for(int j = 0;j < a.h;j++){
                for(int k = 0;k < a.w;k++){
                    res[i][k] += dat[i][j] * a.dat[j][k];
                }
            }
        }
        *this = res;
        return *this;
    }

    inline constexpr Matrix operator+(const Matrix& a) const noexcept { return Matrix(*this) += a; }
    inline constexpr Matrix operator*(const Matrix& a) const noexcept { return Matrix(*this) *= a; }

    inline constexpr Matrix pow(long long k) const noexcept {
        assert(h == w);
        Matrix res = id(h),a(*this);
        while(k){
            if(k & 1)res *= a;
            a *= a;
            k >>= 1;
        }
        return res;
    }

    inline constexpr static Matrix id(int n){
        Matrix res(n,n);
        for(int i = 0;i < n;i++)res.dat[i][i] = T(1);
        return res;
    }

    friend std::ostream &operator<<(std::ostream& os,const Matrix& a){
        for(int i = 0;i < a.dat.size();i++){
            os << "[";
            for(int j = 0;j < a.dat[i].size();j++){
                os << a.dat[i][j] << (j == a.dat[i].size() - 1 ? "]" : " ");
            }
            if(i != a.dat.size() - 1)os << "\n";
        }
        return os;
    }
};
