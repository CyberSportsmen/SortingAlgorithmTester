#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string_view>
#include <array>

using namespace std;

enum SortingMethods
{
    STL,
    RADIX10,
    RADIX2TO16,
    MERGE,
    SHELL,
    QUICK,
    COUNT // important
};

std::string_view toString(SortingMethods method)
{
    static const std::array<std::string_view, SortingMethods::COUNT> names = {
        "STL", "RADIX10", "RADIX2TO16", "MERGE", "SHELL", "QUICK"};

    if (static_cast<size_t>(method) < names.size())
        return names[method];
    else
        return "UNKNOWN";
}

template <class T>
class Tester
{
    vector<T> v;

    void mergesort(std::vector<T> &a, std::vector<T> &c, T st, T dr)
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
    void RadixSort(std::vector<T> &v, long long B = 10)
    {
        long long Max = v[0], count[B];
        long long N = v.size();

        for (long long i = 1; i < N; i++)
            if (v[i] > Max)
                Max = v[i];

        for (long long exp = 1; Max / exp > 0; exp *= B)
        {
            std::vector<T> aux(N);
            std::fill(count, count + B, 0);

            for (long long i = 0; i < N; i++)
                count[(v[i] / exp) % B]++;
            for (long long i = 1; i < B; i++)
                count[i] += count[i - 1];

            for (long long i = N - 1; i >= 0; i--)
            {
                long long c = (v[i] / exp) % B;
                count[c]--;
                aux[count[c]] = v[i];
            }

            v.swap(aux);
        }
    }
    void QuickSort(std::vector<T> &a, long long st, long long dr)
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

    void ShellSort(std::vector<T> &v)
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
        {
            std::sort(v.begin(), v.end());
            break;
        }
        case RADIX10:
        {
            RadixSort(v);
            break;
        }
        case RADIX2TO16:
        {
            RadixSort(v, 1 << 16 * 1LL);
            break;
        }
        case MERGE:
        {
            vector<T> aux(v.size());
            mergesort(v, aux, 0, v.size() - 1); // TODO: ask about calling scheme
            break;
        }
        case SHELL:
        {
            ShellSort(v);
            break;
        }
        case QUICK:
        {
            QuickSort(v, 0, v.size() - 1); // same TODO here
            break;
        }
        }
    }
};

void Testcase(Tester<long long> t, const SortingMethods m)
{
    t.Sort(m);
    if (t.isSorted())
        cout << toString(m) << " was sorted successfully!\n";
    else
        cout << toString(m) << " was NOT sorted correctly!\n";
}

int main(int argc, char *argv[])
{
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
    for (int i = 0; i < 6; i++)
    {
        SortingMethods method = static_cast<SortingMethods>(i);
        cout << "penis" << '\n';
        Testcase(t, method);
    }

    file.close();
    return 0;
}
