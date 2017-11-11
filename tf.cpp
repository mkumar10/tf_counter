#include <iostream>
#include <regex>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "process_document.cpp"
#include "TermFrequency.cpp"

using namespace std;

/*
 *   create_tf_matrix:
 *    creates the term frequency matrix
 *   Parameters:
 *    file_list : vector of file names
 *    word_idx_dict : dictionary maps word to a unique row index in the matrix
 *    term_frequency : matrix of term frequencies
 *   Returns:
 *    None
 */
void create_tf_matrix(vector<string> file_list,unordered_map<string,int> &word_idx_dict,vector<vector<double>> &term_frequency)
{
  for(auto fil: file_list)
  {
    auto cur_file = process_file(fil);
    update_dict(word_idx_dict,cur_file);
  }
  auto num_words = word_idx_dict.size();
  auto num_files = file_list.size();
  initialise_tf_matrix(term_frequency,num_files,num_words);
  for(auto idx = 0;idx<num_files;idx++)
  {
    auto cur_file = process_file(file_list[idx]);
    update_tf_matrix(term_frequency,word_idx_dict,cur_file,idx);
  }
  return;
}
int main()
{
  vector<string> file_list;
  read_file_names(file_list,"file_list.txt");
  unordered_map<string,int> word_idx_dict;
  vector<vector<double>> term_frequency;
  vector<string> word_list;
  create_tf_matrix(file_list,word_idx_dict,term_frequency);
  read_word_list(word_list,"word_list.txt");
  for(auto word:word_list)
  {
    cout<<"The tf's for the word "<<word<<" are:"<<endl;
    for(int i=0;i<file_list.size();i++)
    {
      cout<<term_frequency[word_idx_dict[word]][i]<<" ";
    }
    cout<<endl;
    auto max_tf_idx = find_max_tf(term_frequency[word_idx_dict[word]]);
    cout<<"The max tf for "<<word<<" is "<<term_frequency[word_idx_dict[word]][max_tf_idx]<<" in the document "<<file_list[max_tf_idx]<<endl;
  }


  return 0;
}
