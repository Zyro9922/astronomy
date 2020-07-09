

#ifndef BOOST_ASTRONOMY_GRAPH_HPP
#define BOOST_ASTRONOMY_GRAPH_HPP

#include <iostream>
#include <boost/astronomy/coordinate/coord_sys/equatorial_coord.hpp>
//#include <boost/astronomy/coordinate/coord_sys/equatorial_ra_coord.hpp>
#include <boost/astronomy/coordinate/coord_sys/ecliptic_coord.hpp>
#include <boost/astronomy/coordinate/rep/spherical_equatorial_representation.hpp>
#include <boost/astronomy/coordinate/coord_sys/horizon_coord.hpp>
#include <boost/astronomy/coordinate/rep/spherical_representation.hpp>
#include <boost/astronomy/coordinate/io/io.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/luminous_flux.hpp>
#include <boost/units/systems/si/time.hpp>
#include <boost/units/systems/si/velocity.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/units/io.hpp>
#include <boost/units/systems/angle/degrees.hpp>
//Matrix
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/astronomy/coordinate/conversion/matrix_utilities.hpp>

////TIME
#include <boost/astronomy/time/time_conversions.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <stack>
#include <map>

namespace bac = boost::astronomy::coordinate;

template<typename T>
class Graph {

  map<T, list<pair<T, matrix<double> > > > adjList;

 public:
  Graph() {}

  void addEdge(T u, T v, matrix<double> m)
  {
    adjList[u].push_back(make_pair(v,m));
  }

  matrix<double> getEdge(T u, T v)
  {
    for (const auto& p : adjList[u])
    {
      if(p.first == v)
        return p.second;
    }

    return identity_matrix<double>(3);
  }

  void printAdjList()
  {
    for (const auto& p : adjList)
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

  void bfsPrint(T src)
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

      for (const auto& i : adjList[node])
      {
        if (visited[i.first] == 0)
        {
          q.push(i.first);
          visited[i.first] = true;
        }
      }
    }

  }

  int sssp(T src, T dest)
  {
    map<T, bool> visited;
    map<T, int> distance;
    queue<T> q;

    //ENTER START ELEMENT
    q.push(src);
    visited[src] = true;
    distance[src] = 0;

    while (q.front() != dest)
    {
      T node = q.front();
      q.pop();

      for (const auto& i : adjList[node])
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

  bool sssp2(T src, T dest, map<T, T> &pred)
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

      for (const auto& i : adjList[node])
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

  matrix<double> convert(T src, T dest, matrix<double> col_vec)
  {
    map<T, T> pred;

    if (!sssp2(src, dest, pred)) {
      std::cout << "Given source and destination are not connected";
      return identity_matrix<double>(3);
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
    for (int i = n - 1; i > 0; i--)
    {
      ans = prod(getEdge(path[i], path[i-1]), ans);
    }

    return ans;
  }
};

Graph<string> g;

void init_graph(double phi, double st, double obliquity)
{
  g.addEdge("Equatorial HA Dec", "Horizon",bac::ha_dec_hor<double>(phi).get());
  g.addEdge("Horizon","Equatorial HA Dec",bac::ha_dec_hor<double>(phi).get());

  g.addEdge("Equatorial HA Dec", "Equatorial RA Dec",bac::ha_dec_ra_dec<double>(st).get());
  g.addEdge("Equatorial RA Dec", "Equatorial HA Dec",bac::ha_dec_ra_dec<double>(st).get());

  g.addEdge("Equatorial RA Dec", "Ecliptic",bac::ra_dec_to_ecliptic<double>(obliquity).get());
  g.addEdge("Ecliptic","Equatorial RA Dec",bac::ecliptic_to_ra_dec<double>(obliquity).get());

  g.addEdge("Equatorial RA Dec", "Galactic",bac::ra_dec_to_galactic<double>().get());
  g.addEdge( "Galactic", "Equatorial RA Dec",bac::galactic_to_ra_dec<double>().get());
}

#endif  // BOOST_ASTRONOMY_GRAPH_HPP
