#include <stdio.h>
void pnew(FILE *fptr){
  char cname[100];
  int cno,bal,cid;
  printf("Enter customer name: ");
  scanf("%s",cname);
  printf("Enter customer ID: ");
  scanf("%d",&cid);
  printf("Enter customer mobile number: ");
  scanf("%d",&cno);
  printf("Enter customer account balance: ");
  scanf("%d",&bal);
  fprintf(fptr,"\n%d %d %d %s",cid,cno,bal,cname);
}

void disp(FILE *fptr){
  char cname[100];
  int cno,bal,cid,gid;
  printf("Enter Customer ID to display: ");
  scanf("%d",&gid);
  while(fscanf(fptr,"%d %d %d %s",&cid,&cno,&bal,cname)!=EOF){
    if(cid==gid){
      printf("-------------------------\n");
      printf("Customer Name: %s\nCustomer ID: %d\nCustomer Number: %d\nCustomer Balance: %d\n",cname,cid,cno,bal);
      printf("-------------------------\n");
    }
    
  }
}

void dispall(FILE *fptr){
  char cname[100];
  int cno,bal,cid;
  while(fscanf(fptr,"%d %d %d %s",&cid,&cno,&bal,cname)!=EOF){
      printf("Customer Name: %s\nCustomer ID: %d\nCustomer Number: %d\nCustomer Balance: %d\n",cname,cid,cno,bal);
      printf("-------------------------\n");

  }
}

void pay(FILE *fptr,FILE *fptr2){
  char cname[100];
  int cno,bal,cid,gid,bill;
  printf("Enter Customer ID to pay the bill: ");
  scanf("%d",&gid);
  printf("Enter the bill amount to be paid: ");
  scanf("%d",&bill);
  while(fscanf(fptr,"%d %d %d %s",&cid,&cno,&bal,cname)!=EOF){
    if(cid==gid){
      bal=bal-bill;
      printf("-------------------------\n");
      printf("Customer Name: %s\nCustomer ID: %d\nCustomer Number: %d\nCustomer Balance: %d\n",cname,cid,cno,bal);
      printf("-------------------------\n");
      fprintf(fptr2,"\n%d %d %d %s",cid,cno,bal,cname);
    }
    else
      fprintf(fptr2,"\n%d %d %d %s",cid,cno,bal,cname);
  }
}


void add(FILE *fptr,FILE *fptr2){
  char cname[100];
  int cno,bal,cid,gid,bill;
  printf("Enter Customer ID to add the amount: ");
  scanf("%d",&gid);
  printf("Enter the amount to be added: ");
  scanf("%d",&bill);
  while(fscanf(fptr,"%d %d %d %s",&cid,&cno,&bal,cname)!=EOF){
    if(cid==gid){
      bal=bal+bill;
      printf("-------------------------\n");
      printf("Customer Name: %s\nCustomer ID: %d\nCustomer Number: %d\nCustomer Balance: %d\n",cname,cid,cno,bal);
      printf("-------------------------\n");
      fprintf(fptr2,"\n%d %d %d %s",cid,cno,bal,cname);
    }
    else
      fprintf(fptr2,"\n%d %d %d %s",cid,cno,bal,cname);
  }
}



int main(){
  while(1){
  printf("1.Create new account\n2.Print customer details\n3.Pay bill and display account details\n4.Print information of all customers\n5.Search for an account\n6.Add ammount to existing customer's wallet\n7.exit\n");
  printf("Enter the option: ");
  int op;
  scanf("%d",&op);
  if (op==1){
    FILE *fptr;
    fptr=fopen("test5.txt","a+");
    pnew(fptr);
    fclose(fptr);
  }

  else if(op==2||op==5){
    FILE *fptr;
    fptr=fopen("test5.txt","r");
    disp(fptr);
    fclose(fptr);
  }
  else if(op==3){
    FILE *fptr;
    FILE *fptr2;
    char temp[]="temp.txt";
    char test[]="test5.txt";
    fptr=fopen("test5.txt","r");
    fptr2=fopen("temp.txt","w+");
    pay(fptr,fptr2);
    rename(temp,test);
    fclose(fptr);
    fclose(fptr2);
  }
    else if(op==6){
      FILE *fptr;
      FILE *fptr2;
      char temp[]="temp.txt";
      char test[]="test5.txt";
      fptr=fopen("test5.txt","r");
      fptr2=fopen("temp.txt","w+");
      add(fptr,fptr2);
      rename(temp,test);
      fclose(fptr);
      fclose(fptr2);
    }
  else if(op==4){
    FILE *fptr;
    fptr=fopen("test5.txt","r");
    dispall(fptr);
    fclose(fptr);
  }
    
  else if(op==7)
    break;

  
  }
  
}
