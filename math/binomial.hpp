template<class T>
struct binomial{
    binomial(int n = 0):_fac(n + 10),_inv(n + 10),_finv(n + 10){
        _fac[0] = _inv[0] = _finv[0] = 1;
        _fac[1] = _inv[1] = _finv[1] = 1;
        for(int i = 2;i < n + 10;i++){
            _fac[i] = _fac[i - 1] * i;
            _inv[i] = T(i).inv();
            _finv[i] = _finv[i - 1] * _inv[i];
        }
    }
    void expand(int n){
        for(int i = _fac.size();i < n + 10;i++){
            _fac.push_back(_fac[i - 1] * i);
            _inv.push_back(T(i).inv());
            _finv.push_back(_finv[i - 1] * _inv[i]);
        }
    }
    T fac(int n){
        expand(n);
        return _fac[n];
    }
    T inv(int n){
        expand(n);
        return _inv[n];
    }
    T finv(int n){
        expand(n);
        return _finv[n];
    }

    T C(int n,int k){
        if(n < k || k < 0 || n < 0)return T(0);
        return fac(n) * finv(n - k) * finv(k);
    }
    T P(int n,int k){
        if(n < k || k < 0 || n < 0)return T(0);
        debug(n,fac(n),n-k,finv(n - k));
        return fac(n) * finv(n - k);
    }
    T H(int n,int k){
        if(n < 0 || k < 0)return T(0);
        return k == 0 ? T(1) : C(n + k - 1,k);
    }
private:
    std::vector<T> _fac,_inv,_finv;
};
