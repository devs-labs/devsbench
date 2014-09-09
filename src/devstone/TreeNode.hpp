/**
 * @file TreeNode.hpp
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

#ifndef DEVSTONE_TREE_NODE
#define DEVSTONE_TREE_NODE 1

#include <devstone/Node.hpp>

#include <iostream>
#include <vector>

namespace devstone {

    class TreeNode
    {
    public :
        TreeNode(int level, int index, Graph* graph = 0) :
            _graph(graph), _index(index), _level(level)
        { }

        virtual ~TreeNode()
        {
            for (std::map < int, TreeNode* >::iterator it = _children.begin();
                 it != _children.end(); ++it) {
                delete it->second;
            }
            delete _graph;
        }

        void addChild(TreeNode* child)
        {
            _children[child->index()] = child;
        }

        void addGraph(Graph* graph)
        {
            _graph = graph;
        }

        void display() const
        {
            std::cout << make_space() << "(" << _level << "/"
                      << _index << "): ";
            if (_graph) {
                _graph->display();
            }
            std::cout << std::endl;
            for (std::map < int, TreeNode* >::const_iterator
                     it = _children.begin(); it != _children.end(); ++it) {
                it->second->display();
            }
        }

        unsigned int index() const
        {
            return _index;
        }

        unsigned int level() const
        {
            return _level;
        }

        unsigned int modelNumber() const
        {
            return num_vertices(*_graph);
        }

    private :
        std::string make_space() const
        { return std::string(_level * 2, ' '); }

        std::map < int, TreeNode* > _children;
        Graph* _graph;
        int _index;
        int _level;
    };

} // namespace devstone

#endif
