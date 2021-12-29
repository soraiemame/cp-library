#ifndef SORIAE_DEBUG
#define SORIAE_DEBUG

#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <iterator>
#include <queue>
#include <sstream>
#include <deque>

namespace debugging {
    std::vector<std::string> split(const std::string& s, char delim) {
        std::vector<std::string> res; std::stringstream ss(s); std::string x;
        while (std::getline(ss, x, delim)) res.emplace_back(x);
        return std::move(res);
    }

    template<class Head>
    void do_debug(std::vector<std::string>::iterator it, Head head) {
        std::cerr << it->substr((*it)[0] == ' ', it->length()) << ": " << head << "\n";
    }
    template<class Head, class... Tail> void do_debug(std::vector<std::string>::iterator it, Head head, Tail... tail) {
        std::cerr << it->substr((*it)[0] == ' ', it->length()) << ": " << head << ", ";
        do_debug(++it, tail...);
    }
};

#define debug(args...) \
{ \
    std::vector<std::string> _debug = debugging::split(#args, ','); \
    debugging::do_debug(_debug.begin(), args); \
}


template<class stream, class First, class Second>
stream& operator<<(stream& os, const std::pair<First, Second>& pp) {
    return os << "(" << pp.first << ", " << pp.second << ")";
}

template<class stream, class T>
stream& operator<<(stream& os, const std::vector<T>& v) {
    os << "[";
    for (int i = 0;i < int(v.size());i++)os << v[i] << (i == int(v.size()) - 1 ? "" : ", ");
    os << "]";
    return os;
}

template<class stream, class T>
stream& operator<<(stream& os, const std::set<T>& s) {
    os << "{";
    auto it = s.begin();
    for (;it != s.end();it++)os << *it << (it == std::prev(s.end()) ? "" : ", ");
    os << "}";
    return os;
}

template<class stream,class Key, class Tp>
stream& operator<<(stream& os, const std::map<Key, Tp>& m) {
    os << "{";
    auto it = m.begin();
    for (;it != m.end();it++)os << "" << it -> first << ": " << it -> second << (it == std::prev(m.end()) ? "" : ", ");
    os << "}";
    return os;
}

template<class stream, class T, class S,class C>
stream& operator<<(stream& os, const std::priority_queue<T,S,C>& pq) {
    auto cpq = pq;
    os << "[";
    while(!cpq.empty()){
        os << cpq.top() << (cpq.size() == 1 ? "" : ", ");
        cpq.pop();
    }
    os << "]";
    return os;
}

template<class stream, class T>
stream& operator<<(stream& os, const std::queue<T>& q) {
    auto cq = q;
    os << "[";
    while(!cq.empty()){
        os << cq.front() << (cq.size() == 1 ? "" : ", ");
        cq.pop();
    }
    os << "]";
    return os;
}

template<class stream, class T>
stream& operator<<(stream& os, const std::deque<T>& q) {
    auto cq = q;
    os << "[";
    while(!cq.empty()){
        os << cq.front() << (cq.size() == 1 ? "" : ", ");
        cq.pop_front();
    }
    os << "]";
    return os;
}

namespace tuple_printer{
    template<class stream,class Tup,size_t... I>
    void print_tuple(stream& os,const Tup& tup,std::index_sequence<I...>){
        os << "(";
        (..., (os << (I == 0 ? "" : ", ") << std::get<I>(tup)));
        os << ")";
    }
}

template<class stream,class... T>
stream& operator<<(stream& os,const std::tuple<T...>& tup){
    tuple_printer::print_tuple(os, tup, std::make_index_sequence<sizeof...(T)>());
    return os;
}

#define koko cerr << "koko\n";
#define pass(...) __VA_ARGS__ ;

#endif /*SORIAE_DEBUG*/