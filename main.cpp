#include <iostream>
#include <string>
#include <list>
#include <filesystem>
#include "helperFunctions.hpp"
#include "divastar.hpp"
#include "node.hpp"
#include "entry.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
    helperFunctions helpers;
    if(argc != 3)
    {
        cout << "To run the program: './main searchTerm kValue'\n";
        exit(1);
    }
    else
    {
        string query = argv[1];
        int k = stoi(argv[2]);

        helperFunctions help;
        std::map<string, std::map<string, std::vector<float>>> scores = help.calculate_keyword_scores();


        std::map<string, float> relevant_scored_nodes = help.calculate_doc_scores(scores, query);

        for(auto it = relevant_scored_nodes.cbegin(); it != relevant_scored_nodes.cend(); it++)
        {
            cout << it->first << "\t" << it->second << endl;
        }

        //help.topK(filename,query,k);

        vector<node> adj_list;
        string edgesFromPaper[6] = {"10 5 3 4", "8 5 3 4", "7 1 2 6", "7 1 2 6", "6 1 2 6", "1 5 3 4"};
        // make k nodes for the graph (since its a top-k result graph as input for div astar)
        // this will change from k to the # of nodes from the dataset they selected.
        for(int i = 0; i < 6; i++)
        {
            string test = edgesFromPaper[i];
            node temp = node("0",(i+1));
            adj_list.push_back(temp);
            adj_list.at(i).addEdges(test);
        }
        divastar div;
        auto result = div.doDivAStar(&adj_list,k);
        auto answer = result.getSolution();
        cout << "final answer alex: \n";
        
        for(int i = 0; i < answer.size(); i++)
        {
            cout << answer.at(i).getNodeNum() << endl;
        }
        /*
        node s;
        s.setNodeNum(3);
        s.addEdges("7 1 2 6");

        entry node3;
        node3.addSolution(s);
        node3.setScore(7);

        int upperBound = div.astarBound(&adj_list,&node3,3);
        cout << upperBound << endl;
        */


        //helperFunctions help;
        //help.topK(filename,query,k);
    }
    return 0;
}
