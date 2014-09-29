/**
 * @file Merge.hpp
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

#ifndef DEVSBENCH_MERGE
#define DEVSBENCH_MERGE 1

#include <devsbench/Node.hpp>

#include <iostream>
#include <fstream>
#include <vector>

namespace devsbench {
         
void Merge_Devs_Level_Coupled(Graph *go1, const Graph *go2, 
			const std::vector<std::pair<int,int>> &in_edge_connection,
			const std::vector<std::pair<int,int>> &out_edge_connection,
			std::vector<std::pair<int,int>> &liste_father, uint cpt_vertex);
			
void Merge_Devs_Graph(TreeNode* root, bool rec);

void Plot_Graph(Graph *go1,const char* text);

void Affichage_OrientedGraph(Graph *go);

} // namespace devsbench

#endif
