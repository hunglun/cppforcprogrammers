// Objective : Find the shortest distance from s to d.

// General Strategy:
// Step 0: Initialise distance of all nodes to infinity.
// Step 1: include s in the closed set
// Step 2: include all immediate successors of s with their distance in the open set
// Step 3: pick the open node of least distance cost
// Step 4: If the node that is picked is d, stop
//         Otherwise, compute all open successors k of n
// Step 5: Update distance cost of k to (the distance from s to n)+(distance from n to k)
// Step 6: If it improves on the distance value of k, then store as its new distance value
// Step 7: repeat from step 3

#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <climits>
#include "gtest/gtest.h"
using namespace std;


// compiler usage:
// clang++ -std=c++11

class Node {
public:
  int name;
  int cost;
  Node(int name, int cost):name(name),cost(cost){};
  bool operator==(int name){
    return this->name == name;
  }
  // ostream& operator<<(ostream& os, const Node& node){
  //   os << node.name << "[" << node.cost <<"]";
  //   return os;
  // }
};

ostream& operator<<(ostream& os, const Node& node)
{
  os << node.name << "[" << node.cost <<"]"<<endl;
  return os;
}
bool nodeLessThan(const struct Node &lhs, const struct Node &rhs){
    return lhs.cost < rhs.cost;
}

vector<int> successors(int node, vector<vector<int> > &graph){
  vector<int> ss;
  for(int i=0; i<graph.size(); ++i){
    if(graph[i][node]!=0){
      ss.push_back(i);
    }
  }
  return ss;
}

void printShortestPath(int src, int dst,  vector<vector<int> > &graph, vector<Node> closed) {
  if (src == dst) return; // completed.
  // Backtracking begins.
  // Closed set contains visited node with its distance value from the source.
  // The distance value from the source is computed in dijkstra algorithm beforehand.

  // now find the neighbour that is closest to the source.
  vector<Node> neighbours;
  for(auto n : successors(dst,graph)){
    auto node = find(closed.begin(),closed.end(),n);
    if (node != closed.end()) { // if the neighbour is in the closed set
      neighbours.push_back(*node);
    }
  }
  sort(neighbours.begin(),neighbours.end(),nodeLessThan);
  auto min = neighbours[0];
  cout << dst <<  "<--" << min.name << endl ;
  printShortestPath(src,min.name, graph,closed);
}
bool dijkstra(int cur, int dst, vector<vector<int> > &graph, vector<Node> &open, vector<Node> &closed, vector<int> &cost){
  if(cur == dst){
    return true; // Termination point 1: arrive at destination.
  }
  auto ss = successors(cur,graph);
  if (ss.size() == 0) return false; // Termination point 2: no more successors.
  closed.push_back(Node(cur,cost[cur])); // add this to closed set.
  for(auto s : ss){
    if (find(closed.begin(), closed.end(), s) == closed.end()){ // if this successor is not in closed set
      auto newcost = graph[cur][s] + cost[cur];
      if (cost[s]==0 || newcost < cost[s]){ // update cost, if it improves on value in open set
	cost[s] = newcost;
      }
      auto found = find(open.begin(), open.end(), s) ;
      if (found  == open.end()){ //not found
	open.push_back(Node(s,cost[s]));
      } else{
	found->cost=cost[s];
      }
    }
  }
  sort(open.begin(),open.end(),nodeLessThan);
  auto min = open[0];

  open[0].cost=INT_MAX; 

  return dijkstra(min.name, dst, graph, open, closed, cost);
}

TEST (DikjstraTest, SingleNodeGraph) { 
  //    ASSERT_EQ (0.0,  0.0);
  /* 
     graph {
       0
     }
  */
  // input data
  vector<vector<int> > graph { { 0 } } ;
  int src = 0;
  int dst = 0;
  vector<int>  cost(1,0);
  vector<Node> open,closed;

  // run the algorithm
  ASSERT_TRUE(dijkstra(src, dst, graph, open, closed, cost));

  // check output
  ASSERT_EQ(cost[dst],0);

  for(auto n : closed){
    cout << n;
  }
  printShortestPath(src, dst, graph, closed);
}

