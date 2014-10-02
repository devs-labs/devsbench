/**
 * @file app/main.cpp
 * @author The VLE Development Team
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

#include <devstone/Generator.hpp>
#include <devsbench/Node.hpp>
#include <devsbench/TreeNode.hpp>
#include <devsbench/Merge.cpp>
#include <tree/Generator.hpp>

using namespace devsbench;

/*Modidif !!!*/
/*Graph::vertex_iterator vertexIto, vertexEndo;
Graph::adjacency_iterator neighbourIto, neighbourEndo;*/

void example1()
{
// root
    devsbench::TreeNode* root = new devsbench::TreeNode(0, 0);
    {
        devsbench::Graph* groot = new devsbench::Graph();
        devsbench::Graph::vertex_descriptor v0_0 = boost::add_vertex(*groot);
        devsbench::Graph::vertex_descriptor v0_1 = boost::add_vertex(*groot);
        devsbench::Graph::vertex_descriptor v0_2 = boost::add_vertex(*groot);

        (*groot)[v0_0] = devsbench::VertexProperties(0, 1., devsbench::COUPLED);
        (*groot)[v0_1] = devsbench::VertexProperties(1, 1., devsbench::COUPLED);
        (*groot)[v0_2] = devsbench::VertexProperties(2, 1., devsbench::ATOMIC);
        boost::add_edge(v0_0, v0_1, *groot);
        boost::add_edge(v0_1, v0_2, *groot);

        root->addGraph(groot);
    }

// level 1 - node 0
    devsbench::TreeNode* n10 = new devsbench::TreeNode(1, 0);
    {
        devsbench::Graph* g10 = new devsbench::Graph();
        devsbench::Graph::vertex_descriptor v10_0 = boost::add_vertex(*g10);
        devsbench::Graph::vertex_descriptor v10_1 = boost::add_vertex(*g10);
        devsbench::Graph::vertex_descriptor v10_2 = boost::add_vertex(*g10);

        (*g10)[v10_0] = devsbench::VertexProperties(3, 1., devsbench::ATOMIC);
        (*g10)[v10_1] = devsbench::VertexProperties(4, 1., devsbench::ATOMIC);
        (*g10)[v10_2] = devsbench::VertexProperties(5, 1., devsbench::OUTPUT);
        boost::add_edge(v10_0, v10_1, *g10);
        boost::add_edge(v10_0, v10_1, *g10);
        boost::add_edge(v10_1, v10_2, *g10);

        n10->addGraph(g10);
    }
    root->addChild(n10);
    
// level 1 - node 1
    devsbench::TreeNode* n11 = new devsbench::TreeNode(1, 1);
    {
        devsbench::Graph* g11 = new devsbench::Graph();
        devsbench::Graph::vertex_descriptor v11_0 = boost::add_vertex(*g11);
        devsbench::Graph::vertex_descriptor v11_1 = boost::add_vertex(*g11);
        devsbench::Graph::vertex_descriptor v11_2 = boost::add_vertex(*g11);
        devsbench::Graph::vertex_descriptor v11_3 = boost::add_vertex(*g11);
        devsbench::Graph::vertex_descriptor v11_4 = boost::add_vertex(*g11);

        (*g11)[v11_0] = devsbench::VertexProperties(6, 1., devsbench::INPUT);
        (*g11)[v11_1] = devsbench::VertexProperties(7, 1., devsbench::COUPLED);
        (*g11)[v11_2] = devsbench::VertexProperties(8, 1., devsbench::ATOMIC);
        (*g11)[v11_3] = devsbench::VertexProperties(9, 1., devsbench::ATOMIC);
        (*g11)[v11_4] = devsbench::VertexProperties(14, 1., devsbench::OUTPUT);
        boost::add_edge(v11_0, v11_1, *g11);
        boost::add_edge(v11_1, v11_2, *g11);
        boost::add_edge(v11_1, v11_3, *g11);
        boost::add_edge(v11_2, v11_3, *g11);
        boost::add_edge(v11_3, v11_4, *g11);

        n11->addGraph(g11);
    }
    root->addChild(n11);
    
    devsbench::TreeNode* n20 = new devsbench::TreeNode(2,7);
    {
        devsbench::Graph* g20 = new devsbench::Graph();
        devsbench::Graph::vertex_descriptor v20_0 = boost::add_vertex(*g20);
        devsbench::Graph::vertex_descriptor v20_1 = boost::add_vertex(*g20);
        devsbench::Graph::vertex_descriptor v20_3 = boost::add_vertex(*g20);
        devsbench::Graph::vertex_descriptor v20_4 = boost::add_vertex(*g20);
		
		(*g20)[v20_0] = devsbench::VertexProperties(10, 1., devsbench::INPUT);
        (*g20)[v20_1] = devsbench::VertexProperties(11, 1., devsbench::ATOMIC);
        (*g20)[v20_3] = devsbench::VertexProperties(12, 1., devsbench::OUTPUT);
        (*g20)[v20_4] = devsbench::VertexProperties(13, 1., devsbench::OUTPUT);
        boost::add_edge(v20_0, v20_1, *g20);
        boost::add_edge(v20_1, v20_3, *g20);
        boost::add_edge(v20_1, v20_4, *g20);

        n20->addGraph(g20);
    }
    
    TreeNode * father = root->children_treenode(1);
    father->addChild(n20);
    
    std::cout << "Example 1 : " << std::endl;
    root->display();
    std::cout<<std::endl;
    
    Merge_Devs_Graph(root, false);
    	
    delete root;
}

