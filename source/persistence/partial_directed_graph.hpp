// Copyright 2021 Roger Peralta Aranibar
#ifndef SOURCE_PERSISTENCE_PARTIAL_DIRECTED_GRAPH_HPP_
#define SOURCE_PERSISTENCE_PARTIAL_DIRECTED_GRAPH_HPP_

#include <utility>

//#include "pointer_machine/directed_graph.hpp"


namespace ADE {
    namespace Persistence {

        template <typename Type>
        class PartialNode {
        public:
            typedef Type data_type;

            PartialNode() {}

            PartialNode(data_type const& data,
                std::size_t const& out_ptrs_size,
                std::size_t const& in_ptrs_size,
                unsigned int* version //mine
            ) {
                backward_ = new PartialNode<Type>*[in_ptrs_size]();
                forward_ = new PartialNode<Type>*[out_ptrs_size]();
                main_value = data;
            }

            data_type get_data(unsigned int version) { return data_; }

            bool set_data(data_type const& data) { return true; }

            PartialNode* insert_vertex(std::size_t const& position,    // out_ptrs_size
                data_type const& data           // en nuevo nodo con cual valor
            ) {
                return nullptr;
            }

            bool update_edge(std::size_t const& position, PartialNode* v) { return true; }

            PartialNode& operator[](std::pair<std::size_t, unsigned int> const& position_version)
                const {
                return;
            }



            data_type* data_ = &main_value;
            std::size_t out_ptrs_size_;
            PartialNode** forward_;
            PartialNode* main_forward_ = NULL;

            std::size_t in_ptrs_size_;
            std::size_t current_modifications_size_;
            std::size_t current_back_pointer_size_;

            PartialNode** backward_;
            // TODO: Table mods, 2 * in_ptrs_size_
            data_type main_value = 0;

            data_type which_version[2] = { 0,0 };
            bool is_ptr_int[2] = { 0,0 };
            data_type version_value[2] = { 0,0 };
            PartialNode* version_ptr[2] = { 0,0 };

        };

        template <typename Type, typename Node>
        class PartialDirectedGraph {
        public:
            typedef Type data_type;

            PartialDirectedGraph(data_type const data,
                std::size_t const& out_ptrs_size,
                std::size_t const& in_ptrs_size
            ) {
                Node* tmp = new Node(data, out_ptrs_size, in_ptrs_size, current_version_);
                ++(*current_version_);
                out_ptrs_size_ = out_ptrs_size; in_ptrs_size_ = in_ptrs_size;
                root_ptr_ = tmp;
            }

            Node* get_root_ptr(unsigned int const& version) { return root_ptr_; }

            Node get_root(unsigned int const& version) { return *root_ptr_; }

            bool find(int data, Node*& tmp, int version) { // implementar uso de int version - previous Node * find()

                for (tmp = root_ptr_; tmp && tmp->main_value != data; tmp = tmp->main_forward_) {
                    if (!tmp->main_forward_)break;
                }
                return tmp != 0;
            }

            Node* insert_vertex(data_type const data,   // data_old_vertice
                int u,                // nuevo nodo
                std::size_t position    // punteroNro_old_vertice
            ) {
                Node* tmp;
                if (find(data, tmp, *current_version_)) {
                    //std::cout << "find success" << std::endl;
                }
                else
                {
                    //std::cout << "no finded" << std::endl;
                }
                ++(*current_version_);
                add_edge(tmp, u, position);
                return nullptr;
            }

            bool add_edge(Node* u, int v, std::size_t position) {
                //u->*forward[(position,*current_version_)]
                if (!u->which_version[0]) {
                    u->which_version[0] = *current_version_;
                    u->version_ptr[0] = new Node(v, out_ptrs_size_, in_ptrs_size_, current_version_);
                }
                else if (!u->which_version[1])
                {
                    u->which_version[1] = *current_version_;
                    u->version_ptr[1] = new Node(v, out_ptrs_size_, in_ptrs_size_, current_version_);
                }
                else
                {
                    std::cout << "else case on edd_edge" << std::endl;//here code to expand PartialDirectGraph
                }
                //++(*current_version_);
                return true;
            }

            void print_version(int version = 0) {
                if (!version)version = *current_version_;
                //root_ptr_->print(version);//previous
                Node* tmp = root_ptr_;
                do
                {
                    std::cout << "node value = " << tmp->main_value << std::endl; //this only one - previous

                    //std::cout << "a = " << tmp->which_version[0] << std::endl; //test
                    //std::cout << "b = " << tmp->which_version[1] << std::endl; //test
                    //std::cout << "c = " << tmp->main_value << std::endl; //test
                    //std::cout << "d = " << tmp->main_value << std::endl; //test

                    if (tmp->which_version[0] == version && tmp->is_ptr_int[0] == 0)
                    {
                        tmp = tmp->version_ptr[0];
                    }
                    else if (tmp->which_version[1] == version && tmp->is_ptr_int[1] == 0)
                    {
                        tmp = tmp->version_ptr[1];
                    }
                    else
                    {
                        tmp = NULL;
                    }

                } while (tmp);
            }

        protected:
            unsigned int* current_version_ = &current_version;
            unsigned int current_version = 1;
            std::size_t in_ptrs_size_;

            Node* root_ptr_ = NULL;
            std::size_t out_ptrs_size_;
        };

    }  // namespace Persistence
}  // namespace ADE

#endif  // SOURCE_PERSISTENCE_PARTIAL_DIRECTED_GRAPH_HPP_
