#ifdef _VS
#include "../LeetCode/stdafx.h"
#else
#include "shared.h"
#endif
#include "heap.cpp"

namespace Algorithms {
    class InnerSort{
    public:
        void insertSort(vector<int>& arr){
            for(int i = 1; i < arr.size(); ++ i){
                int key = arr[i];
                int j = i - 1;
                while(j >= 0 && arr[j] > key){
                    swap(arr[j], arr[j + 1]);
                    j --;
                }
                arr[j + 1] = key;
            }
        }
        void insertSort(int arr[], int length){
            for(int i = 1; i < length; ++ i){
                int key = arr[i];
                int j = i - 1;
                while(j >= 0 && arr[j] > key){
                    swap(arr[j], arr[j + 1]);
                    j --;
                }
                arr[j + 1] = key;
            }
        }
    };
    class MergeSort{
    public:
        void sort(vector<int>& arr){
            mergeSort(arr, 0, (int)arr.size() - 1);
        }
    private:
        void mergeSort(vector<int>& arr, int p, int r){
            if (p >= r)
                return;
            int q = (p + r) / 2;
            mergeSort(arr, p, q);
            mergeSort(arr, q + 1, r);
            merge(arr, p, q, r);
        }
        void merge(vector<int>& arr, int p, int q, int r){
            vector<int> left (arr.begin() + p, arr.begin() + q + 1);
            vector<int> right (arr.begin() + q + 1, arr.begin() + r + 1);
            auto liter = left.begin(), riter = right.begin(), aiter = arr.begin() + p;
            while(liter != left.end() && riter != right.end()){
                if(*liter <= *riter)
                    *(aiter ++) = *(liter ++);
                else
                    *(aiter ++) = *(riter ++);
            }
            while(liter != left.end()){
                *(aiter ++) = *(liter ++);
            }
            while(riter != right.end()){
                *(aiter ++) = *(riter ++ );
            }
        }
    };
    
    class BubbleSort{
    public:
        void sort(vector<int>& arr){
            for(auto iter = arr.begin(); iter != arr.end(); ++ iter){
                for(auto iter2 = arr.end() - 1; iter2 != iter;  -- iter2){
                    if(*iter2 < *(iter2 - 1))
                        swap(*iter2, *(iter2 - 1));
                }
            }
        }
    };
    
    class HeapSort{
    public:
        void sort(vector<int>& arr){
            heap h;
            h.heap_sort(arr);
        }
    private:
        int left(int i){
            return 2 * i;
        }
        int right(int i ){
            return 2 * i + 1;
        }
        int parent(int i){
            return i / 2;
        }
    };
    
    class QuickSort{
    public:
        void sort(vector<int>& arr){
            qsort(arr, 0, (int)arr.size() - 1);
        }
    private:
        void qsort(vector<int>& arr, int start, int end){
            if(start >= end)
                return;
            
            
            int p = partition(arr, start, end);
            qsort(arr, start, p - 1);
            qsort(arr, p + 1, end);
        }
        int partition(vector<int>& arr, int start, int end){
            int i = start - 1, x = arr[end];
            for(int j = start; j < end; ++ j){
                if(arr[j] <= x){
                    i ++;
                    swap(arr[i], arr[j]);
                }
            }
            swap(arr[i + 1], arr[end]);
            return i + 1;
        }
    };
    class helper{
    public:
        void test(vector<int> original, vector<int> expected){
            InnerSort is;
            auto temp = original;
            is.insertSort(temp);
            ASSERT_EQ(temp, expected);
            auto temp2 = original;
            is.insertSort(&temp2[0], (int)temp2.size());
            ASSERT_EQ(temp2, expected);
            
            auto temp3 = original;
            MergeSort ms;
            ms.sort(temp3);
            ASSERT_EQ(expected, temp3);
            
            auto temp4 = original;
            BubbleSort bs;
            bs.sort(temp4);
            ASSERT_EQ(expected, temp4);
            
            auto temp5 = original;
            HeapSort hs;
            hs.sort(temp5);
            ASSERT_EQ(expected, temp5);
            
            auto temp6 = original;
            QuickSort qs;
            qs.sort(temp6);
            ASSERT_EQ(expected, temp6);
        }
    };
    TEST(Sort, sort) {
        helper h;
        h.test({5, 4, 3, 2, 1}, {1, 2, 3, 4, 5});
        h.test({1}, {1});
        h.test({2, 1}, {1, 2});
        h.test({1, 2}, {1, 2});
        h.test({1, 3, 2}, {1, 2, 3});
    }
}
