#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

class Edge {
  public:
    int vertex;
    int distance;
    Edge(int v, int d) : vertex(v), distance(d) {}
};

class Graph {
  private:
  vector<vector<Edge> > _edges;
  int _vert_n;
  
  public:
  Graph(int n): _edges(n, vector<Edge>()), _vert_n(n) {
  }
  
  void add_edge(int va, int vb, int d) {
    _edges[va-1].push_back(Edge(vb-1,d));
    _edges[vb-1].push_back(Edge(va-1,d));
  }
  
  vector<int>* compute_distances(int source) {
    vector<int>* results = new vector<int>(_vert_n, INT_MAX);
    vector<int>& dist = *results;
    dist[source] = 0;
    priority_queue<pair<int,int> > vert_queue;
    vert_queue.push(make_pair(0,source));
    while(!vert_queue.empty()) {
      pair<int, int> s = vert_queue.top();
      vert_queue.pop();
      for(vector<Edge>::iterator i = _edges[s.second].begin(); i != _edges[s.second].end(); i++) {
        if(dist[i->vertex] > dist[s.second] + i->distance) {
          dist[i->vertex] = dist[s.second] + i->distance;
          vert_queue.push(make_pair(dist[i->vertex], i->vertex));
        }
      }
    }
    //print_distances(source, dist);
    return results;
  }
  
  int get_max_distance(vector<int> restaurants) {
    vector<int> min_distances(_vert_n, INT_MAX);
    for(vector<int>::iterator i = restaurants.begin(); i!=restaurants.end(); i++) {
      vector<int>& distances = *(compute_distances(*i-1));
      for(int j = 0; j<_vert_n; j++) {
        if(min_distances[j] > distances[j])
          min_distances[j] = distances[j];
      }
    }
    int result = -1;
    for(vector<int>::iterator i = min_distances.begin(); i!=min_distances.end(); i++) {
      if(*i > result)
        result = *i;
    }
    return result;
  }
};

int main() {
  int vertices, rest_no, edges;
  cin >> vertices >> rest_no >> edges;
  Graph* g = new Graph(vertices);
  vector<int> restaurants(rest_no);
  for(int i = 0; i<rest_no; i++) {
    cin >> restaurants[i];
  }
  int a,b,d;
  while(edges --) {
    cin >> a >> b >> d;
    g->add_edge(a,b,d);
  }
  cout << g->get_max_distance(restaurants) << endl;
  return 0;
}
