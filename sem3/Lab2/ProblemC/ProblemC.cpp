#include <bits/stdc++.h>

using namespace std;
int n, m;

class vert {
public:
    int u, v;
    int prior, size_st;
    vert * l_son;
    vert * r_son;
    vert * batya;

    //empty constructor
    vert() {}

    //main constructor
    vert(int new_size_st, int new_prior, int new_u, int new_v) {
        size_st = new_size_st;
        prior = new_prior;
        l_son = nullptr;
        r_son = nullptr;
        batya = nullptr;
        u = new_u;
        v = new_v;
    }
};

//vector<vect> vert_vec;

typedef vert * vert_ptr;

int size_st(vert_ptr cur_treap) {
    return cur_treap ? cur_treap->size_st : 0;
}

void update(vert_ptr cur_treap) {
    if (cur_treap) {
        cur_treap->size_st = size_st(cur_treap->l_son) + size_st(cur_treap->r_son) + 1;
        if (cur_treap->l_son != nullptr) {
            cur_treap->l_son->batya = cur_treap;
        }
        if (cur_treap->r_son != nullptr) {
            cur_treap->r_son->batya = cur_treap;
        }
    }
}

/*void merge_treap(vert_ptr & cur_treap, vert_ptr l, vert_ptr r) {
    if (!l || !r) {
        cur_treap = l ? l : r;
    } else if (l->prior > r->prior) {
        merge_treap(l->r_son, l->r_son, r);
        cur_treap = l;
    } else {
        merge_treap(r->l_son, l, r->l_son);
    }
    update(cur_treap);
}*/

void merge_treap(vert_ptr & t, vert_ptr l, vert_ptr r) {
	if (!l || !r)
		t = l ? l : r;
	else
	if (l->prior > r->prior) {
	//	(*r).parent = l;
		merge_treap((*l).r_son, (*l).r_son, r);
		t = l;
	}
	else {
	//	(*l).parent = r;
		merge_treap((*r).l_son, l, (*r).l_son);
		t = r;
	}
	update(t);
}

void split (vert_ptr cur_treap, vert_ptr & l, vert_ptr & r, int split_key, int a = 0, bool first = true) {
    if (!cur_treap) {
        l = 0;
        r = 0;
        return;
    }
    int temp_key = a + size_st(cur_treap->l_son);
    if (split_key <= temp_key) {
        split(cur_treap->l_son, l, cur_treap->l_son, split_key, a, false);
        r = cur_treap;
    } else {
        split(cur_treap->r_son, cur_treap->r_son, r, split_key, a + 1 + size_st(cur_treap->l_son), false);
        l = r;
    }
    if (first) {
        if (l) {
            l->batya = nullptr;
        }
        if (r) {
            r->batya = nullptr;
        }
    }
    update(cur_treap);
}

/*pair<int, int> place_to_edge(vert_ptr cur_treap, int place, int a = 0) {
    int temp_place = a + size_st(cur_treap->l_son);
    if (temp_place == place) {
        return make_pair(cur_treap->u, cur_treap->v);
    } else if (place < temp_place) {
        return place_to_edge(cur_treap->l_son, place, a);
    } else {
        return place_to_edge(cur_treap->r_son, place, a + 1 + size_st(cur_treap->l_son));
    }
}*/

int vert_to_place(vert_ptr cur_treap) {
    int result = 1;
    if (cur_treap->l_son) {
        result += cur_treap->l_son->size_st;
    }
    while(cur_treap->batya != nullptr) {
        if (/*cur_treap->bata->r_son &&*/ cur_treap == cur_treap->batya->r_son) {
            result++;
        }
        if (cur_treap == cur_treap->batya->l_son) {
            result += cur_treap->batya->l_son->size_st;
        }
        cur_treap = cur_treap->batya;
    }
    return result;
}

vert_ptr root(vert_ptr cur_treap) {
    vert_ptr result = cur_treap;
    if (cur_treap->batya != nullptr) {
        result = cur_treap->batya;
    }
    while (result->batya != nullptr) {
        result = result->batya;
    }
    return result;
}

map<pair<int, int>, vert_ptr> places;

