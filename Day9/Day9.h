#pragma once

#include <algorithm>
#include <map>
#include <vector>

using namespace std;

struct Point {
  long long x;
  long long y;
  Point() = default;
  Point(long long x, long long y) : x(x), y(y) {}
};

struct Seg {
  long long start;
  long long end;
  long long len;
  Seg() = default;
  Seg(long long start, long long end, long long len) : start(start), end(end), len(len) {}
};

struct VEdge {
  long long x;
  long long y1;
  long long y2;
  VEdge() = default;
  VEdge(long long x, long long y1, long long y2) : x(x), y1(y1), y2(y2) {}
};

struct HEdge {
  long long y;
  long long x1;
  long long x2;
  HEdge() = default;
  HEdge(long long y, long long x1, long long x2) : y(y), x1(x1), x2(x2) {}
};

struct Interval {
  long long l;
  long long r;
  Interval() = default;
  Interval(long long l, long long r) : l(l), r(r) {}
};

inline vector<Seg> build_segments(const vector<long long> &coords, map<long long, int> &coord_to_index) {
  vector<long long> sorted_coords = coords;
  sort(sorted_coords.begin(), sorted_coords.end());
  sorted_coords.erase(unique(sorted_coords.begin(), sorted_coords.end()), sorted_coords.end());

  vector<Seg> segs;

  if (coords.empty()) {
    return segs;
  }

  for (size_t i = 0; i < sorted_coords.size(); ++i) {
    long long c = sorted_coords[i];
    if (i > 0) {
      long long prev = sorted_coords[i - 1];
      if (c > prev + 1) {
        segs.emplace_back(prev + 1, c - 1, c - prev - 1);
      }
    }
    segs.emplace_back(c, c, 1);
    coord_to_index[c] = static_cast<int>(segs.size()) - 1;
  }

  return segs;
}
