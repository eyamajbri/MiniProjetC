#include<string.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct {
	int j,m,a;
} date;
typedef struct {
	char nom[300],marque[300],fournisseur[300];
	float prix;
	int id,qte,qtevendue,enstock;
	date date;
} produit; 
void ajout() {
  produit item;

  printf("Introduire l'ID du produit:");
  scanf("%ld", &item.id);

  // Check if the product already exists in the file
  int productExists = checkIfProductExists(item.id);
  if (productExists) {
    printf("Le produit existe deja dans le fichier\n");
    return;
  };

  // Product does not exist in the file, prompt the user for all the attributes
  printf("Introduire le nom du produit: ");
  scanf("%s", item.nom);
  printf("Introduire la marque: ");
  scanf("%s", item.marque);
  printf("Introduire le prix:");
  scanf("%f", &item.prix);
  printf("Introduire la quantite:");
  scanf("%d", &item.qte);
  printf("Introduire la quantite vendue: ");
  scanf("%d", &item.qtevendue);
  printf("Introduire le fournisseur: ");
  scanf("%s", item.fournisseur);
  printf("Le produit est il en stock? introduire 1 si oui 0 sinon: ");
  scanf("%d", &item.enstock);
  do {
            printf("introduire la date de restockage sous forme j/m/a: ");
            scanf("%d/%d/%d", &item.date.j, &item.date.m, &item.date.a);
        } while(!(item.date.j>=01&&item.date.j<=31&&item.date.m>=01&&item.date.m<=12));

  // Open the file in append mode
  FILE *fp = fopen("stock.txt", "a");
  if (fp == NULL) {
    printf("Error opening file\n");
    return;
  }

  fprintf(fp, "%ld %s %s %f %d %d %s %d %d/%d/%d\n",
        item.id, item.nom, item.marque,
        item.prix, item.qte, item.qtevendue, item.fournisseur, item.enstock,
        item.date.j, item.date.m, item.date.a);
  fclose(fp);
};
int compareprix(const void* a, const void* b) {
  produit* prodA = (produit*)a;
  produit* prodB = (produit*)b;
  return (prodA->prix - prodB->prix);
};

void trieparprix() {
	int i;
  FILE *fp = fopen("stock.txt", "r");
  if (fp == NULL) {
    printf("Error opening file\n");
    return;
  };
  int numProducts = 0;
  produit products[100];
   while (fscanf(fp, "%ld %s %s %f %d %d %s %d %d/%d/%d", &products[numProducts].id, &products[numProducts].nom, &products[numProducts].marque, &products[numProducts].prix, &products[numProducts].qte, &products[numProducts].qtevendue, &products[numProducts].fournisseur, &products[numProducts].enstock, &products[numProducts].date.j, &products[numProducts].date.m, &products[numProducts].date.a) == 11) {
    numProducts++;
  };

  fclose(fp);

  // Sort the products by price
  qsort(products, numProducts, sizeof(produit), compareprix);

  // Rewrite the file with the sorted products
  fp = fopen("stock.txt", "w");
  if (fp == NULL) {
    printf("Error opening file\n");
    return;
  };
  for (i = 0; i < numProducts; i++) {
    fprintf(fp, "%ld %s %s %f %d %d %s %d %d/%d/%d\n", products[i].id, products[i].nom, products[i].marque, products[i].prix, products[i].qte, products[i].qtevendue,  products[i].fournisseur, products[i].enstock, products[i].date.j, products[i].date.m, products[i].date.a);
  };

  fclose(fp);
};
int checkIfProductExists(long int id) {
  produit item;
  FILE *fp = fopen("stock.txt", "r");
  if (fp == NULL) {
    printf("Error opening file\n");
    return 0;
  };

  while (fread(&item, sizeof(produit), 1, fp) == 1) {
    if (item.id == id) {
      fclose(fp);
      return 1;
    };
  };

  fclose(fp);
  return 0;
};
void Tri_par_nom() {
  FILE *fp = fopen("stock.txt", "r");
  if (fp == NULL) {
    printf("Error opening file\n");
    return;
  };
  int numProducts = 0;
  produit products[100];
   while (!feof(fp)) {
   	 fscanf(fp, "%ld %s %s %f %d %d %s %d %d/%d/%d", &products[numProducts].id,&products[numProducts].nom,&products[numProducts].marque, &products[numProducts].prix, &products[numProducts].qte, &products[numProducts].qtevendue, &products[numProducts].fournisseur, &products[numProducts].enstock, &products[numProducts].date.j, &products[numProducts].date.m, &products[numProducts].date.a) ;
     numProducts++;
  };
  printf("le nombre de produits est : %d  \n",numProducts);
  produit product,aux;
  int i,j,min ;
  for ( i = 0; i < numProducts; i++) {
  	min=i;
  	for (j=i+1;j< numProducts ; j++){
  		if(strcmp(products[j].nom,products[min].nom)<=0){
  			min=j;
		  }
	}
	   aux=products[i];
	   products[i]=products[min];
	   products[min]=aux;
	  }

  	
 
  int k ;
  for ( k = 0; k < numProducts; k++) {
    printf ("%ld %s %s %f %d %d %s %d %d/%d/%d \n ", products[k].id,products[k].nom,products[k].marque,products[k].prix,products[k].qte,products[k].qtevendue, products[k].fournisseur, products[k].enstock, products[k].date.j, products[k].date.m, products[k].date.a);
  }

}

