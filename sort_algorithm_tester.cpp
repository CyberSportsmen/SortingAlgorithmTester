#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <array>
#include <chrono>
#include <thread>

using namespace std;
void nos()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

enum SortingMethods
{
    STL,
    RADIX10,
    RADIX2TO16,
    MERGE,
    SHELL,
    QUICK,
    HEAP,
    BUCKET,
    COUNT // important
};

std::string_view toString(SortingMethods method)
{
    static const std::array<std::string_view, SortingMethods::COUNT> names = {
        "STL", "RADIX10", "RADIX2TO16", "MERGE", "SHELL", "QUICK", "HEAP", "BUCKET"};

    if (static_cast<size_t>(method) < names.size())
        return names[method];
    else
        return "UNKNOWN";
}

template <class T>
class Tester
{
    vector<T> v;

    static void mergesort(std::vector<T> &a, std::vector<T> &c, T st, T dr)
    {
        if (st < dr)
        {
            T m = (st + dr) / 2;
            mergesort(a, c, st, m);
            mergesort(a, c, m + 1, dr);
            T i = st, j = m + 1, k = 0;
            while (i <= m && j <= dr)
                if (a[i] <= a[j])
                    c[k++] = a[i++];
                else
                    c[k++] = a[j++];
            while (i <= m)
                c[k++] = a[i++];
            while (j <= dr)
                c[k++] = a[j++];
            k = 0;
            for (i = st; i <= dr; i++)
                a[i] = c[k++];
        }
    }
    static void RadixSortPositive(std::vector<T> &vect, long long B = 10)
    {
        long long Max = -1;
        std::vector<long long> count(B, 0);
        long long N = vect.size();

        for (long long i = 0; i < N; i++)
            if (vect[i] > Max)
                Max = vect[i];

        for (__int128 exp = 1; exp <= Max; exp *= B)
        {
            std::vector<T> aux(N);
            std::fill(count.begin(), count.end(), 0);

            for (long long i = 0; i < N; i++)
                count[(vect[i] / exp) % B]++;
            for (long long i = 1; i < B; i++)
                count[i] += count[i - 1];

            for (long long i = N - 1; i >= 0; i--)
            {
                long long c = (vect[i] / exp) % B;
                count[c]--;
                aux[count[c]] = vect[i];
            }

            vect.swap(aux);
        }
    }
    static void RadixSort(std::vector<T> &v, long long B = 10)
    {

        std::vector<T> positives;
        std::vector<T> negatives;
        for (auto w : v)
            if (w < 0)
                negatives.push_back(-w);
            else
                positives.push_back(w);

        if (!positives.empty())
            RadixSortPositive(positives, B);
        if (!negatives.empty())
            RadixSortPositive(negatives, B); // but it should be descending, so we need to concatenate it inversed
        v.clear();

        for (long long i = negatives.size() - 1; i >= 0; i--)
            v.push_back(-negatives[i]);

        for (auto w : positives)
            v.push_back(w);
    }
    static void QuickSort(std::vector<T> &a, long long st, long long dr)
    {
        if (st >= dr)
        {
            return;
        }
        long long piv[3];
        piv[0] = st + std::rand() % (dr - st + 1);
        piv[1] = st + std::rand() % (dr - st + 1);
        piv[2] = st + std::rand() % (dr - st + 1);
        int i = 0;
        if ((a[piv[0]] <= a[piv[1]] && a[piv[1]] <= a[piv[2]]) || (a[piv[0]] >= a[piv[1]] && a[piv[1]] >= a[piv[2]]))
        {
            i = 1;
        }
        if ((a[piv[0]] <= a[piv[2]] && a[piv[2]] <= a[piv[1]]) || (a[piv[0]] >= a[piv[2]] && a[piv[2]] >= a[piv[1]]))
        {
            i = 2;
        }
        std::swap(a[dr], a[piv[i]]);
        // std::cout<<piv[1]<<piv[2]<<piv[0]<<std::endl;

        long long pivot = a[dr];
        long long k = st;
        long long less = st;
        long long more = dr;
        while (k <= more)
        {
            if (a[k] < pivot)
            {
                std::swap(a[less], a[k]);
                k++;
                less++;
            }
            else if (a[k] > pivot)
            {
                std::swap(a[k], a[more]);
                more--;
            }
            else
                k++;
            ;
        }
        QuickSort(a, st, less - 1);
        QuickSort(a, more + 1, dr);
    }

