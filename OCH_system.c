/* Online Computer Hardware system */
/*-- Raj Jani --*/


#include<stdio.h>
#include<stdlib.h>


//structure
struct hardware{
	char type[20];		//hardwre motherboard,smps,processor
	char name[20];		//hardware name
	char brand[20];		//brand name
	char code[20];		//unique code for search
	int price;		//hardware price
		}item;
//structure end
//extra
void f_display(char filterType[20]);
void empty_cart();
int count_cart_item() ;
//Admin side
void admin();
void adm_insert();
void adm_viewAll();
void adm_find();
void adm_update();
void adm_del();

//end admin side
//user side 
void user_main();
void user_select_motherBoard(); 	//aading motherboard to the cart 
void user_select_procesor(); 
void user_select_smps();
void user_view_cart();
void user_invoice();
void search_brand();
//user side function ends
void main()
{

 int ch;
 
 system("clear");
 do
 {
   
   printf("\n\t------------------------------------------------");
   printf("\n\t|    COMPUTER HARDWARE QUOTATION MANAGER       |");
   printf("\n\t------------------------------------------------");
   printf("\n\n");
   
   printf("\nPress <1> ADMIN");
   printf("\nPress <2> USER");
   printf("\nPress <0> EXIT");

   printf("\nEnter your Choice ::");
   scanf("%d",&ch); 	

   switch (ch)
   {
    case 1 :
    admin();
    break;
    
    case 2:
	user_main();
    break;

    case 0:
    exit(0);
    break;

    default:
    printf("Wrong choice !");
    break;
   }
 }while(ch!=0);



}

//Admin Functions
void admin()
{
 FILE *fp;

 int ch;
 char adm_name[20]="admin";
 char adm_pass[20]="admin";
 char temp_name[20],temp_pass[20];

 printf("\n\tUser Name:- ");
 scanf("%s",temp_name);
 printf("\n\tPassword:- ");
 scanf("%s",temp_pass);
 system("clear");
 if(strcmp(adm_name,temp_name) == 0 && strcmp(adm_pass,temp_pass) == 0)
 {
	do
 	{
   
   		printf("\n\t------------------------------------------------");
   		printf("\n\t|    COMPUTER HARDWARE QUOTATION MANAGER       |");
   		printf("\n\t------------------------------------------------");
   		printf("\n\n");
   
   		printf("\nPress <1> Insert New Item ");
   		printf("\nPress <2> search Item ");
		printf("\nPress <3> View All ");
		printf("\nPress <4> Update Price ");
   		printf("\nPress <5> Delete Item ");
		printf("\nPress <0> Exit ");

   		printf("\nEnter your Choice ::");
   		scanf("%d",&ch); 	

   		switch (ch)
   		{
	    		case 1 :
	    		adm_insert();
	    		break;
	    	
			case 2:
			adm_find();
			break;	

			case 3:
			adm_viewAll();
			break;

			case 4:
			adm_update();
			break;	
			
			case 5:
			adm_del();
			break;			

	    		case 0:
	    		exit(0);
	    		break;

	    		default:
	    		printf("Wrong choice !");
	    		break;
   		}
 	}while(ch!=0);

 }
 else
   printf("Password and User name are not matched\n");
}

