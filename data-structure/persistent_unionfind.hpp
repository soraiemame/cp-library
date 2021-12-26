template<class T, int csz = 16>
struct PersistentArray{
private:
    struct node;
    using np = node*;
    struct node{
        T val;
        np ch[csz] = {};
    };
    np root;
    np set(int idx,const T& x,const np& t){
        np res = new node();
        if(t){
            memcpy(res->ch,t->ch,sizeof(t->ch));
            res->val = t->val;
        }
        if(idx == 0) res->val = x;
        else res->ch[idx % csz] = set(idx / csz,x,res->ch[idx % csz]);
        return res;
    }
    T get(int idx,const np& t) const {
        if(idx == 0)return t->val;
        return get(idx / csz,t->ch[idx % csz]);
    }
public:
    int n;
    void set(int idx,const T& x){
        assert(0 <= idx && (n < 0 || idx < n));
        root = set(idx,x,root);
    }
    T get(int idx) const {
        assert(0 <= idx && (n < 0 || idx < n));
        return get(idx, root);
    }
    PersistentArray(int n = -1) : root(nullptr), n(n) {}
    template<class stream> friend stream& operator<<(stream& os, const PersistentArray& a){
        assert(a.n >= 0);
        os << '[';
        for(int i = 0;i < a.n;i++)os << a.get(i) << (i == a.n - 1 ? "" : ",");
        os << ']';
        return os;
    }
};

struct PersistentUnionFind{
    PersistentUnionFind(int n = 0) : n(n), dat(n) {
        for(int i = 0;i < n;i++)dat.set(i,-1);
    }
    int find(int a) const {
        assert(0 <= a && a < n);
        if(dat.get(a) < 0)return a;
        else return find(dat.get(a));
    }
    void merge(int a,int b){
        assert(0 <= a && a < n && 0 <= b && b < n);
        a = find(a);
        b = find(b);
        if(a == b)return;
        if(dat.get(a) > dat.get(b))swap(a,b);
        dat.set(a,dat.get(a) + dat.get(b));
        dat.set(b,a);
    }
    bool same(int a,int b) const {
        assert(0 <= a && a < n && 0 <= b && b < n);
        return find(a) == find(b);
    }
    int size(int a) const {
        assert(0 <= a && a < n);
        return -dat.get(find(a));
    }
    template<class stream> friend stream& operator<<(stream& os, const PersistentUnionFind& a){ return os << a.dat; }

    int n;
    PersistentArray<int> dat;
};