void example_n_level()
{
// root
    devsbench::TreeNode* root = new devsbench::TreeNode(0,0);
    {
        devsbench::Graph* groot = new devsbench::Graph();
        devsbench::Graph::vertex_descriptor v0_0 = boost::add_vertex(*groot);
        devsbench::Graph::vertex_descriptor v0_1 = boost::add_vertex(*groot);
        devsbench::Graph::vertex_descriptor v0_2 = boost::add_vertex(*groot);
        devsbench::Graph::vertex_descriptor v0_3 = boost::add_vertex(*groot);
        devsbench::Graph::vertex_descriptor v0_4 = boost::add_vertex(*groot);
        devsbench::Graph::vertex_descriptor v0_5 = boost::add_vertex(*groot);
        devsbench::Graph::vertex_descriptor v0_6 = boost::add_vertex(*groot);

        (*groot)[v0_0] = devsbench::VertexProperties(0, 1., devsbench::ATOMIC);
        (*groot)[v0_1] = devsbench::VertexProperties(1, 1., devsbench::COUPLED);
        (*groot)[v0_2] = devsbench::VertexProperties(2, 1., devsbench::COUPLED);
        (*groot)[v0_3] = devsbench::VertexProperties(3, 1., devsbench::ATOMIC);
        (*groot)[v0_4] = devsbench::VertexProperties(4, 1., devsbench::ATOMIC);
        (*groot)[v0_5] = devsbench::VertexProperties(5, 1., devsbench::COUPLED);
        (*groot)[v0_6] = devsbench::VertexProperties(6, 1., devsbench::ATOMIC);
        
        boost::add_edge(v0_0, v0_1, EdgeProperties("out1", "in1", 1), *groot);
        boost::add_edge(v0_1, v0_2, EdgeProperties("out1", "in1", 1), *groot);
        boost::add_edge(v0_1, v0_5, EdgeProperties("out2", "in2", 1), *groot);
        boost::add_edge(v0_2, v0_3, EdgeProperties("out1", "in1", 1), *groot);
        boost::add_edge(v0_2, v0_4, EdgeProperties("out2", "in1", 1), *groot);
        boost::add_edge(v0_2, v0_5, EdgeProperties("out3", "in1", 1), *groot);
        boost::add_edge(v0_3, v0_6, EdgeProperties("out1", "in1", 1), *groot);
        boost::add_edge(v0_4, v0_6, EdgeProperties("out1", "in2", 1), *groot);        
        boost::add_edge(v0_5, v0_6, EdgeProperties("out1", "in3", 1), *groot);
      
        root->addGraph(groot);
    }

// level 1 - node 1
    devsbench::TreeNode* n11 = new devsbench::TreeNode(1, 1);
    {
        devsbench::Graph* g11 = new devsbench::Graph();
        devsbench::Graph::vertex_descriptor v11_0 = boost::add_vertex(*g11);
        devsbench::Graph::vertex_descriptor v11_1 = boost::add_vertex(*g11);
        devsbench::Graph::vertex_descriptor v11_2 = boost::add_vertex(*g11);
        devsbench::Graph::vertex_descriptor v11_3 = boost::add_vertex(*g11);
        devsbench::Graph::vertex_descriptor v11_4 = boost::add_vertex(*g11);
        devsbench::Graph::vertex_descriptor v11_5 = boost::add_vertex(*g11);
        devsbench::Graph::vertex_descriptor v11_6 = boost::add_vertex(*g11);

        (*g11)[v11_0] = devsbench::VertexProperties(7, 1., devsbench::INPUT);
        (*g11)[v11_1] = devsbench::VertexProperties(8, 1., devsbench::COUPLED);
        (*g11)[v11_2] = devsbench::VertexProperties(9, 1., devsbench::ATOMIC);
        (*g11)[v11_3] = devsbench::VertexProperties(10, 1., devsbench::ATOMIC);
        (*g11)[v11_4] = devsbench::VertexProperties(11, 1., devsbench::COUPLED);
        (*g11)[v11_5] = devsbench::VertexProperties(12, 1., devsbench::OUTPUT);
        (*g11)[v11_6] = devsbench::VertexProperties(13, 1., devsbench::OUTPUT);
        
        boost::add_edge(v11_0, v11_1, EdgeProperties("out1", "in1", 1), *g11);
        boost::add_edge(v11_1, v11_2, EdgeProperties("out1", "in1", 1), *g11);
        boost::add_edge(v11_1, v11_3, EdgeProperties("out2", "in1", 1), *g11);
        boost::add_edge(v11_2, v11_5, EdgeProperties("out1", "in1", 1), *g11);
        boost::add_edge(v11_3, v11_4, EdgeProperties("out1", "in1", 1), *g11);
        boost::add_edge(v11_4, v11_6, EdgeProperties("out1", "in1", 1), *g11);

        n11->addGraph(g11);
    }
    root->addChild(n11);
    
// level 1 - node 2  
    devsbench::TreeNode* n10 = new devsbench::TreeNode(1, 2);
    {
        devsbench::Graph* g10 = new devsbench::Graph();
        devsbench::Graph::vertex_descriptor v10_0 = boost::add_vertex(*g10);
        devsbench::Graph::vertex_descriptor v10_1 = boost::add_vertex(*g10);
        devsbench::Graph::vertex_descriptor v10_2 = boost::add_vertex(*g10);
        devsbench::Graph::vertex_descriptor v10_3 = boost::add_vertex(*g10);
        devsbench::Graph::vertex_descriptor v10_4 = boost::add_vertex(*g10);
        devsbench::Graph::vertex_descriptor v10_5 = boost::add_vertex(*g10);
        devsbench::Graph::vertex_descriptor v10_6 = boost::add_vertex(*g10);
        devsbench::Graph::vertex_descriptor v10_7 = boost::add_vertex(*g10);

        (*g10)[v10_0] = devsbench::VertexProperties(14, 1., devsbench::INPUT);
        (*g10)[v10_1] = devsbench::VertexProperties(15, 1., devsbench::ATOMIC);
        (*g10)[v10_2] = devsbench::VertexProperties(16, 1., devsbench::ATOMIC);
        (*g10)[v10_3] = devsbench::VertexProperties(17, 1., devsbench::ATOMIC);
        (*g10)[v10_4] = devsbench::VertexProperties(18, 1., devsbench::ATOMIC);
        (*g10)[v10_5] = devsbench::VertexProperties(19, 1., devsbench::OUTPUT);
        (*g10)[v10_6] = devsbench::VertexProperties(20, 1., devsbench::OUTPUT);
        (*g10)[v10_7] = devsbench::VertexProperties(21, 1., devsbench::OUTPUT);
        
        boost::add_edge(v10_0, v10_1, EdgeProperties("out1", "in1", 1), *g10);
        boost::add_edge(v10_1, v10_3, EdgeProperties("out1", "in1", 1), *g10);
        boost::add_edge(v10_1, v10_3, EdgeProperties("out2", "in2", 1), *g10);
        boost::add_edge(v10_3, v10_2, EdgeProperties("out2", "in1", 1), *g10);
        boost::add_edge(v10_3, v10_4, EdgeProperties("out1", "in1", 1), *g10);
        boost::add_edge(v10_2, v10_1, EdgeProperties("out1", "in2", 1), *g10);
        boost::add_edge(v10_2, v10_5, EdgeProperties("out2", "in1", 1), *g10);
        boost::add_edge(v10_4, v10_6, EdgeProperties("out1", "in1", 1), *g10);
        boost::add_edge(v10_4, v10_7, EdgeProperties("out2", "in1", 1), *g10);

        n10->addGraph(g10);
    }
    root->addChild(n10);
    
// level 1 - node 5    
    devsbench::TreeNode* n12 = new devsbench::TreeNode(1, 5);
    {
        devsbench::Graph* g12 = new devsbench::Graph();
        devsbench::Graph::vertex_descriptor v12_0 = boost::add_vertex(*g12);
        devsbench::Graph::vertex_descriptor v12_1 = boost::add_vertex(*g12);
        devsbench::Graph::vertex_descriptor v12_2 = boost::add_vertex(*g12);
        devsbench::Graph::vertex_descriptor v12_3 = boost::add_vertex(*g12);
        devsbench::Graph::vertex_descriptor v12_4 = boost::add_vertex(*g12);
        devsbench::Graph::vertex_descriptor v12_5 = boost::add_vertex(*g12);
        devsbench::Graph::vertex_descriptor v12_6 = boost::add_vertex(*g12);
        devsbench::Graph::vertex_descriptor v12_7 = boost::add_vertex(*g12);
        devsbench::Graph::vertex_descriptor v12_8 = boost::add_vertex(*g12);

        (*g12)[v12_0] = devsbench::VertexProperties(22, 1., devsbench::INPUT);
        (*g12)[v12_1] = devsbench::VertexProperties(23, 1., devsbench::INPUT);
        (*g12)[v12_2] = devsbench::VertexProperties(24, 1., devsbench::COUPLED);
        (*g12)[v12_3] = devsbench::VertexProperties(25, 1., devsbench::ATOMIC);
        (*g12)[v12_4] = devsbench::VertexProperties(26, 1., devsbench::ATOMIC);
        (*g12)[v12_5] = devsbench::VertexProperties(27, 1., devsbench::COUPLED);
        (*g12)[v12_6] = devsbench::VertexProperties(28, 1., devsbench::ATOMIC);
        (*g12)[v12_7] = devsbench::VertexProperties(29, 1., devsbench::ATOMIC);
        (*g12)[v12_8] = devsbench::VertexProperties(30, 1., devsbench::OUTPUT);
        
        boost::add_edge(v12_0, v12_2, EdgeProperties("out1", "in1", 1), *g12);
        boost::add_edge(v12_1, v12_3, EdgeProperties("out1", "in1", 1), *g12);
        boost::add_edge(v12_2, v12_4, EdgeProperties("out1", "in1", 1), *g12);
        boost::add_edge(v12_3, v12_2, EdgeProperties("out1", "in2", 1), *g12);
        boost::add_edge(v12_3, v12_4, EdgeProperties("out2", "in2", 1), *g12);
        boost::add_edge(v12_4, v12_5, EdgeProperties("out1", "in1", 1), *g12);
        boost::add_edge(v12_7, v12_8, EdgeProperties("out1", "in1", 1), *g12);
        boost::add_edge(v12_5, v12_6, EdgeProperties("out1", "in1", 1), *g12);
        boost::add_edge(v12_5, v12_7, EdgeProperties("out2", "in1", 1), *g12);

        n12->addGraph(g12);
    }
    root->addChild(n12);

// level 2 - node 8    
    devsbench::TreeNode* n20 = new devsbench::TreeNode(2,8);
    {
        devsbench::Graph* g20 = new devsbench::Graph();
        devsbench::Graph::vertex_descriptor v20_0 = boost::add_vertex(*g20);
        devsbench::Graph::vertex_descriptor v20_1 = boost::add_vertex(*g20);
        devsbench::Graph::vertex_descriptor v20_2 = boost::add_vertex(*g20);
        devsbench::Graph::vertex_descriptor v20_3 = boost::add_vertex(*g20);
        devsbench::Graph::vertex_descriptor v20_4 = boost::add_vertex(*g20);
        devsbench::Graph::vertex_descriptor v20_5 = boost::add_vertex(*g20);

		
		(*g20)[v20_0] = devsbench::VertexProperties(31, 1., devsbench::INPUT);
        (*g20)[v20_1] = devsbench::VertexProperties(32, 1., devsbench::ATOMIC);
        (*g20)[v20_2] = devsbench::VertexProperties(33, 1., devsbench::ATOMIC);
        (*g20)[v20_3] = devsbench::VertexProperties(34, 1., devsbench::ATOMIC);
        (*g20)[v20_4] = devsbench::VertexProperties(35, 1., devsbench::OUTPUT);
        (*g20)[v20_5] = devsbench::VertexProperties(36, 1., devsbench::OUTPUT);
        
        boost::add_edge(v20_0, v20_1, EdgeProperties("out1", "in1", 1), *g20);
        boost::add_edge(v20_1, v20_2, EdgeProperties("out1", "in1", 1), *g20);
        boost::add_edge(v20_1, v20_3, EdgeProperties("out2", "in1", 1), *g20);
        boost::add_edge(v20_2, v20_5, EdgeProperties("out1", "in1", 1), *g20);
        boost::add_edge(v20_3, v20_4, EdgeProperties("out1", "in1", 1), *g20);

        n20->addGraph(g20);
    }
    
    TreeNode * father1 = root->children_treenode(1);
    father1->addChild(n20);
    
// level 2 - node 11    
    devsbench::TreeNode* n21 = new devsbench::TreeNode(2,11);
    {
        devsbench::Graph* g21 = new devsbench::Graph();
        devsbench::Graph::vertex_descriptor v21_0 = boost::add_vertex(*g21);
        devsbench::Graph::vertex_descriptor v21_1 = boost::add_vertex(*g21);
        devsbench::Graph::vertex_descriptor v21_2 = boost::add_vertex(*g21);
        devsbench::Graph::vertex_descriptor v21_3 = boost::add_vertex(*g21);
        devsbench::Graph::vertex_descriptor v21_4 = boost::add_vertex(*g21);

		
		(*g21)[v21_0] = devsbench::VertexProperties(37, 1., devsbench::INPUT);
        (*g21)[v21_1] = devsbench::VertexProperties(38, 1., devsbench::ATOMIC);
        (*g21)[v21_2] = devsbench::VertexProperties(39, 1., devsbench::ATOMIC);
        (*g21)[v21_3] = devsbench::VertexProperties(40, 1., devsbench::ATOMIC);
        (*g21)[v21_4] = devsbench::VertexProperties(41, 1., devsbench::OUTPUT);
        
        boost::add_edge(v21_0, v21_2, EdgeProperties("out1", "in4", 1), *g21);
        boost::add_edge(v21_1, v21_2, EdgeProperties("out1", "in1", 1), *g21);
        boost::add_edge(v21_1, v21_2, EdgeProperties("out2", "in2", 1), *g21);
        boost::add_edge(v21_1, v21_2, EdgeProperties("out3", "in3", 1), *g21);
        boost::add_edge(v21_1, v21_3, EdgeProperties("out4", "in1", 1), *g21);
        boost::add_edge(v21_2, v21_3, EdgeProperties("out1", "in2", 1), *g21);
        boost::add_edge(v21_3, v21_4, EdgeProperties("out1", "in1", 1), *g21);

        n21->addGraph(g21);
    }

    father1->addChild(n21);
    
// level 2 - node 24     
    devsbench::TreeNode* n22 = new devsbench::TreeNode(2,24);
    {
        devsbench::Graph* g22 = new devsbench::Graph();
        devsbench::Graph::vertex_descriptor v22_0 = boost::add_vertex(*g22);
        devsbench::Graph::vertex_descriptor v22_1 = boost::add_vertex(*g22);
        devsbench::Graph::vertex_descriptor v22_2 = boost::add_vertex(*g22);
        devsbench::Graph::vertex_descriptor v22_3 = boost::add_vertex(*g22);
        devsbench::Graph::vertex_descriptor v22_4 = boost::add_vertex(*g22);
        devsbench::Graph::vertex_descriptor v22_5 = boost::add_vertex(*g22);
		
		(*g22)[v22_0] = devsbench::VertexProperties(42, 1., devsbench::INPUT);
        (*g22)[v22_1] = devsbench::VertexProperties(43, 1., devsbench::INPUT);
        (*g22)[v22_2] = devsbench::VertexProperties(44, 1., devsbench::ATOMIC);
        (*g22)[v22_3] = devsbench::VertexProperties(45, 1., devsbench::ATOMIC);
        (*g22)[v22_4] = devsbench::VertexProperties(46, 1., devsbench::ATOMIC);
        (*g22)[v22_5] = devsbench::VertexProperties(47, 1., devsbench::OUTPUT);
        
        boost::add_edge(v22_0, v22_2, EdgeProperties("out1", "in1", 1), *g22);
        boost::add_edge(v22_1, v22_3, EdgeProperties("out1", "in1", 1), *g22);
        boost::add_edge(v22_2, v22_4, EdgeProperties("out1", "in1", 1), *g22);
        boost::add_edge(v22_2, v22_3, EdgeProperties("out2", "in2", 1), *g22);
        boost::add_edge(v22_3, v22_4, EdgeProperties("out1", "in2", 1), *g22);
        boost::add_edge(v22_4, v22_5, EdgeProperties("out1", "in1", 1), *g22);

        n22->addGraph(g22);
    }

	TreeNode * father2 = root->children_treenode(5);
    father2->addChild(n22);
    
// level 2 - node 27    
    devsbench::TreeNode* n23 = new devsbench::TreeNode(2,27);
    {
        devsbench::Graph* g23 = new devsbench::Graph();
        devsbench::Graph::vertex_descriptor v23_0 = boost::add_vertex(*g23);
        devsbench::Graph::vertex_descriptor v23_1 = boost::add_vertex(*g23);
        devsbench::Graph::vertex_descriptor v23_2 = boost::add_vertex(*g23);
        devsbench::Graph::vertex_descriptor v23_3 = boost::add_vertex(*g23);
        devsbench::Graph::vertex_descriptor v23_4 = boost::add_vertex(*g23);
        devsbench::Graph::vertex_descriptor v23_5 = boost::add_vertex(*g23);
        devsbench::Graph::vertex_descriptor v23_6 = boost::add_vertex(*g23);
		
		(*g23)[v23_0] = devsbench::VertexProperties(48, 1., devsbench::INPUT);
        (*g23)[v23_1] = devsbench::VertexProperties(49, 1., devsbench::ATOMIC);
        (*g23)[v23_2] = devsbench::VertexProperties(50, 1., devsbench::COUPLED);
        (*g23)[v23_3] = devsbench::VertexProperties(51, 1., devsbench::COUPLED);
        (*g23)[v23_4] = devsbench::VertexProperties(52, 1., devsbench::ATOMIC);
        (*g23)[v23_5] = devsbench::VertexProperties(53, 1., devsbench::OUTPUT);
        (*g23)[v23_6] = devsbench::VertexProperties(54, 1., devsbench::OUTPUT);
        
        boost::add_edge(v23_0, v23_1, EdgeProperties("out1", "in1", 1), *g23);
        boost::add_edge(v23_1, v23_3, EdgeProperties("out2", "in1", 1), *g23);
        boost::add_edge(v23_1, v23_2, EdgeProperties("out1", "in1", 1), *g23);
        boost::add_edge(v23_2, v23_4, EdgeProperties("out1", "in1", 1), *g23);
        boost::add_edge(v23_3, v23_4, EdgeProperties("out1", "in2", 1), *g23);
        boost::add_edge(v23_4, v23_5, EdgeProperties("out1", "in1", 1), *g23);
        boost::add_edge(v23_4, v23_6, EdgeProperties("out2", "in1", 1), *g23);

        n23->addGraph(g23);
    }
    
    father2->addChild(n23);
    
// level 3 - node 50     
    devsbench::TreeNode* n30 = new devsbench::TreeNode(3,50);
    {
        devsbench::Graph* g30 = new devsbench::Graph();
        devsbench::Graph::vertex_descriptor v30_0 = boost::add_vertex(*g30);
        devsbench::Graph::vertex_descriptor v30_1 = boost::add_vertex(*g30);
        devsbench::Graph::vertex_descriptor v30_2 = boost::add_vertex(*g30);
        devsbench::Graph::vertex_descriptor v30_3 = boost::add_vertex(*g30);
		
		(*g30)[v30_0] = devsbench::VertexProperties(55, 1., devsbench::INPUT);
        (*g30)[v30_1] = devsbench::VertexProperties(56, 1., devsbench::ATOMIC);
        (*g30)[v30_2] = devsbench::VertexProperties(57, 1., devsbench::ATOMIC);
        (*g30)[v30_3] = devsbench::VertexProperties(58, 1., devsbench::OUTPUT);
        
        boost::add_edge(v30_0, v30_1, EdgeProperties("out1", "in1", 1), *g30);
        boost::add_edge(v30_1, v30_2, EdgeProperties("out1", "in1", 1), *g30);
        boost::add_edge(v30_2, v30_3, EdgeProperties("out1", "in1", 1), *g30);

        n30->addGraph(g30);
    }
    
    TreeNode * father3 = father2->children_treenode(27);
    father3->addChild(n30);
    
// level 3 - node 51  
    devsbench::TreeNode* n31 = new devsbench::TreeNode(3,51);
    {
        devsbench::Graph* g31= new devsbench::Graph();
        devsbench::Graph::vertex_descriptor v31_0 = boost::add_vertex(*g31);
        devsbench::Graph::vertex_descriptor v31_1 = boost::add_vertex(*g31);
        devsbench::Graph::vertex_descriptor v31_2 = boost::add_vertex(*g31);
        devsbench::Graph::vertex_descriptor v31_3 = boost::add_vertex(*g31);
		
		(*g31)[v31_0] = devsbench::VertexProperties(59, 1., devsbench::INPUT);
        (*g31)[v31_1] = devsbench::VertexProperties(60, 1., devsbench::ATOMIC);
        (*g31)[v31_2] = devsbench::VertexProperties(61, 1., devsbench::COUPLED);
        (*g31)[v31_3] = devsbench::VertexProperties(62, 1., devsbench::OUTPUT);
        
        boost::add_edge(v31_0, v31_1, EdgeProperties("out1", "in1", 1), *g31);
        boost::add_edge(v31_1, v31_2, EdgeProperties("out1", "in1", 1), *g31);
        boost::add_edge(v31_1, v31_2, EdgeProperties("out2", "in2", 2), *g31);
        boost::add_edge(v31_1, v31_2, EdgeProperties("out3", "in3", 3), *g31);
        boost::add_edge(v31_1, v31_2, EdgeProperties("out4", "in4", 4), *g31);
        boost::add_edge(v31_2, v31_3, EdgeProperties("out1", "in1", 1), *g31);

        n31->addGraph(g31);
    }
    
    father3->addChild(n31);
    
// level 4 - node 61     
    devsbench::TreeNode* n40 = new devsbench::TreeNode(4,61);
    {
        devsbench::Graph* g40 = new devsbench::Graph();
        devsbench::Graph::vertex_descriptor v40_0 = boost::add_vertex(*g40);
        devsbench::Graph::vertex_descriptor v40_1 = boost::add_vertex(*g40);
        devsbench::Graph::vertex_descriptor v40_2 = boost::add_vertex(*g40);
        devsbench::Graph::vertex_descriptor v40_3 = boost::add_vertex(*g40);
        devsbench::Graph::vertex_descriptor v40_4 = boost::add_vertex(*g40);
        devsbench::Graph::vertex_descriptor v40_5 = boost::add_vertex(*g40);
        devsbench::Graph::vertex_descriptor v40_6 = boost::add_vertex(*g40);
        devsbench::Graph::vertex_descriptor v40_7 = boost::add_vertex(*g40);
		
		(*g40)[v40_0] = devsbench::VertexProperties(63, 1., devsbench::INPUT);
        (*g40)[v40_1] = devsbench::VertexProperties(64, 1., devsbench::INPUT);
        (*g40)[v40_2] = devsbench::VertexProperties(65, 1., devsbench::INPUT);
        (*g40)[v40_3] = devsbench::VertexProperties(66, 1., devsbench::INPUT);
		(*g40)[v40_4] = devsbench::VertexProperties(67, 1., devsbench::ATOMIC);
        (*g40)[v40_5] = devsbench::VertexProperties(68, 1., devsbench::ATOMIC);
        (*g40)[v40_6] = devsbench::VertexProperties(69, 1., devsbench::ATOMIC);
        (*g40)[v40_7] = devsbench::VertexProperties(70, 1., devsbench::OUTPUT);
        
        boost::add_edge(v40_0, v40_4, EdgeProperties("out1", "in1", 1), *g40);
        boost::add_edge(v40_1, v40_4, EdgeProperties("out1", "in2", 2), *g40);
        boost::add_edge(v40_2, v40_5, EdgeProperties("out1", "in1", 3), *g40);
        boost::add_edge(v40_3, v40_5, EdgeProperties("out1", "in2", 4), *g40);
        boost::add_edge(v40_4, v40_6, EdgeProperties("out1", "in1", 1), *g40);
        boost::add_edge(v40_5, v40_6, EdgeProperties("out1", "in2", 1), *g40);
        boost::add_edge(v40_6, v40_7, EdgeProperties("out1", "in1", 1), *g40);

        n40->addGraph(g40);
    }
    
    TreeNode * father4 = father3->children_treenode(51);
    father4->addChild(n40);
    
    std::cout << "Example n level : " << std::endl;
    root->display();
    std::cout<<std::endl;
    
    Merge_Devs_Graph(root, true);
    
    
    delete root;
    
}