/* insert record */
void adm_insert()
{
	struct hardware item;
	FILE *fp;
	
	
	system("clear");
	
	fp=fopen("all_data.txt","a");	

	printf("\n\tEnter Hardware type (mo for Motharborad/po for Procesor/sm for SMPS ::");
	scanf("%s",item.type);
	setbuf(stdin,NULL);

	printf("\n\t Enter Hardware Code(must be unique)  ::");
	scanf("%s",item.code);
	setbuf(stdin,NULL);

	printf("\n\t Enter Hardware name :: ");
	scanf("%s",item.name);
	setbuf(stdin,NULL);

	printf("\n\t Enter Brand name :: ");
	scanf("%s",item.brand);
	setbuf(stdin,NULL);

	printf("\n\t Enter Price of Item ::");
	scanf("%d",&item.price);
	
	if(fp == NULL)
	{
	}
	else
	{
		fprintf(fp,"%s %s %s %d %s \n",item.code,item.name,item.brand,item.price,item.type);
		printf("Record Inserted ! ...... \n");
		fclose(fp);
	}
	
	

}
/* update record    */
void adm_update() //update price of item
{
	FILE *tf,*fp;
	char code[20];	//search code
	int rno,cnt=0;

	tf=fopen("temp.txt","w");

	fp=fopen("all_data.txt","r");

	printf("\n Enter Item Code : ");
	scanf("%s",code);

	
		while(fscanf(fp,"%s %s %s %d %s \n",item.code,item.name,item.brand,&item.price,item.type) != EOF)
		{
			
			if(strcmp(item.code,code) == 0)
			{	
				cnt = 1;
		
				printf("\n Record Found\n");
				printf("\n\t\tCode ::%s",item.code);
				printf("\n\t\tHardware name ::%s",item.name);
				printf("\n\t\tBrand name ::%s",item.brand);
				printf("\n\t\tCost of Item ::%d",item.price);
				
				printf("\n\t Enter New Price ::");
				scanf("%d",&item.price);

				fprintf(tf,"%s %s %s %d %s \n",item.code,item.name,item.brand,item.price,item.type);

			}
			else
			{
				fprintf(tf,"%s %s %s %d %s \n",item.code,item.name,item.brand,item.price,item.type);
			}
		}
		fclose(fp);
		fclose(tf);

	if(cnt==0)
	{			
		printf("\n\n\n *****************************************\n\n");
		printf("\n Record Not Available ");		
		printf("\n\n\n *****************************************\n\n");
	}
	else
	{
		fp=fopen("all_data.txt","w");

		tf=fopen("temp.txt","r");

			while(fscanf(tf,"%s %s %s %d %s \n",item.code,item.name,item.brand,&item.price,item.type)!=EOF)
		{
			if(item.code==0)
				break;

			fprintf(fp,"%s %s %s %d %s \n",item.code,item.name,item.brand,item.price,item.type);
		}

		printf("\n Record Successfully Updated .............................!");		

		fclose(fp);
		fclose(tf);
	}
		
	


}
/* Delete Record */
void adm_del()
{
	FILE *fpt,*fptr;
	struct hardware item;
	int found=0;
	char code[20]; //for search

	fpt=fopen("all_data.txt","r");

	if(fpt==NULL)
	{
		printf("\n Error In Opening File....");
		//exit(0);
	} 	

	fptr=fopen("temp.txt","w");

	if(fptr==NULL)
	{
		printf("\n Error In Opening File....");
		//exit(0);
	}	

	
	setbuf(stdin,NULL);

	printf("\n Enter code  : ");
	scanf("%s",code);
	
	while(fscanf(fpt,"%s %s %s %d %s \n",item.code,item.name,item.brand,&item.price,item.type)!=EOF)
	{
		if(item.code==0)			
			break;
		
		if(strcmp(item.code,code)==0)
		{	
			found=1;
		}
		else
		{			
			fprintf(fptr,"%s ",item.code);
			fprintf(fptr,"%s ",item.name);
			fprintf(fptr,"%s ",item.brand);
			fprintf(fptr,"%d ",item.price);
			fprintf(fptr,"%s ",item.type);
					
		}
	}

	fclose(fptr);
	fclose(fpt);

	if(found==0)
	{
		printf("\n\n\n *****************************************\n\n");
		printf("\n Record Not Found....");	
		printf("\n\n\n *****************************************\n\n");
	}
	else
	{
		fpt=fopen("all_data.txt","w");

		if(fpt==NULL)
		{
			printf("\n Error In Opening File....");
			//exit(0);
		} 	

		fptr=fopen("temp.txt","r");

		if(fptr==NULL)
		{
			printf("\n Error In Opening File....");
			//exit(0);
		}		               
	
		while(fscanf(fptr,"%s %s %s %d %s \n",item.code,item.name,item.brand,&item.price,item.type)!=EOF)
		{
			if(item.code==0)
				break;
	
			fprintf(fpt,"%s %s %s %d %s \n",item.code,item.name,item.brand,item.price,item.type);
		}
	
		printf("\n Record Successfully Deleted...............................!\n");
		fclose(fptr);
		fclose(fpt);
	}

}

