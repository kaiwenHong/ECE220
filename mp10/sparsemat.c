//This program takes large matricies and does basic calculations with them. This also implements linkedlists. 
//partners: Luis aragon (laragon1), Manan Mittal (manansm2)
#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>
sp_tuples * load_tuples(char* input_file)
{
  FILE *fptr=fopen(input_file,"r");//opening file
  sp_tuples *list=(sp_tuples*) malloc(sizeof(sp_tuples));
  fscanf(fptr,"%d %d",&list->m, &list->n);// getting width and height
  fgetc(fptr);
  list->nz=0;
  list->tuples_head=NULL;
  int row,col;
  double value;
  while(fscanf(fptr,"%d %d %lf", &row, &col, &value)!=EOF) {

     set_tuples(list,row,col,value);//calls set tuples

   }
  fclose(fptr);
  return list;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    sp_tuples_node *current;
    current=mat_t->tuples_head;
    while(current!=NULL)
    {
      if(current->row==row && current->col==col)
      return current->value;
      else
      current=current->next;
    }

    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
  if(mat_t->tuples_head==NULL)
  {
    sp_tuples_node *new =(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    new->row=row;
    new->col=col;
    new->value=value;
    new->next=NULL;
    mat_t->tuples_head=new;
    mat_t->nz++;
    return;
  }
  else
  {

      sp_tuples_node * prevNode = NULL;

     // initialize current stuff
     sp_tuples_node * curr;
     curr = mat_t->tuples_head;

     // loop through entire linked list
     while(curr != NULL) {

     if((curr->row == row) && (curr->col == col)) {


     // if the value was 0, delete it
     if(value == 0) {
       if(curr!=mat_t->tuples_head)
        prevNode->next = curr->next;
       else
       mat_t->tuples_head=curr->next;

       free(curr);
       mat_t->nz--;
       return;
     }
     else
      {
     // if found and we arent supposed to delete, update the value to the new one
     curr->value = value;
     return;
        }
     }
     // add the node in
     if(curr->row >= row && value!=0)
   {
     if(curr->row ==row && curr->col>col)
    {
         sp_tuples_node * new = (sp_tuples_node *) malloc(sizeof(struct sp_tuples_node));
          new->row = row;
           new->col = col;
            new->value = value;

             new->next = curr;
           if(curr!=mat_t->tuples_head)
              prevNode->next = new;
            else
            mat_t->tuples_head=new;

            mat_t->nz++;
            return;
    }
    else if(curr->row>row)//if not in same row
    {
      sp_tuples_node * new = (sp_tuples_node *) malloc(sizeof(struct sp_tuples_node));
       new->row = row;
        new->col = col;
         new->value = value;

          new->next = curr;
          if(curr!=mat_t->tuples_head)
           prevNode->next = new;
           else
           mat_t->tuples_head=new;

           mat_t->nz++;
           return;
    }
     }

     // iterate
     prevNode = curr;
     curr = curr->next;
     }
   if(value!=0)
   {
   sp_tuples_node * new = (sp_tuples_node *) malloc(sizeof(struct sp_tuples_node));
   new->row = row;
   new->col = col;
   new->value = value;
   prevNode->next=new;
   new->next=NULL;
   mat_t->nz++;
 }
     return;
  }
}




void save_tuples(char * file_name, sp_tuples * mat_t)
{
  if(mat_t!=NULL)
  {
    FILE *fptr=fopen(file_name,"w");//ope file
    fprintf(fptr,"%d %d\n",mat_t->m,mat_t->n);
    sp_tuples_node* current=mat_t->tuples_head;//print
    while(current!=NULL)
    {
      fprintf(fptr, "%d %d %lf\n",current->row,current->col,current->value);
      current=current->next;
    }
  fclose(fptr);
  }
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
  if(matA->m!=matB->m || matA->n!=matB->n)
    return NULL;
  sp_tuples *addmat=(sp_tuples*)malloc(sizeof(sp_tuples));
  addmat->m=matB->m;
  addmat->n=matB->n;
  addmat->nz=0;
  sp_tuples_node* Ahead= matA->tuples_head;
  sp_tuples_node* Bhead= matB->tuples_head;
  while(Ahead!=NULL)
  {
      set_tuples(addmat,Ahead->row,Ahead->col,Ahead->value);
      Ahead=Ahead->next;
  }
  while(Bhead!=NULL)
  {
      set_tuples(addmat,Bhead->row,Bhead->col,Bhead->value+ gv_tuples(addmat,Bhead->row,Bhead->col));
      Bhead=Bhead->next;
  }
  return addmat;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){
  if(matA->n!=matB->m)
 return NULL;
sp_tuples* multmat=(sp_tuples*)malloc(sizeof(sp_tuples));
multmat->m=matA->m;
multmat->n=matB->n;
multmat->nz=0;
sp_tuples_node* Ahead= matA->tuples_head;
sp_tuples_node* Bhead= matB->tuples_head;
while(Ahead!=NULL)
{
  while(Bhead!=NULL)
  {
    if(Bhead->row == Ahead->col)
    set_tuples(multmat,Ahead->row,Bhead->col,(Bhead->value*Ahead->value)+gv_tuples(multmat,Ahead->row,Bhead->col));

    Bhead=Bhead->next;
  }
  Ahead=Ahead->next;
  Bhead= matB->tuples_head;
}
return multmat;

}



void destroy_tuples(sp_tuples * mat_t)
{
  if(mat_t!=NULL)
  {
    sp_tuples_node *current;
    current=mat_t->tuples_head;
    sp_tuples_node *currentfreed=NULL;
    while(current!=NULL)
    {
      currentfreed=current;
      current=current->next;
      free(currentfreed);
    }
    free(mat_t);
  }
}