void exampleLI()
{
    devstone::Generator generator(devstone::LI, 3, 4, 1, 1);
    devsbench::TreeNode* root = generator.generate();

    std::cout << "Example LI:" << std::endl;
    root->display();
    
    /* Modifs !!! */
    std::cout<<std::endl;
    Graph* go1 = root->graph();
	tie(vertexIto, vertexEndo) = vertices(*go1);
	for (; vertexIto != vertexEndo; ++vertexIto){
		if((*go1)[*vertexIto]._type != COUPLED){
			std::cout<<*vertexIto<<" -> ";
			tie(neighbourIto, neighbourEndo) = adjacent_vertices(*vertexIto,*go1);
			for (; neighbourIto != neighbourEndo; ++neighbourIto){
				std::cout<<*neighbourIto<<" ";
			}
			std::cout<<std::endl;
		}else{
			std::cout<<"C'est un couplé : "<<std::endl;
		}
	}

    delete root;
}

void exampleHI()
{
    devstone::Generator generator(devstone::HI, 3, 4, 1, 1);
    devsbench::TreeNode* root = generator.generate();

    std::cout << "Example HI:" << std::endl;
    root->display();

    delete root;
}

void exampleHO()
{
    devstone::Generator generator(devstone::HO, 3, 4, 1, 1);
    devsbench::TreeNode* root = generator.generate();

    std::cout << "Example HO:" << std::endl;
    root->display();
		
    delete root;
}

void exampleTree()
{
    int nbr_sommets = 100;
    int nbr_sources = nbr_sommets / 100;
    std::vector < int > niveau = {  3, 2 };
    tree::Generator generator;
    devsbench::TreeNode* root = generator.generate(nbr_sommets, nbr_sources,
                                                   2, 3, niveau);

    std::cout << "Example Tree:" << std::endl;
    root->display();

    delete root;
}


int main()
{
    example1();
    std::cout<<std::endl;
    example_n_level();
    //exampleLI();
    //exampleHI();
    //exampleHO();
    //exampleTree();
    return 0;
}
