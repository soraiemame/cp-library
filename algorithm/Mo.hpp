struct Mo {
    explicit Mo(int n) : n(n) {}
    void add(int l, int r) {
        lr.emplace_back(l, r);
    }
    template<class AL, class AR, class EL, class ER, class O>
    void build(const AL& add_left, const AR& add_right, const EL& erase_left, const ER& erase_right, const O& out) {
        int q = int(lr.size());
        if (q == 0) {
            std::cerr << "No queries found.\n";
            return;
        }
        int bs = n / std::min<int>(n, std::sqrt(q));
        std::vector<int> ord(q);
        std::iota(ord.begin(), ord.end(), 0);
        std::sort(ord.begin(), ord.end(), [&](int a, int b) {
            int abl = lr[a].first / bs, bbl = lr[b].first / bs;
            if (abl != bbl) return abl < bbl;
            else return (abl & 1) ? lr[a].second > lr[b].second : lr[a].second < lr[b].second;
            });
        int cl = 0, cr = 0;
        for (int idx : ord) {
            while (cl > lr[idx].first)  add_left(--cl);
            while (cr < lr[idx].second) add_right(cr++);
            while (cl < lr[idx].first)  erase_left(cl++);
            while (cr > lr[idx].second) erase_right(--cr);
            out(idx);
        }
    }
    template<class A, class E, class O>
    void build(const A& add, const E& erase, const O& out) { build(add, add, erase, erase, out); }
private:
    int n;
    std::vector<std::pair<int, int>> lr;
};
