template<class T>
std::vector<int> LIS(const std::vector<T>& vec){
    int n = vec.size();
    std::vector<int> memo(n,__INT32_MAX__);
    for(T a : vec)*std::lower_bound(memo.begin(),memo.end(),a) = a;
    return std::vector<int>(memo.begin(),std::lower_bound(memo.begin(),memo.end(),__INT32_MAX__));
}
template<class T>
std::vector<int> LDS(const std::vector<T>& _vec){
    std::vector<T> vec = _vec;
    std::reverse(vec.begin(),vec.end());
    auto res = LIS(vec);
    std::reverse(res.begin(),res.end());
    return res;
}
