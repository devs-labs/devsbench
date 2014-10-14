/**
 * @file Node.hpp
 * @author The DEVSBENCH Development Team
 * See the AUTHORS or Authors.txt file
 */

/*
 * DEVSBENCH - a DEVS model generator
 * This file is a part of the DEVSBENCH software
 *
 * Copyright (C) 2014 ULCO http://www.univ-litoral.fr
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEVSBENCH_NODE
#define DEVSBENCH_NODE 1

#include <boost/graph/adjacency_list.hpp>
#include <iostream>

namespace devsbench {

    enum VertexType {
        INPUT = 0, OUTPUT, ATOMIC, COUPLED
    };

    struct VertexProperties
    {
        int        _index;
        double     _weight;
        VertexType _type;

        VertexProperties(int index = 0, double weight = 1.0,
                         VertexType type = ATOMIC) :
            _index(index), _weight(weight), _type(type)
        { }
    };

    struct EdgeProperties
    {
        uint _beginName;
        uint _endName;
        double      _weight;

        EdgeProperties(const uint &beginName = 1,
                       const uint &endName = 1,
                       double weight = 1) :
            _beginName(beginName), _endName(endName), _weight(weight)
        { }
    };

    class Graph : public boost::adjacency_list < boost::vecS, boost::vecS,
                                                 boost::bidirectionalS,//directedS,
                                                 VertexProperties,
                                                 EdgeProperties>
    {
    public:
        Graph()
        { }

        virtual ~Graph()
        { }

        void addEdge(Graph::vertex_descriptor begin,
                     const uint &begin_name,
                     Graph::vertex_descriptor end,
                     const uint &end_name)
        {
            boost::add_edge(begin, end, EdgeProperties(begin_name, end_name, 1),
                            *this);
        }

        Graph::vertex_descriptor addVertex(
            int index, double weight, VertexType type)
        {
            Graph::vertex_descriptor vertex = boost::add_vertex(*this);
            (*this)[vertex] = VertexProperties(index, weight, type);
            return vertex;
        }

        void display() const
        {
            vertex_iterator it_g, end_g;

            tie(it_g, end_g) = vertices(*this);
            for (; it_g != end_g; ++it_g) {
                // adjacency_iterator neighbour_it, neighbour_end;
                out_edge_iterator neighbour_it, neighbour_end;

                std::cout << (*this)[*it_g]._index << " [";
                if ((*this)[*it_g]._type == COUPLED) {
                    std::cout << "COUPLED";
                } else if ((*this)[*it_g]._type == ATOMIC) {
                    std::cout << "ATOMIC";
                } else if ((*this)[*it_g]._type == INPUT) {
                    std::cout << "INPUT";
                } else if ((*this)[*it_g]._type == OUTPUT) {
                    std::cout << "OUTPUT";
                }

                std::cout << "] -> { ";
                tie(neighbour_it, neighbour_end) = out_edges(*it_g, *this);
                for (; neighbour_it != neighbour_end; ++neighbour_it) {
                    vertex_descriptor vertex = target(*neighbour_it, *this);

                    std::cout << (*this)[*neighbour_it]._beginName
                              << " -> "
                              << (*this)[vertex]._index << ":"
                              << (*this)[*neighbour_it]._endName << " ";
                }
                std::cout << "} ; ";
            }
        }
    };

    typedef Graph::vertex_descriptor vertex_to;
    typedef Graph::edge_descriptor edge_to;
    Graph::vertex_iterator vertexIto, vertexEndo;
    Graph::adjacency_iterator neighbourIto, neighbourEndo;
    Graph::in_edge_iterator ei, edge_end;

} // namespace devsbench

#endif
