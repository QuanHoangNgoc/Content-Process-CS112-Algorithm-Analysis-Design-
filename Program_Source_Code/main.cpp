#include <bits/stdc++.h>
#define int long long
#define cerr cout
using namespace std;

const int N = 2e5 + 7;
const int NODE = 4 * N;
pair<int, int> y[NODE];  // ..
int leng[NODE];          // 0
int cnt[NODE];           // 0

void mark(int id, int l, int r, int u, int v, int k) {
  if (u > v) return;
  if (v <= y[l].first || u >= y[r].second) return;

  if (u <= y[l].first && y[r].second <= v) {
    cnt[id] += k;
    if (cnt[id] > 0)
      leng[id] = y[r].second - y[l].first;
    else {
      // if (l == r)
      //   leng[id] = y[r].second - y[l].first;
      // else
      leng[id] = leng[id * 2] + leng[id * 2 + 1];
    }
    return;
  }

  int m = (l + r) / 2;
  mark(id * 2, l, m, u, v, k);
  mark(id * 2 + 1, m + 1, r, u, v, k);
  if (cnt[id] > 0)
    leng[id] = y[r].second - y[l].first;
  else {
    // if (l == r)
    //   leng[id] = y[r].second - y[l].first;
    // else
    leng[id] = leng[id * 2] + leng[id * 2 + 1];
  }
}

int n, K;
vector<pair<pair<int, int>, pair<int, int>>> event;

set<int> s;
// int numEncode;
// map<int, int> encode;

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  freopen("A.inp", "r", stdin);
  freopen("A.out", "w", stdout);

  cin >> K >> n;
  int x1 = 0, y1 = 0, x2 = K, y2 = K;
  for (int i = 0; i < n; ++i) {
    char d;
    int l, _x1 = x1, _y1 = y1, _x2 = x2, _y2 = y2;
    cin >> d >> l;
    if (d == 'N') {
      _y1 += l;
      _y2 += l;
    }
    if (d == 'S') {
      _y1 -= l;
      _y2 -= l;
    }
    if (d == 'W') {
      _x1 -= l;
      _x2 -= l;
    }
    if (d == 'E') {
      _x1 += l;
      _x2 += l;
    }
    int x = min({x1, x2, _x1, _x2});
    int y = min({y1, y2, _y1, _y2});
    int u = max({x1, x2, _x1, _x2});
    int v = max({y1, y2, _y1, _y2});
    // cerr << x << " " << y << " " << u << " " << v << endl;

    event.push_back({{x, +1}, {y, v}});
    event.push_back({{u, -1}, {y, v}});
    x1 = _x1, y1 = _y1, x2 = _x2, y2 = _y2;
    s.insert(y);
    // s.insert(y - 1);
    // s.insert(y + 1);
    s.insert(v);
    // s.insert(v - 2);
    // s.insert(v);
  }

  sort(event.begin(), event.end());
  // cerr << "event: " << endl;
  //  for (auto e : event)
  //    cerr << e.first.first << " " << e.first.second << " " << e.second.first
  //         << " " << e.second.second << endl;
  vector<int> v;
  for (int x : s) {
    // encode[x] = ++numEncode;
    v.push_back(x);
  }
  for (int i = 0; i < v.size() - 1; ++i) {
    y[i + 1] = {v[i], v[i + 1]};
  }
  y[v.size()] = {v.back(), v.back()};
  // for (int i = 1; i <= v.size(); ++i)
  //   cerr << y[i].first << " " << y[i].second << endl;

  long long res = 0;
  int i = 0;
  mark(1, 1, v.size(), event[i].second.first, event[i].second.second,
       event[i].first.second);
  for (int i = 1; i < event.size(); ++i) {
    // cerr << "x = " << event[i].first.first << endl;
    // cerr << "leng " << leng[1] << endl;
    res += (event[i].first.first - event[i - 1].first.first) * leng[1];
    // cerr << res << endl;
    //  if (event[i].first.first != 2)
    mark(1, 1, v.size(), event[i].second.first, event[i].second.second,
         event[i].first.second);
    // cerr << "leng " << leng[1] << endl;
  }
  cout << res;

  return 0;
}