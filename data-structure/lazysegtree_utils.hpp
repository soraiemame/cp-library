namespace tools{
    template<class T>
    T lim_max(){return std::numeric_limits<T>::max();}
    template<class T>
    T lim_min(){return std::numeric_limits<T>::min();}
    template<class T>
    T zero(){return T(0);}

    template<class T>
    T _min(T a,T b){return std::min(a,b);}
    template<class T>
    T _max(T a,T b){return std::max(a,b);}
    template<class T>
    T sum(T a,T b){return a + b;}
    template<class T>
    T none(T a,T b){return a == tools::lim_max<T>() ? b : a;}

    template<class T>
    struct range_add{
        T val;
        int size;
        friend std::ostream& operator<<(std::ostream& os,range_add r){return os << r.val;}
    };
    template<class T>
    range_add<T> range_add_sum(range_add<T> a,range_add<T> b){return range_add<T>{a.val + b.val,a.size + b.size};}
    template<class T>
    range_add<T> range_add_e(){return range_add<T>{T(0),1};}
    template<class T>
    range_add<T> range_add_add(T f,range_add<T> x){return range_add<T>{x.size * f + x.val,x.size};}
    template<class T>
    range_add<T> range_add_update(T f,range_add<T> x){return f == lim_max<T>() ? x : range_add<T>{x.size * f,x.size};}
};

namespace aliases{
    template<class T>
    using RMQ_RUQ = lazy_segtree<T,tools::_min<T>,tools::lim_max<T>,T,tools::none<T>,tools::none<T>,tools::lim_max<T>>;
    template<class T>
    using RMQ_RAQ = lazy_segtree<T,tools::_min<T>,tools::lim_max<T>,T,tools::sum<T>,tools::sum<T>,tools::zero<T>>;
    template<class T>
    using RMaxQ_RUQ = lazy_segtree<T,tools::_max<T>,tools::lim_max<T>,T,tools::none<T>,tools::none<T>,tools::lim_max<T>>;
    template<class T>
    using RMaxQ_RAQ = lazy_segtree<T,tools::_max<T>,tools::lim_max<T>,T,tools::sum<T>,tools::sum<T>,tools::zero<T>>;
    template<class T>
    using RSQ_RUQ = lazy_segtree<tools::range_add<T>,tools::range_add_sum<T>,tools::range_add_e<T>,
    T,tools::range_add_update<T>,tools::none<T>,tools::lim_max<T>>;
    template<class T>
    using RSQ_RAQ = lazy_segtree<tools::range_add<T>,tools::range_add_sum<T>,tools::range_add_e<T>,
    T,tools::range_add_add,tools::sum<T>,tools::zero<T>>;
};

using aliases::RMQ_RAQ;
using aliases::RMQ_RUQ;
using aliases::RMaxQ_RAQ;
using aliases::RMaxQ_RUQ;
using aliases::RSQ_RAQ;
using aliases::RSQ_RUQ;
