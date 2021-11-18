typedef struct Node{
    int x;
    int y;
    int move;
    int visited;
    struct Node* right;
    struct Node* down;

}node;

typedef struct List{
    node* head;
    struct List* bottom;
}list;

typedef struct co_ordinates{
    int x;
    int y;
    int distance;

}cod;

typedef struct Stack{
    node* a[1000];  
    int top;  
}stack;

void init(list** p);
void create(list** p);
void add_element(list** p,int buffer[]);
void add_lists(list** p);
void display(list* p);
node* create_node(int x,int y,int ele);
void establish_down_link(list** p);
void bot_path(list** p);
void init_visited(list** p);