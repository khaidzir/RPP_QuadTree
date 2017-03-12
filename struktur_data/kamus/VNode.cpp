#include "VNode.h"
#include <cstdlib>
#include <cstdio>

VNode::VNode() {
    this->left = NULL;
    this->right = NULL;
}

VNode::VNode(char ch) {
    //ctor
    this->info = ch;
    this->left = NULL;
    this->right = NULL;
}

VNode::VNode(const VNode& other) {
    this->info = other.info;
    this->left = other.left;
    this->right = other.right;
}

VNode& VNode::operator=(const VNode& other) {
    this->info = other.info;
    this->left = other.left;
    this->right = other.right;
    return *this;
}

VNode::~VNode() {
    //dtor
}

void VNode::print() {
    printf("%c",this->info);
}
