#include <stdio.h>
#include <stdlib.h>

int *arr; // int declared here, but change date type as necessary
int list_sz;

int *arr_init(int);
void merge_sort(int *, int, int, int *);
void merge(int *, int , int , int , int *);
void merge_arrays(int *, int , int *, int , int *);
void arr_display(int *, int);
void arr_free(int *);

int main()
{
    int i;

    int *tmp_arr;

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

    tmp_arr = arr_init(list_sz);
    if (!tmp_arr)
    {
	arr_free(arr);
	return 0;
    }

    for (i=0; i<list_sz; i++)
	scanf("%d", &arr[i]); // INput verification not done
    merge_sort(arr, 0, list_sz-1, tmp_arr); // Sort in ascending order
    printf("Elements after Merge sorting: ");
    for (i=0; i<list_sz; i++)
	printf("%d ", arr[i]);
    printf("\r\n");

    arr_free(arr);
    arr_free(tmp_arr);
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

// Avg, Worst: O(nlogn) algo
void merge_sort(int *a, int start, int end, int *tmp_a)
{
    int i, j, mid;

    if (start >= end)
	return;

    mid = (start+end)/2;
    // Sort the first half of the array recursively
    merge_sort(a, start, mid, tmp_a);
    // Sort the second half of the array recursively
    merge_sort(a, mid+1, end, tmp_a);
    // Merge the sorted halves into a tmp array
    //merge_arrays(&a[start], (mid-start+1), &a[mid+1], (end-mid), tmp_a);
    merge(a, start, mid, end, tmp_a);
}

void merge(int *a, int start, int mid, int end, int *tmp_a)
{
    int i=start, j=mid+1, k=0;

    while ((i <= mid) && (j <= end))
    {
	if (a[i] < a[j])
	    tmp_a[k++]=a[i++];
	else
	    tmp_a[k++]=a[j++];
    }

    while (i <= mid )
	tmp_a[k++]=a[i++];

    while (j <= end)
	tmp_a[k++]=a[j++];

    // replace the original array with tmp array
    for(i=0, j=start; i <= (end-start); i++, j++)
	a[j] = tmp_a[i];
}

// Merge a1 & a2 arrays into array a. Unused in this file.
void merge_arrays(int *a1, int a1_size, int *a2, int a2_size, int *a)
{
    int i=0, j=0, k=0;

    while ((i < a1_size) && (j < a2_size))
    {
	if (a1[i] < a2[j])
	    a[k++]=a1[i++];
	else
	    a[k++]=a2[j++];
    }

    while (i < a1_size)
	a[k++]=a1[i++];

    while (j < a2_size)
	a[k++]=a2[j++];

    // replace the original array with tmp array
    for(i=0, j=start; i <= (end-start); i++, j++)
	a[j] = tmp_a[i];
}

void arr_free(int *a)
{
    free(a);
}


