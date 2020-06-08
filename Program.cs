using System;

namespace ConsoleApp1
{
     class Program
     {
          static void swap(ref int a, ref int b)
          {
               int c = a;
               a = b;
               b = c;
          }
          static void Insertion_Sort(int []d ,int n, ref int comp, ref int move)
          {
               comp = 0;
               move = 0;
               int length = n;
               int[] da2 = new int[length];
               for (int k = 0; k < length; k++)
                    da2[k] = d[k];
               for (int i = 2; i < length; i++)
               {
                    da2[0] = da2[i];
                    move++;
                    int j = i - 1;
                    while (da2[0] < da2[j])
                    {
                         comp++;
                         da2[j + 1] = da2[j--];
                         move++;
                    }
                    comp++;
                    da2[j + 1] = da2[0];
                    move++;
               }
          }        
          static void Binary_Insert_Sort(int[] a, int n, ref int comp, ref int move)
          {
               comp = 0;
               move = 0;
               int i, j, temp, low, high, m;
               for (i = 1; i < n; ++i)
               {
                    temp = a[i];
                    low = 0;
                    high = i - 1;
                    while (low <= high)
                    {
                         m = (low + high) / 2;
                         comp++;
                         if (temp < a[m])
                         {
                              high = m - 1;
                         }
                         else
                         {
                              low = m + 1;
                         }
                    }
                    for (j = i - 1; j > high; j--)
                    {
                         move++;
                         a[j + 1] = a[j];
                    }
                    move++;
                    a[high + 1] = temp;
               }

          }
          static void Shell_Sort(int[] a, int n, ref int comp, ref int move)
          {
               comp = 0;
               move = 0;
               int size = n;
               for (int i = size / 2; i > 0; i = i / 2)
               {
                    for (int j = i; j < size; j++)
                    {
                         for (int k = j - i; k >= 0; k = k - i)
                         {
                              comp++;
                              if (a[k] < a[k + i])
                              {
                                   break;
                              }
                              else
                              {
                                   move++;
                                   swap(ref a[k], ref a[k + 1]);
                              }
                         }
                    }
               }
          }
          static int partition(int []arr, int low, int high, ref int comp, ref int move)
          {
               int pivot = arr[high];    
               int i = (low - 1);     
               for (int j = low; j < high; j++)
               {
                    comp++;
                    if (arr[j] <= pivot)
                    {
                         i++;
                         swap(ref arr[i],ref arr[j]);
                         move++;
                    }
               }
               swap(ref arr[i+1], ref arr[high]);
               move++;
               return (i + 1);
          }
          static void Quick_Sort(int []arr, int low, int high, ref int comp, ref int move)
          {
               if (low < high)
               {
                    int p = partition(arr, low, high,ref comp,ref move);
                    Quick_Sort(arr, low, p - 1, ref comp, ref move);
                    Quick_Sort(arr, p + 1, high, ref comp, ref move);
               }
          }          
          static void Select_Sort(int []a,int n, ref int comp, ref int move)
          {
               int i, index, j, temp;
               for (i = 1; i < n; i++)//执行第i遍扫描操作
               {
                    index = i;
                    for (j = i + 1; j < n; j++)//比较无序序列中的记录
                    {
                         comp++;
                         if (a[index] > a[j])//记录序列中最小值的位置
                         {
                              index = j;
                         }
                    }
                    if (index != i)//如果无序序列中第一个记录不是最小值，则进行交换
                    {
                         move++;
                         temp = a[index];
                         a[index] = a[i];
                         a[i] = temp;
                    }
               }

          }
          static void maxHeapIfy(int []A, int i, int n, ref int comp, ref int move)
          {
               int l = 2 * i + 1;
               int r = 2 * i + 2;
               int largest = i;
               comp++;
               if (l < n && A[l] > A[largest])
                    largest = l;
               comp++;
               if (r < n && A[r] > A[largest])
                    largest = r;

               if (largest != i)
               {
                    move++;
                    swap(ref A[i],ref  A[largest]);
                    maxHeapIfy(A, largest, n,ref comp,ref move);
               }
          }
          static void buildMaxHeap(int []A, int n, ref int comp, ref int move)
          {
               for (int i = n / 2 - 1; i >= 0; i--)
                    maxHeapIfy(A, i, n, ref comp, ref move);

          }


          static void Heap_Sort(int []A, int n, ref int comp, ref int move)

