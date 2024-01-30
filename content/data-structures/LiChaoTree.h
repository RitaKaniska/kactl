/**
 * Author: Lamu
 * Date: 2024
 * Description: 
 */

struct node
{
    Line f;
    node *l, *r;
    node() {
        f = {0,(int)1e18};
        l = r = 0;
    }
};
struct LiChaoTree
{
    node *tree;
    void upd(node *&x, int lx, int rx, Line line) {
        if (!x) x = new node;
        if (lx == rx)
        {
            if (x->f(lx) > line(lx)) swap(x->f, line);
            return;
        }
        int mid = lx + (rx - lx) / 2;
        if (x->f(mid) > line(mid)) swap(x->f, line);
        if (x->f(lx) > line(lx))
            upd(x->l, lx, mid, line);
        else upd(x->r, mid+1, rx, line);
    }

    int get(node *&x, int lx, int rx, int k) {
        if (!x) return 1e18;
        if (lx == rx) return x->f(k);
        int mid = lx + (rx - lx) / 2;
        if (k <= mid) return min(x->f(k), get(x->l, lx, mid, k));
        else return min(x->f(k), get(x->r, mid+1, rx, k));
    }

    void updr(node *&x, int lx, int rx, int l, int r, Line line) {
        if (lx > r || rx < l) return;
        if (!x) x = new node;
        if (lx >= l && rx <= r) {
            upd(x, lx, rx, line);
            return;
        }
        int mid = lx + (rx - lx) / 2;
        updr(x->l, lx, mid, l, r, line);
        updr(x->r, mid+1, rx, l, r, line);
    }
};
