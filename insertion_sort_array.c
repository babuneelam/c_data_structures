#include <stdio.h>
#include <stdlib.h>

#define NO_MORE -1

int *arr; // int declared here, but change date type as necessary
int list_sz;

int *arr_init(int);
void insertion_sort(int *, int);
void arr_display(int *, int);
void arr_free(int *);

int main()
{
    int i;

    printf("Enter the number of elements :");
    scanf("%d", &list_sz);
    if (list_sz <0)
    {
	printf("Invalid list size \r\n");
	return 0;
    }
    arr = arr_init(list_sz);
    if (!arr)
	return 0;

    for (i=0; i<list_sz; i++)
	scanf("%d", &arr[i]); // INput verification not done
    insertion_sort(arr, list_sz); // Sort in ascending order
    printf("Elements after insertion sorting: ");
    for (i=0; i<list_sz; i++)
	printf("%d ", arr[i]);
    printf("\r\n");

    arr_free(arr);
    arr=NULL;

    return 0;
}

int *arr_init(int size)
{
    int *a=NULL;

    a = (int *)calloc(1, size*sizeof(int));
    if (!a)
	printf("Memory Allocation failure \r\n");
    return a;
}

void insertion_sort(int *a, int size)
{
    int i, j, tmp;

    // Avg: O(n^2), Worst: O(n^2), Best: O(n)
    for(i=1; i<size; i++)
    {
	tmp = a[i];
	// Sort in ascending order
	for(j=i; (j>0) && (tmp < a[j-1]); j--)
	    a[j] = a[j-1];
	a[j] = tmp;
    }
}

void arr_free(int *a)
{
    free(a);
}