    static void ShellSort(std::vector<T> &v)
    {
        long long N = v.size();
        long long K = 1;
        while (K < N)
            K = K * 3 + 1;

        for (long long gap = K; gap > 0; gap = (gap - 1) / 3)
        {
            for (long long i = gap; i < N; i++)
            {
                long long j;
                T aux = v[i];

                for (j = i; j >= gap && v[j - gap] > aux; j -= gap)
                    v[j] = v[j - gap];

                v[j] = aux;
            }
        }
    }

    static void HeapSort(std::vector<T> &a, T n)
    {
        auto heapy = [&](int n, int i, auto &&heapy_ref) -> void
        {
            long long big = i;
            long long lson = 2 * i + 1;
            long long rson = 2 * i + 2;
            if (lson < n && a[lson] > a[big])
            {
                big = lson;
            }
            if (rson < n && a[rson] > a[big])
            {
                big = rson;
            }
            if (big != i)
            {
                std::swap(a[i], a[big]);
                heapy_ref(n, big, heapy_ref);
            }
        };

        for (long long i = n / 2 - 1; i >= 0; i--)
        {
            heapy(n, i, heapy);
        }

        for (long long i = n - 1; i >= 1; i--)
        {
            std::swap(a[0], a[i]);
            heapy(i, 0, heapy);
        }
    }

    static void BucketSort(std::vector<long long> &a, long long nr = 10000)
    {

        __int128 mi = *std::min_element(a.begin(), a.end());
        __int128 ma = *std::max_element(a.begin(), a.end());

        __int128 size = (ma - mi) / nr;
        if (size == 0)
            size = 1;

        std::vector<std::vector<long long>> bucket(nr);
        for (size_t i = 0; i < a.size(); i++)
        {
            long long poz = std::min(static_cast<long long>((a[i] - (mi)) / size), nr - 1);
            bucket[poz].push_back(a[i]);
        }

        for (long long i = 0; i < nr; i++)
        {
            std::sort(bucket[i].begin(), bucket[i].end());
        }

        long long k = 0;
        for (long long i = 0; i < nr; i++)
        {
            for (size_t j = 0; j < bucket[i].size(); j++)
            {
                a[k++] = bucket[i][j];
            }
        }
    }

public:
    Tester() = default;

    explicit Tester(vector<T> v_clone)
    {
        v = v_clone;
    }
    void Push_back(T val)
    {
        v.push_back(val);
    }
    bool isSorted()
    {
        for (int i = 1; i < v.size(); i++)
            if (v[i] < v[i - 1])
                return false;
        return true;
    }
    void Sort(const SortingMethods m)
    {
        switch (m)
        {
        case STL:
            std::sort(v.begin(), v.end());
            break;
        case RADIX10:
            RadixSort(v);
            break;
        case RADIX2TO16:
            RadixSort(v, 1LL << 16); // explicit: RadixSort(v, 1 << 16 * 1LL);
            break;
        case MERGE:
        {
            vector<T> aux(v.size());
            mergesort(v, aux, 0, v.size() - 1);
            break;
        }
        case SHELL:
            ShellSort(v);
            break;
        case QUICK:
            QuickSort(v, 0, v.size() - 1);
            break;
        case HEAP:
            HeapSort(v, v.size());
            break;
        case BUCKET:
            BucketSort(v);
            break;
        default:
            cout << "Sort function was not called and the vector"; // was/wasn't sorted correctly
            break;
        }
    }
};

void Testcase(Tester<long long> t, const int i)
{
    SortingMethods m = static_cast<SortingMethods>(i);
    t.Sort(m);
    if (!t.isSorted())
        cout << toString(m) << " was NOT sorted correctly!\n";
}

int main(int argc, char *argv[])
{
    nos();
    std::string filename;
    try
    {
        if (argc > 1)
            filename = argv[1];
        else
            throw std::out_of_range("naspa");
    }
    catch (std::out_of_range)
    {
        std::cerr << "No argument found!\n";
        return 0;
    }
    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Error opening file for reading!\n";
        return 1;
    }
    long long num;
    Tester<long long> t;
    while (file.read(reinterpret_cast<char *>(&num), sizeof(long long)))
        t.Push_back(num);
    
    std::vector<std::thread> threads;
    for (int i = 0; i < COUNT; i++)
    {
        threads.emplace_back([t, i]()
                             {
            auto start = std::chrono::steady_clock::now();
            Testcase(t, i);
            auto end = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::cout << "Thread " << toString(static_cast<SortingMethods>(i)) << " took " << elapsed.count() << " ms\n"; });
    }
    for (auto &thread : threads)
    {
        if (thread.joinable())
            thread.join();
    }

    file.close();
    return 0;
}
