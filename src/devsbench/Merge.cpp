/**
 * @file Merge.cpp
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

#include <devsbench/Merge.hpp>

namespace devsbench {

void Merge_Devs_Level_Coupled(Graph *go1, const Graph *go2, const std::vector<std::pair<int,int>> &in_edge_connection,
								const std::vector<std::pair<int,int>> &out_edge_connection, 
								std::vector<std::pair<int,int>> &liste_father, uint cpt_vertex){
	/*Destruction de l'arc reliant le modèle couplé à son voisin*/
	for(uint i =0; i <out_edge_connection.size(); i++){
		remove_edge(out_edge_connection.at(i).first,out_edge_connection.at(i).second,*go1);
	}
	
	uint nbr_vertex_go1 = num_vertices(*go1); //Nombre de noeud dans go1 avant modification
	uint nbr_in = 0; //Nombre de port d'entrée
	uint nbr_out = 0; //Nombre de port de sortie
	uint ec_cpt = 0; //Compteur sur les ports de sortie
	uint in_ec_cpt = 0; //Compteur sur les ports d'entrée
	edge_to e1,e2;
	bool found;
	
	/*Calcul du nombre de port d'entrée*/
	tie(vertexIto, vertexEndo) = vertices(*go2);
	for (; vertexIto != vertexEndo; ++vertexIto){
		if((*go2)[*vertexIto]._type == INPUT)
			nbr_in++;
		else if((*go2)[*vertexIto]._type == OUTPUT)
			nbr_out++;
		else if((*go2)[*vertexIto]._type == COUPLED){
			std::pair<int,int> father;
			father.first = (*go2)[*vertexIto]._index;
			//std::cout<<"father : ("<<father.first<<",";
			father.second = (*go1)[cpt_vertex]._index;
			//std::cout<<father.second<<")"<<std::endl;
			liste_father.push_back(father);
		}
	}
		
	/*Création des noeuds dans go1 (sauf les IN ET OUT)*/
	tie(vertexIto, vertexEndo) = vertices(*go2);
	uint tmp = 0;
	while(tmp < nbr_in + 1){
		vertexIto++;
		tmp++;
	}
	for (; vertexIto != vertexEndo; ++vertexIto){
		if((*go2)[*vertexIto]._type != OUTPUT){
			vertex_to v0 = boost::add_vertex(*go1);
			(*go1)[v0] = VertexProperties((*go2)[*vertexIto]._index, (*go2)[*vertexIto]._weight, (*go2)[*vertexIto]._type);
		}
	}
	
	(*go1)[cpt_vertex]._type = (*go2)[nbr_in]._type;
	(*go1)[cpt_vertex]._index = (*go2)[nbr_in]._index;
	(*go1)[cpt_vertex]._weight = (*go2)[nbr_in]._weight; 

	/*Pour chaque noeud de go2 faire ...*/
	tie(vertexIto, vertexEndo) = vertices(*go2);
	for (; vertexIto != vertexEndo; ++vertexIto){
		if((*go2)[*vertexIto]._type != OUTPUT && (*go2)[*vertexIto]._type != INPUT){
			tie(neighbourIto, neighbourEndo) = adjacent_vertices(*vertexIto,*go2);
			uint rec_neigh = -1;
			for (; neighbourIto != neighbourEndo; ++neighbourIto){
				if(rec_neigh != *neighbourIto){
					rec_neigh = *neighbourIto;
					if(*neighbourIto != nbr_in){
						if((*go2)[*neighbourIto]._type != OUTPUT){
							tie(e1,found)=edge(vertex(*vertexIto,*go2),vertex(*neighbourIto,*go2),*go2);
							if(*vertexIto  == nbr_in){
								add_edge(out_edge_connection.at(ec_cpt).first, *neighbourIto + nbr_vertex_go1 -1 - nbr_in, 
								EdgeProperties((*go2)[e1]._beginName,(*go2)[e1]._endName,(*go2)[e1]._weight), *go1);
							}else{
								add_edge(*vertexIto + nbr_vertex_go1 -1 - nbr_in, *neighbourIto + nbr_vertex_go1 -1 - nbr_in,
								EdgeProperties((*go2)[e1]._beginName,(*go2)[e1]._endName,(*go2)[e1]._weight), *go1);
							}
						}else{
							if((num_vertices(*go2) - nbr_in - nbr_out) == 1 && nbr_in != 0){
								tie(e1,found)=edge(vertex(*vertexIto,*go2),vertex(*neighbourIto,*go2),*go2);
								add_edge(out_edge_connection.at(ec_cpt).first, out_edge_connection.at(ec_cpt).second ,
								EdgeProperties((*go2)[e1]._beginName,(*go2)[e1]._endName,(*go2)[e1]._weight), *go1);
								ec_cpt++;
							}else{
								tie(e1,found)=edge(vertex(*vertexIto,*go2),vertex(*neighbourIto,*go2),*go2);
								add_edge(*vertexIto + nbr_vertex_go1 -1 - nbr_in, out_edge_connection.at(ec_cpt).second ,
								EdgeProperties((*go2)[e1]._beginName,(*go2)[e1]._endName,(*go2)[e1]._weight), *go1);
								ec_cpt++;
							}
						}
					}else{
						tie(e1,found)=edge(vertex(*vertexIto,*go2),vertex(*neighbourIto,*go2),*go2);
						add_edge(*vertexIto + nbr_vertex_go1 -1 - nbr_in, out_edge_connection.at(ec_cpt).first,
						EdgeProperties((*go2)[e1]._beginName,(*go2)[e1]._endName,(*go2)[e1]._weight), *go1);
					}
				}else{
					tie(e1,found)=edge(vertex(*vertexIto,*go2),vertex(*neighbourIto,*go2),*go2);
					if(*vertexIto  == nbr_in)
						tie(e2,found)=edge(vertex(out_edge_connection.at(ec_cpt).first,*go1),vertex(*neighbourIto + nbr_vertex_go1 -1 - nbr_in,*go1),*go1);
					else if (*neighbourIto == nbr_in)
						tie(e2,found)=edge(vertex(*vertexIto + nbr_vertex_go1 -1 - nbr_in,*go1),vertex(out_edge_connection.at(ec_cpt).first,*go1),*go1);
					else
						tie(e2,found)=edge(vertex(*vertexIto + nbr_vertex_go1 -1 - nbr_in,*go1),vertex(*neighbourIto + nbr_vertex_go1 -1 - nbr_in,*go1),*go1);
					(*go1)[e2]._weight += (*go2)[e1]._weight;				
				}
			}
		}else if((*go2)[*vertexIto]._type == INPUT){
			tie(neighbourIto, neighbourEndo) = adjacent_vertices(*vertexIto,*go2);
			for (; neighbourIto != neighbourEndo; ++neighbourIto){
				if(*neighbourIto != nbr_in){
					tie(e1,found)=edge(vertex(*vertexIto,*go2),vertex(*neighbourIto,*go2),*go2);
					remove_edge(in_edge_connection.at(in_ec_cpt).first,out_edge_connection.at(ec_cpt).first,*go1);
					add_edge(in_edge_connection.at(in_ec_cpt).first,*neighbourIto + nbr_vertex_go1 -1 -nbr_in,
					EdgeProperties((*go2)[e1]._beginName,(*go2)[e1]._endName,(*go2)[e1]._weight), *go1);
				}
			}
			in_ec_cpt++;
		}
	}
}