TEST (DikjstraTest, DoubleNodeGraph) { 
  /*
     graph {
       0 -- 1 [label = 3] 
     }
  */
  // input data
  vector<vector<int> > graph { { 0, 3 },
                               { 3, 0 } };
  int src = 0;
  int dst = 1;
  vector<int>   cost(2,0);
  vector<Node> open, closed;
  

  // run the algorithm
  ASSERT_TRUE(dijkstra(src, dst, graph, open, closed, cost));

  ASSERT_EQ(cost[dst],3);

  for(auto n : closed){
    cout << n;
  }
  printShortestPath(src, dst, graph, closed);
}

TEST (DikjstraTest, MultiNodeGraph1) { 
/* TEST CASE 2

     graph {
       0 -- 1 [label = 3] 
       0 -- 2 [label = 2] 
       1 -- 4 [label = 1] 
       2 -- 3 [label = 5] 
       4 -- 3 [label = 1] 

     }
  */
  // input data
  vector<vector<int> > graph {
      { 0, 3 , 2 , 0 , 0 },
      { 3, 0 , 0 , 0 , 1 },
      { 2, 0 , 0 , 5 , 0 },
      { 0, 0 , 5 , 0 , 1 },
      { 0, 1 , 0 , 1 , 0 },		
      };
  int src = 0;
  int dst = 3;
  vector<int>   cost(5,0);
  vector<Node> open, closed;
  

  // run the algorithm
  ASSERT_TRUE(dijkstra(src, dst, graph, open, closed, cost));

  ASSERT_EQ(cost[dst],5);

  for(auto n : closed){
    cout << n;
  }
  printShortestPath(src, dst, graph, closed);
}

TEST (DikjstraTest, MultiNodeGraph2) { 
/*   graph {
       0 -- 2 [label = 1] 
       0 -- 4 [label = 2] 
       2 -- 3 [label = 9] 
       4 -- 3 [label = 2] 
       3 -- 5 [label = 1]
       3 -- 6 [label = 2]
       5 -- 7 [label = 8]
       5 -- 8 [label = 9]
       7 -- 9 [label = 1]
       8 -- 9 [label = 1]
     }
  */
  // input data
  vector<vector<int> > graph {
    { 0, 0 , 1 , 0 , 2 , 0 , 0 , 0 , 0 ,0 },
    { 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,0 },
    { 1, 0 , 0 , 9 , 0 , 0 , 0 , 0 , 0 ,0 },
    { 0, 0 , 9 , 0 , 2 , 1 , 2 , 0 , 0 ,0 },
    { 2, 0 , 0 , 2 , 0 , 0 , 0 , 0 , 0 ,0 },
    { 0, 0 , 0 , 1 , 0 , 0 , 0 , 8 , 9 ,0 },
    { 0, 0 , 0 , 2 , 0 , 0 , 0 , 0 , 0 ,0 },
    { 0, 0 , 0 , 0 , 0 , 8 , 0 , 0 , 0 ,1 },
    { 0, 0 , 0 , 0 , 0 , 9 , 0 , 0 , 0 ,1 },
    { 0, 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 ,1 },      
      };
  int src = 0;
  int dst = 9;
  vector<int>   cost(10,0);
  vector<Node> open, closed;
  

  // run the algorithm
  ASSERT_TRUE(dijkstra(src, dst, graph, open, closed, cost));

  ASSERT_EQ(cost[dst],14);

  for(auto n : closed){
    cout << n;
  }
  printShortestPath(src, dst, graph, closed);
}


TEST (DikjstraTest, NodeTest) { 
  vector<Node> nodes;
  ASSERT_TRUE(find(nodes.begin(),nodes.end(),0) == nodes.end()); // not found 0
  nodes.push_back(Node(0,1));
  nodes.push_back(Node(2,1));
  ASSERT_NE(find(nodes.begin(),nodes.end(),0), nodes.end()); // found 0
  ASSERT_EQ(find(nodes.begin(),nodes.end(),1), nodes.end());    // can't find 1
  ASSERT_NE(find(nodes.begin(),nodes.end(),2), nodes.end()); // found 2
}


 
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();  
}
