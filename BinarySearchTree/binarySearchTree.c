#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct dosya{
	char dosyaIsmi[30];
	struct dosya *next;
}DOSYA;

typedef struct node{
	char kelime[50];
	int dosyaSayisi;
	struct node *right;
	struct node *left;
	struct dosya *dosyaRoot;
}NODE;

int menu(){
	int secim;
	do{
		system("cls");
		printf("\tEngin Memis\n\t19011040\n\n");
		printf("1. Yeni Dosya Ekle\n2. Dosya Sil\n3. Kelime Ara\n4. Agaci Yazdir\n5. Cikis\n\nSeciminiz:");
		scanf("%d",&secim);
	}while(secim < 1 || secim > 5);
}

DOSYA* dosyaNodeOlustur(){															//KELÝME NODE ÝÇERÝSÝNDE DOSYALARI TUTAN LÝNK LÝSTENÝN NODE'UNU OLUÞTURAN FONKSÝYON
	DOSYA *temp = (DOSYA*)malloc(sizeof(DOSYA));
	temp->next = NULL;
	return temp;
}

NODE* kelimeNodeOlustur(){															//AÐAÇTA BULUNAN NODELARI OLUÞTURAN FONKSÝYON
	NODE *temp = (NODE*)malloc(sizeof(NODE));
	temp->right = NULL;
	temp->left = NULL;
	temp->dosyaSayisi = 0;
	temp->dosyaRoot = NULL;
	return temp;
}


int kelimeAra(NODE *tree, char *aranan){											//ARANILAN KELÝME AÐAÇTA OLUP OLMADIÐINA BAKAN FONKSÝYON
	NODE *temp;
	if(tree == NULL)
		return 0;
	
	if( strcmp(aranan, tree->kelime) == 0 )
		return 1;
	
	if( strcmp(aranan, tree->kelime) > 0 )
		tree = tree->right;
	else
		tree = tree->left;
		
	kelimeAra(tree, aranan);
}

int dosyayiAra(DOSYA *root, char *aranan){
	while(root != NULL){
		if(strcmp(root->dosyaIsmi, aranan) == 0){
			return 1;
		}
		root = root->next;
	}
	return 0;
}

DOSYA* dosyayiKelimeyeEkle(NODE *node, char *dosyaIsmi){							//KELÝME NODE'UNUN ÝÇÝNDEKÝ LÝNK LÝSTEYE BULUNDUÐU DOSYANIN ADININ YERLEÞTÝRÝLMESÝ
	DOSYA *root = node->dosyaRoot;
	DOSYA *iter, *temp;
	if(root == NULL){
		root = dosyaNodeOlustur();
		strcpy(root->dosyaIsmi, dosyaIsmi);
		return root;
	}
	temp = dosyaNodeOlustur();
	strcpy(temp->dosyaIsmi, dosyaIsmi);
	if(strcmp(dosyaIsmi, root->dosyaIsmi) < 0){
		temp->next = root;
		return temp;
	}
	
	iter = root;
	while(iter->next != NULL && strcmp(dosyaIsmi, iter->next->dosyaIsmi) > 0){
		iter = iter->next;
	}
	temp->next = iter->next;
	iter->next = temp;
	return root;
}

NODE* kelimeyiEkle(NODE *tree, char *kelime, char *dosyaIsmi){						//KELÝMEYÝ AÐAÇ YAPISINA EKLEYEN FONSKSÝYON
	
	if(tree == NULL){
		tree = kelimeNodeOlustur();
		strcpy(tree->kelime, kelime);
		tree->dosyaSayisi++;
		tree->dosyaRoot = dosyayiKelimeyeEkle(tree, dosyaIsmi);
		return tree;
	}
	
	if(strcmp(kelime, tree->kelime) > 0)
		tree->right = kelimeyiEkle(tree->right, kelime, dosyaIsmi);
	else
		tree->left = kelimeyiEkle(tree->left, kelime, dosyaIsmi);
	return tree;
}

NODE *kelimeyiAra(NODE *tree, char *kelime){							//AÐAÇTA BULDUÐU KELÝMENÝN NODE'UNU DÖNDÜRÜYOR
	if(tree == NULL)
		return NULL;
	if(strcmp(tree->kelime, kelime) == 0)
		return tree;
	
	if(strcmp(tree->kelime, kelime) > 0)
		kelimeyiAra(tree->left, kelime);
	else
		kelimeyiAra(tree->right, kelime);
	return tree;
}

