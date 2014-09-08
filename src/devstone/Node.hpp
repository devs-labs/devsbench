/**
 * @file Node.hpp
 * @author The DEVSTONE Development Team
 * See the AUTHORS or Authors.txt file
 */

/*
 * DEVSTONE - a DEVS model generator
 * This file is a part of the DEVSTONE software
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

#ifndef DEVSTONE_NODE
#define DEVSTONE_NODE 1

#include <boost/graph/adjacency_list.hpp>
#include <iostream>

namespace devstone {

    enum VertexType {
        INPUT = 0, OUTPUT, ATOMIC, COUPLED
    };

    struct VertexProperties
    {
        int        _index;
        VertexType _type;

        VertexProperties() : _index(0), _type(ATOMIC)
        { }

        VertexProperties(int index, VertexType type) :
            _index(index), _type(type)
        { }
    };

    struct EdgeProperties
    {
        EdgeProperties()
        { }
    };

    class Graph : public boost::adjacency_list < boost::vecS, boost::vecS,
                                                 boost::directedS,
                                                 VertexProperties,
                                                 EdgeProperties>
    {
    public:
        Graph()
        { }

        virtual ~Graph()
        { }

        void display() const
        {
            vertex_iterator it_g, end_g;

            tie(it_g, end_g) = vertices(*this);
            for (; it_g != end_g; ++it_g) {
                adjacency_iterator neighbour_it, neighbour_end;

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
                tie(neighbour_it, neighbour_end) = adjacent_vertices(*it_g,
                                                                     *this);
                for (; neighbour_it != neighbour_end; ++neighbour_it) {
                    std::cout << (*this)[*neighbour_it]._index << " ";
                }
                std::cout << "} ; ";
            }
        }
    };

} // namespace devstone

#endif
