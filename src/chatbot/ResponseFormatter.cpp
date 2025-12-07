#include "chatbot/ResponseFormatter.hpp"

std::string ResponseFormatter::definition(const std::string &t) const {
    if(t=="stack") return "A stack is a linear data structure that follows LIFO (Last In, First Out).";
    if(t=="queue") return "A queue is a linear data structure that follows FIFO (First In, First Out).";
    if(t=="heap") return "A heap is a tree-based structure used to implement priority queues.";
    if(t=="bst" || t=="tree") return "A Binary Search Tree (BST) is a node-based tree where left < node < right, allowing fast search, insert and delete.";
    if(t=="graph") return "A graph is a set of vertices connected by edges; used to model relationships.";
    if(t=="sorting") return "Sorting arranges elements in an order; common sorts include bubble, merge, quick.";
    if(t=="searching") return "Searching finds elements; e.g., linear and binary search.";
    if(t=="knapsack") return "Knapsack is a DP optimization problem to maximize value under weight constraint.";
    if(t=="dp") return "DP (Dynamic Programming) solves problems by reusing subproblem solutions.";
    if(t=="trie") return "A trie is a prefix-tree used for fast string retrieval.";
    return "Sorry — I don't have a concise definition for that topic yet.";
}

std::string ResponseFormatter::example(const std::string &t) const {
    if(t=="stack") return "C++ stack example (std::vector used):\nclass Stack{ std::vector<int> s; public: void push(int x){s.push_back(x);} void pop(){if(!s.empty()) s.pop_back();} int top(){return s.back();} };";
    if(t=="bst") return "Minimal BST insert example:\nstruct Node{int v;Node*l,*r;Node(int x):v(x),l(nullptr),r(nullptr){}};\nNode* insert(Node*root,int x){if(!root) return new Node(x); if(x<root->v) root->l=insert(root->l,x); else root->r=insert(root->r,x); return root;}";
    if(t=="graph") return "Graph adjacency list example:\nvector<vector<int>> g(n); g[u].push_back(v); g[v].push_back(u);";
    return "No example available for that topic yet.";
}

std::string ResponseFormatter::notUnderstood() const {
    return "I didn't understand that. Try: 'What is a stack?', 'Show example of heap', or 'Make a BST from 1,5,3'.";
}

std::string ResponseFormatter::confirmBuild(const std::string &topic, const std::string &detail) const {
    return "Built " + topic + " with: " + detail;
}
