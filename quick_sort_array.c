#include <stdio.h>
#include <stdlib.h>

int *arr; // int declared here, but change date type as necessary
int list_sz;

int *arr_init(int);
void quick_sort(int *, int, int);
int qs_partition(int *, int , int , int );
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
    quick_sort(arr, 0, list_sz-1); // Sort in ascending order
    printf("Elements after quick sorting: ");
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

// Avg: O(nlogn) algo, worst: O(n^2), but no extra array required as in merge sort. Recursion needs memory
void quick_sort(int *a, int start, int end)
{
    int pivot, partition_index;

    if (start >= end)
	return;

    pivot = a[end]; // picking last element of the list as pivot
		    // Other ways: choose a random index, 
		    // choose 3 random indices & take median of the three numbers at these indices.
    partition_index = qs_partition(a, start, end, pivot);
    quick_sort(a, start, partition_index-1); 
    quick_sort(a, partition_index+1, end);
}

int qs_partition(int *a, int start, int end, int pivot)
{
    int left=start-1, right=end, tmp;

    while (left < right)
    {
	while (a[++left] < pivot) ;
	while ((right > 0) && (a[--right] > pivot)) ;
        if (left >= right )
	    break;
	// swap the elements at indices left & right
	tmp = a[left];
	a[left] = a[right];
	a[right] = tmp;
    }
    
    // swap elements at end & left
    tmp = a[left];
    a[left] = a[end];
    a[end] = tmp;

    return left;
}

void arr_free(int *a)
{
    free(a);
}


