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

    typedef boost::adjacency_list < boost::vecS, boost::vecS,
                                    boost::directedS,
                                    VertexProperties,
                                    EdgeProperties> Graph;

} // namespace devstone

#endif
