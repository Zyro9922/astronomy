/*=============================================================================
Copyright 2020 Syed Ali Hasan <alihasan9922@gmail.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#ifndef BOOST_ASTRONOMY_GRAPH_HPP
#define BOOST_ASTRONOMY_GRAPH_HPP

#include <iostream>

#include <map>
#include <list>
#include <stack>
#include <queue>

//Matrix
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/astronomy/coordinate/conversion/matrix_utilities.hpp>

//Time
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/astronomy/time/time_conversions.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace bac = boost::astronomy::coordinate;

template<typename T>
class Graph {

map<T, list<pair<T, matrix<double> > > > adj_list;

public:
Graph() {}

void add_edge(T u, T v, matrix<double> m){
  adj_list[u].push_back(make_pair(v,m));
}

matrix<double> get_edge(T u, T v)
{
  for (const auto& p : adj_list[u]){
    if(p.first == v)
      return p.second;
  }

  return identity_matrix<double>(3);
}

void print_adjacency_list()
{
  for (const auto& p : adj_list)
  {
    T A = p.first;

    std::cout << A << " -> ";

    auto nbrs = p.second;

    for (const auto& i : nbrs)
    {
      std::cout << "(" << i.first << ") ";
    }

    std::cout << std::endl;
  }
}

//Prints Breadth First from Source
void bfs_print(T src)
{
  map<T, bool> visited;
  queue<T> q;

  //ENTER START ELEMENT
  q.push(src);
  visited[src] = true;

  while (!q.empty())
  {
    T node = q.front();
    cout << node << ", ";
    q.pop();

    for (const auto& i : adj_list[node])
    {
      if (visited[i.first] == 0)
      {
        q.push(i.first);
        visited[i.first] = true;
      }
    }
  }

}

// Single Source Shortest Path
// Returns path length from Source to Destination
// Prints path length from source to every vertex in path
int sssp(T src, T dest)
{
  map<T, bool> visited;
  map<T, int> distance;
  queue<T> q;

  q.push(src);
  visited[src] = true;
  distance[src] = 0;

  while (q.front() != dest)
  {
    T node = q.front();
    q.pop();

    for (const auto& i : adj_list[node])
    {
      if (visited[i.first] == 0)
      {
        q.push(i.first);
        visited[i.first] = true;
        distance[i.first] = distance[node] + 1;
        cout << "Distance of " << i.first << " from source " << src << " is " << distance[i.first] << endl;

        if(i.first == dest)
          break;
      }
    }
  }

  return distance[dest];
}

// BFS Helper for convert function
bool bfs_convert(T src, T dest, map<T, T> &pred)
{
  map<T, bool> visited;
  map<T, int> distance;
  queue<T> q;

  //ENTER START ELEMENT
  q.push(src);
  visited[src] = true;
  distance[src] = 0;

  while (!q.empty())
  {
    T node = q.front();
    q.pop();

    for (const auto& i : adj_list[node])
    {
      if (visited[i.first] == 0)
      {
        q.push(i.first);
        visited[i.first] = true;
        distance[i.first] = distance[node] + 1;
        pred[i.first] = node;
        if(i.first == dest)
          return true;
      }
    }
  }
  return false;
}

matrix<double> convert(T src, T dest, const matrix<double> col_vec)
{

  //Is Source coordinate system valid?
  if (adj_list.find(src) == adj_list.end()) {
    throw std::range_error("Not found " + src);
  }

  //Is Destination coordinate system valid?
  if (adj_list.find(dest) == adj_list.end()) {
    throw std::range_error("Not found " + dest);
  }

  map<T, T> pred;

  if (!bfs_convert(src, dest, pred)) {
    throw std::range_error("No valid path between " + src + " and " + dest);
  }

  std::vector<T> path;
  T crawl = dest;
  path.push_back(crawl);

  while(pred[crawl] != src){
    path.push_back(pred[crawl]);
    crawl = pred[crawl];
  }

  path.push_back(src);

  int n = path.size();
  // printing path from source to destination
  cout << "\nConversion path: ";
  cout << path[n - 1];
  for (int i = n - 2; i >= 0; i--)
    cout << " -> " << path[i];

  matrix<double> ans = col_vec;

  std::cout << "\n";

  // matrix
  for (int i = n - 1; i > 0; i--) {
    ans = prod(get_edge(path[i], path[i - 1]), ans);
  }

  return ans;
}
};

Graph<string> g;

void init_graph(double phi, double st, double obliquity)
{
  g.add_edge("Equatorial HA Dec", "Horizon",
             bac::ha_dec_hor<double>(phi).get());
  g.add_edge("Horizon", "Equatorial HA Dec",
             bac::ha_dec_hor<double>(phi).get());

  g.add_edge("Equatorial HA Dec", "Equatorial RA Dec",
             bac::ha_dec_ra_dec<double>(st).get());
  g.add_edge("Equatorial RA Dec", "Equatorial HA Dec",
             bac::ha_dec_ra_dec<double>(st).get());

  g.add_edge("Equatorial RA Dec", "Ecliptic",
             bac::ra_dec_to_ecliptic<double>(obliquity).get());
  g.add_edge("Ecliptic", "Equatorial RA Dec",
             bac::ecliptic_to_ra_dec<double>(obliquity).get());

  g.add_edge("Equatorial RA Dec", "Galactic",
             bac::ra_dec_to_galactic<double>().get());
  g.add_edge("Galactic", "Equatorial RA Dec",
             bac::galactic_to_ra_dec<double>().get());
}

#endif  // BOOST_ASTRONOMY_GRAPH_HPP