void link(int u, int v) {
    /*vert_ptr a1, a2, b1, b2;
    a1 = nullptr;
    a2 = nullptr;
    b1 = nullptr;
    b2 = nullptr;

    pair<int, int> new_edge(u, u);
    cout << "root u : " << root(places[new_edge])->u << " " << root(places[new_edge])->v << endl;
    split(root(places[new_edge]), a1, a2, vert_to_place(places[new_edge]));

    new_edge = make_pair(v, v);
    cout << "root v : " << root(places[new_edge])->u << " " << root(places[new_edge])->v << endl;
    split(root(places[new_edge]), b1, b2, vert_to_place(places[new_edge]));

    new_edge = make_pair(u, v);
    places.insert(make_pair(make_pair(u, v), new vert(1, rand() % 100000, u, v)));
    //places[make_pair(v, u)] = new vert(1, rand() % 100000, v, u);
    merge_treap(a1, a1, places[new_edge]);
    //cout << "root u : " << root(places[make_pair(u, v)])->u << " " << root(places[make_pair(u, v)])->v << endl;

    new_edge = make_pair(v, u);
    places.insert(make_pair(make_pair(v, u), new vert(1, rand() % 100000, v, u)));
    //places[make_pair(u, v)] = new vert(1, rand() % 100000, u, v);
    merge_treap(b1, b1, places[new_edge]);

    merge_treap(a1, a1, b2);
    merge_treap(a1, a1, b1);
    merge_treap(a1, a1, a2);

    cout << "after link: " << endl;
    cout << "root u : " << root(places[make_pair(u, u)])->u << " " << root(places[make_pair(u, u)])->v << endl;
    cout << "root v : " << root(places[make_pair(v, v)])->u << " " << root(places[make_pair(v, v)])->v << endl << endl;*/
    vert_ptr a = nullptr, b = nullptr, c = nullptr, d = nullptr;
    pair<int, int> e;
	e.first = u; e.second = u;
	split(root(places[e]), a, b, vert_to_place(places[e]));
	e.second = v;
	places[e] = new vert(1, rand() % 100000, e.first, e.second);
	merge_treap(a, a, places[e]);
	e.first = v;
	split(root(places[e]), c, d, vert_to_place(places[e]));
	e.second = u;
	places[e] = new vert(1, rand() % 100000, e.first, e.second);
	merge_treap(c, c, places[e]);

	merge_treap(a, a, d);
	merge_treap(a, a, c);
	merge_treap(a, a, b);
}

void cut(int v, int u) {
    vert_ptr a1, a2, b1, b2;
    a1 = nullptr;
    a2 = nullptr;
    b1 = nullptr;
    b2 = nullptr;

    pair<int, int> edge1(v, u);
    pair<int, int> edge2(u, v);
    if (vert_to_place(places[edge1]) > vert_to_place(places[edge2])) {
        swap(edge1, edge2);
    }

    split(root(places[edge1]), a1, a2, vert_to_place(places[edge1]));
    split(root(places[edge2]), b1, b2, vert_to_place(places[edge2]));
    split(a1, a1, b1, size_st(a1) - 1);
    merge_treap(a1, a1, b2);
    split(b1, b1, a2, size_st(b1) - 1);
    places[edge1] = nullptr;
    places[edge2] = nullptr;
}

void connected(int u, int v) {
    pair<int, int> edge1(u, u);
    pair<int, int> edge2(v, v);
    if (root(places[edge1]) == root(places[edge2])) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }
}

void sizze(int u) {
    pair<int, int> edge1(u, u);
    cout << (root(places[edge1])->size_st + 2)/3;
}

int main() {

    ifstream cin("smth.in");
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        places.insert(make_pair(make_pair(i, i), new vert(1, rand() % 100000, i, i)));
    }

    string command;
    int v, u;
    for (int i = 0; i < m; i++) {
        cin >> command >> v;
        v--;
        if (command == "link") {
            cin >> u;
            u--;
            cout << "run link v = " << v << "   u = " << u << endl;
            link(v, u);
        } else if (command == "connected") {
            cin >> u;
            u--;
            connected(v, u);
        } else if (command == "cut") {
            cin >> u;
            u--;
            cut(v, u);
        } else if (command == "size") {
            sizze(v);
        }
    }

    return 0;
}
