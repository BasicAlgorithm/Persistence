// Copyright 2021 Roger Peralta Aranibar
#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>

#include "persistence/partial_directed_graph.hpp"
#include "pointer_machine/directed_graph.hpp"


//TEST DONE FOR TEACHER
void test_directed_graph() {


  std::cout << "Directed Graph EDITED"
            << "\n";
  // Create a DirectedGraph, a maximum of 5 edge for each node and the root with
  // the starting value of 1.
  ADE::PointerMachine::DirectedGraph<int, ADE::PointerMachine::Node<int>>
      my_graph(1, 5);

  // We can obtain the root and print their value.
  ADE::PointerMachine::Node<int>* root_ptr = my_graph.get_root_ptr();
  std::cout << "Root Value: " << root_ptr->get_data() << "\n";  // 1[0-5]

  // Also, we can insert a new vertex passing the new Node value, and the index
  // of the pointer that will be used to point the inserted node.
  my_graph.get_root().insert_vertex(0, 2);  // 1[0] -> 2[0-5]

  std::cout << "Inserted Value: " << my_graph.get_root()[0].get_data()
            << "\n";  // 2

  // Likewise, the method to insert a new vertex, returns a reference of the
  // new vertex inserted.
  ADE::PointerMachine::Node<int>* other_inserted_node_ptr =
      my_graph.get_root()[0].insert_vertex(1, 3);  // 1[0] -> 2[1] -> 3[0-5]

  std::cout << "Inserted Value: " << my_graph.get_root()[0][1].get_data()
            << "\n";  // 3

  // To add an edge between two vertex, we call the function update edge from
  // the startin Node with the index id that will link both nodes.
  my_graph.get_root().update_edge(1,
                                  other_inserted_node_ptr);  // 1[0] -> 2[1] -> 3[0-5]
                                                             // 1[1] -> 3[0-5]

  std::cout << "Following other Edge: " << my_graph.get_root()[1].get_data() // 3
            << "\n";

  std::cout << "Imprimiendo las versiones del grafo" << std::endl;
  std::cout << "VERSION 01" << std::endl;
}

int main() {
  test_directed_graph();

  return 0;
}

/*
void test_partial_graph(){
    int p = 2;
    ADE::Persistence::PartialDirectedGraph<int, ADE::Persistence::PartialNode<int>> my_partial_graph(1, 99, 99); // 1 [V1]
    my_partial_graph.add(2); // 1-> 2 [V2]
    my_partial_graph.add(3); // 1-> 2 -> 3 [V3]
    my_partial_graph.modify(2, 20); // 1-> 20 -> 3 [V4]
    my_partial_graph.modify(2, 200); // 1-> 200 -> 3 [V5]
    my_partial_graph.modify(2, 400); // 1-> 400 -> 3 [V6]

    my_partial_graph.print_version(1);
    my_partial_graph.print_version(2);
    my_partial_graph.print_version(3);
    my_partial_graph.print_version(4);
    my_partial_graph.print_version(5);
    my_partial_graph.print_version(6);

    std::cout << "PROGRAM WORK OK" << std::endl;
}

int main() {
    test_partial_graph();
    return 0;
}*/