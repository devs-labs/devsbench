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

namespace devsbench { namespace devstone {

    Graph* Generator::build_low_level_graph(int id) const
    {
		Graph* g = new Graph();
		if(_type != HO){
	        Graph::vertex_descriptor input_vertex = g->addVertex(id+0, 1, INPUT);
	        Graph::vertex_descriptor inner_vertex = g->addVertex(id+1, 1, ATOMIC);
	        Graph::vertex_descriptor output_vertex = g->addVertex(id+2, 1, OUTPUT);

        g->addEdge(input_vertex, 1, inner_vertex, 1);
        g->addEdge(inner_vertex, 1, output_vertex, 1);
		}else{
			Graph::vertex_descriptor input_vertex = g->addVertex(id+0, 1, INPUT);
			Graph::vertex_descriptor input_vertex1 = g->addVertex(id+1, 1, INPUT);
	        Graph::vertex_descriptor inner_vertex = g->addVertex(id+2, 1, ATOMIC);
	        Graph::vertex_descriptor output_vertex = g->addVertex(id+3, 1, OUTPUT);
	        Graph::vertex_descriptor output_vertex2 = g->addVertex(id+4, 1, OUTPUT);
	        
	    g->addEdge(input_vertex , 1, inner_vertex , 1);
	    g->addEdge(input_vertex1, 2, inner_vertex , 2);
        g->addEdge(inner_vertex , 1, output_vertex, 1);
        g->addEdge(inner_vertex , 2, output_vertex2, 2);
		}
        return g;
    }

    /*Graph* Generator::build_graph() const
    {
        Graph* g = new Graph();
        std::vector < Graph::vertex_descriptor > vertexList;

        for (int i = 0; i < _width; ++i) {
            if (i == 0) {
                vertexList.push_back(g->addVertex(i, 1, COUPLED));
            } else {
                vertexList.push_back(g->addVertex(i, 1, ATOMIC));
            }
        }

        Graph::vertex_descriptor input_vertex =
            g->addVertex(_width, 0, INPUT);
        Graph::vertex_descriptor output_vertex =
            g->addVertex(_width + 1, 0, OUTPUT);

        // edges
        for (int i = 0; i < _width; ++i) {
            g->addEdge(input_vertex, "in1", vertexList[i], "in1");
        }
        g->addEdge(vertexList[0], "out1", output_vertex, "out1");
        if (_type == HI or _type == HO) {
            for (int i = 1; i < _width - 1; ++i) {
                g->addEdge(vertexList[i], "out1", vertexList[i + 1], "in1");
            }
        }

        if (_type == HO) {
            Graph::vertex_descriptor input_vertex_2 =
                g->addVertex(_width + 2, 0, INPUT);
            Graph::vertex_descriptor output_vertex_2 =
                g->addVertex(_width + 3, 0, OUTPUT);

            g->addEdge(input_vertex_2, "in2", vertexList[1], "in2");
            g->addEdge(vertexList[1], "out2", output_vertex_2, "out2");
            g->addEdge(input_vertex_2, "in2", vertexList[0], "in2");
        }
        return g;
    }*/
    
    Graph* Generator::build_graph(int id) const
    {
        Graph* g = new Graph();
        std::vector < Graph::vertex_descriptor > vertexList;
        
        if(_type == HO){
			vertexList.push_back(g->addVertex(id+0, 1, INPUT));
			vertexList.push_back(g->addVertex(id+1, 1, INPUT));
			
			for (int i = 0; i < _width; ++i) {
	            if (i == 0) {
	                vertexList.push_back(g->addVertex(id+i+2, 1, COUPLED));
	            } else {
	                vertexList.push_back(g->addVertex(id+i+2, 1, ATOMIC));
	            }
	        }
	        
	        vertexList.push_back(g->addVertex(id+_width + 2, 1, OUTPUT));
	        vertexList.push_back(g->addVertex(id+_width + 3, 1, OUTPUT));
			
			for(int j = 2; j < _width + 2; j++)
				g->addEdge(vertexList[0], 1, vertexList[j], 1);
				
			g->addEdge(vertexList[1], 2, vertexList[2], 2);
			g->addEdge(vertexList[1], 2, vertexList[3], 2);
	        
			g->addEdge(vertexList[2], 1, vertexList[_width+2], 1);
			g->addEdge(vertexList[2], 2, vertexList[_width+3], 2);
	       
	        for (int i = 3; i < _width + 1 ; ++i)
	             g->addEdge(vertexList[i], 1, vertexList[i + 1], 2);
	             
		}else{
	        vertexList.push_back(g->addVertex(id+0, 1, INPUT));
	
	        for (int i = 0; i < _width; ++i) {
	            if (i == 0) {
	                vertexList.push_back(g->addVertex(id+i+1, 1, COUPLED));
	            } else {
	                vertexList.push_back(g->addVertex(id+i+1, 1, ATOMIC));
	            }
	        }
	             
	        vertexList.push_back(g->addVertex(id+_width + 1, 1, OUTPUT));
	
	        // edges
	        for (int i = 0; i < _width; ++i) {
	            g->addEdge(vertexList[0], 1, vertexList[i+1], 1);
	        }
	        g->addEdge(vertexList[1], 1, vertexList[_width+1], 1);
	        if (_type == HI or _type == HO) {
	            for (int i = 2; i < _width ; ++i) {
	                g->addEdge(vertexList[i], 1, vertexList[i + 1], 2);
	            }
	        }
		}
		
        return g;
    }
    
