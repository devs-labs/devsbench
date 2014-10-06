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
								std::vector<std::pair<int,int>> &liste_father, uint cpt_vertex, bool multiple){
	/*Destruction de l'arc reliant le modèle couplé à son voisin*/
	for(uint i =0; i <out_edge_connection.size(); i++){
		remove_edge(out_edge_connection.at(i).first,out_edge_connection.at(i).second,*go1);
	}
	if(multiple == true){
		for(uint i =0; i <in_edge_connection.size(); i++){
			remove_edge(in_edge_connection.at(i).first,in_edge_connection.at(i).second,*go1);
		}
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
			father.second = (*go1)[cpt_vertex]._index;
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
				if(rec_neigh != *neighbourIto || (*go2)[*neighbourIto]._type == COUPLED){
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
		}else if((*go2)[*vertexIto]._type == INPUT && multiple == false){
			tie(neighbourIto, neighbourEndo) = adjacent_vertices(*vertexIto,*go2);
			for (; neighbourIto != neighbourEndo; ++neighbourIto){
				if(*neighbourIto != nbr_in ){
					tie(e1,found)=edge(vertex(*vertexIto,*go2),vertex(*neighbourIto,*go2),*go2);
					remove_edge(in_edge_connection.at(in_ec_cpt).first,out_edge_connection.at(ec_cpt).first,*go1);
					add_edge(in_edge_connection.at(in_ec_cpt).first,*neighbourIto + nbr_vertex_go1 -1 -nbr_in,
					EdgeProperties((*go2)[e1]._beginName,(*go2)[e1]._endName,(*go2)[e1]._weight), *go1);
				}
			}
			in_ec_cpt++;
		}else if((*go2)[*vertexIto]._type == INPUT && multiple == true){
			tie(neighbourIto, neighbourEndo) = adjacent_vertices(*vertexIto,*go2);
			for (; neighbourIto != neighbourEndo; ++neighbourIto){
				if(*neighbourIto != nbr_in){	
					tie(e1,found)=edge(vertex(*vertexIto,*go2),vertex(*neighbourIto,*go2),*go2);
					add_edge(in_edge_connection.at(in_ec_cpt).first,*neighbourIto + nbr_vertex_go1 -1 -nbr_in,
					EdgeProperties((*go2)[e1]._beginName,(*go2)[e1]._endName,(*go2)[e1]._weight), *go1);
				}else{
					tie(e1,found)=edge(vertex(*vertexIto,*go2),vertex(*neighbourIto,*go2),*go2);
					add_edge(vertex(in_edge_connection.at(in_ec_cpt).first,*go1),
					vertex(*neighbourIto + nbr_vertex_go1 -1 -nbr_in,*go1),
					EdgeProperties((*go2)[e1]._beginName,(*go2)[e1]._endName,(*go2)[e1]._weight),*go1);
				}
			}
			in_ec_cpt++;
		}
	}
}