void maxBul(NODE *tree, char *silinecek){
	while(tree->right != NULL)
		tree = tree->right;
	strcpy(silinecek, tree->kelime);
}

void minBul(NODE *tree, char *silinecek){
	while(tree->left != NULL)
		tree = tree->left;
	strcpy(silinecek, tree->kelime);
}

NODE* deleteElement(NODE *tree, char *kelime, int *control){
	char silinecek[50];
	char word[50];
	NODE *temp;
	DOSYA *iter;
	DOSYA *temp2;
	if(tree == NULL)
		return NULL;
	
	if(strcmp(tree->kelime, kelime) == 0){											
		if(tree->right == NULL && tree->left == NULL){					//EÐER SÝLÝNECEK NODE'UN ÇOCUÐU YOKSA DÝREKT SÝL
			return NULL;
		}
		
		if(tree->right != NULL){				//SAÐDA ÇOCUÐU VARSA 
			
			temp = tree->right;
			while(temp->left != NULL)					//SAÐDAKÝ EN KÜÇÜK ELEMANI BULUYOR
				temp = temp->left;
				
			strcpy(word, tree->kelime);					//SAÐDAKÝ BULDUÐU EN KÜÇÜK ÇOCUK ÝLE BÝLGÝLERÝNÝN YER DEÐÝÞTÝRMESÝ
			strcpy(tree->kelime, temp->kelime);
			strcpy(temp->kelime, word);
			
			temp2 = tree->dosyaRoot;						//ÝÇÝNDEKÝ LÝNK LÝSTELERÝN KÖKLERÝNÝN YER DEÐÝÞTÝRMESÝ
			tree->dosyaRoot = temp->dosyaRoot;
			temp->dosyaRoot = temp2;  
			
			tree->right = deleteElement(tree->right, kelime, control);			//SAÐ ÇOCUKTA RECURSÝVE OLARAK DEVAM EDÝYOR
			return tree;
		}
	
		temp = tree->left;						//SAÐDA ÇOCUK YOK SOLDA VAR ÝSE
		while(temp->right != NULL)				//SOLDAKÝ EN BÜYÜK ELEMANI BULUYOR
			temp = temp->right;
		
		strcpy(word, tree->kelime);				//BÝLGÝLER YER DEÐÝÞTÝRÝLÝYOR
		strcpy(tree->kelime, temp->kelime);
		strcpy(temp->kelime, word);
		
		temp2 = tree->dosyaRoot;
		tree->dosyaRoot = temp->dosyaRoot;
		temp->dosyaRoot = temp2;  
		
		tree->left = deleteElement(tree->left, kelime, control);		//SOL ÇOCUKTA RECURSÝVE OLARAK DEVAM EDÝYOR
		return tree;
	}
	
	if(strcmp(tree->kelime, kelime) < 0){									//ARADAÐI KELÝME DAHA BÜYÜK ÝSE SAÐ AÐAÇTAN DEVAM
		tree->right = deleteElement(tree->right, kelime, control);
		return tree;
	}
	else{																	//ARADIÐI KELÝME DAHA KÜÇÜK ÝSE SOL AÐAÇTAN DEVAM
		tree->left = deleteElement(tree->left, kelime, control);
		return tree;
	}
}

