#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

/*
   The file menuTree.c should be compile with command 
   $ gcc menuTree.c -o menuTree
   $ menuTree
    
*/

typedef struct menu node;
node * createNode(int c, int nodeID, char* text, node* p);


struct menu {
    int count;
    int nodeID;
    char textLabel[30];
    node *children;

} ;

node* createNode(int c, int nodeID, char* text, node *p) {
    node* new = (node*)malloc(sizeof(node));
    new -> count = c;
    new-> nodeID = nodeID;
    strcpy(new->textLabel,text);
    new -> children = (node*)malloc(sizeof(node));
    if(p!=NULL){
    }
    return new;
}




void addChild(node* child, node* parent){

    parent -> children = (node*)realloc((parent -> children), (parent -> count+1)*sizeof(node));
    parent -> children[parent -> count] = *child;
    parent -> count+=1;
}

node* search(node* start, int ID){
    node* current = start;
    //printf("Current node searched %s\n", current -> textLabel);
    //printf("Current node id %d, id that is needed %d\n", current -> nodeID, ID);
    if(current ->nodeID == ID){
        //printf("Current node returning %s\n", current -> textLabel);
        return current;
    }
    else{
        for( int i = 0; i<current -> count; i++){

            if (search(&(current -> children[i]), ID)!=NULL){
                return &(current -> children[i]) ;
            }
        }
        return NULL;
    }
}

int getLabel(int node, int size, int *id){
      for(int i = 0; i<size; i++){
          if(id[i] == node){
          return i;
          }
      }
      return 0;

}

/*
void display(node* n, int x, int start){
    int c[x];
    c[start] = n->nodeID;
    if(n->count==0){
       printf("%3d",c[0]);
       for(int i=0;int<start;i++){
       printf("%.d",c[i]);
       }
       printf(" %s\n", n->textLabel);
       }
       else{
           for(int j=0; j<n->count; j++)
       
    

    }
}
*/
int main(){
    

    FILE *f;
    char input[200];
    int count_nodes=0;
    node *head;
    int ID;
    int items = 100;
    int char_length = 30;
    char labels[items][char_length];
    int id[items];
    char name;
    
    printf("Please choose a file: ");
    if(scanf("%[^\n]s",input )==1){
    	
       if ((f = fopen(input, "r"))!=NULL){
       		printf("Parameter listing: \n");
       		printf("%3d input filename: %s\n", 1, input); 
       		printf("Data values read from file: ");
       		while ((name= fgetc(f)) != EOF){

        		if(name=='A'){
            		fscanf(f, "%d%[^\n]s",&id[count_nodes], labels[count_nodes]);
            
            		fgetc(f);
            		printf("%d: %s\n",id[count_nodes],labels[count_nodes]);
            		count_nodes++;


        }
        else{
           

            int ch;
            int par;


            fscanf(f, "%4d%4d",  &ch, &par);
            fgetc(f); 
            printf(" child %d, parent %d\n", ch, par); 

            //printf("PN is %d and CH id %d\n", par, ch);
            if (par==0){
                node* root;
                root = createNode(0, ch,labels[getLabel(ch, items, id)], NULL);
                head = root;

            }
            else{

                //printf("\nCurren Parent node is %s with id %d \n", labels[getLabel(ch, items, id)], ch);

                node* x = search(head, par);
                if(x!=NULL){
                    //printf("\nNode name %s\n", x->textLabel);
                    node* child= createNode(0, ch, labels[getLabel(ch, items, id)], x);
                    addChild(child, x);
                    //printf("Child added %s\n", child->textLabel);

                }

            }

        }
    }
    }
    else{
        printf("Unable to open the file, error %d - %s\n",errno, strerror(errno));
        main();
         
        exit(1);
    }
    }
    
    


    fclose(f);



    return 0;
}

