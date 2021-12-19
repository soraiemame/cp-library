template<class T>
long long inversion_number(const std::vector<T> &V,bool compress = true){
    int n = V.size();
    std::vector<T> vec = V;
    if(compress){
        std::vector<T> zaatu = V;
        std::sort(zaatu.begin(),zaatu.end());
        for(T& a : vec)a = std::lower_bound(zaatu.begin(),zaatu.end(),a) - zaatu.begin();
    }
    fenwick_tree<int> BIT(n);
    long long ans = 0;
    for(int i = 0;i < n;i++){
        ans = ans + i - BIT.sum(0,vec[i]);
        BIT.add(vec[i],1);
    }
    return ans;
}
