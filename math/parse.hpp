long long x10(const std::string& s,size_t n){
    if(s.front() == '-')return -x10(s.substr(1),n);
    auto pos = s.find('.');
    if(pos == std::string::npos)return stoll(s + std::string(n,'0'));
    else return stoll(s.substr(0,pos) + s.substr(pos + 1) + std::string(n + pos + 1 - s.size(),'0'));
}
