#include<stdio.h>
#include<stdlib.h>

typedef struct list{
	int vertex, edge, value;
}LIST;


void printList(LIST *root, int size){
	int i;
	for(i=0; i<size; ++i){
		printf("%d %d %d\n",root[i].value, root[i].vertex, root[i].edge);
	}
}

int findPath(LIST *list, int edge, int newEdge, int newValue, int visited[100], int *array, int size){
	int i;
	i = 0;
	int control = 0;
	if(edge == newEdge){
		return 1;
	}
	while(i < size && control == 0){
		if(list[i].vertex == edge && visited[list[i].edge] == 0){
			if(list[i].edge == newEdge){
				return list[i].value;
			}
			else{
				visited[edge] = 1;
				control = findPath(list, list[i].edge, newEdge, newValue, visited, array, size);
				if(control != 0)
					array[list[i].edge] = 1;
			}
		}
		else{
			if(list[i].edge == edge && visited[list[i].vertex] == 0){
				if(list[i].vertex == newEdge){
					return list[i].value;
				}
				else{
					visited[edge] = 1;
					control = findPath(list, list[i].vertex, newEdge, newValue, visited, array,size);
					if(control != 0)
						array[list[i].vertex] = 1;
				}
			}
		}	
		i++;
	}
	if(control == 0)
		return 0;
	else{
		return list[i].value;
	}
		
}

void findMaxEdge(LIST *list, int array[100], LIST *maxNode, int size){
	int i;

	for(i=0; i<size; ++i){
		if(array[ list[i].vertex ] == 1 && array[ list[i].edge ] == 1 && list[i].value > maxNode->value){
			maxNode->vertex = list[i].vertex;
			maxNode->edge = list[i].edge;
			maxNode->value = list[i].value;
		}
	}
}

void bubbleSort(LIST *list, int size){
	int i,j;
	LIST temp;
	for(i=0; i<size-1; ++i){
		for(j=0; j<size - i - 1; ++j){
			if(list[j].value > list[j+1].value){
				temp.value = list[j].value;
				temp.vertex = list[j].vertex;
				temp.edge = list[j].edge;
				
				list[j].value = list[j+1].value;
				list[j].vertex = list[j+1].vertex;
				list[j].edge = list[j+1].edge;
				
				list[j+1].value = temp.value;	
				list[j+1].vertex = temp.vertex;
				list[j+1].edge = temp.edge;
			}
		}
	}
}


int main(){
	
	
	int vertex, edge, value;
	int newVertex, newEdge, newValue;
	int maxEdge;
	FILE *file = NULL;
	int i;
	int control;
	int visited[100];
	int array[100];
	int size;
	int again;
	LIST maxNode;
	LIST list[100];
	
	if((file = fopen("graf.txt","r")) != NULL){
		i = 0;
		
		printf("Node Sayisini Giriniz:");
		scanf("%d",&size);
		
		while(!feof(file)){
			fscanf(file,"\n%d %d %d",&value, &vertex, &edge);
			list[i].value = value;
			list[i].vertex = vertex;
			list[i].edge = edge;
			i++;
		}
		
		
		again = 1;
		while(again == 1){
			
			for(i=0; i<100; ++i){
				visited[i] = 0;
				array[i] = 0;
			}
			
			printList(list, size-1);
			
			printf("Yeni baglantinin (Value Vertex Edge) giriniz:");
			scanf("%d %d %d",&newValue, &newVertex, &newEdge);
			
			
			control = 0;
			i = 0;
			visited[newVertex] = 1;
			array[newVertex] = 1;
			array[newEdge] = 1;
			while(control == 0){
				if(list[i].vertex == newVertex){
					control = findPath(list, list[i].edge, newEdge, newValue, visited, array, size-1);
					if(control != 0)
						array[list[i].edge] = 1;
				}
				else if(list[i].edge == newVertex){
					control = findPath(list, list[i].vertex, newEdge, newValue, visited, array, size-1);
					if(control != 0)
						array[list[i].vertex] = 1;
				}
				i++;
			}
			
			printf("\n");
			
			maxNode.value = -1;
			findMaxEdge(list, array, &maxNode, size-1);
			
			if(maxNode.value > newValue){
				i = 0;
				while(list[i].value != maxNode.value || list[i].vertex != maxNode.vertex || list[i].edge != maxNode.edge){
					i++;
				}
				list[i].value = newValue;
				list[i].edge = newEdge;
				list[i].vertex = newVertex;
			}
			
			bubbleSort(list, size-1);
			
			printList(list, size-1);
			
			printf("\n1.Yeni Baglanti\n2.Cikis\nChoice:");
			scanf("%d",&again);
		}
		
	}
	else
		printf("File could not be opened!");
	
	
	return 0;
}