void Merge_Devs_Coupled_port(Graph *go1, const Graph *go2, const std::vector<std::pair<int,int>> &in_edge_connection,
								const std::vector<std::pair<int,int>> &out_edge_connection, 
								const std::vector<std::pair<std::pair<std::string,std::string>,double>> &save_connection_in,
								const std::vector<std::pair<std::pair<std::string,std::string>,double>> &save_connection_out,
								std::vector<std::pair<int,int>> &liste_father, uint cpt_vertex, bool multiple){
	//Destruction de l'arc reliant le modèle couplé à son voisin
	for(uint i =0; i <out_edge_connection.size(); i++){
		remove_edge(out_edge_connection.at(i).first,out_edge_connection.at(i).second,*go1);
	}
	if(multiple == true){
		for(uint i =0; i <in_edge_connection.size(); i++){
			remove_edge(in_edge_connection.at(i).first,in_edge_connection.at(i).second,*go1);
		}
	}
	
	uint nbr_vertex_go1 = num_vertices(*go1); //Nombre de noeud dans go1 avant modification
	uint nbr_in = 0; //Nombre de port d'entrée
	uint nbr_out = 0; //Nombre de port de sortie
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
			father.second = (*go1)[cpt_vertex]._index;
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
			//std::cout<<"Ce n'est pas un input"<<std::endl;
			tie(neighbourIto, neighbourEndo) = adjacent_vertices(*vertexIto,*go2);
			uint rec_neigh = -1;
			for (; neighbourIto != neighbourEndo; ++neighbourIto){
				if(rec_neigh != *neighbourIto || (*go2)[*neighbourIto]._type == COUPLED){
					rec_neigh = *neighbourIto;
					if(*neighbourIto != nbr_in){
						//std::cout<<" *Son voisin n'est pas le sommet originel"<<std::endl;
						if((*go2)[*neighbourIto]._type != OUTPUT){
							//std::cout<<"  **ni un output"<<std::endl;
							tie(e1,found)=edge(vertex(*vertexIto,*go2),vertex(*neighbourIto,*go2),*go2);
							if(*vertexIto  == nbr_in){
								//std::cout<<"   ***mais il est l'originel"<<std::endl;
								add_edge(cpt_vertex /*out_edge_connection.at(ec_cpt).first*/, *neighbourIto + nbr_vertex_go1 -1 - nbr_in, 
								EdgeProperties((*go2)[e1]._beginName,(*go2)[e1]._endName,(*go2)[e1]._weight), *go1);
								//std::cout<<"bla"<<std::endl;
							}else{
								//std::cout<<"   ***et ce n'est pas l'originel"<<std::endl;
								add_edge(*vertexIto + nbr_vertex_go1 -1 - nbr_in, *neighbourIto + nbr_vertex_go1 -1 - nbr_in,
								EdgeProperties((*go2)[e1]._beginName,(*go2)[e1]._endName,(*go2)[e1]._weight), *go1);
							}
						}else{
							//std::cout<<"  **mais c'est un output"<<std::endl;
							if((num_vertices(*go2) - nbr_in - nbr_out) == 1 && nbr_in != 0){
								tie(e1,found)=edge(vertex(*vertexIto,*go2),vertex(*neighbourIto,*go2),*go2);
								std::string index_port = (*go2)[e1]._endName;
								uint port;
								for(uint id = 0; id < save_connection_out.size(); id++){
									if(save_connection_out.at(id).first.first == index_port)
										port = id;
								}
								add_edge(out_edge_connection.at(port).first, out_edge_connection.at(port).second ,
								EdgeProperties((*go2)[e1]._beginName,save_connection_out.at(port).first.second,save_connection_out.at(port).second), *go1);
							}else{
								tie(e1,found)=edge(vertex(*vertexIto,*go2),vertex(*neighbourIto,*go2),*go2);
								std::string index_port = (*go2)[e1]._endName;
								uint port;
								for(uint id = 0; id < save_connection_out.size(); id++){
									if(save_connection_out.at(id).first.first == index_port)
										port = id;
								}
								add_edge(*vertexIto + nbr_vertex_go1 -1 - nbr_in, out_edge_connection.at(port).second ,
								EdgeProperties((*go2)[e1]._beginName,save_connection_out.at(port).first.second,save_connection_out.at(port).second), *go1);
							}
						}
					}else{
						//std::cout<<" *Son voisin est le sommet originel"<<std::endl;
						tie(e1,found)=edge(vertex(*vertexIto,*go2),vertex(*neighbourIto,*go2),*go2);
						if(in_edge_connection.size() != 0)
							add_edge(*vertexIto + nbr_vertex_go1 -1 - nbr_in, in_edge_connection.at(0).second,
									EdgeProperties((*go2)[e1]._beginName,(*go2)[e1]._endName,(*go2)[e1]._weight), *go1);
						else
							add_edge(*vertexIto + nbr_vertex_go1 -1 - nbr_in, out_edge_connection.at(0).first,
									EdgeProperties((*go2)[e1]._beginName,(*go2)[e1]._endName,(*go2)[e1]._weight), *go1);
					}
				}else{
					tie(e1,found)=edge(vertex(*vertexIto,*go2),vertex(*neighbourIto,*go2),*go2);
					if(*vertexIto  == nbr_in){
						if(in_edge_connection.size() != 0)
							tie(e2,found)=edge(vertex(in_edge_connection.at(0).second,*go1),vertex(*neighbourIto + nbr_vertex_go1 -1 - nbr_in,*go1),*go1);
						else
							tie(e2,found)=edge(vertex(out_edge_connection.at(0).first,*go1),vertex(*neighbourIto + nbr_vertex_go1 -1 - nbr_in,*go1),*go1);
					}else if (*neighbourIto == nbr_in){
						if(in_edge_connection.size() != 0)
							tie(e2,found)=edge(vertex(*vertexIto + nbr_vertex_go1 -1 - nbr_in,*go1),vertex(in_edge_connection.at(0).second,*go1),*go1);
						else
							tie(e2,found)=edge(vertex(*vertexIto + nbr_vertex_go1 -1 - nbr_in,*go1),vertex(out_edge_connection.at(0).first,*go1),*go1);
					}else
						tie(e2,found)=edge(vertex(*vertexIto + nbr_vertex_go1 -1 - nbr_in,*go1),vertex(*neighbourIto + nbr_vertex_go1 -1 - nbr_in,*go1),*go1);
					(*go1)[e2]._weight += (*go2)[e1]._weight;				
				}
			}
		}else if((*go2)[*vertexIto]._type == INPUT && multiple == false){
			//std::cout<<"C'est un input"<<std::endl;
			tie(neighbourIto, neighbourEndo) = adjacent_vertices(*vertexIto,*go2);
			for (; neighbourIto != neighbourEndo; ++neighbourIto){
				if(*neighbourIto != nbr_in ){
					//std::cout<<" *Son voisin n'est pas le sommet originel"<<std::endl;
					tie(e1,found)=edge(vertex(*vertexIto,*go2),vertex(*neighbourIto,*go2),*go2);
					std::string index_port = (*go2)[e1]._beginName;
					//std::cout<<index_port<<" -> ";
					uint port;
					for(uint id = 0; id < save_connection_in.size(); id++){
						if(save_connection_in.at(id).first.second == index_port){
							//std::cout<<id<<" -> "<<std::endl;
							port = id;
						}
					}
					//std::cout<<"  Sommet de depart : "<<(*go1)[in_edge_connection.at(port).first]._index<<std::endl;
					//std::cout<<"  Sommet d'arrivé : "<<(*go1)[*neighbourIto + nbr_vertex_go1 -1 -nbr_in]._index<<std::endl;
					remove_edge(in_edge_connection.at(port).first,in_edge_connection.at(port).second,*go1);			
					add_edge(in_edge_connection.at(port).first,*neighbourIto + nbr_vertex_go1 -1 -nbr_in,
					EdgeProperties(save_connection_in.at(port).first.first,(*go2)[e1]._endName,save_connection_in.at(port).second), *go1);
				}else{
					//std::cout<<" *Son voisin est le sommet originel"<<std::endl;
					tie(e1,found)=edge(vertex(*vertexIto,*go2),vertex(*neighbourIto,*go2),*go2);
					std::string index_port = (*go2)[e1]._beginName;
					//std::cout<<index_port<<" -> ";
					uint port;
					for(uint id = 0; id < save_connection_in.size(); id++){
						if(save_connection_in.at(id).first.second == index_port){
							//std::cout<<id<<" -> "<<std::endl;
							port = id;
						}
					}
					//std::cout<<"  Sommet de depart : "<<(*go1)[in_edge_connection.at(port).first]._index<<std::endl;
					//std::cout<<"  Sommet d'arrivé : "<<(*go1)[in_edge_connection.at(port).second]._index<<std::endl;
					tie(e2,found)=edge(vertex(in_edge_connection.at(port).first,*go1),vertex(in_edge_connection.at(port).second,*go1),*go1);
					//std::cout<<(*go1)[e2]._endName<<std::endl;
					(*go1)[e2]._endName = (*go2)[e1]._endName;
					//std::cout<<(*go1)[e2]._endName<<std::endl;
				}
			}
		}else if((*go2)[*vertexIto]._type == INPUT && multiple == true){
			tie(neighbourIto, neighbourEndo) = adjacent_vertices(*vertexIto,*go2);
			for (; neighbourIto != neighbourEndo; ++neighbourIto){
				tie(e1,found)=edge(vertex(*vertexIto,*go2),vertex(*neighbourIto,*go2),*go2);
				std::string index_port = (*go2)[e1]._beginName;
				uint port;
				for(uint id = 0; id < save_connection_in.size(); id++){
					if(save_connection_in.at(id).first.second == index_port)
						port = id;
				}
				add_edge(in_edge_connection.at(port).first,*neighbourIto + nbr_vertex_go1 -1 -nbr_in,
				EdgeProperties(save_connection_in.at(port).first.first,(*go2)[e1]._endName,save_connection_in.at(port).second), *go1);
			}
		}
	}
}

