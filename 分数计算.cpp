struct Fraction{
    int up,down;
};
int gcb(int a,int b)
{
    if(b==0)
        return a;
    else
        return gcb(b,a%b);
}
Fraction reduction(Fraction &result)
{
    if(result.down < 0)
    {
        result.down = -result.down;
        result.up = - result.up;
    }
    else if(result.up == 0)
        result.down = 1;
    else
    {
        int x = gcb(abs(result.up),abs(result.down));
        result.up /= x;
        result.down /= x;
    }
    return result;
}
Fraction Add(Fraction a,Fraction b)
{
    Fraction c;
    c.up = a.up * b.down + a.down * b.up;
    c.down = a.down * b.down;
    return reduction(c);
}
Fraction minu(Fraction a,Fraction b)
{
    Fraction c;
    c.up = a.up * b.down - a.down * b.up;
    c.down = a.down * b.down;
    return reduction(c);
}
Fraction multi(Fraction a,Fraction b)
{
    Fraction c;
    c.up = a.up * b.up;
    c.down = a.down * b.down;
    return reduction(c);
}
Fraction divide(Fraction a,Fraction b)
{
    Fraction c;
    c.up = a.up * b.down;
    c.down = a.down * b.up;
    return reduction(c);
}
string to_string(Fraction x) {
   return to_string(to_string(x.up) +  "/" + to_string(x.down) );
}
bool cmp(Fraction a, Fraction b) {
    return a.up * b.down > b.up * a.down;  //>
}
Fraction to(int x) = {
    return (Fraction){x, 1};
}