/* find specific record  */ 
void adm_find() //search using code
{
	struct hardware item;
	FILE *fp;
	int flag=0;
	char findCode[20];
	printf("Entewr Hardware code for search specefic record ::");
	scanf("%s",findCode);
	system("clear");
	fp = fopen("all_data.txt","r");
	if(fp == NULL)
	{
		printf("file does not found !");
		exit(1);

	}
	else
	{	
		while(fscanf(fp,"%s %s %s %d %s \n",item.code,item.name,item.brand,&item.price,item.type) != EOF)
		{
			
		
			if(strcmp(item.code,findCode) == 0)
			{	flag=1;
				printf("\n Record Found\n");
				printf("\n\t\tCode ::%s",item.code);
				printf("\n\t\tHardware name ::%s",item.name);
				printf("\n\t\tBrand name ::%s",item.brand);
				printf("\n\t\tCost of Item ::%d",item.price);

			}
		}
		if(flag == 0)
			printf("\nRecord Not Found\n");
		
	}




}
/* view all records */
void adm_viewAll()
{
	char ch;
	FILE *fp;

	fp = fopen("all_data.txt","r");
	if(fp == NULL)
	{
		printf("file does not found !");
		exit(1);

	}
	else
	{	
		system("clear");
		printf("Code \tName \tBrand Name \tPrice \tType\n");
		while( fscanf(fp,"%s %s %s %d %s \n",item.code,item.name,item.brand,&item.price,item.type) != EOF )
      		{
			printf("%s \t%s \t%s \t%d \t%s \n",item.code,item.name,item.brand,item.price,item.type);
		}
		
	}
}



/* End Admin functions */

/* user function starts  */
void user_main()//main user side function 
{
 FILE *fp;

 int ch,exsist_cart_item;
 char user_name[20]="user";
 char user_pass[20]="user";
 char temp_name[20],temp_pass[20];

 printf("\n\tUser Name:- ");
 scanf("%s",temp_name);
 printf("\n\tPassword:- ");
 scanf("%s",temp_pass);
 system("clear");
 if(strcmp(user_name,temp_name) == 0 && strcmp(user_pass,temp_pass) == 0)
 {
	do
 	{
   
   		printf("\n\t------------------------------------------------");
   		printf("\n\t|    COMPUTER HARDWARE QUOTATION MANAGER       |");
   		printf("\n\t------------------------------------------------");
   		printf("\n\n");

   		exsist_cart_item = count_cart_item();
   		printf("\nPress <1> Select Motherboard");
   		printf("\nPress <2> select Procesor");
		printf("\nPress <3> Select SMPS");
		printf("\nPress <4> Search item of specefic Brand");
		printf("\nPress <5> View your Cart (%d Items in cart)",exsist_cart_item);
		printf("\nPress <6> Empty cart ");
		printf("\nPress <22> Need Help ?");
   		printf("\nPress <0> Exit");

   		printf("\nEnter your Choice ::");
   		scanf("%d",&ch); 	

   		switch (ch)
   		{
	    		case 1 :
	    			user_select_motherBoard();
	    		break;
	    			
			case 2:
				user_select_procesor();
			break;	

			case 3:
				user_select_smps();
			break;
			
			case 4:
				search_brand();
			break;

			case 5:
				user_view_cart();
			break;				

			case 6:
				empty_cart();
			break;
				
	    		case 0:
	    		exit(0);
	    		break;

	    		default:
	    		printf("Wrong choice !");
	    		break;
   		}
 	}while(ch!=0);

 }
 else
   printf("Password and User name are not matched\n");
}

