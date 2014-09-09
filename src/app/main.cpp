/**
 * @file app/main.cpp
 * @author The VLE Development Team
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
#include <devstone/Node.hpp>
#include <devstone/TreeNode.hpp>

void example1()
{
// root
    devstone::TreeNode* root = new devstone::TreeNode(0, 0);
    {
        devstone::Graph* groot = new devstone::Graph();
        devstone::Graph::vertex_descriptor v0_0 = boost::add_vertex(*groot);
        devstone::Graph::vertex_descriptor v0_1 = boost::add_vertex(*groot);
        devstone::Graph::vertex_descriptor v0_2 = boost::add_vertex(*groot);

        (*groot)[v0_0] = devstone::VertexProperties(0, 0, devstone::COUPLED);
        (*groot)[v0_1] = devstone::VertexProperties(1, 0, devstone::COUPLED);
        (*groot)[v0_2] = devstone::VertexProperties(2, 0, devstone::ATOMIC);
        boost::add_edge(v0_0, v0_1, *groot);
        boost::add_edge(v0_1, v0_2, *groot);

        root->addGraph(groot);
    }

// level 1 - node 0
    devstone::TreeNode* n10 = new devstone::TreeNode(1, 0);
    {
        devstone::Graph* g10 = new devstone::Graph();
        devstone::Graph::vertex_descriptor v10_0 = boost::add_vertex(*g10);
        devstone::Graph::vertex_descriptor v10_1 = boost::add_vertex(*g10);
        devstone::Graph::vertex_descriptor v10_2 = boost::add_vertex(*g10);

        (*g10)[v10_0] = devstone::VertexProperties(0, 0, devstone::ATOMIC);
        (*g10)[v10_1] = devstone::VertexProperties(1, 0, devstone::ATOMIC);
        (*g10)[v10_2] = devstone::VertexProperties(2, 0, devstone::OUTPUT);
        boost::add_edge(v10_0, v10_1, *g10);
        boost::add_edge(v10_0, v10_1, *g10);
        boost::add_edge(v10_1, v10_2, *g10);

        n10->addGraph(g10);
    }
    root->addChild(n10);

// level 1 - node 1
    devstone::TreeNode* n11 = new devstone::TreeNode(1, 1);
    {
        devstone::Graph* g11 = new devstone::Graph();
        devstone::Graph::vertex_descriptor v11_0 = boost::add_vertex(*g11);
        devstone::Graph::vertex_descriptor v11_1 = boost::add_vertex(*g11);
        devstone::Graph::vertex_descriptor v11_2 = boost::add_vertex(*g11);
        devstone::Graph::vertex_descriptor v11_3 = boost::add_vertex(*g11);

        (*g11)[v11_0] = devstone::VertexProperties(0, 0, devstone::INPUT);
        (*g11)[v11_1] = devstone::VertexProperties(1, 0, devstone::ATOMIC);
        (*g11)[v11_2] = devstone::VertexProperties(2, 0, devstone::ATOMIC);
        (*g11)[v11_3] = devstone::VertexProperties(3, 0, devstone::OUTPUT);
        boost::add_edge(v11_0, v11_1, *g11);
        boost::add_edge(v11_1, v11_2, *g11);
        boost::add_edge(v11_2, v11_3, *g11);

        n11->addGraph(g11);
    }
    root->addChild(n11);

    std::cout << "Example 1:" << std::endl;
    root->display();

    delete root;
}

void example2()
{
    devstone::Generator generator(devstone::LI, 3, 4, 1, 1);
    devstone::TreeNode* root = generator.generate();

    std::cout << "Example 2:" << std::endl;
    root->display();

    delete root;
}

int main()
{
    example1();
    example2();
    return 0;
}
