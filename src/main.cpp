#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<string>
#include<list>
using namespace std;

class tag
{
public:
    string tagName;
    vector<string>attributes;
    tag();
    tag(string,vector<string>);
    void setTagName(string);
    friend ostream& operator<<(ostream&,tag);
};


ostream& operator<<(ostream& o,tag t)
{
    o<<t.tagName<<" ";
    for(string s:t.attributes)
    {
        o<<s<<" ";
    }
    return o;
}
tag::tag(string name,vector<string>attributes)
{
    this->tagName = name;
    this->attributes = attributes;
}

tag::tag()
{
    this->tagName="";
    this->attributes = {};
}

void tag::setTagName(string name)
{
    this->tagName = name;
}


tag ProccesTag(string s)
{
    s.append(" ");
    string space_delimiter = " ";
    vector<string> words{};
    vector<string> atts;

    size_t pos = 0;
    while ((pos = s.find(space_delimiter)) != string::npos) {
        words.push_back(s.substr(0, pos));
        s.erase(0, pos + space_delimiter.length());
    }
    

    words[words.size()-1].erase(remove(words[words.size()-1].begin(), words[words.size()-1].end(), '>'), words[words.size()-1].end());
    for(int i=1;i<words.size();i++)
    {
        // string attribute = words[i].substr(words[i].find_first_of("'")+1,words[i].find_last_of("'")-words[i].find_first_of("'")-1);
        //    size_t end1 = words[i].find_first_of("'");
        //    string part1 = words[i].substr(end1+1);
        //    size_t end2 = part1.find_first_of("'");
        //    string part2 = part1.substr(0,end2);
        
        
        atts.push_back(words[i]);
    }
        
    words[0].erase(remove(words[0].begin(), words[0].end(), '<'), words[0].end());
    
    tag tag(words[0],atts);
    return tag;
}


class Node{
public:
    tag tagData;
    vector<Node*> child;
    Node(tag);
};

Node::Node(tag data)
{
    this->tagData=data;
}

void LevelOrderTraversal(Node* root)
{
    if(root==nullptr)
    return;

    list<Node*> queue;
    queue.push_back(root);
    Node* curr = nullptr;
    string name;
    while(queue.size())
    {
        curr = queue.front();
        queue.pop_front();

        cout<<curr->tagData<<" ";
        name+=curr->tagData.tagName+".";
        for(int i=0;i<curr->child.size();i++)
        {
            queue.push_back(curr->child.at(i));
        }
    }
    cout<<name;
}

int main() 
{
    int n,q;
    cin>>n;
    vector<tag>tags;
    string input;
    for (int i=0; i<=n; i++) 
    {
        getline(cin,input,'\n');
        tag inputTag = ProccesTag(input);
        tags.push_back(inputTag);
    }
    tags.erase(tags.begin());
    
    Node* root = new Node(tag("a",{}));
    root->child.push_back(new Node(tag("b",{})));
    root->child.push_back(new Node(tag("c",{})));
    root->child.push_back(new Node(tag("d",{})));
    root->child[0]->child.push_back(new Node(tag("e",{})));
    LevelOrderTraversal(root);

    /*
    for(int i=tags.size()-1;i>0;i--)
    {
        if(tags.at(i).tagName != "")
        {
            cout<<"<"<<tags.at(i).tagName<<"/>"<<endl;
        }
    }
    */

    //TODO
    /*
    proccess qris 
    cin q
    check for tag name
    if found call ProccesQU func : params - tag.atributes
    */

    return 0;
}