void user_select_motherBoard()//view hardware according to chooise
{
		
	
	struct hardware item;
	FILE *fp;
	FILE *cart;//user cart file
	int flag=0;
	char ch[20];
	
/*START diplay only all motherboard */
	printf("*** -------------------------------------------- ***\n");
	printf("CODE \tNAME \tBRAND \tPRICE\n");
		f_display("mo");
	printf("*** -------------------------------------------- ***");
/*END  */	
/*START adding selected item to the user cart */
	printf("\n\t Enter MotherBoard code ::");
	scanf("%s",ch);
	fp = fopen("all_data.txt","r");
	cart = fopen("user_cart.txt","w");
	if(fp == NULL)
	{
		printf("file does not found !");
		exit(1);

	}
	else
	{	
		while(fscanf(fp,"%s %s %s %d %s \n",item.code,item.name,item.brand,&item.price,item.type) != EOF)
		{
			
		
			if(strcmp(item.code,ch) == 0)
			{	flag=1;
				printf("\n \n");
				printf("\n\t\tCode ::%s",item.code);
				printf("\n\t\tHardware name ::%s",item.name);
				printf("\n\t\tBrand name ::%s",item.brand);
				printf("\n\t\tCost of Item ::%d",item.price);
				fprintf(cart,"%s %s %s %d \n",item.code,item.name,item.brand,item.price);
				printf("\n\n\tItem Added To cart \n");
					

			}
		}
		if(flag == 0)
			printf("\nRecord Not Found\n");
		
	}
	fclose(cart);
	fclose(fp);
/*END block for user cart entry */
}