    Graph* Generator::build_start_graph() const
    {
        Graph* g = new Graph();
        std::vector < Graph::vertex_descriptor > vertexList;
        
        if(_type == HO){
			vertexList.push_back(g->addVertex(0, 1, ATOMIC));
			vertexList.push_back(g->addVertex(1, 1, ATOMIC));
			
			for (int i = 0; i < _width; ++i) {
	            if (i == 0) {
	                vertexList.push_back(g->addVertex(i+2, 1, COUPLED));
	            } else {
	                vertexList.push_back(g->addVertex(i+2, 1, ATOMIC));
	            }
	        }
	        
	        vertexList.push_back(g->addVertex(_width + 2, 1, ATOMIC));
	        vertexList.push_back(g->addVertex(_width + 3, 1, ATOMIC));
			
			for(int j = 2; j < _width + 2; j++)
				g->addEdge(vertexList[0], j-1, vertexList[j], 1);
				
			g->addEdge(vertexList[1], 1, vertexList[2], 2);
			g->addEdge(vertexList[1], 2, vertexList[3], 2);
	        
			g->addEdge(vertexList[2], 1, vertexList[_width+2], 1);
			g->addEdge(vertexList[2], 2, vertexList[_width+3], 1);
	       
	        for (int i = 3; i < _width + 1 ; ++i)
	             g->addEdge(vertexList[i],1, vertexList[i + 1], 2);
	             
		}else{
	        vertexList.push_back(g->addVertex(0, 1, ATOMIC));
	
	        for (int i = 0; i < _width; ++i) {
	            if (i == 0) {
	                vertexList.push_back(g->addVertex(i+1, 1, COUPLED));
	            } else {
	                vertexList.push_back(g->addVertex(i+1, 1, ATOMIC));
	            }
	        }
	             
	        vertexList.push_back(g->addVertex(_width + 1, 1, ATOMIC));
	
	        // edges
	        for (int i = 0; i < _width; ++i) {
	            g->addEdge(vertexList[0], i+1, vertexList[i+1], 1);
	        }
	        g->addEdge(vertexList[1], 1, vertexList[_width+1], 1);
	        if (_type == HI ) {
	            for (int i = 2; i < _width ; ++i) {
	                g->addEdge(vertexList[i], 1, vertexList[i + 1], 2);
	            }
	        }
		}
		
        return g;
    }

    TreeNode* Generator::generate() const
    {
        TreeNode* root = new TreeNode(0, 0);
        root->addGraph(build_start_graph());
        root->display();

        int l = 1;
        TreeNode* father = root;

        while (l < _depth - 1) {
			int id;
			if(_type != HO)
	            id = (l-1)*6+1;
	        else
				id = (l-1)*8+2;
			std::cout<<l<<" - > "<<id<<std::endl;
			TreeNode* n = new TreeNode(l, id);
			if(_type != HO)
				n->addGraph(build_graph(l*6));
			else
				n->addGraph(build_graph(l*8));
            father->addChild(n);
            father = n;
            ++l;
        }

        {
			int id;
			if(_type != HO)
				id = (_depth-2)*6+1;
			else
				id = (_depth-2)*8+2;
			
			std::cout<<l<<" - > "<<id<<std::endl;	
			TreeNode* n = new TreeNode(l,id);
			if(_type != HO)
				n->addGraph(build_low_level_graph(6*l));
			else
				n->addGraph(build_low_level_graph(8*l));
            father->addChild(n);
        }

        return root;
    }

} } // namespace devstone devsbench
