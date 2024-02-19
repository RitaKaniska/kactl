/**
 * Author: Lamu
 * Date: 2024-02-16
 * Description: Link Cut Tree.
 * Time: All operations take amortized O(\log N).
 */

using Data = array<int, 2>;

Data mergeData(Data a, Data b) {
  int x = 1LL * b[0] * a[0] % MOD;
  int y = (1LL * b[0] * a[1] + b[1]) % MOD;
  return {x, y};
}

#define SPLAY_NODE_INJECTION \
  Data val, d, drev;         \
  void recalc();             \
  void pushdown();

#define LINK_CUT 
struct Node {
  int cnt, flip; Node *p, *pp, *c[2]; // pp for LCT
  Node() {
    p = pp = c[0] = c[1] = 0; flip = 0; cnt = 1;
  }
  int side() const { return p->c[1] == this; }
#ifdef SPLAY_NODE_INJECTION 
  SPLAY_NODE_INJECTION 
#else 
  void recalc() {
    // recalc segment value and REVERSE VALUE (for LCT)
    cnt = 1;
    if (c[0]) {
      c[0]->pushdown(); cnt += c[0]->cnt;
    }
    if (c[1]) {
      c[1]->pushdown(); cnt += c[1]->cnt;
    }
  }
  void pushdown() {
    // lazy propagation. remove below if use splay only
    if (!flip) return;
    flip = 0, swap(c[0], c[1]);
    if (c[0]) c[0]->flip ^= 1;
    if (c[1]) c[1]->flip ^= 1;
  }
#endif 
  void attach(Node* x, int side) {
    assert(!flip); if (x) x->p = this;
    c[side] = x; this->recalc();
  }
  void rotate() {
#ifdef LINK_CUT 
    if (p->p) p->p->pushdown(); // LCT only
    p->pushdown(), pushdown();  // LCT only
#endif 
    Node* par = p; int s = side();
    if (par->p) par->p->attach(this, par->side());
    else p = nullptr;
    par->attach(c[s ^ 1], s); attach(par, s ^ 1);
#ifdef LINK_CUT 
    swap(this->pp, par->pp); // LCT only
#endif
  }
  void splay() {
    for (pushdown(); p; rotate()) {
#ifdef LINK_CUT
      if (p->p) p->p->pushdown(); // LCT only
      p->pushdown(), pushdown();  // LCT only
#endif
      if (p->p) (side() == p->side() ? p : this)->rotate();
    }
  }
  array<Node*, 2> split(int k) {
    if (k == 0) return {0, this};
    Node *cur = find(k), *r = cur->c[1];
    if (r) r->p = 0;
    cur->c[1] = 0; cur->recalc(); return {cur, r};
  }
  Node* find(int k) { // find k-th, splay to root
    assert(0 <= k && k <= cnt);
    Node* cur = this; while (1) {
      cur->pushdown();
      int sz = (cur->c[0] ? cur->c[0]->cnt : 0);
      if (k <= sz) cur = cur->c[0];
      else if (k > sz + 1) k -= sz + 1, cur = cur->c[1];
      else return cur->splay(), cur;
    }
  }
  Node* merge(Node* r) {
    Node* tmp = split(cnt)[0];
    return tmp->attach(r, 1), tmp;
  }
};

struct LinkCutTree {
  vector<Node> a;
  LinkCutTree(int n) : a(n) {}
  int id(Node *u) {
    return int(!u ? -1 : u - &a[0]);
  }
  void detach(Node *node) {
    if (node->c[1]) {
      swap(node->c[1]->pp, node->c[1]->p);
      node->c[1] = 0;
    }
  }
  int access(int u) {
    Node *node = &a[u], *par = node;
    node->splay(); detach(node);
    while (node->pp) {
      par = node->pp; par->splay();
      detach(par); par->attach(node, 1);
      node->pp = 0; node->splay();
    }
    return id(par);
  }
  void link(int p, int u) {
    access(u); a[u].pp = &a[p]; access(u);
  }
  void cut(int u) {
    access(u); assert(a[u].c[0]);
    a[u].c[0] = a[u].c[0]->p = 0;
    a[u].recalc();
  }
  int getRoot(int u) {
    access(u); return id(a[u].find(1));
  }
  bool sameTree(int u, int v) {
    return getRoot(u) == getRoot(v);
  }
  int lca(int u, int v) {
    if (!sameTree(u, v)) return -1;
    return access(u), access(v);
  }
  void makeRoot(int u) {
    access(u);
    if (a[u].c[0]) {
      a[u].c[0]->pp = &a[u];
      a[u].c[0]->flip ^= 1;
      a[u].c[0] = a[u].c[0]->p = 0;
      a[u].recalc();
    }
  }
  Node getPath(int u, int v) {
    assert(sameTree(u, v));
    makeRoot(u); access(v); return a[v];
  }
  void addEdge(int u, int v) {
    assert(!sameTree(u, v));
    makeRoot(v); link(u, v);
  }
  void remEdge(int u, int v) {
    assert(sameTree(u, v));
    makeRoot(u); access(v);
    assert(id(a[v].c[0]) == u);
    cut(v);
  }
};

#undef SPLAY_NODE_INJECTION

void Node::recalc() {
  cnt = 1;
  d = drev = val;
  if (c[0]) {
    c[0]->pushdown();
    cnt += c[0]->cnt;
    d = mergeData(c[0]->d, d);
    drev = mergeData(drev, c[0]->drev);
  }
  if (c[1]) {
    c[1]->pushdown();
    cnt += c[1]->cnt;
    d = mergeData(d, c[1]->d);
    drev = mergeData(c[1]->drev, drev);
  }
}

void Node::pushdown() {
  if (!flip) return;
  flip = 0, swap(c[0], c[1]);
  if (c[0]) c[0]->flip ^= 1;
  if (c[1]) c[1]->flip ^= 1;
  swap(d, drev);
}

struct LCT : LinkCutTree {
  using LinkCutTree::LinkCutTree;
  void update(int u, Data d) {
    access(u);
    a[u].val = d;
    a[u].recalc();
  }
};
