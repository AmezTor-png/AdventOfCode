#include "Day9.h"

#include <iostream>

using namespace std;

bool orden(const Interval &a, const Interval &b) {
  if (a.l != b.l){
    return a.l < b.l;
  }
  
  return a.r < b.r;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<Point> points;
  string line;

  while (getline(cin, line)) {
    if (line.empty()) {
      continue;
    }
    
    size_t comma = line.find(',');
    
    if (comma == string::npos) {
      continue;
    }
    
    long long x = stoll(line.substr(0, comma));
    long long y = stoll(line.substr(comma + 1));
    points.push_back({x, y});
  }

  if (points.empty()) {
    return 0;
  }

  const int n = static_cast<int>(points.size());
  long long best1 = 0;
  
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      long long area = (llabs(points[i].x - points[j].x) + 1) * (llabs(points[i].y - points[j].y) + 1);
      
      best1 = max(best1, area);
    }
  }

  vector<VEdge> v_edges;
  vector<HEdge> h_edges;
  vector<long long> x_coords;
  vector<long long> y_coords;
  
  x_coords.reserve(n);
  y_coords.reserve(n);
  
  for (size_t i = 0; i < points.size(); ++i) {
    const Point &p = points[i];
    x_coords.push_back(p.x);
    y_coords.push_back(p.y);
  }

  for (int i = 0; i < n; ++i) {
    const Point &a = points[i];
    const Point &b = points[(i + 1) % n];
    
    if (a.x == b.x) {
      if (a.y == b.y) {
        continue;
      }
      
      long long y1 = min(a.y, b.y);
      long long y2 = max(a.y, b.y);
      v_edges.emplace_back(a.x, y1, y2);
    
    } else if (a.y == b.y) {
      long long x1 = min(a.x, b.x);
      long long x2 = max(a.x, b.x);
      h_edges.emplace_back(a.y, x1, x2);
    
    } else {
      cerr << "Invalido.\n";
      return 1;
    }
  }

  map<long long, int> x_index;
  map<long long, int> y_index;
  vector<Seg> x_segs = build_segments(x_coords, x_index);
  vector<Seg> y_segs = build_segments(y_coords, y_index);

  const int X = static_cast<int>(x_segs.size());
  const int Y = static_cast<int>(y_segs.size());
  
  vector<long long> pref(static_cast<size_t>(X + 1) * (Y + 1), 0);

  auto pref_at = [&](int y, int x) -> long long & {
    return pref[static_cast<size_t>(y) * (X + 1) + x];
  };

  for (int yi = 0; yi < Y; ++yi) {
    long long y0 = y_segs[yi].start;
    vector<long long> crossings;
    crossings.reserve(v_edges.size());
    
    for (size_t i = 0; i < v_edges.size(); ++i) {
      const VEdge &e = v_edges[i];
      if (y0 >= e.y1 && y0 < e.y2) {
        crossings.emplace_back(e.x);
      }
    }
    
    sort(crossings.begin(), crossings.end());

    vector<Interval> intervals;
    intervals.reserve(crossings.size() / 2 + h_edges.size());
    
    for (size_t k = 0; k + 1 < crossings.size(); k += 2) {
      long long l = crossings[k];
      long long r = crossings[k + 1];
      
      if (l > r) {
        swap(l, r);
      }
      
      intervals.emplace_back(l, r);
    }
    
    for (size_t i = 0; i < h_edges.size(); ++i) {
      const HEdge &e = h_edges[i];
      if (e.y == y0) {
        intervals.emplace_back(e.x1, e.x2);
      }
    }
    
    if (!intervals.empty()) {
      sort(intervals.begin(), intervals.end(), orden);
    }

    vector<Interval> merged;
    
    for (size_t i = 0; i < intervals.size(); ++i) {
      const Interval &in = intervals[i];
      if (merged.empty() || in.l > merged.back().r + 1) {
        merged.emplace_back(in.l, in.r);
      } else if (in.r > merged.back().r) {
        merged.back().r = in.r;
      }
    }

    for (int xi = 0; xi < X; ++xi) {
      const auto &xs = x_segs[xi];
      auto it = lower_bound(merged.begin(), merged.end(), xs.start,
                                 [](const Interval &a, long long val) {
                                   return a.r < val;
                                 });
      
      bool inside = (it != merged.end() && it->l <= xs.start && it->r >= xs.end);
      long long weight = inside ? 0 : xs.len * y_segs[yi].len;
      pref_at(yi + 1, xi + 1) = pref_at(yi + 1, xi) + pref_at(yi, xi + 1) - pref_at(yi, xi) + weight;
    }
  }

  auto sum_outside = [&](int xa, int xb, int ya, int yb) -> long long {
    if (xa > xb) swap(xa, xb);
    if (ya > yb) swap(ya, yb);
    return pref_at(yb + 1, xb + 1) - pref_at(ya, xb + 1) - pref_at(yb + 1, xa) + pref_at(ya, xa);
  };

  long long best2 = 0;
  
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      long long x1 = points[i].x, y1 = points[i].y;
      long long x2 = points[j].x, y2 = points[j].y;
      long long xlo = min(x1, x2), xhi = max(x1, x2);
      long long ylo = min(y1, y2), yhi = max(y1, y2);
      long long area = (xhi - xlo + 1) * (yhi - ylo + 1);
      
      if (area <= best2) continue;
      
      auto it_x1 = x_index.find(xlo), it_x2 = x_index.find(xhi);
      auto it_y1 = y_index.find(ylo), it_y2 = y_index.find(yhi);
      
      if (it_x1 != x_index.end() && it_x2 != x_index.end() && it_y1 != y_index.end() && it_y2 != y_index.end() && sum_outside(it_x1->second, it_x2->second, it_y1->second, it_y2->second) == 0) {
        best2 = area;
      }
    }
  }

  cout << "Parte 1: " << best1 << "\n";
  cout << "Parte 2: " << best2 << "\n";

  return 0;
}
