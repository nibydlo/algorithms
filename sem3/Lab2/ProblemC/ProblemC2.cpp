/* .                .
            :"-.          .-";
            |:`.`.__..__.'.';|
            || :-"      "-; ||
            :;              :;
            /  .==.    .==.  \
           :      _.--._      ;
           ; .--.' `--' `.--. :
          :   __;`      ':__   ;
          ;  '  '-._:;_.-'  '  :
          '.       `--'       .'
           ."-._          _.-".
         .'     ""------""     `.
        /`-                    -'\
       /`-                      -'\
      :`-   .'              `.   -';
      ;    /                  \    :
     :    :                    ;    ;
     ;    ;                    :    :
     ':_:.'                    '.;_;'
        :_                      _;
        ; "-._                -" :`-.     _.._
        :_          ()          _;   "--::__. `.
         \"-                  -"/`._           :
        .-"-.                 -"-.  ""--..____.'
       /         .__  __.         \
      : / ,       / "" \       . \ ;
       "-:___..--"      "--..___;-"    */


#include <bits/stdc++.h>

using namespace std;

class vert {
public:
	int size_st, prior;
	vert *l, *r, *batya;

	vert() { }

	vert(int k, int p/*, pair<int,int> new_edge*/){

	    size_st = k;
	    prior = p;
	    //edge = v;
	    l = nullptr;
	    r = nullptr;
	    batya = nullptr;
	}
};

typedef vert * vert_ptr;

int size_st(vert_ptr cur_vert) {

	int result = 0;
	if (cur_vert != nullptr) {
		result = cur_vert->size_st;
	}
	return result;
}

void update(vert_ptr cur_vert) {

	if (cur_vert) {
		cur_vert->size_st = size_st(cur_vert->l) + size_st(cur_vert->r) + 1;
		if (cur_vert->l != nullptr)
			(cur_vert->l)->batya = cur_vert;
		if (cur_vert->r != nullptr)
			(cur_vert->r)->batya = cur_vert;
	}
}

vert_ptr root(vert_ptr cur_vert) {

	vert_ptr result = cur_vert;
	if (cur_vert->batya != nullptr)
		result = cur_vert->batya;

	while (result->batya != nullptr) {
		result = result->batya;
	}

	return result;
}

int ptr_to_int(vert_ptr cur_vert) {

	int result = 1;

	if (cur_vert->l) {
		result += (cur_vert->l)->size_st;
	}

	while (cur_vert->batya != nullptr) {
		if (cur_vert->batya->r && cur_vert == cur_vert->batya->r)
			++result;
		if (cur_vert->batya->l && (cur_vert != cur_vert->batya->l))
			result += (cur_vert->batya->l)->size_st;
		cur_vert = cur_vert->batya;
	}
	return result;
}

void merge_treap(vert_ptr & cur_vert, vert_ptr l, vert_ptr r) {

	if (!l || !r) {
		cur_vert = l ? l : r;
	} else if (l->prior > r->prior) {
		merge_treap(l->r, l->r, r);
		cur_vert = l;
	} else {
		merge_treap(r->l, l, r->l);
		cur_vert = r;
	}
	update(cur_vert);
}

void split_treap(vert_ptr cur_vert, vert_ptr &l, vert_ptr &r, int k, int a = 0, bool first = true) {

	if (!cur_vert) {
        l = 0;
        r = 0;
        return;
	}

	if (k <= a + size_st(cur_vert->l)) {
		split_treap(cur_vert->l, l, cur_vert->l, k, a, false);
		r = cur_vert;
	} else {
		split_treap(cur_vert->r, cur_vert->r, r, k, a + 1 + size_st(cur_vert->l), false);
		l = cur_vert;
	}

	if (first) {
		if (r) {
			r->batya = nullptr;
		}
		if (l) {
			l->batya = nullptr;
		}
	}
	update(cur_vert);
}

map<pair<int,int>, vert_ptr> places;

void link(int u, int v) {

	vert_ptr a1 = nullptr;
	vert_ptr a2 = nullptr;
	vert_ptr b1 = nullptr;
	vert_ptr b2 = nullptr;

	pair<int, int> edge(u, u);
	split_treap(root(places[edge]), a1, a2, ptr_to_int(places[edge]));

	edge = make_pair(v, v);
	split_treap(root(places[edge]), b1, b2, ptr_to_int(places[edge]));

	edge = make_pair(u, v);
	places[edge] = new vert(1, rand() % 100000);
	merge_treap(a1, a1, places[edge]);

	edge = make_pair(v, u);
	places[edge] = new vert(1, rand() % 100000);
	merge_treap(b1, b1, places[edge]);

	merge_treap(a1, a1, b2);
	merge_treap(a1, a1, b1);
	merge_treap(a1, a1, a2);
}

void cut(int u, int v) {

	vert_ptr a1 = nullptr;
	vert_ptr a2 = nullptr;
	vert_ptr b1 = nullptr;
	vert_ptr b2 = nullptr;

    pair<int, int> edge1(u, v), edge2(v, u);
	if (ptr_to_int(places[edge1]) > ptr_to_int(places[edge2])) {
		swap(edge1, edge2);
	}

	split_treap(root(places[edge1]), a1, a2, ptr_to_int(places[edge1]));
	split_treap(root(places[edge2]), b1, b2, ptr_to_int(places[edge2]));
	split_treap(a1, a1, a2, size_st(a1) - 1);
	merge_treap(a1, a1, b2);
	split_treap(b1, b1, a2, size_st(b1) - 1);

	places[edge1] = nullptr;
	places[edge2] = nullptr;
}

void connected(int u, int v) {

	pair<int, int> edge1(u, u), edge2(v, v);
	if (root(places[edge1]) == root(places[edge2])) {
        cout << "1" << endl;
	} else {
        cout << "0" << endl;
	}
}

void sizze(int u) {

	pair<int, int> edge(u, u);
	cout << (root(places[edge])->size_st + 2) / 3 << endl;
}

int main() {

	//ifstream cin("smth.in");

	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		pair<int, int> new_edge(i, i);
		places[new_edge] = new vert(1, rand() % 100000);
	}

    string command;
    int u, v;
	for (int i = 0; i < m; ++i) {
		cin >> command >> u;
		if (command == "link") {
			cin >> v;
			link(u - 1, v - 1);
		} else if (command == "cut") {
			cin >> v;
			cut(u - 1, v - 1);
		} else if (command == "connected") {
			cin >> v;
			connected(u - 1, v - 1);
		} else if (command == "size"){
			sizze(u - 1);
		}
	}
}
