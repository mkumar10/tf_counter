#include <iostream>
#include <regex>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <unordered_map>

/*
 *   initialise_tf_matrix:
 *    initialises matrix for term frequency
 *    each row corresponds to a word
 *    each col corresponds to a document
 *   Parameters:
 *    term_frequency : matrix of term frequencies
 *    num_files : total number of documents
 *    num_words : total number of words
 *   Returns:
 *    None
 */
void initialise_tf_matrix(vector<vector<double>> &term_frequency,int num_files,int num_words)
{
  for(int i=0;i<num_words;i++)
  {
    vector<double> per_word;
    per_word.resize(num_files,0.0);
    term_frequency.push_back(per_word);
  }
}

/*
 *   update_tf_matrix:
 *    updates the matrix of term frequencies
 *    by iterating through all documents
 *   Parameters:
 *    term_frequency : matrix of term frequencies
 *    word_idx_dict : dictionary maps word to a unique row index in the matrix
 *    cur_file : words in a documented in the form of a vector
 *    cur_idx : index of the document being processed
 *   Returns:
 *    None
 */
void update_tf_matrix(vector<vector<double>> &term_frequency,unordered_map<string,int> word_idx_dict,vector<string> cur_file,int cur_idx)
{
  for(auto str:cur_file)
  {
    term_frequency[word_idx_dict[str]][cur_idx] += 1.0;
  }
  for(int i=0;i<term_frequency.size();i++)
  {
    term_frequency[i][cur_idx] /= double(cur_file.size());
  }
  return;
}

/*
 *   find_max_tf:
 *    finds the index of the document with the max term frequency
 *   Parameters:
 *    word_tf : vector of term frequencies of a particular word in all documents
 *   Returns:
 *    an integer value
 */
int find_max_tf(vector<double> word_tf)
{
  return distance(word_tf.begin(), max_element(word_tf.begin(), word_tf.end()));
}
