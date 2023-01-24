#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct liste{
	int value;
	struct liste *next;
	struct liste *down; 
}LISTE;

LISTE* createNode(){
	LISTE *node = (LISTE *)malloc(sizeof(LISTE));
	node->next = NULL;
	node->down = NULL;
	return node;
}

void createLink(LISTE **heads, int index){
	
	LISTE *i, *j;
	i = heads[index];
	j = heads[index-1];
	
	while(i->next != NULL){
		while(j->next->value != i->next->value){
			j = j->next;
		}
		i->next->down = j->next;
		i = i->next;
	}
}

void *createLinkedList(LISTE **heads, int index, int value){
	LISTE *iter = heads[index];
	LISTE *temp;
	
	temp = createNode();
	temp->value = value;
	while(iter->next != NULL && iter->next->value < value){
		iter = iter->next;
	}
	temp->next = iter->next;
	iter->next = temp;
}

void createAllLinkedLists(LISTE **heads, int *values, int index, int levelCount, int size){
	
	int *elements;
	int random, i;
	
	elements = (int *)malloc(sizeof(int) * size);
	
	heads[index] = createNode();
	heads[index]->down = heads[index-1];
	
	if(index == levelCount - 1)
		return;

	else{
		for(i=0; i<(size+1)/2; ++i){
			do{
				random = rand()%size;	
			}while(values[random] == -1);
			elements[i] = values[random];
			createLinkedList(heads, index, values[random]);
			values[random] = -1;
			createLink(heads,index);
		}
	}
	
	createAllLinkedLists(heads, elements, index + 1, levelCount, (size+1)/2);
}

int searchElement(LISTE **heads, int levelCount, int value){
	LISTE *iter = heads[levelCount-2];
	int index = levelCount-2;
	int control = 1;
	
	if(value < heads[0]->next->value){
		return -1;
	}
	while((index != 0 || iter->next != NULL) && control){
		if(iter->next == NULL){
			iter = iter->down;
			index--;
		}
		else if(iter->next->value > value){
			if(index == 0){
				return -1;
			}
			else{
				iter = iter->down;
				index--;	
			}
			
		}
		else if(iter->next->value == value){
			control = 0;
		}
		else{
			iter = iter->next;
		}
	}
	if(control == 0){
		return index;
	}
	else{
		return -1;
	}
	
}

void addNode(LISTE **heads, int index, int value){
	LISTE *temp = createNode();
	LISTE *iter = heads[index];
	
	temp->value = value;
	while(iter->next != NULL && iter->next->value < value){
		iter = iter->next;
	}
	temp->next = iter->next;
	iter->next = temp;
	
	if(index != 0){
		iter = heads[index-1];
		while(iter->next != NULL && iter->next->value != value){
			iter = iter->next;
		}
		temp->down = iter->next;
	}
}

void deleteNode(LISTE **heads, int index, int value){
	LISTE *iter = heads[index];
	LISTE *temp;
	while(index != -1){
		if(iter->next->value == value){
			temp = iter->next;
			iter->next = iter->next->next;
			free(temp);
			iter = iter->down;
			index--;
		}
		else
			iter = iter->next;
	}
}

int menu(){
	int choice;
	printf("\n	1-Orijinal Listeyi Olustur\n	2-Tum Seviyeleri Ekrana Yazdir\n	3-Tum Seviyelerde Eleman Ara\n	4-Veri Yapisina Yeni Eleman Ekle\n	5-Veri Yapisindan Bir Deger Sil\n	6-Cikis\n\n\n");
	do{
		printf("	Seciminiz:");
		scanf("%d",&choice);
	}while(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6);
	return choice;
}

void printLinkedList(LISTE **heads, int index){
	LISTE *iter = heads[index];
	printf("%d. Katman - ",index+1);
	while(iter->next != NULL){
		printf("%d ",iter->next->value);
		iter = iter->next;
	}
	printf("\n");
}

int main(){
	
	LISTE **heads, **temp;
	int *values;
	int size, levelCount, value;
	int i;
	int choice = 1;
	int foundLevel, searchValue;
	int isContinue;
	
	srand(time(NULL));
	
	while(choice != 6){
		choice = menu();
		
		switch(choice){
			case 1:
				printf("Boyutu Giriniz:");
				scanf("%d",&size);
				
				levelCount = sqrt(size);
				levelCount += 3;
				heads = (LISTE**)malloc(sizeof(LISTE*)*levelCount);
				values = (int *)malloc(sizeof(int) * size);
				
				heads[0] = createNode();
				for(i=0; i<size; ++i){
					printf("%d. Elemani Giriniz: ",i+1);
					scanf("%d", &value);
					values[i] = value;
					createLinkedList(heads, 0, value);
				}
				
				createAllLinkedLists(heads, values, 1, levelCount, size);
				
				printf("\nVeri Yapisi Basarili Bir Sekilde Olusmustur\nDevam Etmek Icin Herhangi Bir Tusa Basiniz!\n");
				getch();
				system("cls");
				
				break;
			case 2:
				
				for(i=levelCount-1; i>=0; --i){
					printLinkedList(heads, i);
				}
				
				printf("\nDevam Etmek Icin Herhangi Bir Tusa Basiniz!\n");
				getch();
				system("cls");
				
				break;
			case 3:
				
				printf("Aramak Istediginiz Sayiyi Giriniz:");
				scanf("%d",&searchValue);
				foundLevel = searchElement(heads, levelCount, searchValue);
				if(foundLevel != -1)
					printf("Aradiginiz Sayi %d. Katmanda Bulunmustur!\n\n",foundLevel+1);
				else
					printf("Aradiginiz Sayi Veri Yapisinda Bulunmamaktadir!\n\n");
					
				printf("\nDevam Etmek Icin Herhangi Bir Tusa Basiniz!\n");
				getch();
				system("cls");
				
				break;
			case 4:
				printf("Eklemek Istediginiz Degeri Giriniz:");
				scanf("%d",&value);
				
				levelCount++;
				temp = heads;
				temp = (LISTE**)realloc(temp, levelCount*sizeof(LISTE*));
				if(temp != NULL){
					heads = temp;
					heads[levelCount-1] = createNode();
					heads[levelCount-1]->down = heads[levelCount-2];
					for(i = 0; i<levelCount-1; i++){
						addNode(heads, i, value);
					}
					printf("Eleman Basarili Bir Sekilde Eklendi!\n");
				}
				else{
					printf("Alan Acilamadi!\n");
				}
				
				printf("\nDevam Etmek Icin Herhangi Bir Tusa Basiniz!\n");
				getch();
				system("cls");
					
				break;
			case 5:
				printf("Silmek Istediginiz Degeri Giriniz:");
				scanf("%d",&value);
				
				foundLevel = searchElement(heads, levelCount, value);
				if(foundLevel != -1){
					
					if(foundLevel == levelCount-2){
						levelCount--;
						temp = heads;
						temp = (LISTE**)realloc(temp, levelCount*sizeof(LISTE*));
						if(temp != NULL)
							heads = temp;
						else{
							printf("Alan Acilamadi!\n");
						}
					}
					
					deleteNode(heads, foundLevel, value);
					printf("Eleman Basarili Bir Sekilde Silindi!\n");
					
				}
				else
					printf("Silmek Istediginiz Eleman Yapida Bulunmamaktadir!\n");
					
				printf("\nDevam Etmek Icin Herhangi Bir Tusa Basiniz!\n");
				getch();
				system("cls");
				
				break;
			default:
				break;
		}
	}
	
	return 0;
}
