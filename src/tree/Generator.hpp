/**
 * @file Generator.hpp
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

#ifndef DEVSBENCH_TREE_GENERATOR
#define DEVSBENCH_TREE_GENERATOR 1

#include <devsbench/TreeNode.hpp>

namespace devsbench { namespace tree {

    enum GeneratorType {
        LI = 0, HI, HO
    };

    class Generator
    {
    public:
        Generator()
        { }

        TreeNode* generate(int nbr_vertex, int nbr_source,
                           int nbr_v_min, int nbr_v_max,
                           const std::vector<int> &niveau) const;

    private:
        void brhtg_source(Graph *go,
                          int nbr_vertex,
                          int nbr_source,
                          int nbr_v_min,
                          int nbr_v_max,
                          const std::vector < int > &niveau,
                          std::vector < int > &Ram,
                          std::vector < int > &Exu,
                          const std::vector < vertex_to > &Vertexs,
                          int nbr_passe, int nbr_npb) const;
        void brhtg_ramification(Graph *go, int nbr_vertex, int nbr_v_min,
                                int nbr_v_max,
                                const std::vector<int> &niveau,
                                std::vector<int> &Ram,
                                std::vector<int> &Exu,
                                const std::vector<vertex_to> &Vertexs,
                                int nbr_passe, int nbr_npb) const;
        void brhtg_exutoire(Graph *go, int nbr_vertex, int nbr_v_min,
                            int nbr_v_max,
                            std::vector<int> &Ram,
                            const std::vector<vertex_to> &Vertexs,
                            int nbr_passe) const;
        void build_graph(Graph *go, int nbr_vertex,
                         int nbr_source, int nbr_v_min,
                         int nbr_v_max,
                         const std::vector<int> &niveau) const;
    };

} } // namespace devsbench tree

#endif
