const int M = 1e6 + 5;
const double Pi = acos(-1.0);
struct ComPlex
{
    double x, y;
    ComPlex(double a = 0, double b = 0)
    {
        x = a, y = b;
        return;
    }
} a[M << 2], b[M << 2];
ComPlex operator+(ComPlex a, ComPlex b)
{
    return ComPlex(a.x + b.x, a.y + b.y);
}
ComPlex operator-(ComPlex a, ComPlex b)
{
    return ComPlex(a.x - b.x, a.y - b.y);
}
ComPlex operator*(ComPlex a, ComPlex b)
{
    return ComPlex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}
int n, m;
int l, r[M << 2];
int Limit = 1;
void FFT(ComPlex *A, int flag)
{
    for (int i = 0; i < Limit; i++)
        if (i < r[i])
            swap(A[i], A[r[i]]);
    for (int j = 1; j < Limit; j <<= 1)
    {
        ComPlex Wn(cos(Pi / j), flag * sin(Pi / j));
        for (int k = 0; k < Limit; k += (j << 1))
        {
            ComPlex W(1, 0);
            for (int q = 0; q < j; q++, W = W * Wn)
            {
                ComPlex x = A[k + q], y = W * A[j + k + q];
                A[k + q] = x + y;
                A[j + k + q] = x - y;
            }
        }
    }
}
inline void init_fft()
{
    int t = max(n, m);
    while (Limit <= t << 1)
        Limit <<= 1, l++;
    for (int i = 0; i < Limit; i++)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
}
inline void mul(double *a, double *b, double *result)
{
    static bool inited = false;
    if (!inited)
        init_fft(), inited = true;
    //debug(Limit);
    for (int i = 0; i < Limit; i++)
        ::a[i].x = a[i], ::b[i].x = b[i], ::a[i].y = ::b[i].y = 0;
    FFT(::a, 1);
    FFT(::b, 1);
    for (int i = 0; i < Limit; i++)
        ::a[i] = ::a[i] * ::b[i];
    FFT(::a, -1);
    for (int i = 0; i < Limit; i++)
        result[i] = ::a[i].x / Limit;
}
double q[M << 2],  g[M << 2], A[M << 2];