void Merge_Devs_Graph(TreeNode *root, bool rec){
	Graph *go1 = root->graph();
	uint level; 
	root->level_max(level);
	std::cout<<"level: "<<level<<std::endl;
	uint compteur = 0;
	std::vector<std::pair<int,int>> in_edge_connection, out_edge_connection;
	std::vector<std::pair<int,int>> liste_father, liste_father2;
	std::map<int, TreeNode*> table_father1, table_father2;
	table_father1[0] = root;

	while(compteur < level){
		uint cpt_vertex = 0;
		//std::cout<<std::endl;
		//std::cout<<"*** Niveau *** -> "<<compteur<<std::endl;
		tie(vertexIto, vertexEndo) = vertices(*go1);
		uint nbr_go1 = num_vertices(*go1);
		while(cpt_vertex < nbr_go1){
			//std::cout<<"vertex -> "<<cpt_vertex<<" Noeud : "<<(*go1)[cpt_vertex]._index<<" Type = "<<(*go1)[cpt_vertex]._type<<std::endl;
			if((*go1)[cpt_vertex]._type == COUPLED){
				//std::cout<<"C'est un COUPLED "<<std::endl;
				//std::cout<<"IN : ";
				for (boost::tie(ei,edge_end) = in_edges(cpt_vertex, *go1); ei != edge_end; ++ei){
					std::pair<int,int> couple;
					//std::cout<<"("<<(*go1)[source(*ei, *go1)]._index<<",";
					couple.first = source(*ei, *go1);
					//std::cout<<(*go1)[cpt_vertex]._index<<") / ";
					couple.second = cpt_vertex; 
					in_edge_connection.push_back(couple);
				}
				//std::cout<<std::endl;
				//std::cout<<"OUT : ";
				tie(neighbourIto, neighbourEndo) = adjacent_vertices(cpt_vertex,*go1);
				for (; neighbourIto != neighbourEndo; ++neighbourIto){
					std::pair<int,int> couple1;
					//std::cout<<"("<<(*go1)[cpt_vertex]._index<<",";
					couple1.first = cpt_vertex; 
					//std::cout<<(*go1)[*neighbourIto]._index<<") / ";
					couple1.second = *neighbourIto;
					out_edge_connection.push_back(couple1);
				}
				if(compteur > 0){
					int father_index;
					//std::cout<<liste_father.size()<<std::endl;
					for(uint id = 0; id<liste_father.size(); id++){
						if(liste_father.at(id).first == (*go1)[cpt_vertex]._index){
							father_index = liste_father.at(id).second;
							//std::cout<<"father_index : "<<father_index<<std::endl; 
							break;
						}
					}
					table_father2[(*go1)[cpt_vertex]._index] = table_father1[father_index]->children_treenode((*go1)[cpt_vertex]._index);
					TreeNode *father = table_father1[father_index];
					Merge_Devs_Level_Coupled(go1, father->children_graph((*go1)[cpt_vertex]._index), in_edge_connection, out_edge_connection, liste_father2, cpt_vertex);
				}else{
					table_father2[(*go1)[cpt_vertex]._index] = table_father1[0]->children_treenode((*go1)[cpt_vertex]._index);
					Merge_Devs_Level_Coupled(go1, root->children_graph((*go1)[cpt_vertex]._index), in_edge_connection, out_edge_connection, liste_father2, cpt_vertex);
				}
				Affichage_OrientedGraph(go1);
				in_edge_connection.clear();
				out_edge_connection.clear();
				if(rec == true){
					const char* text = "../../sortie_graphe/Tests/Graphes/Merge/txt/Coupled_Merge.txt";
					Plot_Graph(go1,text);
				}
			}
			cpt_vertex++;
		}
		table_father1 = table_father2;
		table_father2.clear();
		liste_father = liste_father2;
		liste_father2.clear();
		compteur++;
	}
}

