//We get the problem from "input.txt" and print the result in "output.txt"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int priority(char c){
  if(c == '/' || c == '*') return 2;
  else if (c == '+' || c == '-') return 1;
  else return -1;
}

long long operation(long long a, long long b, char c){
  if(c == '+') return a + b;
  else if(c == '-') return a - b;
  else if(c == '*') return a * b;
  else if(c == '/') return a / b;
  else return -3;
}

struct stack{
  union{
    char *data;
    long long *num;
  };
  int size;
};
typedef struct stack stack;

char popchar(stack *s){
  if(s->size){
    char res = s->data[s->size-1];
    --s->size;
    s->data = realloc(s->data, sizeof(char) * (s->size + 1));
    return res;
  }
  return -1;
}

long long poplong(stack *s){
  if(s->size){
    long long res = s->num[s->size-1];
    --s->size;
    s->num = realloc(s->num, sizeof(long long) * (s->size + 1));
    return res;
  }
  return -1;
}

void pushchar(stack *s, char x){
  if(!s->data){
    s->data = malloc(sizeof(char) * 2);
    s->data[0] = x;
    ++s->size;
  }
  else{
    s->data[s->size] = x;
    ++s->size;
    s->data = realloc(s->data, sizeof(char) * (s->size + 1));
  }
}

void pushlong(stack *s, long long x){
  if(!s->num){
    s->num = malloc(sizeof(long long) * 2);
    s->num[0] = x;
    ++s->size;
  }
  else{
    s->num[s->size] = x;
    ++s->size;
    s->num = realloc(s->num, sizeof(long long) * (s->size + 1));
  }
}

int main(void){
  stack *dig = (stack*)malloc(sizeof(stack));
  stack *op = (stack*)malloc(sizeof(stack));
  FILE *f, *o;
  long long a, b;
  char c = ' ', pr = ' ';
  f = fopen("input.txt", "r");
  o = fopen("output.txt", "w");

  while((c = fgetc(f)) != EOF){
    if(!isspace(c)){

      if(isdigit(c)){
        long long i = 0;
        while(isdigit(c)){
          i += (c - '0');
          i = i * 10;
          c = fgetc(f);
        }
        pushlong(dig, i/10);

        if(c == ')'){
          while ((pr = popchar(op)) != '(' && op->size){
            b = poplong(dig);
            a = poplong(dig);
            pushlong(dig, operation(a, b, pr));
          }
        }
        else if (c != EOF && !isspace(c)){
          while (op->size && priority(c) <= priority(pr = popchar(op))){
            b = poplong(dig);
            a = poplong(dig);
            pushlong(dig, operation(a, b, pr));
            }
          pushchar(op, pr);
          pushchar(op, c);
        }
      }

      else if(c == '(') pushchar(op, c);
      
      else if(c == ')'){
        while ((pr = popchar(op)) != '(' && op->size){
          b = poplong(dig);
          a = poplong(dig);
          pushlong(dig, operation(a, b, pr));
        }
      }

      else{
        while (op->size && priority(c) <= priority((pr = popchar(op)))){
          b = poplong(dig);
          a = poplong(dig);
          pushlong(dig, operation(a, b, pr));
          }
          pushchar(op, pr);
          pushchar(op, c);
        }


    }
  }

  while(dig->size != 1){
    b = poplong(dig);
    a = poplong(dig);
    pr = popchar(op);
    pushlong(dig, operation(a, b, pr));
  }

  while(dig->size){
    fprintf(o, "%lld", poplong(dig));
  }
  

  free(dig->data);
  free(op->data);
  free(dig);
  free(op);
  fclose(f);
  fclose(o);
  return 0;
}