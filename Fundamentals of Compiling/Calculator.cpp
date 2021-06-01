#include <bits/stdc++.h>

using namespace std;
//exp: factor
//| exp '+' factor
//| exp '-' factor
//;
//
//factor: term
//| factor '*' term
//| factor '/' term
//;
//
//term: NUMBER
//| '|' term
//| '(' exp ')'
//| '-' term
//;
//%%

int str_index = 0;
string cacl_str;

void skip_space() {
    while (cacl_str[str_index] == ' ') {
        ++str_index;
    }
}

void index_add() {
    //跳过无用的空格
    skip_space();
    ++str_index;
    skip_space();
}

char get_char() {
    skip_space();
    return cacl_str[str_index];
}

struct Node {
    bool tag;
    double num;

    Node(bool tagg, double numm) {
        tag = tagg;
        num = numm;
    }

    Node operator+(const Node &b) {

        Node node(this->tag & b.tag, this->num + b.num);
        return node;
    }

    Node operator-(const Node &b) {
        Node node(this->tag & b.tag, this->num - b.num);
        return node;
    }

    Node operator*(const Node &b) {

        Node node(this->tag & b.tag, this->num * b.num);
        return node;
    }

    Node operator/(const Node &b) {

        Node node(this->tag & b.tag, this->num / b.num);
        return node;
    }
};

//实现加减法
Node exp();

//实现乘除法
Node factor();

//获取括号中的值
Node term();

//获取一个数字
Node number();

Node exp() {

    Node node = factor();

    if (get_char() == '+') {
        index_add();
        Node node2 = exp();
        return node + node2;
    } else if (get_char() == '-') {
        index_add();
        Node node2 = exp();
        return node - node2;
    }
    return node;
}

Node factor() {
    Node node = term();
    if (get_char() == '*') {
        index_add();
        Node node2 = factor();
        return node * node2;
    } else if (get_char() == '/') {
        index_add();
        Node node2 = factor();
        return node / node2;
    }
    return node;
}

int read_num_char() {
    return cacl_str[str_index++] - '0';
}

Node number() {
    skip_space();
    if (cacl_str[str_index] >= '0' && cacl_str[str_index] <= '9') {
        int tem = 0;
        while (cacl_str[str_index] >= '0' && cacl_str[str_index] <= '9') {
            tem = tem * 10 + read_num_char();
        }
        return Node(true, tem);
    } else {
        return Node(false, 0);
    }
}

Node term() {
    Node node = number();
    if (get_char() == '(') {
        index_add();
        Node node1 = exp();
        if (get_char() == ')') {
            index_add();
            return node1;
        } else {
            return Node(false, 0);
        }
    }
    if (get_char() == '-') {
        index_add();
        Node node1 = term();
        return Node(true, -node1.num);
    }
    return node;
}

int main() {
    cacl_str = "-2+3/2";
    str_index = 0;
    Node pi = exp();
    if (!pi.tag) {
        cout << "错误" << endl;
    }
    cout << pi.num << endl;
}