          {
               buildMaxHeap(A, n, ref comp, ref move);
               for (int i = n - 1; i > 0; i--)
               {
                    swap(ref A[0],ref A[i]);
                    maxHeapIfy(A, 0, i, ref comp, ref move);
               }
          }
          static void merge(int []arr, int l, int m, int r, ref int comp, ref int move)
          {
               int i, j, k;
               int n1 = m - l + 1;
               int n2 = r - m;
               int[] L = new int[n1];
               int[] R = new int[n2];

               for (i = 0; i < n1; i++)
               {
                    move++;
                    L[i] = arr[l + i];
               }
               for (j = 0; j < n2; j++)
               {
                    move++;
                    R[j] = arr[m + 1 + j];
               }

               i = 0;
               j = 0;
               k = l;
               while (i < n1 && j < n2)
               {
                    comp++;
                    if (L[i] <= R[j])
                    {
                         move++;
                         arr[k] = L[i];
                         i++;
                    }
                    else
                    {
                         move++;
                         arr[k] = R[j];
                         j++;
                    }
                    k++;
               }

               while (i < n1)
               {
                    move++;
                    arr[k] = L[i];
                    i++;
                    k++;
               }

               while (j < n2)
               {
                    move++;
                    arr[k] = R[j];
                    j++;
                    k++;
               }
          }
          static void Merge_Sort(int []arr, int l, int r, ref int comp, ref int move)
          {
               if (l < r)
               {

                    int m = l + (r - l) / 2;

                    Merge_Sort(arr, l, m,ref comp,ref move);
                    Merge_Sort(arr, m + 1, r, ref comp, ref move);

                    merge(arr, l, m, r, ref comp, ref move);
               }
          }
          static void Bubble_Sort(int []a,int n,ref int comp,ref int move)
          {
               comp = 0;
               move = 0;
               short swap_check = 1;
               for (int i = 0; (i < n) && (swap_check == 1); i++)
               {
                    swap_check = 0;
                    for (int j = 0; j < n - 1 - i; j++)
                    {
                         comp++;
                         if (a[j] > a[j + 1])
                         {
                              move++;
                              swap_check = 1;
                              swap(ref a[j], ref a[j + 1]);
                         }
                    }
               }

          }
          static void Gen_Rad_numbers(int[] a, int n)
          {
               Random r = new Random(0);
               for(int i= 0; i < n; i++)
               {
                    a[i] = r.Next();
               }
          }
          static int [] Copy_Array(int []a,int n)
          {
               int[] b = new int[n];
               for(int i = 0; i < n; i++)
               {
                    b[i] = a[i];                    
               }
               return b;
          }
          static void Print_Array(int []a,int n)
          {
               for(int i = 0; i < n; i++)
               {
                    Console.Write(a[i]);
                    Console.Write(" ");
               }
               Console.WriteLine();
          }

          static void Gen_Rad_numbers1000(int[] a, int n)
          {
               Random r = new Random(0);
               for (int i = 0; i < n; i++)
               {
                    a[i] = r.Next() % 1000;
               }
          }
          static bool Compare_Two_Number(int a, int b)
          {
               int c1 = 0, c2 = 0;
               while (a > 0)
               {
                    c1 += (a % 10);
                    a /= 10;
               }
               while (b > 0)
               {
                    c2 += (b % 10);
                    b /= 10;
               }
               return c1 < c2;
          }
          static void Our_Sort(int[] a, int n)
          {
               short swap_check = 1;
               for (int i = 0; (i < n) && (swap_check == 1); i++)
               {
                    swap_check = 0;
                    for (int j = 0; j < n - 1 - i; j++)
                    {                         
                         if (Compare_Two_Number(a[j + 1], a[j]))
                         {
                              swap_check = 1;
                              swap(ref a[j], ref a[j + 1]);
                         }
                    }
               }

          }
          static void Main(string[] args)
          {
               int comp = 0, move = 0;
               int n = 2000;
               for (n = 1000; n <= 5000; n += 1000)
               {
                    Console.WriteLine("This test n:{0} ",n);
                    int[] a = new int[n];
                    Gen_Rad_numbers(a, n);                   
                    int[] temp_array = Copy_Array(a, n);
                    //Bubble_Sort
                    comp = 0; move = 0;
                    Bubble_Sort(temp_array, n, ref comp, ref move);
                    Console.WriteLine("Bubble_Sort        {0:d10}:   comp: {1:d10}   move: {2:d10}", n, comp, move);
                    //Print_Array(temp_array, n);
                    temp_array = Copy_Array(a, n);
                    comp = 0; move = 0;
                    //Heap_Sort
                    Heap_Sort(temp_array, n, ref comp, ref move);
                    Console.WriteLine("Heap_Sort          {0:d10}:   comp: {1:d10}   move: {2:d10}", n, comp, move);
                    //Print_Array(temp_array, n);
                    temp_array = Copy_Array(a, n);
                    comp = 0; move = 0;
                    //Select_Sort
                    Select_Sort(temp_array, n, ref comp, ref move);
                    Console.WriteLine("Select_Sort        {0:d10}:   comp: {1:d10}   move: {2:d10}", n, comp, move);
                    //Print_Array(temp_array, n);
                    temp_array = Copy_Array(a, n);
                    comp = 0; move = 0;
                    //Quick_Sort
                    Quick_Sort(temp_array,0, n-1, ref comp, ref move);
                    Console.WriteLine("Quick_Sort         {0:d10}:   comp: {1:d10}   move: {2:d10}", n, comp, move);
                    //Print_Array(temp_array, n);
                    temp_array = Copy_Array(a, n);
                    comp = 0; move = 0;
                    //Shell_Sort
                    Shell_Sort(temp_array, n, ref comp, ref move);
                    Console.WriteLine("Shell_Sort         {0:d10}:   comp: {1:d10}   move: {2:d10}", n, comp, move);
                    //Print_Array(temp_array, n);
                    temp_array = Copy_Array(a, n);
                    comp = 0; move = 0;
                    //Binary_Insert_Sort
                    Binary_Insert_Sort(temp_array, n, ref comp, ref move);
                    Console.WriteLine("Binary_Insert_Sort {0:d10}:   comp: {1:d10}   move: {2:d10}", n, comp, move);
                    //Print_Array(temp_array, n);
                    temp_array = Copy_Array(a, n);
                    comp = 0; move = 0;
                    //Merge_Sort
                    Merge_Sort(temp_array,0, n-1, ref comp, ref move);
                    Console.WriteLine("Merge_Sort         {0:d10}:   comp: {1:d10}   move: {2:d10}", n, comp, move);
                    //Print_Array(temp_array, n);

               }


               int m = 20;
               int[] b = new int[m];
               Gen_Rad_numbers1000(b, m);
               Print_Array(b, m);
               Our_Sort(b, m);
               Print_Array(b, m);
               Console.ReadLine();
          }
     }
}
