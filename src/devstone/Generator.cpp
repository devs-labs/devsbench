/**
 * @file Generator.cpp
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

#include <devstone/Generator.hpp>

namespace devstone {

    Graph* Generator::build_low_level_graph() const
    {
        Graph* g = new Graph();
        Graph::vertex_descriptor inner_vertex = g->addVertex(0, 0, ATOMIC);
        Graph::vertex_descriptor input_vertex = g->addVertex(1, 0, INPUT);
        Graph::vertex_descriptor output_vertex = g->addVertex(2, 0, OUTPUT);

        g->addEdge(input_vertex, inner_vertex);
        g->addEdge(inner_vertex, output_vertex);
        return g;
    }

    Graph* Generator::build_graph() const
    {
        Graph* g = new Graph();
        std::vector < Graph::vertex_descriptor > vertexList;

        for (int i = 0; i < _width; ++i) {
            if (i == 0) {
                vertexList.push_back(g->addVertex(i, 0, COUPLED));
            } else {
                vertexList.push_back(g->addVertex(i, 0, ATOMIC));
            }
        }

        Graph::vertex_descriptor input_vertex =
            g->addVertex(_width, 0, INPUT);
        Graph::vertex_descriptor output_vertex =
            g->addVertex(_width + 1, 0, OUTPUT);

        // edges
        for (int i = 0; i < _width; ++i) {
            g->addEdge(input_vertex, vertexList[i]);
        }
        g->addEdge(vertexList[0], output_vertex);
        if (_type == HI) {
            for (int i = 1; i < _width - 1; ++i) {
                g->addEdge(vertexList[i], vertexList[i + 1]);
            }
            g->addEdge(vertexList[0], output_vertex);
        }
        return g;
    }

    TreeNode* Generator::generate() const
    {
        TreeNode* root = new TreeNode(0, 0);
        root->addGraph(build_graph());

        int l = 1;
        TreeNode* father = root;

        while (l < _depth - 1) {
            TreeNode* n = new TreeNode(l, 0);
            n->addGraph(build_graph());
            father->addChild(n);
            father = n;
            ++l;
        }

        {
            TreeNode* n = new TreeNode(l, 0);
            n->addGraph(build_low_level_graph());
            father->addChild(n);
        }

        return root;
    }

} // namespace devstone