void Plot_Graph(Graph *go,const char* text){
	edge_to e1;
	bool found;
	
	std::ofstream fichier2 (text, std::ios::out);
	fichier2<<"digraph G {"<<std::endl;   
	tie(vertexIto, vertexEndo) = vertices(*go);
	for (; vertexIto != vertexEndo; ++vertexIto) {
		tie(neighbourIto, neighbourEndo) = adjacent_vertices(*vertexIto,
				*go);
		for (; neighbourIto != neighbourEndo; ++neighbourIto){
				tie(e1,found)=edge(vertex(*vertexIto,*go),vertex(*neighbourIto,*go),*go);
				fichier2<<(*go)[*vertexIto]._index<<" -> "<<(*go)[*neighbourIto]._index<<" [label="<<(*go)[e1]._weight<<",];"<<std::endl;
		}
	}
	
	fichier2<<"}";	
	fichier2.close();
		
}

void Affichage_OrientedGraph(Graph *go){
	tie(vertexIto, vertexEndo) = vertices(*go);
    for (; vertexIto != vertexEndo; ++vertexIto) {
    	std::cout<<(*go)[*vertexIto]._index<<" -> ";
    	tie(neighbourIto, neighbourEndo) = adjacent_vertices(*vertexIto,
    			*go);
    	for (; neighbourIto != neighbourEndo; ++neighbourIto){
    		std::cout<<(*go)[*neighbourIto]._index<<" ";	
    	}
    	std::cout<<std::endl;
    }
	std::cout<<std::endl;
}

}
