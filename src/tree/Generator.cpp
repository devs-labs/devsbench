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

#include <tree/Generator.hpp>

namespace devsbench { namespace tree {

typedef std::vector < int > Entiers;

bool In_tab(const Entiers &tab, int val)
{
    for (uint i = 0; i < tab.size(); i++)
        if(tab[i] == val)
            return true;
    return false;
}

int rand_fini(int a, int b)
{
    return rand() % (b - a) + a;
}

void Generator::brhtg_source(Graph *go,int nbr_vertex, int nbr_source,
                             int nbr_v_min, int nbr_v_max,
                             const std::vector<int> &niveau,
                             std::vector<int> &Ram, std::vector<int> &Exu,
                             const std::vector<vertex_to> &Vertexs,
                             int nbr_passe, int nbr_npb) const
{
    int nbr_voisin;

    int niv=1;
    for(unsigned int j =0; j<niveau.size()-1; j++){
        niv *= niveau.at(j);
    }

    int niv_tot=1;
    for(unsigned int j =0; j<niveau.size(); j++){
        niv_tot *= niveau.at(j);
    }

    for(int b = 0; b<niv; b++){
        std::vector<int> branche;
        int cpt = 0;
        while(cpt != niveau.at(niveau.size()-1)+1){
            branche.push_back((b*niveau.at(niveau.size()-1)+cpt)*nbr_npb);
            cpt++;
        }

        for(unsigned int i =0; i<branche.size()-1;i++){
            for(int j = branche.at(i); j<branche.at(i+1); j++){
                if(j==branche.at(branche.size()-1)-1){
                    break;
                }
                else{
                    nbr_voisin = rand_fini(nbr_v_min, nbr_v_max+1);
                    int cpt=0;
                    Entiers ensemble;
                    int cpt_nbr_s = 0;
                    while(cpt!=nbr_voisin){
                        int val;
                        if(j<branche.at(i)+nbr_source){ // Les sommets sont des sources donc imossible de recevoir des données
                            val = rand_fini(j + 4, j + nbr_v_max + nbr_passe);
                        }
                        else if(j>=branche.at(i)+nbr_npb-nbr_passe && i!= (branche.size()-2)){ // Les sommets sont en fin de branche, nécessité de raccordement avec les autres branches
                            val = rand_fini(branche.at(branche.size()-1)-4, branche.at(branche.size()-1));
                        }
                        else if(j>=branche.at(i)+nbr_npb-nbr_passe && i== (branche.size()-2)){ // Les sommets sont proche de l'exutoire
                            val = rand_fini(j+1,branche.at(branche.size()-1));
                        }
                        else{ // Les sommets sont en plein milieu d'une branche
                            val = rand_fini(j+1, j+nbr_passe);
                        }

                        if(In_tab(ensemble,val)!=1){
                            ensemble.push_back(val);
                            go->addEdge(Vertexs.at(j), 1, Vertexs.at(val), 1);
                            cpt++;
                        }
                        else{
                            if((nbr_vertex-j)==cpt)
                                break;
                            else
                                cpt_nbr_s++;
                        }

                        if(cpt_nbr_s>2*nbr_passe)
                            break;
                    }

                }
            }
        }

        /*for(int i =0; i<branche.size()-1; i++){
          for(int j = branche.at(i)+nbr_source; j<branche.at(i+1); j++){
          (*go)[Vertexs.at(j)] = VertexProperties(j, 1, NORMAL_PIXEL);
          }
          }

          for(int i =0; i<branche.size()-1; i++){
          for(int j = branche.at(i); j<branche.at(i)+nbr_source; j++){
          (*go)[Vertexs.at(j)] = VertexProperties(j, 1, TOP_PIXEL);
          }
          }*/

        Ram.push_back((niv_tot+b)*nbr_npb);
        Exu.push_back(branche.at(branche.size()-1)-1);
    }

    Ram.push_back(Ram.at(Ram.size()-1)+nbr_npb);

    if(niveau.size()>1){
        nbr_voisin = 2;
        for(unsigned int k =0; k<Exu.size(); k++){
            for(int l = Exu.at(k)-2; l<Exu.at(k)+1; l++){
                int cpt=0;
                Entiers ensemble;
                int cpt_nbr_s = 0;
                while(cpt!=nbr_voisin){
                    int val = rand_fini(Ram.at(k),Ram.at(k)+2);

                    if(In_tab(ensemble,val)!=1){
                        ensemble.push_back(val);
                        go->addEdge(Vertexs.at(l), 1, Vertexs.at(val), 1);
                        cpt++;
                    }
                    else{
                        if((nbr_vertex-l)==cpt)
                            break;
                        else
                            cpt_nbr_s++;
                    }

                    if(cpt_nbr_s>2*nbr_passe)
                        break;
                }
            }
        }
    }
}

void Generator::brhtg_ramification(Graph *go, int nbr_vertex, int nbr_v_min,
                                   int nbr_v_max,
                                   const std::vector<int> &niveau,
                                   std::vector<int> &Ram,
                                   std::vector<int> &Exu,
                                   const std::vector<vertex_to> &Vertexs,
                                   int nbr_passe, int nbr_npb) const
{
    int nbr_voisin;
    unsigned int cpt_ram = 1;

    while(cpt_ram != niveau.size()-1){
        int niv=1;
        for(unsigned int j =0; j<niveau.size()-1-cpt_ram; j++){
            niv *= niveau.at(j);
        }

        int niv_tot=0;
        for(unsigned int i =0; i<=cpt_ram; i++){
            int tmp_niv_tot=1;
            for(unsigned int j =0; j<niveau.size()-i; j++){
                tmp_niv_tot *= niveau.at(j);
            }
            niv_tot+=tmp_niv_tot;
        }

        std::vector<std::vector<int> > branche;
        int cpt_b=0;
        for(unsigned int j = 0; j < (Ram.size()-1)/niveau.at(niveau.size()-1-cpt_ram); j++){
            std::vector<int> tmp_branche;
            for(int i =0; i< niveau.at(niveau.size()-1-cpt_ram); i++){
                tmp_branche.push_back(Ram.at(i+cpt_b));
            }
            tmp_branche.push_back(tmp_branche.at(tmp_branche.size()-1)+nbr_npb);
            branche.push_back(tmp_branche);
            cpt_b+=niveau.at(niveau.size()-1-cpt_ram);
        }

        Ram.clear();
        Exu.clear();

        for(int b = 0; b<niv; b++){

            for(unsigned int i =0; i<branche.at(b).size()-1;i++){
                for(int j = branche.at(b).at(i); j<branche.at(b).at(i+1); j++){
                    if(j==branche.at(b).at(branche.at(b).size()-1)-1){
                        break;
                    }
                    else{
                        nbr_voisin = rand_fini(nbr_v_min, nbr_v_max+1);
                        int cpt=0;
                        Entiers ensemble;
                        int cpt_nbr_s = 0;
                        while(cpt!=nbr_voisin){
                            int val;

                            if(j>=branche.at(b).at(i)+nbr_npb-nbr_passe && i!= (branche.at(b).size()-2)){ // Les sommets sont en fin de branche, nécessité de raccordement avec les autres branches
                                val = rand_fini(branche.at(b).at(branche.at(b).size()-1)-4, branche.at(b).at(branche.at(b).size()-1));
                            }
                            else if(j>=branche.at(b).at(i)+nbr_npb-nbr_passe && i== (branche.at(b).size()-2)){ // Les sommets sont proche de l'exutoire
                                val = rand_fini(j+1,branche.at(b).at(branche.at(b).size()-1));
                            }
                            else{ // Les sommets sont en plein milieu d'une branche
                                val = rand_fini(j+1, j+nbr_passe);
                            }

                            if(In_tab(ensemble,val)!=1){
                                ensemble.push_back(val);
                                go->addEdge(Vertexs.at(j), 1,
                                            Vertexs.at(val), 1);
                                cpt++;
                            }
                            else{
                                if((nbr_vertex-j)==cpt)
                                    break;
                                else
                                    cpt_nbr_s++;
                            }

                            if(cpt_nbr_s>2*nbr_passe)
                                break;
                        }

                    }
                }
            }
            Ram.push_back((niv_tot+b)*nbr_npb);
            Exu.push_back(branche.at(b).at(branche.at(b).size()-1)-1);

            /*for(int y =0; y<branche.at(b).size()-1; y++){
              for(int x = branche.at(b).at(y); x<branche.at(b).at(y+1); x++){
              (*go)[Vertexs.at(x)] = VertexProperties(x, 1, NORMAL_PIXEL);
              }
              }*/
        }

        Ram.push_back(Ram.at(Ram.size()-1)+nbr_npb);

        nbr_voisin = 2;
        for(unsigned int k =0; k<Exu.size(); k++){
            for(int l = Exu.at(k)-1; l<Exu.at(k)+1; l++){
                int cpt=0;
                Entiers ensemble;
                int cpt_nbr_s = 0;
                while(cpt!=nbr_voisin){
                    int val = rand_fini(Ram.at(k),Ram.at(k)+2);

                    if(In_tab(ensemble,val)!=1){
                        ensemble.push_back(val);
                        go->addEdge(Vertexs.at(l), 1, Vertexs.at(val), 1);
                        cpt++;
                    }
                    else{
                        if((nbr_vertex-l)==cpt)
                            break;
                        else
                            cpt_nbr_s++;
                    }

                    if(cpt_nbr_s>2*nbr_passe)
                        break;
                }
            }
        }
        cpt_ram++;
    }
}

void Generator::brhtg_exutoire(Graph *go, int nbr_vertex, int nbr_v_min,
                               int nbr_v_max,
                               std::vector<int> &Ram,
                               const std::vector<vertex_to> &Vertexs,
                               int nbr_passe) const
{
    int nbr_voisin;
    Ram.at(Ram.size()-1)=nbr_vertex;

    for(unsigned int i =0; i<Ram.size()-1;i++){
        for(int j = Ram.at(i); j<Ram.at(i+1); j++){
            if(j==Ram.at(Ram.size()-1)-1){
                //(*go)[Vertexs.at(j)] = VertexProperties(j, 1, NORMAL_PIXEL);
                break;
            }
            else{
                if(Ram.at(i+1)-j<nbr_passe)
                    nbr_voisin = 2;
                else
                    nbr_voisin = rand_fini(nbr_v_min, nbr_v_max+1);
                int cpt=0;
                Entiers ensemble;
                int cpt_nbr_s = 0;
                while(cpt!=nbr_voisin){
                    int val;

                    if(j>=Ram.at(i+1)-nbr_passe && i!=Ram.size()-2){ // Les sommets sont proche de l'exutoire
                        val = rand_fini(Ram.at(Ram.size()-1)-4,Ram.at(Ram.size()-1));
                    }
                    else if(j>=Ram.at(i+1)-nbr_passe && i==Ram.size()-2){ // Les sommets sont proche de l'exutoire
                        val = rand_fini(j+1,Ram.at(Ram.size()-1));
                    }
                    else{ // Les sommets sont en plein milieu d'une branche
                        val = rand_fini(j+1, j+nbr_passe);
                    }

                    if(In_tab(ensemble,val)!=1&& j!=val){
                        ensemble.push_back(val);
                        go->addEdge(Vertexs.at(j), 1, Vertexs.at(val),1);
                        cpt++;
                    }
                    else{
                        if((nbr_vertex-j)==cpt)
                            break;
                        else
                            cpt_nbr_s++;
                    }

                    if(cpt_nbr_s>2*nbr_passe)
                        break;
                }

            }
            //(*go)[Vertexs.at(j)] = VertexProperties(j, 1, NORMAL_PIXEL);
        }
    }
}


void Generator::build_graph(Graph *go, int nbr_vertex,
                            int nbr_source, int nbr_v_min,
                            int nbr_v_max,
                            const std::vector<int> &niveau) const
{
    std::vector<vertex_to> Vertexs;

    int nbr_npb;
    int nbr_branche = 0;
    int nbr_passe = 4;

    for(int i =0; i<nbr_vertex; i++){
        vertex_to vo = boost::add_vertex(*go);
        Vertexs.push_back(vo);
    }

    // Calcul du nombre de branches à partir de l'information des niveaux
    for(unsigned int i =0; i< niveau.size(); i++){
        int nbr_tmp =1;
        for(unsigned int j =0; j<=i; j++){
            nbr_tmp *= niveau.at(j);
        }
        nbr_branche += nbr_tmp;
    }

    nbr_npb = nbr_vertex/(nbr_branche);

    std::vector<int> Ram;
    std::vector<int> Exu;

    if(niveau.size()>1){
        /*
         * *** Code Source ***
         */

        brhtg_source(go,nbr_vertex,nbr_source,nbr_v_min,nbr_v_max,niveau,Ram,Exu,Vertexs,nbr_passe,nbr_npb);

        /*
         * *** Code Ramifications ***
         */

        brhtg_ramification(go,nbr_vertex,nbr_v_min,nbr_v_max,niveau,
                           Ram,Exu,Vertexs,nbr_passe,nbr_npb);

        /*
         * *** Code Exutoire ***
         */

        brhtg_exutoire(go,nbr_vertex,nbr_v_min,nbr_v_max,
                       Ram,Vertexs,nbr_passe);

    } else {
        brhtg_source(go,nbr_vertex,nbr_source,nbr_v_min,nbr_v_max,niveau,Ram,Exu,Vertexs,nbr_passe,nbr_npb);
    }

    std::vector < int > dg_in_vertex_list;
    std::vector <vertex_to> dg_vertex_list;
    Graph::vertex_iterator it_dg, end_dg;

    tie(it_dg, end_dg) = vertices(*go);
    for (uint i = 0; it_dg != end_dg; ++it_dg, ++i) {
        dg_in_vertex_list.push_back(0);
        dg_vertex_list.push_back(*it_dg);
    }

    tie(it_dg, end_dg) = vertices(*go);
    for (uint i = 0; it_dg != end_dg; ++it_dg, ++i) {
        Graph::adjacency_iterator neighbour_it, neighbour_end;

        tie(neighbour_it, neighbour_end) = adjacent_vertices(*it_dg, *go);
        for (; neighbour_it != neighbour_end; ++neighbour_it) {
            uint index = 0;

            while (dg_vertex_list[index] != *neighbour_it) {
                ++index;
            }
            ++dg_in_vertex_list[index];
        }
    }

    for(uint i = 0; i<num_vertices(*go); i++){
        (*go)[i] = VertexProperties(i, 1, ATOMIC);
/*        if(dg_in_vertex_list.at(i) == 0){
            (*go)[i] = VertexProperties(i, 1, TOP_PIXEL);
        }else{
            (*go)[i] = VertexProperties(i, 1, NORMAL_PIXEL);
            } */
    }
}

TreeNode* Generator::generate(int nbr_vertex, int nbr_source,
                              int nbr_v_min, int nbr_v_max,
                              const std::vector<int> &niveau) const
{
    TreeNode* root = new TreeNode(0, 0);
    Graph* g = new Graph();

    build_graph(g, nbr_vertex, nbr_source, nbr_v_min, nbr_v_max, niveau);
    root->addGraph(g);
    return root;
}

} } // namespace devsbench tree
