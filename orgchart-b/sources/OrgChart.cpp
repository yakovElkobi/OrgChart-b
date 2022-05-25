
#include "OrgChart.hpp"
using namespace std;

namespace ariel{

    OrgChart &OrgChart::add_root(string name){
        if(name.empty()){
            throw invalid_argument("root is empty:");
        }
        this->_root._name = move(name);
        return *this;
    }
    OrgChart &OrgChart::add_sub(const string &father, const string &son){
        if(son.empty()){
            throw invalid_argument("son is empty:");
        }
        if(!find(this->_root, father, son)){
            throw invalid_argument(father + "not found");
        }
        return *this;
    }
    bool OrgChart::find(Node &curr_node, const std::string &father, const std::string &son) {
        int b = curr_node._name.compare(father);
        if(b==0){
            Node new_node;
            new_node._name = son;
            curr_node._children.push_back(new_node);
            return true;
        }
        for(size_t i = 0; i < curr_node._children.size(); ++i){
            if(find(curr_node._children.at(i), father, son)){
                return true;
            }
        }
        return false;
    }
    string *OrgChart::begin_level_order(){
        if(this->_root._name.empty()){
            throw runtime_error("is empty:");
        }
        this->_levelOrder.clear();
        fill_level_order(this->_root);
        return &this->_levelOrder.at(0);
    }
    void OrgChart::fill_level_order(Node &root) {
        queue<Node*> q;
        q.push(&root);
        while (!q.empty()){
            Node *temp = q.front();
            this->_levelOrder.push_back(temp->_name);
            q.pop();
            for(size_t i = 0; i < temp->_children.size(); ++i){
                q.push(&temp->_children.at(i));
            }
        }
    }
    string *OrgChart::begin_preorder(){
        if(this->_root._name.empty()){
            throw runtime_error("is empty:");
        }
        this->_preOrder.clear();
        fill_preorder(this->_root);
        return &_preOrder[0];
    }
    void OrgChart::fill_preorder(Node &root) {
        this->_preOrder.push_back(root._name);
        for(size_t i = 0; i < root._children.size(); ++i){
            fill_preorder(root._children.at(i));
        }
    }
    string *OrgChart::begin_reverse_order(){
        if(this->_root._name.empty()){
            throw runtime_error("is empty:");
        }
        this->_reverseOrder.clear();
        this->fill_reverse_order(this->_root);
        return &this->_reverseOrder.at(0);
    }
    void OrgChart::fill_reverse_order(Node &root) {
        queue<Node*> q;
        stack<string> s;
        q.push(&root);
        while (!q.empty()){
            Node *temp = q.front();
            s.push(temp->_name);
            q.pop();
            for(int i = (int)temp->_children.size()-1; i >=0; --i){
                q.push(&temp->_children.at((size_t)i));
            }
        }
        while (!s.empty()){
            this->_reverseOrder.push_back(s.top());
            s.pop();
        }
    }
    string *OrgChart::end_level_order(){
        if(this->_root._name.empty()){
            throw runtime_error("is empty:");
        }
        return &this->_levelOrder[this->_levelOrder.size()];
    }
    string *OrgChart::end_preorder(){
        if(this->_root._name.empty()){
            throw runtime_error("is empty:");
        }
        return &this->_preOrder[this->_preOrder.size()];
    }
    string *OrgChart::reverse_order(){
        if(this->_root._name.empty()){
            throw runtime_error("is empty:");
        }
        return &this->_reverseOrder[this->_reverseOrder.size()];
    }
    ostream &operator<<(ostream &out, OrgChart &root){
        for(auto *it = root.begin_level_order(); it != root.end_level_order(); ++it){
            out << *it <<endl;
        }
        return out;
    }
}