void dosyayiSil(NODE **tree, char *silinecekDosya, int *control){				//BÜTÜN AÐAÇI RECURSÝVE GEZÝP SÝLMEK ÝSTENÝLEN DOSYAYA SAHÝP KELÝME VAR ÝSE ÝÞLEM YAPIYOR
	DOSYA *iter, *freeEdilecek;
	NODE *temp;

	if(*tree == NULL)
		return;
	temp = (*tree);
	dosyayiSil( &(temp->left), silinecekDosya, control);	
	iter = (*tree)->dosyaRoot;
	if(strcmp(iter->dosyaIsmi, silinecekDosya) == 0 && iter->next == NULL){						//KELÝME SADECE SÝLÝNECEK DOSYADA BULUNUYORSA KELÝME AÐAÇTAN SÝLÝNECEK
		(*tree) = deleteElement((*tree), (*tree)->kelime, control);
		*control = 1;
	}	
	else if(strcmp(iter->dosyaIsmi, silinecekDosya) == 0 && iter->next != NULL){					//KELÝME SADECE SÝLÝNECEK DOSYADA BULUNMUYORSA VE DOSYA LÝNK LÝSTEDE EN BAÞTA ÝSE
		(*tree)->dosyaRoot = iter->next;
	}
	else if(iter->next != NULL){																			//KELÝME LÝNK LÝSTEDE BAÞTA DEÐÝLSE
		while(iter->next != NULL && strcmp(iter->next->dosyaIsmi, silinecekDosya) < 0){
			iter = iter->next;
		}
		if(iter->next != NULL){
			if(strcmp(iter->next->dosyaIsmi, silinecekDosya) == 0){
				iter->next = iter->next->next;	
			}
		}
	
	}
	dosyayiSil( &(temp->right), silinecekDosya, control);
}

void dosyaYazdir(NODE *root){
	DOSYA *temp = root->dosyaRoot;
	while(temp != NULL){
		printf("%s ",temp->dosyaIsmi);
		temp = temp->next;
	}
}

void agacYazdir(NODE *root){
	if(root == NULL )
		return;
	
	agacYazdir(root->left);
	printf("\n%s: ",root->kelime);
	dosyaYazdir(root);
	agacYazdir(root->right);
}

int main(){
	
	int secim;
	char kelime[50];
	char dosyaIsmi[50];
	char dosya[50];
	char satir[1000];
	char silinenDosya[50];
	int i,j;
	int control;
	FILE *file = NULL;
	
	NODE *tree = NULL;
	NODE *node = NULL;
	
	do{
		secim = menu();
		switch(secim){
			case 1:
				system("cls");		
				printf("Dosyayi Giriniz:");
				scanf("%s",dosyaIsmi);
				
				file = fopen(dosyaIsmi, "r");
				if(file != NULL){
					while(!feof(file)){
						strcpy(dosya, "");
						fscanf(file,"%[^:]s",dosya);													
						fscanf(file,"%[^\n]s",satir);
						fscanf(file, "%c");
						j = 0;
						strcpy(kelime, "");
						for(i=2; i<strlen(satir); i++){
							
							if(satir[i] == ' '){
								kelime[j] = '\0';
								node = kelimeyiAra(tree, kelime);
								if(node == NULL)
									tree = kelimeyiEkle(tree, kelime, dosya);
								else{
									if(dosyayiAra(node->dosyaRoot, dosya) == 0){
										node->dosyaRoot = dosyayiKelimeyeEkle(node, dosya);
									}
								}
								j = 0;
								strcpy(kelime, "");
							}
							else{
								kelime[j] = satir[i];
								j++;
							}
						}
						kelime[j] = '\0';
						node = kelimeyiAra(tree, kelime);
						if(node == NULL){
							tree = kelimeyiEkle(tree, kelime, dosya);
						}
						else{
							if(dosyayiAra(node->dosyaRoot, dosya) == 0){
								node->dosyaRoot = dosyayiKelimeyeEkle(node, dosya);
							}
						}
					}
					fclose(file);
					printf("Agac Yapisi Basarili Bir Sekilde Olusturuldu!");
				}
				else{
					printf("Dosya Bulunamadi!");
				}
				break;
				
			case 2:
				printf("Silinecek Dosyayi Giriniz:");
				scanf("%s",silinenDosya);
				control = 1;
				while(control){
					control = 0;
					dosyayiSil(&tree, silinenDosya, &control);
				}
				
				break;
				
			case 3:
				system("cls");
				printf("Aradiginiz Kelimeyi Giriniz:");
				scanf("%s",kelime);
				if(kelimeAra(tree, kelime))
					printf("Kelime bulundu!");
				else
					printf("Kelime bulunamadi!");
				break;
			case 4:
				system("cls");
				printf("Agac Yapisi InOrder (L-N-R) Seklinde Yazdirilmaktadir!\n");
				agacYazdir(tree);
				break;
			case 5:
				printf("Basarili Sekilde Cikis Yaptiniz!");
				break;
		}
		printf("\nDevam Etmek Icin Herhangi Bir Tusa Basiniz!");
		getch();
	}while(secim != 5);
	
	return 0;
}