void Merge_Devs_Graph_port(TreeNode *root, bool rec){
	Graph *go1 = root->graph();
	uint level = 1;
	root->level_max(level);
	//std::cout<<"level: "<<level<<std::endl;
	uint compteur = 0;
	std::vector<std::pair<int,int>> in_edge_connection, out_edge_connection;
	std::vector<std::pair<int,int>> liste_father, liste_father2;
	std::vector<std::pair<std::pair<std::string,std::string>,double>> save_connection_in, save_connection_out;
	std::map<int, TreeNode*> table_father1, table_father2;
	table_father1[0] = root;
	edge_to e1,e2;
	bool found;

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
				uint rec_neight = -1;
				bool multiple = false;
				for (boost::tie(ei,edge_end) = in_edges(cpt_vertex, *go1); ei != edge_end; ++ei){
					std::pair<int,int> couple;
					//std::cout<<"("<<(*go1)[source(*ei, *go1)]._index<<",";
					couple.first = source(*ei, *go1);
					//std::cout<<(*go1)[cpt_vertex]._index<<") / ";
					couple.second = cpt_vertex; 
					in_edge_connection.push_back(couple);
					
					/*Enregistrement des informations sur les arcs entrant*/
					tie(e1,found)= edge(vertex(couple.first,*go1),vertex(couple.second,*go1),*go1);
					std::pair<std::string, std::string> edge_name;
					edge_name.first = (*go1)[e1]._beginName;
					edge_name.second = (*go1)[e1]._endName;
					std::pair<std::pair<std::string, std::string>,double> edge_inf;
					edge_inf.first = edge_name;
					edge_inf.second = (*go1)[e1]._weight;
					save_connection_in.push_back(edge_inf);
					
					if(rec_neight == source(*ei, *go1))
						multiple = true;
					rec_neight = source(*ei, *go1);
				}
				//std::cout<<std::endl;
				//std::cout<<"OUT : ";
				tie(neighbourIto, neighbourEndo) = adjacent_vertices(cpt_vertex,*go1);
				for (; neighbourIto != neighbourEndo; ++neighbourIto){
					std::pair<int,int> couple;
					//std::cout<<"("<<(*go1)[cpt_vertex]._index<<",";
					couple.first = cpt_vertex; 
					//std::cout<<(*go1)[*neighbourIto]._index<<") / ";
					couple.second = *neighbourIto;
					out_edge_connection.push_back(couple);
					
					/*Enregistrement des informations sur les arcs sortant*/
					tie(e1,found)= edge(vertex(couple.first,*go1),vertex(couple.second,*go1),*go1);
					std::pair<std::string, std::string> edge_name;
					edge_name.first = (*go1)[e1]._beginName;
					edge_name.second = (*go1)[e1]._endName;
					std::pair<std::pair<std::string, std::string>,double> edge_inf;
					edge_inf.first = edge_name;
					edge_inf.second = (*go1)[e1]._weight;
					save_connection_out.push_back(edge_inf);
				}
				//std::cout<<std::endl;
				if(compteur > 0){
					int father_index;
					for(uint id = 0; id<liste_father.size(); id++){
						if(liste_father.at(id).first == (*go1)[cpt_vertex]._index){
							father_index = liste_father.at(id).second;
							break;
						}
					}
					table_father2[(*go1)[cpt_vertex]._index] = table_father1[father_index]->children_treenode((*go1)[cpt_vertex]._index);
					TreeNode *father = table_father1[father_index];
					Merge_Devs_Coupled_port(go1, father->children_graph((*go1)[cpt_vertex]._index), 
					in_edge_connection, out_edge_connection, save_connection_in,
					save_connection_out, liste_father2, cpt_vertex, multiple);
				}else{
					table_father2[(*go1)[cpt_vertex]._index] = table_father1[0]->children_treenode((*go1)[cpt_vertex]._index);
					Merge_Devs_Coupled_port(go1, root->children_graph((*go1)[cpt_vertex]._index), 
					in_edge_connection, out_edge_connection, save_connection_in, 
					save_connection_out, liste_father2, cpt_vertex, multiple);
				}
				if(multiple == true){
					//std::cout<<"Multiple !!!!"<<std::endl;
					int vertex_save = -1;
					for(uint i =0; i <in_edge_connection.size(); i++){
						if(vertex_save != in_edge_connection.at(i).first){
							uint rec_vertex = -1;
							double rec_weight = 0;
							bool repete = false;
							std::vector<std::pair<double,int>> truc;
							tie(neighbourIto, neighbourEndo) = adjacent_vertices(in_edge_connection.at(i).first,*go1);
							for (; neighbourIto != neighbourEndo; ++neighbourIto){
								if(rec_vertex == *neighbourIto){
									repete = true;
									tie(e1,found)=edge(vertex(in_edge_connection.at(i).first,*go1),vertex(*neighbourIto,*go1),*go1);
									rec_weight += (*go1)[e1]._weight;
								}else{
									if(repete == true){
										neighbourIto--;
										std::pair<double,int> tt;
										tt.first = rec_weight;
										tt.second = *neighbourIto;
										truc.push_back(tt);
										neighbourIto++;
										repete = false;
									}
									tie(e1,found)=edge(vertex(in_edge_connection.at(i).first,*go1),vertex(*neighbourIto,*go1),*go1);
									rec_weight = (*go1)[e1]._weight;
									rec_vertex = *neighbourIto;
								}
							}
							neighbourIto--;
							std::pair<double,int> tt;
							tt.first = rec_weight;
							tt.second = *neighbourIto;
							truc.push_back(tt);
							
							for(uint id = 0; id < truc.size(); id++){
								remove_edge(in_edge_connection.at(i).first,truc.at(id).second,*go1);
								add_edge(in_edge_connection.at(i).first,truc.at(id).second, EdgeProperties("out1","in1",truc.at(id).first), *go1);
							}
							
							vertex_save = in_edge_connection.at(i).first;
						}
					}
				}
				//Affichage_OrientedGraph(go1);
				if(rec == true){
					const char* text = "../../sortie_graphe/Tests/Graphes/Merge/txt/Coupled_Merge2.txt";
					Plot_Graph(go1,text);
				}
				in_edge_connection.clear();
				out_edge_connection.clear();
				save_connection_in.clear();
				save_connection_out.clear();
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

void Merge_Devs_Graph(TreeNode *root, bool rec){
	Graph *go1 = root->graph();
	uint level = 1; 
	//root->level_max(level);
	std::cout<<"level: "<<level<<std::endl;
	uint compteur = 0;
	std::vector<std::pair<int,int>> in_edge_connection, out_edge_connection;
	std::vector<std::pair<int,int>> liste_father, liste_father2;
	std::map<int, TreeNode*> table_father1, table_father2;
	table_father1[0] = root;
	edge_to e1,e2;
	bool found;

	while(compteur < level){
		uint cpt_vertex = 0;
		std::cout<<std::endl;
		std::cout<<"*** Niveau *** -> "<<compteur<<std::endl;
		tie(vertexIto, vertexEndo) = vertices(*go1);
		uint nbr_go1 = num_vertices(*go1);
		while(cpt_vertex < nbr_go1){
			std::cout<<"vertex -> "<<cpt_vertex<<" Noeud : "<<(*go1)[cpt_vertex]._index<<" Type = "<<(*go1)[cpt_vertex]._type<<std::endl;
			if((*go1)[cpt_vertex]._type == COUPLED){
				std::cout<<"C'est un COUPLED "<<std::endl;
				std::cout<<"IN : ";
				uint rec_neight = -1;
				bool multiple = false;
				for (boost::tie(ei,edge_end) = in_edges(cpt_vertex, *go1); ei != edge_end; ++ei){
					std::pair<int,int> couple;
					std::cout<<"("<<(*go1)[source(*ei, *go1)]._index<<",";
					couple.first = source(*ei, *go1);
					std::cout<<(*go1)[cpt_vertex]._index<<") / ";
					couple.second = cpt_vertex; 
					in_edge_connection.push_back(couple);
					if(rec_neight == source(*ei, *go1))
						multiple = true;
					rec_neight = source(*ei, *go1);
				}
				std::cout<<std::endl;
				std::cout<<"OUT : ";
				tie(neighbourIto, neighbourEndo) = adjacent_vertices(cpt_vertex,*go1);
				for (; neighbourIto != neighbourEndo; ++neighbourIto){
					std::pair<int,int> couple1;
					std::cout<<"("<<(*go1)[cpt_vertex]._index<<",";
					couple1.first = cpt_vertex; 
					std::cout<<(*go1)[*neighbourIto]._index<<") / ";
					couple1.second = *neighbourIto;
					out_edge_connection.push_back(couple1);
				}
				std::cout<<std::endl;
				if(compteur > 0){
					int father_index;
					for(uint id = 0; id<liste_father.size(); id++){
						if(liste_father.at(id).first == (*go1)[cpt_vertex]._index){
							father_index = liste_father.at(id).second;
							break;
						}
					}
					table_father2[(*go1)[cpt_vertex]._index] = table_father1[father_index]->children_treenode((*go1)[cpt_vertex]._index);
					TreeNode *father = table_father1[father_index];
					Merge_Devs_Level_Coupled(go1, father->children_graph((*go1)[cpt_vertex]._index), in_edge_connection, out_edge_connection, liste_father2, cpt_vertex, multiple);
				}else{
					table_father2[(*go1)[cpt_vertex]._index] = table_father1[0]->children_treenode((*go1)[cpt_vertex]._index);
					Merge_Devs_Level_Coupled(go1, root->children_graph((*go1)[cpt_vertex]._index), in_edge_connection, out_edge_connection, liste_father2, cpt_vertex, multiple);
				}
				if(multiple == true){
					//std::cout<<"Multiple !!!!"<<std::endl;
					int vertex_save = -1;
					for(uint i =0; i <in_edge_connection.size(); i++){
						if(vertex_save != in_edge_connection.at(i).first){
							uint rec_vertex = -1;
							double rec_weight = 0;
							bool repete = false;
							std::vector<std::pair<double,int>> truc;
							tie(neighbourIto, neighbourEndo) = adjacent_vertices(in_edge_connection.at(i).first,*go1);
							for (; neighbourIto != neighbourEndo; ++neighbourIto){
								if(rec_vertex == *neighbourIto){
									repete = true;
									tie(e1,found)=edge(vertex(in_edge_connection.at(i).first,*go1),vertex(*neighbourIto,*go1),*go1);
									rec_weight += (*go1)[e1]._weight;
								}else{
									if(repete == true){
										neighbourIto--;
										std::pair<double,int> tt;
										tt.first = rec_weight;
										tt.second = *neighbourIto;
										truc.push_back(tt);
										neighbourIto++;
										repete = false;
									}
									tie(e1,found)=edge(vertex(in_edge_connection.at(i).first,*go1),vertex(*neighbourIto,*go1),*go1);
									rec_weight = (*go1)[e1]._weight;
									rec_vertex = *neighbourIto;
								}
							}
							neighbourIto--;
							std::pair<double,int> tt;
							tt.first = rec_weight;
							tt.second = *neighbourIto;
							truc.push_back(tt);
							
							for(uint id = 0; id < truc.size(); id++){
								remove_edge(in_edge_connection.at(i).first,truc.at(id).second,*go1);
								add_edge(in_edge_connection.at(i).first,truc.at(id).second, EdgeProperties("out1","in1",truc.at(id).first), *go1);
							}
							
							vertex_save = in_edge_connection.at(i).first;
						}
					}
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

bool In_tab(const std::vector<int> &tab, int val)
{
    for (uint i = 0; i < tab.size(); i++)
        if(tab[i] == val)
            return true;
    return false;
}

}
