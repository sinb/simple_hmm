#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "hmm.hpp"
using namespace std;
int main(int argc, char **argv) {
    
    // 1. 状态集合:
    string states[] = {"Rainy", "Sunny"};
    int length_states = sizeof(states)/sizeof(states[0]);
    // 2. 观测集合:    
    string observations[] = {"walk", "shop", "clean"};    
    int length_obs = sizeof(observations)/sizeof(observations[0]);
    // 3. 初始概率
    map<string, double> start_probability;
    start_probability["Rainy"] = 0.6;
    start_probability["Sunny"] = 0.4;

    // 4. 状态转移概率
    /*	其实是一张表
	    Rainy 	Sunny
    Rainy    0.7	 0.3
    Sunny    0.4	 0.6	
    */
    map<string, map<string, double>> transition_probability;
    transition_probability["Rainy"].insert(make_pair("Rainy", 0.7));
    transition_probability["Rainy"].insert(make_pair("Sunny", 0.3));
    transition_probability["Sunny"].insert(make_pair("Rainy", 0.4));
    transition_probability["Sunny"].insert(make_pair("Sunny", 0.6));
       
    // 5. 发射概率
    /*		walk	shop	clean
     * Rainy	0.1	0.4	0.5
     * Sunny	0.6	0.3	0.1
    */
    map<string, map<string, double>> emission_probability;
    emission_probability["Rainy"].insert(make_pair("walk", 0.1));
    emission_probability["Rainy"].insert(make_pair("shop", 0.4));
    emission_probability["Rainy"].insert(make_pair("clean", 0.5));
    emission_probability["Sunny"].insert(make_pair("walk", 0.6));
    emission_probability["Sunny"].insert(make_pair("shop", 0.3));    
    emission_probability["Sunny"].insert(make_pair("clean", 0.1));
    // 辅助数组
    map<string, double*> weight;
    // 辅助数组
    map<string, string*> path;
    // 输出 维特比路径
    deque<string> viterbi_path;
    HMM hmm(length_states, length_obs, states, observations, start_probability, transition_probability, emission_probability);  
    string end_state = hmm.Viterbi(weight, path);
    hmm.backtrack(end_state, path, viterbi_path);
    for (auto it = viterbi_path.begin(); it != viterbi_path.end(); it++)
      cout << *it << " ";


    
    return 0;
}