void liste_produits_stock(){
	int choix ;
	
	FILE *fp= fopen("stock.txt","r");
	
	if (fp == NULL){
       printf("Error! opening file");
       return;}
       
    produit product; 
	do{
	printf("cher utilisateur, Veuillez entrer : 1 si vous avez besoin de la liste des produits en stock \n");
    printf("cher utilisateur, Veuillez entrer : 0 si vous avez besoin de la liste des produits hors stock \n");
    printf("choix:");
	scanf("%d",&choix);
    if (choix==1){ 
	     int trouve=0; 
	     printf("la liste ci-dessous contient toutes les informations concernant les produits en stock : \n");    
	     while (!feof(fp)){
	         fscanf(fp, "%ld %s %s %f %d %d %s %d %d/%d/%d", &product.id,&product.nom,&product.marque, &product.prix, &product.qte, &product.qtevendue, &product.fournisseur, &product.enstock, &product.date.j, &product.date.m, &product.date.a) ;
             if (product.enstock==1) {
             	trouve=1;
             	printf ("%ld %s %s %f %d %d %s %d %d/%d/%d \n ", product.id,product.nom,product.marque,product.prix,product.qte,product.qtevendue, product.fournisseur, product.enstock, product.date.j, product.date.m, product.date.a);
			 }
		}
		if(trouve==0){
			printf("aucun produit n'est en stock \n");
		}
	}
	if (choix==0){
		int trouve=0;
		printf("la liste ci-dessous contient toutes les informations concernant les produits hors stock : \n");
		while (!feof(fp)){
	         fscanf(fp, "%ld %s %s %f %d %d %s %d %d/%d/%d", &product.id,&product.nom,&product.marque, &product.prix, &product.qte, &product.qtevendue, &product.fournisseur, &product.enstock, &product.date.j, &product.date.m, &product.date.a) ;
             if (product.enstock==0) {
             	trouve=1;
             	printf ("%ld %s %s %f %d %d %s %d %d/%d/%d \n ", product.id,product.nom,product.marque, product.prix, product.qte, product.qtevendue, product.fournisseur, product.enstock, product.date.j, product.date.m, product.date.a);
	           }
		}
		if(trouve==0){
			printf("aucun produit n'est en stock \n");
		}
	}
}
    while(choix!=1 && choix!=0);
}
void rechercheparmarque(char* marque) {
  // Open the file for reading
  FILE *fp = fopen("stock.txt", "r");
  if (fp == NULL) {
    printf("Error opening file\n");
    return;
  };

  produit product;
   while (fscanf(fp, "%ld %s %s %f %d %d %s %d %d/%d/%d", &product.id,&product.nom, &product.marque, &product.prix, &product.qte, &product.qtevendue, product.fournisseur, &product.enstock, &product.date.j, &product.date.m, &product.date.a) == 11) {
    if (strcmp(product.marque, marque) == 0) {
      // If a matching product is found, print its information
      printf("id: %ld\n", product.id);
      printf("nom: %s\n", product.nom);
      printf("marque: %s\n", product.marque);
      printf("prix: %f\n", product.prix);
      printf("quantite: %d\n", product.qte);
      printf("quantite vendue: %d\n", product.qtevendue);
      printf("fournisseur: %s\n", product.fournisseur);
      printf("en stock: %d\n", product.enstock);
      printf("date: %d/%d/%d\n", product.date.j, product.date.m, product.date.a);
    };
  };

  fclose(fp);
};
void rechercheparid(long id){
	int trouve=0;
	FILE *fp= fopen("stock.txt","r");
	
	if (fp == NULL){
       printf("Error! opening file");
       return;}
       
    produit product;       
	while (!feof(fp)){
	     fscanf(fp, "%ld %s %s %f %d %d %s %d %d/%d/%d", &product.id,&product.nom,&product.marque, &product.prix, &product.qte, &product.qtevendue, &product.fournisseur, &product.enstock, &product.date.j, &product.date.m, &product.date.a) ;
            if(product.id==id){
            	trouve=1;
             	printf("id: %ld\n", product.id);
                printf("nom: %s\n", product.nom);
                
                printf("marque: %s\n", product.marque);
                printf("prix: %f\n", product.prix);
                printf("quantite: %d\n", product.qte);
                printf("quantite vendue: %d\n", product.qtevendue);
                printf("fournisseur: %s\n", product.fournisseur);
                printf("en stock: %d\n", product.enstock);
                printf("date: %d/%d/%d\n", product.date.j, product.date.m, product.date.a);
                break;
           	}
	}
	
	if (trouve==0){
		printf("\nAucune entree correspondante !");
	}

	
	fclose(fp); 
	
}
void rechercheparnom(char nom[100]){
	int trouve=0;
	FILE *fp= fopen("stock.txt","r");
	
	if (fp == NULL){
       printf("Error! opening file");
       return;}
       
    produit product;       
	while (!feof(fp)){
	     fscanf(fp, "%ld %s %s %f %d %d %s %d %d/%d/%d", &product.id,&product.nom,&product.marque, &product.prix, &product.qte, &product.qtevendue, &product.fournisseur, &product.enstock, &product.date.j, &product.date.m, &product.date.a) ;
            if(!(strcmp(product.nom,nom))){
            	trouve=1;
             	printf("id: %ld\n", product.id);
                printf("nom: %s\n", product.nom);
                
                printf("marque: %s\n", product.marque);
                printf("prix: %f\n", product.prix);
                printf("quantite: %d\n", product.qte);
                printf("quantite vendue: %d\n", product.qtevendue);
                printf("fournisseur: %s\n", product.fournisseur);
                printf("en stock: %d\n", product.enstock);
                printf("date: %d/%d/%d\n", product.date.j, product.date.m, product.date.a);
                break;
           	
	}
}
	if (trouve==0){
		printf("\nAucune entree correspondante !");
	}

	
	fclose(fp); 
	
		
}
void TriParFournisseur(){
	int i,j;
  FILE *fp = fopen("stock.txt", "r");
  if (fp == NULL) {
    printf("Error opening file\n");
    return;
  };
  
  // Lire du fichier et mettre dans le tableau
  int numProducts = 0;
  produit products[100];
    while (fscanf(fp, "%ld %s %s %f %d %d %s %d %d/%d/%d", &products[numProducts].id, &products[numProducts].nom, &products[numProducts].marque, &products[numProducts].prix, &products[numProducts].qte, &products[numProducts].qtevendue, &products[numProducts].fournisseur, &products[numProducts].enstock, &products[numProducts].date.j, &products[numProducts].date.m, &products[numProducts].date.a) == 11) {
     numProducts++;
  };
 
 // afficher les produits de chaque fournisseur
for (i=0; i< numProducts; i++) {
  printf("les produits du fournisseur %s sont\n",products[i].fournisseur);
   for (j=0; j< numProducts; j++){
     if (products[j].fournisseur==products[i].fournisseur) {
       printf("%jd : %s \n",products[j].id,products[j].nom);}
}
}
}
void supprimer_produit(long identifiant) {
	long id;
	int enstock,qte,qtevendue,j,m,a,verif=0;
	float prix;
	char nom[100],marque[100],fournisseur[100];
	FILE *fichier1=fopen("stock1.txt","a");
	FILE *fichier=fopen("stock.txt","r");
	while (fscanf(fichier,"%li %s %s %f %d %d %s %d %d/%d/%d",&id,nom,marque,&prix,&qte,&qtevendue,fournisseur,&enstock,&j,&m,&a)==11){
		if (identifiant!=id) {
			fprintf(fichier1,"%li %s %s %s %f %d %d %d %d/%d/%d\n",id,nom,marque,fournisseur,prix,qte,qtevendue,enstock,j,m,a);
		}
		else {
			verif=1;
		}
	}
	if (verif==1) {
		printf("operation de suppression effectuee \n");
	}
	else {
		printf("produit inexistant");
	}
	fclose(fichier);
	fclose(fichier1);
	remove("stock.txt");
	rename("stock1.txt","stock.txt");
}
void afficher_description(long identifiant) {
	FILE *fichier=fopen("stock.txt","r");
	long id;
	int qte,qtevendue,j,m,a,enstock,verif=0;
	float prix;
	char nom[300],marque[300],fournisseur[300],disponibilite[100];
	if (fichier!=NULL) {
	while (!feof(fichier)) {
		fscanf(fichier,"%li %s %s %f %d %d %s %d %d/%d/%d",&id,nom,marque,&prix,&qte,&qtevendue,fournisseur,&enstock,&j,&m,&a);
		if (enstock==1) {
			strcpy(disponibilite,"en stock");
		}
		else {
			strcpy(disponibilite,"en rupture de stock");
		}
		if (identifiant==id) {
			printf("la description du produit cherche est:\n reference: %ld\n nom: %s \n marque: %s \n prix: %f \n quantite en stock: %d \n quantite vendue: %d \n fournisseur: %s \n disponibilite: %s \n date de restockage: %d/%d/%d\n",id,nom,marque,prix,qte,qtevendue,fournisseur,disponibilite,j,m,a);
			verif=1;
		}
		
	}
    }
	if (verif==0) {
		printf("produit inexistant\n");
	}
	fclose(fichier);
}
int DisponibilityCheck(long int idP) {
 produit P;
  FILE *fp = fopen("stock.txt", "r");
  if (fp == NULL) {
    printf("Error opening file\n");
    return 0;
  }
while (!feof(fp)) {
   fscanf(fp,"%ld %s %s %f %d %d %s %d %d/%d/%d",&P.id,&P.nom,&P.marque,&P.prix,&P.qte,&P.qtevendue,&P.fournisseur,&P.enstock,&P.date.j,&P.date.m,&P.date.a);
      if (P.id == idP) {
        if (P.enstock==1) {
         printf("Le produit %s est en stock \n",P.nom);
        return ;}
         else {  printf("Le produit %s est epuise \n",P.nom);
             return;
      }


}
fclose(fp);
  return 0;
}
};
void ModifierProduit(long int ID) {
produit P;
FILE *fp = fopen("stock.txt", "r");
FILE *fp1 = fopen("stockUPDATED.txt", "w");
char c;
int ok, choix;
if (checkIfProductExists(ID)==1) //une fonction deja definie precedemment
{
   FILE *fp = fopen("stock.txt", "r");
   FILE *fp1 = fopen("stockUPDATED.txt", "w");
  if (fp == NULL)
  {
    printf("Error opening file\n");
    return;}
 if (fp1 == NULL)
 {
    printf("Error creating file\n");
    return;}
   int readSuccess;
while ((readSuccess = fscanf(fp,"%ld %s %s %f %d %d %s %d %d/%d/%d",&P.id,&P.nom,&P.marque,&P.prix,&P.qte,&P.qtevendue,&P.fournisseur,&P.enstock,&P.date.j,&P.date.m,&P.date.a)) == 11)
    {
        ok=1;
        while (ok==1)
        {
        printf("Choisissez le detail a modifier :\n",
         "(1)ID \n(2)nom \n(3)marque \n(4)prix \n(5)qte \n");
         printf("(6)qtevendue \n(7)fournisseur \n(8)enstock \n(9)date de restockage \n");
        scanf("%d", &choix);
        switch (choix)
           {
              case 1:
                  printf("\n Entrez le nouvel id de ce produit: ");
                  scanf("%ld", &P.id);
                 break;
               case 2:
                  printf("\n Entrez le nouveau nom de ce produit : ");
                  scanf("%s", &P.nom);
                 break;
               case 3:
                  printf("\n Entrez la nouvelle marque de ce produit : ");
                  scanf("%s", &P.marque);
                 break;
               case 4:
                  printf("\n Entrez le nouveau prix de ce produit : ");
                  scanf("%f", &P.prix);
                 break;
               case 5:
                  printf("\n Entrez la nouvelle qte de ce produit : ");
                  scanf("%d", &P.qte);
                 break;
               case 6:
                  printf("\n Entrez la nouvelle qte vendue de ce produit : ");
                  scanf("%d", &P.qtevendue);
                 break;
               case 7:
                  printf("\n Entrez le nouveau fournisseur de ce produit : ");
                  scanf("%s", &P.fournisseur);
                 break;
               case 8:
                  printf("\n Entrez la nouvelle etat de disponibilite de ce produit : ");
                  scanf("%d", &P.enstock);
                 break;
               case 9:
                  printf("\n Entrez la nouvelle date de restockage sous forme j/m/a: ");
                   scanf("%d/%d/%d", P.date.j, P.date.m, P.date.a);
                 break;
               
           }
           printf("Voulez-vous changer un autre detail pour ce produit? \n (1)Oui \n (2)Non \n");
           scanf("%d",ok);
        }
           
  fprintf(fp1,"%ld %s %s %f %d %d %s %d %d/%d/%d",P.id,P.nom,P.marque,P.prix,P.qte,P.qtevendue,P.fournisseur,P.enstock,P.date.j,P.date.m,P.date.a);
}
}
else printf("Cet identifant ne correspond a aucun produit");        
    
fclose(fp);
fclose(fp1);  
rename("stockUPDATED.txt", "stock.txt");
  
if (remove("stock.txt") == 0) 
{
        printf("l'ancien fichier a ete supprime avec succees.");
    } 
    else {
        printf("l'ancien fichier n'a pas ete supprime.");
       printf("la nouvelle base de donnees se trouve a ce chemin:\n","stockUPDATED.txt\n");       
}
}

