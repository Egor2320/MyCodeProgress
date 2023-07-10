#include <stdio.h>
#include <stdlib.h>

struct BT_node{
  int key;
  int data;
  struct BT_node *left;
  struct BT_node *right;
  struct BT_node *parent;
};

struct BT_node *BT_search (struct BT_node *root, int k){
   struct BT_node *p = root;
    while (p) {
        if (k < p->key) p = p->left;
        else if (k > p->key)p = p->right;
        else return p;
    }
    return NULL;
}
struct BT_node *BT_min(struct BT_node *root){
  struct BT_node *p = root;
  while (p->left){
    p = p->left;
  }
  return p;
}

struct BT_node *BT_succ(struct BT_node *node){
  struct BT_node *p = node, *q;
  if(p->right){
    return BT_min(p->right);
  }
  q = p->parent;
  while (q && p == q->right){
    p = q;
    q = q->parent;
  }
  return q;
}

struct BT_node *createNode(int key, int data){
  struct BT_node *new = (struct BT_node *)malloc(sizeof(struct BT_node));
  new->data = data;
  new->key = key;
  new->left = new->right = new->parent = NULL;
  return new;
}

struct BT_node *BT_insert(struct BT_node *root, int key, int data){
  struct BT_node *tmp = root;
  struct BT_node *prev = NULL;
  while (tmp) {
      prev = tmp;
      if (key < tmp->key) tmp = tmp->left;
      else if (key > tmp->key) tmp = tmp->right;
      else break;
  }
  if (prev) {
      if (prev->key == key) prev->data = data;
      else {
        struct BT_node *new = createNode(key, data);
        new->parent = prev;
        if (prev->key < key) prev->right = new;
        else prev->left = new;
      }
      return root;
  }
  else return createNode(key, data);

}

 struct BT_node *BT_delete(struct BT_node *root, int key) {
    struct BT_node *tp;
    if (root == NULL) 
      return NULL;
    else if (key < root->key) 
      root->left = BT_delete(root->left, key);
    else if (key > root->key) 
      root->right = BT_delete(root->right, key);
    else if (root->left && root->right) {
        tp = BT_min(root->right);
        root->key = tp->key;
        root->data = tp->data;
        root->right = BT_delete(root->right, root->key);
    } 
    else {
        tp = root;
        if (root->left == NULL) 
          root = root->right;
        else if (root->right == NULL) 
          root = root->left;
        free(tp);
    }
    return root;
}

void tfree(struct BT_node *root) {
    if (!root) return;
    tfree(root->left);
    tfree(root->right);
    free(root);
}


int main (void){
  char op;
  int key, data;
  struct BT_node *root = NULL;
  while ((op = getchar()) != 'F'){
    if (op == 'A'){
      scanf("%d %d", &key, &data);
      root = BT_insert(root, key, data);
    }
    else if(op == 'S'){
      scanf("%d", &key);
      struct BT_node *p = BT_search(root, key);
      if(p){
        printf("\n");
        printf("%d %d", key, p->data);
      }
    }
    else if (op == 'D'){
      scanf("%d", &key);
      root = BT_delete(root, key);
    }
    scanf("\n");
  }
  tfree(root);
  return 0;
}