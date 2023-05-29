#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define int long long

#define MAXN 100005
#define mod 1000000007

const int inf=INT_MAX;
typedef struct Node{
    int val, size, cnt, w, a, b, up, down;
    struct Node *l, *r;
} Node;

Node *new_node(int x,int a,int b){
    Node* node = (Node*) malloc(sizeof(Node));
    node->val=x;
    node->size=1;
    node->cnt=1;
    node->w=rand();
    node->l=NULL;
    node->r=NULL;
    node->a=a;
    node->b=b;
    node->up=a;
    node->down=b;
    return node;
}

Node *root;

int size(Node *node){
    return node ? node->size : 0;
}

void update_son(Node* node){
    node->size=node->cnt;
    if(node->l==NULL && node->r==NULL) {
        node->up=node->a;
        node->down=node->b;   
        return;
    }

    if(node->r == NULL) {
        node->size+=node->l->size;

        if(node->l->size & 1) node->up = node->l->up + node->b;
        else node->up = node->l->up + node->a;
        
        if(node->l->size & 1) node->down = node->l->down + node->a;
        else node->down = node->l->down + node->b;
    }else if(node->l == NULL) {
        node->size+=node->r->size;
        node->up=node->a + node->r->down;
        node->down=node->b + node->r->up;
    }else{
        node->size+=node->l->size;
        node->size+=node->r->size;
        if(node->l->size & 1) node->up = node->l->up + node->b + node->r->up;
        else node->up = node->l->up + node->a + node->r->down;
        
        if(node->l->size & 1) node->down = node->l->down + node->a + node->r->down;
        else node->down = node->l->down + node->b + node->r->up;
    }
}

void left_rotate(Node** a){
    Node* b=(*a)->r;
    (*a)->r=b->l;
    b->l=(*a);
    (*a)=b;
    update_son((*a));
    update_son((*a)->l);
}

void right_rotate(Node** a){
    Node* b=(*a)->l;
    (*a)->l=b->r;
    b->r=(*a);
    (*a)=b;
    update_son((*a));
    update_son((*a)->r);
}

void insert(Node** node, int a,int b){
    int val=b-a;
    if(root==NULL){
        root=new_node(val,a,b);
        return;
    }
    if(!(*node)){
        (*node)=new_node(val,a,b);
        return;
    }
    if(val > (*node)->val || (val == (*node)->val && a < (*node)->a)){
        insert(&((*node)->l), a, b);
        if((*node)->l->w < (*node)->w) right_rotate(node);
    }else{
        insert(&((*node)->r), a, b);
        if((*node)->r->w < (*node)->w) left_rotate(node);
    }
    update_son((*node));
}

void del(Node** node, int a, int b){
    int val = b - a;
    if (val > (*node)->val || (val == (*node)->val && a < (*node)->a)) del(&(*node)->l, a, b);
    else if ((*node)->val > val || (val == (*node)->val && a > (*node)->a)) del(&(*node)->r, a, b);
    else {
        if ((*node)->l == NULL && (*node)->r == NULL) {
            free(*node);
            *node = NULL;
            return;
        }
        if ((*node)->l == NULL) {
            left_rotate(node);
            del(&(*node)->l, a, b);
        } else if ((*node)->r == NULL) {
            right_rotate(node);
            del(&(*node)->r, a, b);
        } else {
            if ((*node)->l->w < (*node)->r->w) {
                right_rotate(node);
                del(&(*node)->r, a, b);
            } else {
                left_rotate(node);
                del(&(*node)->l, a, b);
            }
        }
    }
    update_son((*node));
}

void swap(int *a,int *b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

// void pre_order(Node *cur){
//     if(cur == NULL) return;
//     pre_order(cur->l);
//     printf("%lld %lld %lld %lld\n",cur->a, cur->b, cur->up, cur->down);
//     pre_order(cur->r);
// }

int A[MAXN],B[MAXN];

signed main(){
    int n,m;
    scanf("%lld %lld",&n,&m);
    for(int i=1;i<=n;i++){
        int a,b;
        scanf("%lld %lld",&A[i],&B[i]);
        if(A[i]>B[i]) swap(&A[i],&B[i]);
        insert(&root,A[i],B[i]);
    }
    printf("%lld\n",root->up);
    m--;
    while(m--){
        long long pre_ans=root->up%mod;

        int t,m1,m2,a1,a2;
        scanf("%lld %lld %lld %lld %lld", &t, &m1, &a1, &m2, &a2);
        
        del(&root,A[t],B[t]);
        
        A[t]=(pre_ans*m1%mod+a1)%mod;
        B[t]=(pre_ans*m2%mod+a2)%mod;
        
        if(A[t]>B[t]) swap(&A[t],&B[t]);
        insert(&root,A[t],B[t]);

        printf("%lld\n",root->up);
    }
}
