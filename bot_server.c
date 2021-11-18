#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "bot_head.h"
cod start,end;
void init(list** p){
    *p=NULL;
}

node* create_node(int x,int y,int ele){
    node* tmep=(node*)malloc(sizeof(node));
    tmep->x=x;
    tmep->y=y;
    tmep->right=tmep->down=NULL;
    tmep->move=ele;
    tmep->visited=0;
    return tmep;
}

void add_element(list** p,int buffer[]){
    //only adding elements to i'th linked list
    static int flag=0;
    static int count=0;
    list* q=*p;
    int a=flag;
    while (a--)
        q=q->bottom;
    node* temp;
    node* qnode;
    node* inithead=create_node(0,flag,buffer[0]);
    q->head=inithead;
    for(int i=1;i<10;i++){
        qnode=inithead;
        temp=create_node(i,flag,buffer[i]);
        while(qnode->right!=NULL){
            qnode=qnode->right;
        }
        qnode->right=temp; 
    }
    flag++;
}

void add_lists(list** p){
    // static int count=0;
    list* temp;
    for(int i=0;i<10;i++){
        temp=(list*)malloc(sizeof(list));
        temp->bottom=NULL;
        temp->head=NULL;
        list* q=*p;
        list* q_prev=NULL;
        if(*p==NULL){
            *p=temp;
        }else{
            while(q!=NULL){
                q_prev=q;
                q=q->bottom;
            }
            q_prev->bottom=temp;
        }
    }
}

//crating vertical links for all the nodes in the linked list
void establish_down_link(list** p){
    list* q=*p;
    node* prev=q->head;
    node* pres=q->bottom->head;
    while(q->bottom!=NULL)
    {
        for(int j=0;j<10;j++){
            prev->down=pres;
            prev=prev->right;
            pres=pres->right;
        }
        q=q->bottom;
        if(q->bottom!=NULL){
        prev=q->head;
        pres=q->bottom->head;
        }
    }
}

void create(list** p){
    FILE *fp=fopen("input.txt","r");
    if(fp==NULL)   printf("Empty file");
    else{
        //creating 10 lists
        add_lists(p);
        //extracting the data && adding it to each of 10 linked list
        int ch;
        int buffer[20];
        fscanf(fp,"%d",&start.x);
        fscanf(fp,"%d",&start.y);
        fscanf(fp,"%d",&end.x);
        fscanf(fp,"%d",&end.y);
        // printf("start-(%d,%d) end-(%d,%d)\n",start.x,start.y,end.x,end.y);
        while (!feof(fp)){
            for(int i=0;i<10;i++){
                fscanf(fp,"%d",buffer+i);
            }
            //adding elements list wise
            add_element(p,buffer);
        }
        establish_down_link(p);

    } 
}

void display(list* p){
    printf("Mulit List elements\n");
    list* temp=p;
    while (temp!=NULL){
        node* temp_node=temp->head;
        while (temp_node!=NULL){
            printf(" %d -(%d,%d) ",temp_node->move,temp_node->x,temp_node->y);
            temp_node=temp_node->right;
        }
        temp=temp->bottom;
        printf("\n");
    }
}

// ----------------------------------------------
// bot movement

void bot_path(list** p){
    
        int count=0;
        stack s;
        list* q=*p;
        s.top=-1;
        node* temp=q->head;
        temp->visited=1;
        s.a[++s.top]=temp;
        //Traversing the whole list to find the path 
        while (1)
        {
            if(temp->right!=NULL && !temp->right->move && !temp->right->visited){
                temp=temp->right;
                temp->visited=1;
                s.a[++s.top]=temp;
                // printf("add1-(%d,%d)",temp->x,temp->y);
            }else if (temp->down!=NULL && !temp->down->move && !temp->down->visited){
                temp=temp->down;
                temp->visited=1;
                s.a[++s.top]=temp;
                // printf("add2-(%d,%d)",temp->x,temp->y);
            }else if (temp->right==NULL || temp->down==NULL ||(temp->right->visited && temp->down->visited)|| temp->down->move==1 || temp->right->move==1 ){
                temp=s.a[--s.top];
                // printf("pop-(%d,%d)",temp->x,temp->y);
            } 
            if((temp->x==end.x && temp->y==end.y)||(temp->x==start.x && temp->y==start.y)){
                break;
            }
        }
        FILE* fpo=fopen("output.txt","w");
        //checking if there is no path for specified table
        if(s.top==-1){
            fprintf(fpo,"%d",-1);
        }else{
            int n=s.top;
            cod arr[100];
            while (s.top!=-1)
            {
                arr[n-s.top].x=s.a[s.top]->x;
                arr[n-s.top].y=s.a[s.top]->y;
                arr[n-s.top].distance=pow(s.a[s.top]->x,2)+pow(s.a[s.top]->y,2);
                s.top--;
            }
            printf("%d",s.top);
            //sorting the co_ordintes structure
            int min;
            for(int i=0;i<n-1;i++){
                min=i;
                for(int j=i;j<n;j++){
                    if(arr[min].distance>arr[j].distance)
                        min=j;
                }
                if(i!=min){
                    cod dummy=arr[min];
                    arr[min]=arr[i];
                    arr[i]=dummy;
                }
            }

            //writng the sorted 
            for(int i=0;i<n;i++){
                fprintf(fpo,"%d %d\n",arr[i].x,arr[i].y);
            }
        }



}