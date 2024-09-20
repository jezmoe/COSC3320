#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, int> pii;

vector<int> dijkstra(int start, const vector<vector<pii> >& graph) {
    int n = graph.size();
    vector<int> dist(n, numeric_limits<int>::max());
    priority_queue<pii, vector<pii>, greater<pii> > pq;

    dist[start] = 0;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        int current_dist = pq.top().first;
        int current_node = pq.top().second;
        pq.pop();

        if (current_dist > dist[current_node]) continue;

        for (size_t i = 0; i < graph[current_node].size(); ++i) {
            int neighbor = graph[current_node][i].first;
            int weight = graph[current_node][i].second;
            int distance_through_current = current_dist + weight;

            if (distance_through_current < dist[neighbor]) {
                dist[neighbor] = distance_through_current;
                pq.push(make_pair(distance_through_current, neighbor));
            }
        }
    }

    return dist;
}

int main() {
    vector<vector<pii> > graph(4);
    graph[0].push_back(make_pair(1, 1));
    graph[0].push_back(make_pair(2, 4));
    graph[1].push_back(make_pair(0, 1));
    graph[1].push_back(make_pair(2, 2));
    graph[1].push_back(make_pair(3, 5));
    graph[2].push_back(make_pair(0, 4));
    graph[2].push_back(make_pair(1, 2));
    graph[2].push_back(make_pair(3, 1));
    graph[3].push_back(make_pair(1, 5));
    graph[3].push_back(make_pair(2, 1));

    int start_node = 0;
    vector<int> shortest_distances = dijkstra(start_node, graph);

    for (int i = 0; i < static_cast<int>(shortest_distances.size()); ++i) {
        cout << "Shortest distance from node " << start_node << " to node " << i << " is " << shortest_distances[i] << endl;
    }

    return 0;
}