void affichageproduits(){
	FILE *fp= fopen("stock.txt","r");
    produit product; 
	
	if (fp == NULL){
       printf("Error! opening file");
       return;}
       
	system("cls");
    printf("\nLe stock\n");
    printf("\n Identifiant \t|Nom             \t|Marque             \t|Prix         \t|Quantite    \t|Quantite vendue   \t|Fournisseur      \t|En stock \t|Date de restockage\t");
    printf("\n----------------+-----------------------+-----------------------+---------------+---------------+----------------------+------------------------+---------------+-------------------\n");
      while (!feof(fp)){
	         fscanf(fp, "%ld %s %s %f %d %d %s %d %d/%d/%d", &product.id,&product.nom,&product.marque, &product.prix, &product.qte, &product.qtevendue, &product.fournisseur, &product.enstock, &product.date.j, &product.date.m, &product.date.a) ; 
             printf("%13d\t|%20s\t|%15s\t|%14f\t|%10d\t|%16d\t|%16s\t|%9d\t|\t%2d/%2d/%4d \n", product.id,product.nom,product.marque,product.prix, product.qte,product.qtevendue,product.fournisseur, product.enstock,product.date.j,product.date.m,product.date.a);
}
}
void main() {
    // Write C code here
  int choix,id,choix1,r;
  char choice,marque[100],nom[100],ch[10];
  choix=0;
  do {
  	system("cls");
  printf("\n ******** MENU PRINCIPAL ******** \n");
  printf("\n1 - Ajouter un produit");
  printf("\n2 - Modifier un produit");
  printf("\n3 - Supprimer un produit");
  printf("\n4 - Recherche d'un produit dans le stock");
  printf("\n5 - Tri des produits dans le stock");
  printf("\n6 - Afficher la description d'un produit");
  printf("\n7 - Tester la disponibilite d'un produit");
  printf("\n8 - Afficher la liste de tous les produits");
  printf("\n9 - Quitter");
  printf("\n\nChoix: ");
  fflush(stdin);
  scanf("%d", &choix);
  } while (choix<1 || choix>9);

	switch(choix) {
	case 1: 
	system("cls");
    //char choice[100];

    do {
    // Add a new stock item to the list
    ajout();

    // Prompt the user to add another item or exit
    printf("Voulez vous ajouter un autre produit? (O/N)");
    scanf(" %c", &choice);
    } while (choice == 'O' || choice == 'o');
    printf("si vous voulez retournez au menu principal pressez -1: \n");
    scanf("%d",&r);
    if (r==-1) {
    	main();
	}
    break;
    case 2:
	 system("cls");
    printf("Ecrire l'id du produit que vous souhaitez modifier: \n");
    scanf("%ld",&id);
    ModifierProduit(id);
    printf("si vous voulez retournez au menu principal pressez -1: \n");
    scanf("%d",&r);
    if (r==-1) {
    	main();}
    break;
    case 3:
    	system("cls");
    	printf("Ecrire l'id du produit que vous souhaitez supprimer: \n");
    	scanf("%ld",&id);
    	supprimer_produit(id);
    	printf("si vous voulez retournez au menu principal pressez -1: \n");
    scanf("%d",&r);
    if (r==-1) {
    	main();}
        break;
    case 4:
    	system("cls");
        printf("Selon quel critere voulez-vous faire la recherche: \n ");
        printf("(1)Nom \n (2)Marque \n");
        scanf("%d",&choix1);
        if (choix1==1) {
        	printf("Ecrire le nom du produit que vous souhaitez chercher: \n");
        	gets(nom);
        	rechercheparnom(nom);
    }
       if (choix1==2) {
       	printf("Ecrire la marque que vous souhaitez chercher: \n");
       	scanf("%s",marque);
       	rechercheparmarque(marque);
   }
   printf("si vous voulez retournez au menu principal pressez -1: \n");
    scanf("%d",&r);
    if (r==-1) {
    	main();}
   break;
   case 5:
   	system("cls");
   	printf("Selon quel critere voulez-vous trier les produits: \n ");
    printf("(1)Nom \n (2)Prix \n (3)Fournisseur \n");
    scanf("%d",&choix1);
    if (choix1==1) {
    	Tri_par_nom();
   }
    if (choix1==2) {
    	trieparprix();
    	affichageproduits();
   }
    if (choix1==3) {
    	TriParFournisseur();
   }
   printf("si vous voulez retournez au menu principal pressez -1: \n");
    scanf("%d",&r);
    if (r==-1) {
    	main();}
    break;
    case 6:
    	system("cls");
    	printf("Ecrire l'id du produit que vous souhaitez afficher sa description: \n");
    	scanf("%ld",&id);
    	afficher_description(id);
    	printf("si vous voulez retournez au menu principal pressez -1: \n");
    scanf("%d",&r);
    if (r==-1) {
    	main();}
    	break;
    case 7:
    	printf("Introduire l'identifiant du produit: ");
        scanf("%li",&id);
        DisponibilityCheck(id);
        printf("si vous voulez retournez au menu principal pressez -1: \n");
    scanf("%d",&r);
    if (r==-1) {
	
    	main();}
        break;
    case 8:
    	system("cls");
    	affichageproduits();
    	printf("si vous voulez retournez au menu principal pressez -1: \n");
    scanf("%d",&r);
    if (r==-1) {
    	main();}
    	break;
    case 9:
    	exit(EXIT_SUCCESS);
      break;
    default:
      printf("ok");
      break;
  }
  }
