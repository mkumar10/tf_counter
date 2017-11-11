#include <iostream>
#include <regex>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;

/*
 *   read_file_names:
 *    creates vector of file names
 *   Parameters:
 *    file_list : vector of file names
 *    files_list_ : path to file_list.txt
 *   Returns:
 *    None
 */
void read_file_names(vector<string> &file_list,string files_list_)
{
  ifstream input(files_list_);
  for(string file_name; getline( input, file_name ); )
  {
      file_list.push_back(file_name);
  }
  return;
}

/*
 *   read_word_list:
 *    creates vector of words to find tf of
 *   Parameters:
 *    file_list : vector of words
 *    files_list_ : path to word_list.txt
 *   Returns:
 *    None
 */
void read_word_list(vector<string> &word_list,string words_list_)
{
  ifstream input_words(words_list_);
  for(string word; getline( input_words, word ); )
  {
      word_list.push_back(word);
  }
  return;
}

/*
 *   process_file:
 *    creates vector of words in a file
 *    converts them to lower case and removes punctuation
 *   Parameters:
 *    file_name : name of file
 *   Returns:
 *    vector of type string
 */
vector<string> process_file(string file_name)
{
  ifstream file(file_name);
  string str;
  string file_contents;
  while (getline(file, str))
  {
    file_contents += str;
    file_contents.push_back('\n');
  }
  transform(file_contents.begin(),file_contents.end(),file_contents.begin(),::tolower);
  istringstream iss(file_contents);
  string word;
  vector<string> cur_file;
  while(iss >> word)
  {
    // Remove punctuation
    word.erase(std::remove_if(word.begin(), word.end(),
                  [](char ch){ return !::iswalnum(ch); }), word.end());
    cur_file.push_back(word);
  }
  return cur_file;
}

/*
 *   update_dict:
 *    updates global dictionary of all unique words in all documents
 *   Parameters:
 *    word_idx_dict : dictionary maps word to a unique index
 *    cur_file : words in a documented in the form of a vector
 *   Returns:
 *    None
 */
void update_dict(unordered_map<string,int> &word_idx_dict,vector<string> cur_file)
{
    for(auto str: cur_file)
    {
      if(word_idx_dict.find(str)==word_idx_dict.end())
      {
        word_idx_dict[str] = word_idx_dict.size();
      }
    }
    return;
}