void user_view_cart()
{
	char ch;
	FILE *cart;
	int i,amount = 0;

	cart = fopen("user_cart.txt","r");
	if(cart == NULL)
	{
		printf("file does not found !");
		exit(1);

	}
	else
	{	
		//system("clear");
		while( fscanf(cart,"%s %s %s %d \n",item.code,item.name,item.brand,&item.price) != EOF )
		{
				
				printf(" %s %s %s %d \n",item.code,item.name,item.brand,item.price);
				amount=amount + item.price;
		}
				printf("\n\t Total Amount :: %d /-Rs",amount);

		
	}



}
void user_select_procesor()
{
	struct hardware item;
	FILE *fp;
	FILE *cart;//user cart file
	int flag=0;
	char ch[20];
	
/*START diplay only all processor */
	printf("*** -------------------------------------------- ***\n");
	printf("CODE \tNAME \tBRAND \tPRICE\n");
		f_display("po");
	printf("*** -------------------------------------------- ***");
/*END  */	
/*START adding selected item to the user cart */
	printf("\n\t Enter processor code ::");
	scanf("%s",ch);
	fp = fopen("all_data.txt","r");
	cart = fopen("user_cart.txt","a");
	if(fp == NULL)
	{
		printf("file does not found !");
		exit(1);

	}
	else
	{	
		while(fscanf(fp,"%s %s %s %d %s \n",item.code,item.name,item.brand,&item.price,item.type) != EOF)
		{
			
		
			if(strcmp(item.code,ch) == 0)
			{	flag=1;
				printf("\n \n");
				printf("\n\t\tCode ::%s",item.code);
				printf("\n\t\tHardware name ::%s",item.name);
				printf("\n\t\tBrand name ::%s",item.brand);
				printf("\n\t\tCost of Item ::%d",item.price);
				fprintf(cart,"%s %s %s %d \n",item.code,item.name,item.brand,item.price);
				printf("\n\n\tItem Added To cart \n");
					

			}
		}
		if(flag == 0)
			printf("\nRecord Not Found\n");
		
	}
	fclose(cart);
	fclose(fp);



}
void user_select_smps()
{
	struct hardware item;
	FILE *fp;
	FILE *cart;//user cart file
	int flag=0;
	char ch[20];
	
/*START diplay only all smps */
	printf("*** -------------------------------------------- ***\n");
	printf("CODE \tNAME \tBRAND \tPRICE\n");
		f_display("sm");
	printf("*** -------------------------------------------- ***");
/*END  */	
/*START adding selected item to the user cart */
	printf("\n\t Enter smps code ::");
	scanf("%s",ch);
	fp = fopen("all_data.txt","r");
	cart = fopen("user_cart.txt","a");
	if(fp == NULL)
	{
		printf("file does not found !");
		exit(1);

	}
	else
	{	
		while(fscanf(fp,"%s %s %s %d %s \n",item.code,item.name,item.brand,&item.price,item.type) != EOF)
		{
			
		
			if(strcmp(item.code,ch) == 0)
			{	flag=1;
				printf("\n \n");
				printf("\n\t\tCode ::%s",item.code);
				printf("\n\t\tHardware name ::%s",item.name);
				printf("\n\t\tBrand name ::%s",item.brand);
				printf("\n\t\tCost of Item ::%d",item.price);
				fprintf(cart,"%s %s %s %d \n",item.code,item.name,item.brand,item.price);
				printf("\n\n\tItem Added To cart \n");
					

			}
		}
		if(flag == 0)
			printf("\nRecord Not Found\n");
		
	}
	fclose(cart);
	fclose(fp);



}
/* this function only for diplay filter data type wise */
void f_display(char filterType[20])
{
	FILE *filter;
	filter = fopen("all_data.txt","r");
	
	if(filter == NULL)
	{
		printf("file does not found !");
		exit(1);

	}
	else
	{	
		while( fscanf(filter,"%s %s %s %d %s \n",item.code,item.name,item.brand,&item.price,item.type) != EOF )
		{
				if(strcmp(item.type,filterType) == 0)
				{
					printf(" %s \t%s \t%s \t%d \n",item.code,item.name,item.brand,item.price);
				}
		}
				

		
	}

}
void empty_cart()
{
	FILE *filter;
	filter = fopen("user_cart.txt","w");
	char name[20],code[20],brand[20],type[20];
	int price;
	if(filter == NULL)
	{
		printf("file does not found !");
		exit(1);

	}
	else
	{	
		while( fscanf(filter,"%s %s %s %d %s \n",item.code,item.name,item.brand,&item.price,item.type) != EOF )
		{
				
			
			fprintf(filter,"%s %s %s %d %s\n",code,name,brand,price,type);
				
		}
				

		
	}

	fclose(filter);
	
}
int count_cart_item() //count items in cart 
{
	char ch;
	FILE *cart;
	int i,count = 0;

	cart = fopen("user_cart.txt","r");
	if(cart == NULL)
	{
		printf("file does not found !");
		exit(1);

	}
	else
	{	
		//system("clear");
		while( fscanf(cart,"%s %s %s %d \n",item.code,item.name,item.brand,&item.price) != EOF )
		{
				
				
				count=count + 1;
		}
				return count;

		
	}


	fclose(cart);
	
}
void search_brand() //search using brand name
{
	struct hardware item;
	FILE *fp;
	FILE *cart;
	int flag=0;
	char findbrand[20],ans,code[20]; //code is for adding into cart
	printf("Entewr Brand Name ::");
	scanf("%s",findbrand);
	system("clear");
	fp = fopen("all_data.txt","r");
	cart = fopen("user_cart.txt","a");
	if(fp == NULL)
	{
		printf("file does not found !");
		exit(1);

	}
	else
	{	
		while(fscanf(fp,"%s %s %s %d %s \n",item.code,item.name,item.brand,&item.price,item.type) != EOF)
		{
			
		
			if(strcmp(item.brand,findbrand) == 0)
			{	flag=1;
				//printf("\n Record Found\n");
				printf("\n\t\tCode ::%s",item.code);
				printf("\n\t\tHardware name ::%s",item.name);
				printf("\n\t\tBrand name ::%s",item.brand);
				printf("\n\t\tCost of Item ::%d",item.price);

			}

		}
		if(flag == 0)
			printf("\nRecord Not Found\n");
		
	}
	
	printf("\nEnter code to Add item in Cart: ");
	scanf("%s",code);

	while(fscanf(fp,"%s %s %s %d %s \n",item.code,item.name,item.brand,&item.price,item.type) != EOF)
	{
		if(strcmp(item.code,code) == 0)
		{	
			fprintf(cart,"%s %s %s %d \n",item.code,item.name,item.brand,item.price);
			printf("\n\n\tItem Added To cart \n");
				
		}
	}



	fclose(cart);
	fclose(fp);
}
/* End user function   */
